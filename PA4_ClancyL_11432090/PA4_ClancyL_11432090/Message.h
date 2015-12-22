#pragma once
#include "Graph.h"
#include "Packet.h"

class Message
{
	/*
	this class is used to store the original message string, convert it into packets, and then start their journey. They are sent through
	the network based on their order in the message.
	*/
private:
	minHeap<Packet<char>> messageChars;//handles packets yet to start the journey
	string message;
	
public:
	Message()
	{

	}
	Message(string myMess, int start, int end, Graph *graphInUse)
	{
		int x = 0;
		messageChars = minHeap<Packet<char>>();
		message = myMess;

		Packet<char> a;
		//int nextHop = graphInUse->getNextNode(start, end);
		for each (char currChar in message)
		{
			a = Packet<char>(currChar, graphInUse, end, start, x);
			messageChars.add(a);
			x++;
		}
	}
	void print()
	{
		messageChars.print();
		return;
	}
	int getSize()
	{
		return messageChars.getHeapSize();
	}
	Packet<char> pop(string* printDis)
	{
		Packet<char> temp = messageChars.removeMin();//starts the packets journey
		*printDis = temp.start();
		return temp;
	}
};