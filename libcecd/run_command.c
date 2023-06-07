// SPDX-License-Identifier: MPL-2.0+
#include "cecd-priv.h"
#include "cecd.h"
#include <3ds/ipc.h>

Result CECD_RunCommand(CEC_Command command) {
	Result res = 0;
	u32* cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(CID_RUNCOMMAND, 1, 0); // 0x000B0040
	cmdbuf[1] = command;

	res = svcSendSyncRequest(cecdGetSessionHandle());

	if (R_FAILED(res)) {
		return res;
	}

	return (Result)cmdbuf[1];
}

Result CECD_RunCommandAlt(CEC_Command command) {
	Result res = 0;
	u32* cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(CID_RUNCOMMANDALT, 1, 0); // 0x000C0040
	cmdbuf[1] = command;

	res = svcSendSyncRequest(cecdGetSessionHandle());

	if (R_FAILED(res)) {
		return res;
	}

	return (Result)cmdbuf[1];
}
