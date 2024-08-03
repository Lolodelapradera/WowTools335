#include "Data.h"
#include "MemoryController.h"
#include "ObjectMgr.h"
#include "WoWEvent.h"

typedef void* (__cdecl* SignalEvent_orig)(int EventId, const char* fmt, va_list arg);
SignalEvent_orig OriginalSignalEvent = (SignalEvent_orig)0x0081AC90;


void* __cdecl SignalEvent(int EventId, const char* fmt, va_list arg)
{
	if (EventId == PLAYER_ENTERING_WORLD)
	{
		ObjectMgr::LocalPlayerBaseAddress = ObjectMgr::GetLocalPlayerAddress();
	}

	if (EventId == PLAYER_TARGET_CHANGED)
	{
		ObjectMgr::LocalTargetBaseAddress = ObjectMgr::GetLocalTargetAddress(0x8);
	}

	return OriginalSignalEvent(EventId, fmt, arg);
}

void SignalEventHk()
{
	MemoryController::DetourPatcher["SignalEvent"] = new DetourManager(0x0081AC90, &(PVOID&)OriginalSignalEvent, SignalEvent);
}