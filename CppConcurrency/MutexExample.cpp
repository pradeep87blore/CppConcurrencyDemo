#if 0

#include <iostream>
#include <thread>
#include <mutex>
#include <list>

using namespace std;

mutex m;

void GetListSize(const list<int>& numList)
{
	lock_guard<mutex> lg(m); // Lock_guard ensures that the locked mutex is unlocked when the lg object goes out of scope
	cout << this_thread::get_id() << ": List size is " << numList.size() << endl;
	
}

void AddToList(list<int> &numList, int num)
{
	lock_guard<mutex> lg(m);
	numList.push_back(num);
}



int main()
{
	list<int> myList;

	thread t1(AddToList, std::ref(myList), 10);
	thread t3(GetListSize, std::ref(myList));
	thread t2(AddToList, std::ref(myList), 20);
	thread t4(GetListSize, std::ref(myList));



	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

#endif