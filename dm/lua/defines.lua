local ffi = require("ffi")
require "cdef"
local M = {}
M.Null = 0x00
M.Turf = 0x01
M.Obj = 0x02
M.Mob = 0x03
M.Area = 0x04
M.Client = 0x05
M.MobType = 0x08
M.ObjType = 0x09
M.Type = 0x0A
M.Image = 0x0D
M.World = 0x0E
M.Global = 0x0E
M.DatumType = 0x20
M.Datum = 0x21
M.Savefile = 0x23
M.Path = 0x26
M.ClientType = 0x3B
M.Null = 0x00
M.Turf = 0x01
M.Obj = 0x02
M.Mob = 0x03
M.Area = 0x04
M.String = 0x06
M.World = 0x0E
M.List = 0x0F
M.Datum = 0x21
M.Path = 0x26
M.Number = 0x2A
M.ConstList = 0x53 --Might be a read-only or a fixed size list (cannot append)
--On a second look this seems to be some kind of invalid type, perhaps for debugging purposes

M.types = {
	[0x00] = "Null",
	[0x01] = "Turf",
	[0x02] = "Obj",
	[0x03] = "Mob",
	[0x04] = "Area",
	[0x05] = "Client",
	[0x08] = "MobType",
	[0x09] = "ObjType",
	[0x0A] = "Type",
	[0x0D] = "Image",
	[0x0E] = "World",
	[0x0E] = "Global",
	[0x20] = "DatumType",
	[0x21] = "Datum",
	[0x23] = "Savefile",
	[0x26] = "Path",
	[0x06] = "String",
	[0x0E] = "World",
	[0x0F] = "List",
	[0x21] = "Datum",
	[0x26] = "Path",
	[0x2A] = "Number",
	[0x3B] = "ClientType",
	[0x53] = "ConstList",
	["Null"] = 0x00,
	["Turf"] = 0x01,
	["Obj"] = 0x02,
	["Mob"] = 0x03,
	["Area"] = 0x04,
	["Client"] = 0x05,
	["MobType"] = 0x08,
	["ObjType"] = 0x09,
	["Type"] = 0x0A,
	["Image"] = 0x0D,
	["World"] = 0x0E,
	["Global"] = 0x0E,
	["DatumType"] = 0x20,
	["Datum"] = 0x21,
	["Savefile"] = 0x23,
	["Path"] = 0x26,
	["String"] = 0x06,
	["World"] = 0x0E,
	["List"] = 0x0F,
	["Datum"] = 0x21,
	["Path"] = 0x26,
	["Number"] = 0x2A,
	["ClientType"] = 0x3B,
	["ConstList"] = 0x53
}

M.null = ffi.new("Value", {type = M.Null, value = 0})

return M