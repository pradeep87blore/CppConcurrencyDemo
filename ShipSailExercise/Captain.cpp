
#include <iostream>
#include <thread>

using namespace std;

void Clean()
{
	int cleanCounter = 10;

	while (cleanCounter--)
	{
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << "[" << this_thread::get_id() << "] : Cleaning" << endl;
	}

	cout << "[" << this_thread::get_id() << "] : Done with Cleaning" << endl;
}

void FullSpeedAhead()
{
	int speedCounter = 3;

	while (speedCounter--)
	{
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << "[" << this_thread::get_id() << "] : Speeding up" << endl;
	}

	cout << "[" << this_thread::get_id() << "] : At max speed" << endl;
}

void StopEngine()
{
	int stopCounter = 3;

	while (stopCounter--)
	{
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << "[" << this_thread::get_id() << "] : Slowing down" << endl;
	}

	cout << "[" << this_thread::get_id() << "] : Stopped" << endl;
}


int main()
{
	// Captain can give three orders: Clean, Full Speed ahead and Stop Engine
	// Captain doesnt have to wait for the Clean command to complete to continue other activities
	// Full Speed Ahead and Stop Engine are blocking calls

	int command;

	while (true)
	{
		cout << " Enter the command: " << endl;
		cout << "1: Cleaning\n2: Full Speed Ahead\n3: Stop the engine" << endl;
		cin >> command;
		switch (command)
		{
			case 1:
			{
				thread cleanerThread(Clean);
				cleanerThread.detach();
			}
			break;
			case 2:
			{
				thread speedThread(FullSpeedAhead);
				speedThread.join();
			}
			break;
			case 3:
			{
				thread stopThread(StopEngine);
				stopThread.join();
			}
			break;
			case 100:
			{
				cout << "Exitting program\n\n\n";
				break;
			}
			default:
			{
				cout << "\nInvalid input\n";
			}

		}

	}
}