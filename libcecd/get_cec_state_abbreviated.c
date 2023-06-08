// SPDX-License-Identifier: MPL-2.0+
#include "cecd-priv.h"
#include "cecd.h"
#include <3ds/ipc.h>

Result CECD_GetCecStateAbbreviated(CEC_StateAbbreviated* out) {
	Result res = 0;
	u32* cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(CID_GETCECSTATEABBR, 0, 0); // 0x000E0000

	res = svcSendSyncRequest(cecdGetSessionHandle());

	if (R_FAILED(res)) {
		return res;
	}

	res = (Result)cmdbuf[1];

	if (R_SUCCEEDED(res) && out) {
		*out = (CEC_StateAbbreviated)cmdbuf[2];
	}

	return res;
}
