
#include "stdafx.h"

#include <algorithm>

#include "instr_control_flow.h"
#include "helpers.h"
#include "context.h"
#include "disassembler.h"

//TODO: finish
void Instr_CALL::Disassemble(Context* context, Disassembler* dism)
{
	comment_ = "";
	dism->disassemble_var(*this);

	std::uint32_t procid = context->eat();
	std::string name = byond_tostring(procid);
	std::replace(name.begin(), name.end(), ' ', '_');
	comment_ += name;
	std::uint32_t num_args = context->eat();

	dism->add_call_args(*this, num_args);
}

void Instr_CALLNR::Disassemble(Context* context, Disassembler* dism)
{
	comment_ = "";
	dism->disassemble_var(*this);

	std::uint32_t procid = context->eat();
	std::string name = byond_tostring(procid);
	std::replace(name.begin(), name.end(), ' ', '_');
	comment_ += name;
	std::uint32_t num_args = context->eat();

	dism->add_call_args(*this, num_args);
}

void Instr_CALLGLOB::Disassemble(Context* context, Disassembler* dism)
{
	std::uint32_t num_args = context->eat();
	std::uint32_t proc_id = context->eat();

	comment_ += context->procs()[proc_id].name;
	dism->add_call_args(*this, num_args);
}
