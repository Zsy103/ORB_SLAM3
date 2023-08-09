#include "unistd.h"


static void //usleep(unsigned long usec)
{
	HANDLE timer;
	LARGE_INTEGER interval;
	interval.QuadPart = (10 * usec);

	timer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(timer, &interval, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}