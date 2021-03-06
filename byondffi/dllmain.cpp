#include "pch.h"
#include "sigscan.h"

#include <thread>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <mutex>

union heck
{
	int i;
	float f;
};

struct Value
{
	char type;
	float value;
};

typedef const char* (byond_ffi_func)(int, const char**);

typedef void(SetVariable)(int datumType, int datumId, unsigned int varNameId, int vtype, heck newvalue);
typedef Value(GetVariable)(int datumType, int datumId, unsigned int varNameId);
typedef unsigned int(GetStringTableIndex)(const char* string, int handleEscapes, int duplicateString);

struct ExecutionContext
{
	char irrelevant[154];
};

struct SuspendedProc
{
	char unknown[0x88];
	short time_to_resume;
};

typedef SuspendedProc*(*ResumeIn)(ExecutionContext* ctx, float deciseconds);

SetVariable* setVariable;
GetVariable* getVariable;
GetStringTableIndex* getStringTableIndex;

int result_string_id = 0;
int completed_string_id = 0;
int internal_id_string_id = 0;

bool initialized = false;

std::mutex map_lock;

std::map<std::string, std::map<std::string, byond_ffi_func*>> library_cache;

std::map<float, SuspendedProc*> suspended_procs;

const char* find_function_pointers()
{
	getVariable = (GetVariable*)Pocket::Sigscan::FindPattern("byondcore.dll", "55 8B EC 8B 4D 08 0F B6 C1 48 83 F8 53 0F 87 F1 00 00 00 0F B6 80 ?? ?? ?? ?? FF 24 85 ?? ?? ?? ?? FF 75 10 FF 75 0C E8 ?? ?? ?? ?? 83 C4 08 5D C3");
	if (!getVariable)
	{
		return "ERROR: Failed to locate getVariable.";
	}
	setVariable = (SetVariable*)Pocket::Sigscan::FindPattern("byondcore.dll", "55 8B EC 8B 4D 08 0F B6 C1 48 57 8B 7D 10 83 F8 53 0F ?? ?? ?? ?? ?? 0F B6 80 ?? ?? ?? ?? FF 24 85 ?? ?? ?? ?? FF 75 18 FF 75 14 57 FF 75 0C E8 ?? ?? ?? ?? 83 C4 10 5F 5D C3");
	if (!setVariable)
	{
		return "ERROR: Failed to locate setVariable.";
	}
	getStringTableIndex = (GetStringTableIndex*)Pocket::Sigscan::FindPattern("byondcore.dll", "55 8B EC 8B 45 08 83 EC 18 53 8B 1D ?? ?? ?? ?? 56 57 85 C0 75 ?? 68 ?? ?? ?? ?? FF D3 83 C4 04 C6 45 10 00 80 7D 0C 00 89 45 E8 74 ?? 8D 45 10 50 8D 45 E8 50");
	if (!getStringTableIndex)
	{
		return "ERROR: Failed to locate getStringTableIndex.";
	}
	result_string_id = getStringTableIndex("result", 0, 0);
	completed_string_id = getStringTableIndex("completed", 0, 0);
	internal_id_string_id = getStringTableIndex("__id", 0, 0);
	initialized = true;
	return "";
}

extern "C" __declspec(dllexport) void register_suspension(float promise_internal_id, SuspendedProc* suspended_proc)
{
	//map_lock.lock();
	suspended_procs[promise_internal_id] = suspended_proc;
	//map_lock.unlock();
}

void ffi_thread(byond_ffi_func* proc, int promise_id, int n_args, std::vector<std::string> args)
{
	std::vector<const char*> a;
	for (int i = 0; i < n_args; i++)
	{
		a.push_back(args[i].c_str());
	}
	const char* res = proc(n_args, a.data());
	//map_lock.lock(); //just realized locking here prevents adding new stuff to the map, how does this even work?
	heck h;
	h.i = getStringTableIndex(res, 0, 1);
	setVariable(0x21, promise_id, result_string_id, 0x06, h);
	h.f = 1;
	setVariable(0x21, promise_id, completed_string_id, 0x2A, h);
	float internal_id = getVariable(0x21, promise_id, internal_id_string_id).value;
	while (true)
	{
		if (suspended_procs.find(internal_id) != suspended_procs.end())
		{
			break;
		}
		Sleep(1);
		//TODO: some kind of conditional variable or WaitForObject?
	}
	suspended_procs[internal_id]->time_to_resume = 1;
	suspended_procs.erase(internal_id);
	//map_lock.unlock();
}

inline void do_it(byond_ffi_func* proc, std::string promise_datum_ref, int n_args, const char** args)
{
	promise_datum_ref.erase(promise_datum_ref.begin(), promise_datum_ref.begin() + 3);
	int promise_id = std::stoi(promise_datum_ref.substr(promise_datum_ref.find("0"), promise_datum_ref.length() - 2), nullptr, 16);
	std::vector<std::string> a;
	for (int i = 3; i < n_args; i++)
	{
		a.push_back(args[i]);
	}
	std::thread t(ffi_thread, proc, promise_id, n_args - 3, a);
	t.detach();
}

extern "C" __declspec(dllexport) const char* call_async(int n_args, const char** args)
{
	if (!initialized)
	{
		return "ERROR: Attempt to call DLL before initializing!";
	}
	const char* dllname = args[1];
	const char* funcname = args[2];
	if (library_cache.find(dllname) != library_cache.end())
	{
		if (library_cache[dllname].find(funcname) != library_cache[dllname].end())
		{
			do_it(library_cache[dllname][funcname], args[0], n_args, args);
			return ""; //this return right here (or the lack thereof) caused hours of debugging
		}
	}

	HMODULE lib = LoadLibraryA(dllname);
	if (!lib)
	{
		return "ERROR: Could not find library!";
	}
	byond_ffi_func* proc = (byond_ffi_func*)GetProcAddress(lib, funcname);
	if (!proc)
	{
		return "ERROR: Could not locate function in library!";
	}

	library_cache[dllname][funcname] = proc;
	do_it(proc, args[0], n_args, args);
	return "";
}

char result[256];

extern "C" __declspec(dllexport) const char* initialize(int n_args, const char** args)
{
	strcpy_s(result, 256, find_function_pointers());
	return "";
}

extern "C" __declspec(dllexport) const char* cleanup(int n_args, const char** args)
{
	library_cache.clear();
	return "";
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

