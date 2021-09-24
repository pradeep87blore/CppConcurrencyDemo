
#include <iostream>
#include <thread>
#include <mutex>
#include <list>

// Refer to https://www.cplusplus.com/reference/condition_variable/condition_variable/ for details


using namespace std;

int currentNumber = 0, targetNumber = 10;

mutex m;
condition_variable cv;

void IncrementNumber()
{
	while (true)
	{
		this_thread::sleep_for(1s);
		currentNumber++;

		cout << " Current number : " << currentNumber << endl;

		if (currentNumber == targetNumber)
		{
			cv.notify_one();

			/*
			https://www.cplusplus.com/reference/condition_variable/condition_variable/notify_one/
			Notify one
			Unblocks one of the threads currently waiting for this condition.

			If no threads are waiting, the function does nothing.

			If more than one, it is unspecified which of the threads is selected.

			*/
		}
	}
}

void IsTargetReached()
{
	unique_lock<mutex> ul(m);
	cv.wait(ul, [] { return currentNumber == targetNumber; });

	cout << "\n\n Target number reached " << endl;

	/*

	https://www.cplusplus.com/reference/condition_variable/condition_variable/wait/

	Wait until notified
	The execution of the current thread (which shall have locked lck's mutex) is blocked until notified.

	At the moment of blocking the thread, the function automatically calls lck.unlock(), allowing other locked threads to continue.

	Once notified (explicitly, by some other thread), the function unblocks and calls lck.lock(), leaving lck in the same state as when the function was called. 
	Then the function returns (notice that this last mutex locking may block again the thread before returning).

	Generally, the function is notified to wake up by a call in another thread either to member notify_one or to member notify_all. 
	But certain implementations may produce spurious wake-up calls without any of these functions being called. Therefore, users of this function shall ensure their condition for resumption is met.

	If pred is specified (2), the function only blocks if pred returns false, and notifications can only unblock the thread when it becomes true 
	(which is specially useful to check against spurious wake-up calls). This version (2) behaves as if implemented as:
	
	while (!pred()) wait(lck);


	*/
}


int main()
{
	thread incrementer(IncrementNumber);
	thread targetChecker(IsTargetReached);

	incrementer.join();
	targetChecker.join();

}