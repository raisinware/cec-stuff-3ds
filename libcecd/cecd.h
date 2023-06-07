// SPDX-License-Identifier: MPL-2.0+
#pragma once
#include <3ds/types.h>

// clang-format off

/// Command to send to CECD
/// TODO: more detailed descriptions for each command
typedef enum {
	/// Does nothing
	CEC_COMMAND_NONE                  = 0x00,

	/// 
	CEC_COMMAND_START                 = 0x01,
	CEC_COMMAND_RESET_START           = 0x02,
	CEC_COMMAND_READYSCAN             = 0x03,
	CEC_COMMAND_READYSCANWAIT         = 0x04,
	CEC_COMMAND_STARTSCAN             = 0x05,
	CEC_COMMAND_RESCAN                = 0x06,
	CEC_COMMAND_NDM_RESUME            = 0x07,
	CEC_COMMAND_NDM_SUSPEND           = 0x08,
	CEC_COMMAND_NDM_SUSPEND_IMMEDIATE = 0x09,
	CEC_COMMAND_STOPWAIT              = 0x0A,
	CEC_COMMAND_STOP                  = 0x0B,
	CEC_COMMAND_STOP_FORCE            = 0x0C,
	CEC_COMMAND_STOP_FORCE_WAIT       = 0x0D,

	// reset MAC address filter
	CEC_COMMAND_RESET_FILTER          = 0x0E,

	///
	CEC_COMMAND_DAEMON_STOP           = 0x0F,
	CEC_COMMAND_DAEMON_START          = 0x10,
	CEC_COMMAND_EXIT                  = 0x11,

	/// streetpass relay (over BOSS) commands
	CEC_COMMAND_OVER_BOSS             = 0x12,
	CEC_COMMAND_OVER_BOSS_FORCE       = 0x13,
	CEC_COMMAND_OVER_BOSS_FORCE_WAIT  = 0x14,

	/// End command.
	CEC_COMMAND_END                   = 0x15,
} CEC_Command;

// clang-format on

/// Abbreviated state of CECD.
typedef enum {
	/// Corresponds to CEC_STATE_IDLE
	CEC_STATE_ABBREV_IDLE = 1,

	/// Corresponds to CEC_STATEs *FINISH*, *POST, and OVER_BOSS
	CEC_STATE_ABBREV_INACTIVE = 2,

	/// Corresponds to CEC_STATE_SCANNING
	CEC_STATE_ABBREV_SCANNING = 3,

	/// Corresponds to CEC_STATE_WIRELESS_READY when some unknown bool is
	/// true
	CEC_STATE_ABBREV_WLREADY = 4,

	/// Corresponds to CEC_STATEs besides *FINISH*, *POST, and OVER_BOSS and
	/// those listed here
	CEC_STATE_ABBREV_OTHER = 5,
} CEC_StateAbbreviated;

/// Initializes communication with CECD (streetpass daemon)
Result cecdInit(void);

/// Deinitializes communication with CECD
void cecdExit(void);

/// Get the current session handle for CECD
Handle cecdGetSessionHandle(void);

/// Start a command on CECD
Result CECD_RunCommand(CEC_Command command);

/// Start a command on CECD, but with some extra checks.
Result CECD_RunCommandAlt(CEC_Command command);

/// Output the abbreviated CECD state to *out*
Result CECD_GetCecStateAbbreviated(CEC_StateAbbreviated* out);
