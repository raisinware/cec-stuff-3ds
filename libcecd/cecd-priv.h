#pragma once
#include <3ds/types.h>

/// cecd:u Command ID headers
enum: u16 {
	CID_OPENRAWFILE = 0x0001,
	CID_READRAWFILE = 0x0002,
	CID_READMESSAGE = 0x0003,
	CID_READMESSAGEWITHHMAC = 0x0004,
	CID_WRITERAWFILE = 0x0005,
	CID_WRITEMESSAGE = 0x0006,
	CID_WRITEMESSAGEWITHHMAC = 0x0007,
	CID_DELETE = 0x0008,
	CID_UNKNOWN1 = 0x0009,
	CID_GETSYSTEMINFO = 0x000A,
	CID_RUNCOMMAND = 0x000B,
	CID_RUNCOMMANDALT = 0x000C,
	CID_GETCECINFOBUFFER = 0x000D,
	CID_GETCECSTATEABBR = 0x000E,
	CID_GETCECINFOEVENTHANDLE = 0x000F,
	CID_GETCHANGESTATEEVENTHANDLE = 0x0010,
	CID_OPENANDWRITE = 0x0011,
	CID_OPENANDREAD = 0x0012,
	CID_GETEVENTLOG = 0x001E,
	CID_GETEVENTLOGSTART = 0x001F,
	CID_UNKNOWN2 = 0x0020,
	CID_UNKNOWN3 = 0x0021,
};
