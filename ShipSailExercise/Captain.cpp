
#include <iostream>
#include <thread>
#include <queue>
using namespace std;

queue<int> speedQueue, cleanQueue;

void FullSpeedAhead()
{

	while (true)
	{
		if (speedQueue.empty())
		{
			cout << "[" << this_thread::get_id() << "] [ Speed Queue ] : Nothing to do, sleeping" << endl;
			this_thread::sleep_for(chrono::milliseconds(2000));
		}
		else
		{
			cout << "[" << this_thread::get_id() << "] [ Speed Queue ] : Speeding up" << endl;
			speedQueue.pop();
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
	}
}

void Clean()
{

	while (true)
	{
		if (cleanQueue.empty())
		{
			cout << "[" << this_thread::get_id() << "] [ Clean Queue ] : Nothing to do, sleeping" << endl;
			this_thread::sleep_for(chrono::milliseconds(2000));
		}
		else
		{
			cout << "[" << this_thread::get_id() << "] [ Clean Queue ] : Cleaning" << endl;
			cleanQueue.pop();
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
	}
}


int main()
{
	// Captain can give three orders: Clean, Full Speed ahead and Stop Engine
	// Captain doesnt have to wait for the commands to complete to continue other activities

	int command;

	thread speedThread(FullSpeedAhead);
	thread cleanThread(Clean);

	speedThread.detach();
	cleanThread.detach();

	while (true)
	{
		cout << " Enter the command: " << endl;
		cout << "1: Cleaning\n2: Full Speed Ahead\n100: Exit program" << endl;
		cin >> command;
		switch (command)
		{
			case 1:
			{
				speedQueue.push(1);
			}
			break;
			case 2:
			{
				cleanQueue.push(1);
			}
			break;
			case 100:
			{
				cout << "Exitting program\n\n\n";
				return 0;
			}
			default:
			{
				cout << "\nInvalid input\n";
			}

		}
		this_thread::sleep_for(chrono::milliseconds(5000)); // Wait for 5 seconds before the next command
	}
}