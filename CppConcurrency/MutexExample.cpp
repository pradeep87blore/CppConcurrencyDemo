#include <iostream>
#include <thread>
#include <mutex>
#include <list>

using namespace std;

mutex m;

void GetListSize(const list<int>& numList)
{
	m.lock();
	cout << this_thread::get_id() << ": List size is " << numList.size() << endl;
	m.unlock();
}

void AddToList(list<int> &numList, int num)
{
	m.lock();
	numList.push_back(num);
	m.unlock();
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