#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>


class threadsafe_queue
{
	std::queue<int> _tsQueue;
	std::mutex _mu;
	std::condition_variable _cv;

public:
	void Push(int value);
	bool Empty();
	void WaitAndPop(int& value);
};
