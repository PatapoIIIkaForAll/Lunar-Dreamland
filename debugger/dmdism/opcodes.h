#pragma once
#include <map>
#include <unordered_map>

enum Opcode
{
	RETN = 0x00,
	NEW = 0x01,
	OUTPUT = 0x03,
	TEST = 0x0D,
	NOT = 0x0E,
	JMP = 0x0F,
	JZ = 0x11,
	RET = 0x12,
	NLIST = 0x1A,
	SLEEP = 0x24,
	SPAWN = 0x25,
	CALL = 0x29,
	CALLNR = 0x2A,
	CALLPATH = 0x2B,
	CALLPARENT = 0x2C,
	CALLGLOB = 0x30,
	GETVAR = 0x33,
	SETVAR = 0x34,
	TEQ = 0x37,
	TNE = 0x38,
	TL = 0x39,
	TG = 0x3A,
	TLE = 0x3B,
	TGE = 0x3C,
	ANEG = 0x3D,
	ADD = 0x3E,
	SUB = 0x3F,
	MUL = 0x40,
	DIV = 0x41,
	MOD = 0x42,
	ROUND = 0x43,
	ROUNDN = 0x44,
	AUGADD = 0x45,
	AUGSUB = 0x46,
	PUSHI = 0x50,
	POP = 0x51,
	ITERLOAD = 0x52,
	ITERNEXT = 0x53,
	LOCATE = 0x5B,
	PUSHVAL = 0x60,
	INC = 0x66,
	DEC = 0x67,
	LISTGET = 0x7B,
	ISTYPE = 0x7D,
	DBG_FILE = 0x84,
	DBG_LINENO = 0x85,
	CALLNAME = 0xB5,
	PROMPTCHECK = 0xBA,
	INPUT_ = 0xC1, //INPUT without underscore was already defined in some windows header
	JMP2 = 0xF8,
	JNZ = 0xFA,
	POPN = 0xFB,
	CHECKNUM = 0xFC,
	MD5 = 0x109,
	CALL_LIB = 0x116,
	DBG_BREAK = 0x1337,
};

enum AccessModifier
{
	SRC = 0xFFCE,
	DOT = 0xFFD0,
	ARG = 0xFFD9,
	LOCAL = 0xFFDA,
	GLOBAL = 0xFFDB,
	SUBVAR = 0xFFDC,
	CACHE = 0xFFDD,
	WORLD = 0xFFE5,
	NULL_ = 0xFFE6,
};

const std::unordered_map<AccessModifier, std::string> modifier_names = {
	{SRC, "SRC"},
	{DOT, "DOT" },
	{ARG, "ARG" },
	{LOCAL, "LOCAL"},
	{GLOBAL, "GLOBAL" },
	{SUBVAR, "SUBVAR"},
	{CACHE, "CACHE"},
	{WORLD, "WORLD"},
	{NULL_, "NULL"},
};

enum DataType
{
	NULL_D = 0x00,
	TURF = 0x01,
	OBJ = 0x02,
	MOB = 0x03,
	AREA = 0x04,
	CLIENT = 0x05,
	STRING = 0x06,
	MOBTYPE = 0x08,
	OBJTYPE = 0x09,
	IMAGE = 0x0D,
	WORLD_D = 0x0E,
	DATUM = 0x21,
	SAVEFILE = 0x23,
	NUMBER = 0x2A,
};

const std::unordered_map<DataType, std::string> datatype_names = {
	{ NULL_D, "NULL" },
	{ TURF, "TURF" },
	{ OBJ, "OBJ" },
	{ MOB, "MOB" },
	{ AREA, "AREA" },
	{ CLIENT, "CLIENT" },
	{ STRING, "STRING" },
	{ MOBTYPE, "MOBTYPE" },
	{ OBJTYPE, "OBJTYPE" },
	{ IMAGE, "IMAGE" },
	{ WORLD_D, "WORLD" },
	{ DATUM, "DATUM" },
	{ SAVEFILE, "SAVEFILE" },
	{ NUMBER, "NUMBER" },
};

const std::unordered_map<Opcode, std::string> mnemonics = {
	{RETN, "RETN"},
	{NEW, "NEW"},
	{OUTPUT, "OUTPUT"},
	{TEST, "TEST"},
	{NOT, "NOT"},
	{JMP, "JMP"},
	{JZ, "JZ"},
	{RET, "RET"},
	{NLIST, "NLIST"},
	{SLEEP, "SLEEP"},
	{SPAWN, "SPAWN"},
	{CALL, "CALL"},
	{CALLNR, "CALLNR"},
	{CALLPATH, "CALLPATH"},
	{CALLPARENT, "CALLPARENT"},
	{CALLGLOB, "CALLGLOB"},
	{GETVAR, "GETVAR"},
	{SETVAR, "SETVAR"},
	{TEQ, "TEQ"},
	{TNE, "TNE"},
	{TL, "TL"},
	{TG, "TG"},
	{TLE, "TLE"},
	{TGE, "TGE"},
	{ANEG, "ANEG"},
	{ADD, "ADD"},
	{SUB, "SUB"},
	{MUL, "MUL"},
	{DIV, "DIV"},
	{MOD, "MOD"},
	{ROUND, "ROUND"},
	{ROUNDN, "ROUNDN"},
	{AUGADD, "AUGADD"},
	{AUGSUB, "AUGSUB"},
	{PUSHI, "PUSHI"},
	{POP, "POP"},
	{ITERLOAD, "ITERLOAD"},
	{ITERNEXT, "ITERNEXT"},
	{LOCATE, "LOCATE"},
	{PUSHVAL, "PUSHVAL"},
	{INC, "INC"},
	{DEC, "DEC"},
	{LISTGET, "LISTGET"},
	{ISTYPE, "ISTYPE"},
	{DBG_FILE, "DBG FILE"},
	{DBG_LINENO, "DBG LINENO"},
	{CALLNAME, "CALLNAME"},
	{PROMPTCHECK, "PROMPTCHECK"},
	{INPUT_, "INPUT"},
	{JMP2, "JMP"},
	{JNZ, "JNZ"},
	{POPN, "POPN"},
	{CHECKNUM, "CHECKNUM"},
	{MD5, "MD5"},
	{CALL_LIB, "CALL LIB"},
	{DBG_BREAK, "DBG BREAK"},
};