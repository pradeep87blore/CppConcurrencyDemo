#include <iostream>
#include "threadsafe_queue.h"

using namespace std;


int main()
{
	vector<thread> workers;
	threadsafe_queue<int> tsQ;

	for (size_t index = 0; index < thread::hardware_concurrency(); index++)
	{
		workers.push_back(thread([&]()
			{
				while (true) // Run this in an infinite loop
				{
					int value;
					tsQ.WaitAndPop(value); // Wait on the condition variable
					cout << "Thread " << this_thread::get_id() << " is printing the value : " << value << endl;
				}
			}));
	}

	for (thread &thrd : workers)
	{
		cout << "Thread id " << thrd.get_id() << " created" << endl;
		thrd.detach();
	}


	while (true)
	{
		cout << "Enter a number : \n";
		int num;
		cin >> num;
		tsQ.Push(num);

		this_thread::sleep_for(chrono::milliseconds(100));
	}

	return 0;
}