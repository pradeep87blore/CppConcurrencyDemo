
#include <iostream>
#include <thread>

#include "thread_guard.h"

using namespace std;

void PrintName(string &name)
{
	this_thread::sleep_for(100ms);
	cout << "[" << this_thread::get_id() << "] " << " Hello from a called function " << name << endl;
}

class CallableClass
{
public:
	void operator() (string &name)
	{
		this_thread::sleep_for(500ms);
		cout << "[" << this_thread::get_id() << "] " << " Hello from an invoked class " << name << endl;
	}
};

void AddNumbers(const int& num1, const int& num2)
{
	cout << " Sum of " << num1 << " and " << num2 << " is " << num1 + num2 << endl;
}

void PrintInLoop(const int& num)
{
	int printCounter = 3;
	while (printCounter--)
	{
		cout << "Printing number : " << num << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
	cout << " Exitting printing in a loop" << endl;
}

int main()
{
	string name = "Pradeep";
	thread t1(PrintName, std::ref(name));	// Invoke a thread using a direct function as the starting point

	CallableClass classObj;
	thread t2(classObj, std::ref(name));	// Invoke a thread using a callable class as the starting point

	thread t3([&] {							// Invoke a thread using a lambda
		this_thread::sleep_for(1000ms);
		cout << "[" << this_thread::get_id() << "] " << " Hello from an Lambda " << name << endl;
		});

	if (t1.joinable())
	{
		cout << " Joining thread t1 " << endl;
		t1.join();
	}

	if (t1.joinable())
	{
		cout << " Joining thread t1 " << endl;
		t1.join();
	}
	else
	{
		cout << " t1 is not joinable " << endl;
	}
	
	t2.join();
	t3.join();

	
	thread t4([]
		{
			cout << "[" << this_thread::get_id() << "] " << " Thread guard example ";
		});

	thread_guard tg(t4);

	thread t5;
	if (t5.joinable())
	{
		cout << " t5 is joinable " << endl;
	}
	else
	{
		cout << " t5 is not joinable since it is not fully initialized (no callable object set)" << endl;
	}

	thread t6(AddNumbers, 5, 6);
	t6.join();

	int num = 100;

	thread t7(PrintInLoop, std::ref(num));

	this_thread::sleep_for(chrono::seconds(1));

	num = 200;
	
	t7.join();

	thread t8(PrintName, std::ref(name));
	auto t9 = move(t8);
	t9.join();
	if (t8.joinable())
	{
		cout << " t8 is joinable " << endl;
	}
	else
	{
		cout << " t8 is not joinable " << endl;
	}

	thread t10(PrintName, std::ref(name));
	t8 = move(t10); // Works

	// thread t11(PrintName, std::ref(name));
	// t8 = move(t11); // Enabling this will cause a crash since t8 is a valid thread and we are trying to assign a new thread object to it
	t8.join();
	

	/*  Be careful while passing references to threads that are going to be detached (not joined)
		If we pass a reference from one thread to another thread and the calling thread execution completes (since the called thread is detached),
		the variable to which the reference is passed is lost. When the called thread tries to access this, it will cause an exception.
		If we are detaching threads, it is better to pass variables by values instead of by reference
	*/

	/*  If a thread already is properly initialized, if we try to initialize it again, it will lead to a crash. 
		thread t1 (addNums, 1,2);
		thread t2 = std::move(t1); // This transfers the thread info from t1 to t2 and now t1 is uninitialized

		t1 = thread(addNums, 2,3); // Works since t1 is now uninitialized
		t1 = thread(addNums, 4,5); // This throws a compiler error since t1 is not free
			
	*/

	/* 
		A default constructed thread (without any callable object initializted) will return 0 on the get_id call
		After a function is done running (i.e.,it's callable object is done running), the get_id will return 0 again. Thus, if we 
		query for the get_id of a thread object after the join call, it will return 0
	*/


	cout << " The Hardware Concurrency value of this system is  " << thread::hardware_concurrency() << endl; // Returns 8 on a system with 8 logical CPUs (i7)
}
