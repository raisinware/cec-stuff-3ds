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
	CID_RUNCOMMAND = 0x000B,
	CID_RUNCOMMANDALT = 0x000C,
	CID_GETCECSTATEABBR = 0x000E,
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

