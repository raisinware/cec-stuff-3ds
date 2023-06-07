// SPDX-License-Identifier: MPL-2.0+
#include "cecd.h"
#include <3ds/ipc.h>
#include <3ds/result.h>
#include <3ds/srv.h>
#include <3ds/svc.h>
#include <3ds/synchronization.h>
#include <3ds/types.h>

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
	u32* ipcbuf = getThreadCommandBuffer();

	ipcbuf[0] = IPC_MakeHeader(0x000B, 1, 0); // 0x000B0040
	ipcbuf[1] = command;

	res = svcSendSyncRequest(cecdHandle);

	if (R_FAILED(res)) {
		return res;
	}

	return (Result)ipcbuf[1];
}

Result CECD_RunCommandAlt(CEC_Command command) {
	Result ret = -1;
	u32* ipcbuf = getThreadCommandBuffer();

	ipcbuf[0] = IPC_MakeHeader(0x000C, 1, 0); // 0x000C0040
	ipcbuf[1] = command;

	ret = svcSendSyncRequest(cecdHandle);

	if (R_FAILED(ret)) {
		return ret;
	}

	return (Result)ipcbuf[1];
}

