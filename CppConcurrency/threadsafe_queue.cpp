#include "threadsafe_queue.h"


void threadsafe_queue::Push(int value)
{
	std::lock_guard<std::mutex> lg(_mu);
	_tsQueue.push(value); // An optimization could be that we move the value instead of copying it
	_cv.notify_one(); // Notify if the condition variable is waiting at the wait and pop function
}



bool threadsafe_queue::Empty()
{
	// Lock the mutex before checking if the queue is indeed empty. 
	// This is needed since some other thread might try to add some elements or remove some elements from the queue when this call occurs
	std::lock_guard<std::mutex> lg(_mu);
	return _tsQueue.empty();
	return false;
}


void threadsafe_queue::WaitAndPop(int& value)
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


