// SPDX-License-Identifier: MPL-2.0+
#include "cecd.h"
#include <3ds/ipc.h>
#include <3ds/result.h>
#include <3ds/srv.h>
#include <3ds/svc.h>
#include <3ds/synchronization.h>
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

static Handle cecdHandle;
static int cecdRefCount;

Result cecdInit(void) {
	Result res = -1;

	if (AtomicPostIncrement(&cecdRefCount)) {
		return 0;
	}

	res = srvGetServiceHandle(&cecdHandle, "cecd:u");

	if (R_FAILED(res)) {
		AtomicDecrement(&cecdRefCount);
	}

	return res;
}

void cecdExit(void) {
	if (AtomicDecrement(&cecdRefCount)) {
		return;
	}

	svcCloseHandle(cecdHandle);
}

Handle cecdGetSessionHandle(void) {
	return cecdHandle;
}

Result CECD_RunCommand(CEC_Command command) {
	Result res = -1;
	u32* cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(CID_RUNCOMMAND, 1, 0); // 0x000B0040
	cmdbuf[1] = command;

	res = svcSendSyncRequest(cecdHandle);

	if (R_FAILED(res)) {
		return res;
	}

	return (Result)cmdbuf[1];
}

Result CECD_RunCommandAlt(CEC_Command command) {
	Result ret = -1;
	u32* cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(CID_RUNCOMMANDALT, 1, 0); // 0x000C0040
	cmdbuf[1] = command;

	ret = svcSendSyncRequest(cecdHandle);

	if (R_FAILED(ret)) {
		return ret;
	}

	return (Result)cmdbuf[1];
}

