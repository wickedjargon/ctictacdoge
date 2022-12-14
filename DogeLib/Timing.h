#pragma once
#define TPS		1000
#define FPS		15
#define TPF		(TPS/FPS)

static inline
uint getTicks(void)
{
	return SDL_GetTicks();
}

static inline
uint secondsToTicks(const uint sec)
{
	return TPS*sec;
}

static inline
uint getTimeIn(const uint sec)
{
	return TPS*sec+getTicks();
}
