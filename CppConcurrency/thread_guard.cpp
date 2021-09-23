#include "thread_guard.h"

thread_guard::thread_guard(std::thread& threadObj) : _thread (threadObj)
{
	
}

thread_guard::~thread_guard()
{
	if (_thread.joinable())
	{
		_thread.join();
	}
}
