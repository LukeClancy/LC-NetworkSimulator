#pragma once
#include "Graph.h"
#include "Message.h"
#include <sstream>
#define _CRT_SECURE_NO_WARNINGS

class Network
{
	/*
	The network is the hub in which i organized the project. Through using the graph class and the message class, it simulates sending
	the message's Packets through the Graph, keeping track of load and wait times. Packets yet to be sent are stored in myMessage.
	Packets still being sent through the network are in inProgress. And those that have arrived are in Finished. The main function in this class
	is ticker();

	Notice that the packets	dont actually travel through the graph nodes, but instead their locations are marked in the packets.
	*/
private:
	Vector<Packet<char>> inProgress;
	minHeap<Packet<char>> Finished;
	Graph *myGraph;
	Message *myMessage;

public:
	Network()
	{

	}
	Network(Graph *myGraph, Message *myMessage)
	{
		this->myGraph = myGraph;
		this->myMessage = myMessage;
	}
	void ticker()
	{
		Packet<char> myPacket;
		bool done;
		int x;
		int tick = 1;
		string temp;
		int num = 0;
		myMessage->print();
		//while there are still packets to send, or there are still packets in commute
		while (inProgress.getSize() != 0 || myMessage->getSize() != 0)
		{
			if (myMessage->getSize() > 0)
			{//while there are still packets not yet in commute, put one in commute.
				myPacket = myMessage->pop(&temp);
				cout << "Sending Packet " << myPacket.getData() << " from start to Vertex " << std::to_string(myPacket.getHop()) << " with a wait time of " << std::to_string(myPacket.getCurrentWait()) << " at Tick " << to_string(tick) << endl;
				inProgress.addElement(myPacket);
			}
			for (x = 0; x < inProgress.getSize(); x++)
			{
				done = inProgress[x].update(tick); //update function updates the packets in commute and prints if the Packet goes to next destination
				if (done) // if at the destination
				{
					inProgress[x].setCurrentWait(tick);//records end tick in currentWait for future print.
					Finished.add(inProgress[x]);//adds to finished minHeap
					inProgress.removeElementAt(x);//deletes from vertex
				}
			}
			tick++;
		}
		cout << "Packet\tArrival Time\tRoute" << endl;
		while (Finished.getHeapSize() > 0)
		{
			//uses minHeap to get Packets based on Order, and then prints their information.
			myPacket = Finished.removeMin();
			cout << myPacket.getData() << "\t" << myPacket.getCurrentWait() << "\t\t" << myPacket.getPath() << endl;
		}
		cout << endl;
		return;
	}
};
