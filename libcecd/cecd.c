// SPDX-License-Identifier: MPL-2.0+
#include "cecd.h"
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
