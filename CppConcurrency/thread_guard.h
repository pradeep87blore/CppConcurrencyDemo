#pragma once
#include<thread>
class thread_guard
{
	std::thread &_thread;
public:
	explicit thread_guard(std::thread& threadObj);
	~thread_guard();

	thread_guard(const thread_guard& t) = delete;
	thread_guard& operator = (const thread_guard& t) = delete;

};

