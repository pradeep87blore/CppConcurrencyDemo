#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <typename  T>
class threadsafe_queue
{
	std::queue<T> _tsQueue;
	std::mutex _mu;
	std::condition_variable _cv;

public:
	void Push(T value);
	bool Empty();
	void WaitAndPop(T& value);
};

template <typename  T>
void threadsafe_queue<T>::Push(T value)
{
	std::lock_guard<std::mutex> lg(_mu);
	_tsQueue.push(value); // An optimization could be that we move the value instead of copying it
	_cv.notify_one(); // Notify if the condition variable is waiting at the wait and pop function
}


template <typename  T>
bool threadsafe_queue<T>::Empty()
{
	// Lock the mutex before checking if the queue is indeed empty. 
	// This is needed since some other thread might try to add some elements or remove some elements from the queue when this call occurs
	std::lock_guard<std::mutex> lg(_mu);
	return _tsQueue.empty();
	return false;
}

template <typename  T>
void threadsafe_queue<T>::WaitAndPop(T& value)
{
	/*
	Instead of having a simple pop that shall pop the top element and return it (if available) or throw an exception if the queue is empty,
	we can have this wait and pop function that will block the caller till some element is pushed into the queue (if it is currently empty)
	This way, the caller doesn't have to continously keep polling to see if the queue contains any elements
	*/
	std::unique_lock<std::mutex> ul(_mu);
	_cv.wait(ul, [this]()
		{
			return !_tsQueue.empty(); // To prevent the cv being notified by spurious calls, we will check to be sure that the queue indeed has some element
		});
	value = _tsQueue.front(); // set the value in the reference
	_tsQueue.pop(); // Remove the element
}