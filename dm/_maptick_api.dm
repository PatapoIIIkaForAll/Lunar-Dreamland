#define MAPTICK_LAST_INTERNAL_TICK_USAGE ((maptick.last_internal_tick_usage / world.tick_lag) * 100)

var/datum/maptick_helper/maptick = new

/datum/maptick_helper
	var/last_internal_tick_usage = 0

/datum/maptick_helper/New()
	last_internal_tick_usage = 0.2 * world.tick_lag // default value of 20%

/proc/maptick_initialize()
	if(!maptick)
		world << "MAPTICK DATUM NOT FOUND"
		world.log << "MAPTICK DATUM NOT FOUND"
		return FALSE
	if(!fexists("maptick.dll"))
		world << "MAPTICK DLL NOT FOUND"
		world.log << "MAPTICK DLL NOT FOUND"
		return FALSE
	var/result = call("maptick.dll", "initialize")("\ref[maptick]")
	world << result
	world.log << result
	if(findtext(result, "MAPTICK ERROR"))
		return FALSE
	return TRUE

/proc/maptick_shutdown()
	call("maptick.dll", "cleanup")()