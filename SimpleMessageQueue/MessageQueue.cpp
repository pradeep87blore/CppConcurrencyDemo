#include "MessageQueue.h"
#include <mutex>

using namespace std;

mutex m;

void MessageQueue::Enqueue(Message msg)
{
	unique_lock<mutex> ul(m);

	msgQueue.push(msg);
}

int MessageQueue::GetQueuedMessageCount()
{
	unique_lock<mutex> ul(m);

	return msgQueue.size();
}

Message MessageQueue::GetNextMessage()
{
	unique_lock<mutex> ul(m);
	if (msgQueue.empty())
	{
		throw new runtime_error("Queue is empty");
	}
	auto msg = msgQueue.front();
	msgQueue.pop();

	return msg;	
}
