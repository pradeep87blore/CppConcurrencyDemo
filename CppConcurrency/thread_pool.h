#pragma once

#include <thread>
#include <vector>
#include <atomic>
#include <functional>
#include <iostream>
#include "threadsafe_queue.h"
#include <iostream>



class thread_pool
{
	/*
	The thread pool should instantiate and keep ready a set of threads
	When a new task is added to the threadpool, one of the threads should pick it and complete it
	When no tasks are available, the threadpool should remain idle
	We should have an option to stop the threads
	*/

	std::atomic_bool done; // A flag to indicate whether the threads should run or exit
	std::vector<std::thread> workers;
	threadsafe_queue < std::function<void()>> taskQueue;

	void workerTask() // This is the function that shall be run on each threads
	{
		while (!done) // Loop till the done flag is set to true
		{
			std::function<void()> task;
			taskQueue.WaitAndPop(task); // This will block till a task is available in the queue
			task(); // Run the task
		}
	}


public:
	thread_pool(size_t threadCount = std::thread::hardware_concurrency()) // If no count specified, better to use the hardware_concurrency value to avoid too many context switches
	{
		workers.reserve(threadCount);
		for (size_t index = 0; index < threadCount; index++)
		{
			// Create a new thread and initialize it with the worker task
			workers.push_back(std::thread(&thread_pool::workerTask, this));
		}

		for (std::thread& thrd : workers)
		{
			std::cout << " Thread Id : " << thrd.get_id() << " is now created \n\n";
			thrd.detach(); // Detach from the main thread
		}
	}

	void AddTask(std::function<void()> task)
	{
		taskQueue.Push(task);
	}

	void TerminateThreadPool()
	{
		done = true;

		for (size_t index = 0; index < workers.size(); index++)
		{
			AddTask([]()
				{
					std::cout << std::this_thread::get_id() << " exitting\n\n";
					// Dummy task to enable the threads to break off from the wait and pop function
				});
		}
	}
};

