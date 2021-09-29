#pragma once

#include <queue>
#include "Message.h"
class MessageQueue
{
	std::queue<Message> msgQueue;

public:
	void Enqueue(Message msg);

	int GetQueuedMessageCount();

	Message GetNextMessage();
};

