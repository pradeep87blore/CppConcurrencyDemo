#include <iostream>
#include <mutex>
#include <thread>
#include "thread_pool.h"

using namespace std;

mutex mu;


#if 0
int main()
{
	thread_pool tp;

	/*
	Here we are adding a few dummy tasks for the thread pool to run.
	Just to see if we are able to push different tasks, we are adding different lambdas when the index is even and when it is odd
	*/
	while (true)
	{

		for (int index = 0; index < 100; index++)
		{
			if (index % 2 == 0)
			{
				tp.AddTask([=]()
					{
						lock_guard<mutex> lg(mu); // Adding this to prevent the output from different threads overlapping
						cout << " Printing the index " << index << " from thread id : " << this_thread::get_id() << endl;
					}
				);
			}
			else
			{
				tp.AddTask([=]()
					{
						lock_guard<mutex> lg(mu);
						cout << " Printing the index x 2 " << index * 2 << " from thread id : " << this_thread::get_id() << endl;
					}
				);
			}

			this_thread::sleep_for(chrono::milliseconds(10)); // Add a pause between adding tasks just to see the output appear clearly
		}

		cout << "Do you want to repeat the operation? 1 for continue, anything else to exit\n";

		char input;
		cin >> input;

		if (input != '1')
		{
			tp.TerminateThreadPool();
			cout << "\n\nBye!\n\n";
			this_thread::sleep_for(chrono::milliseconds(1000)); // Wait for the threads to exit (not an actual need but just to see the thread exit output)
			break;
		}
		else
		{
			cout << "\n\nRepeating the same 100 operations\n";
		}
	}
}
#endif