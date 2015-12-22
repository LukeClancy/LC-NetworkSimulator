#pragma once
#include "Graph.h"
#include <string>

template<class T>
class Packet
{
private:
	T data;
	int order;
	int currentWait;
	int destination;
	int previousLoc;
	int nextHop;
	string path;
	Graph *currentGraph;

public:
	Packet<T>()
	{
		path = "";
		data = T();
		order = 99999999;
		currentWait = 0;
		destination = 0;
		previousLoc = 0;
		nextHop = 0;
		currentGraph = nullptr;
	}
	int getHop()
	{
		return nextHop;
	}
	Packet<T>(T data, Graph *currentGraph, int destination, int previousLoc, int order)
	{//do this
		this->currentGraph = currentGraph;
		this->data = data;
		this->destination = destination;
		this->previousLoc = previousLoc;
		this->nextHop = 0;
		this->currentWait = 0;
		this->order = order; //minHeap, so lowest first
		char *temp = "";
		path = to_string(previousLoc);
	}
	int getOrder()
	{
		return order; // created for input and compatibility with minHeap.
	}
	//update, deincrements wait, if done returns true and calculates next spot
	bool update(int tick)
	{
		/*
		deincrements wait time.
		if less then zero, moves to next (unless at destination then returns true.
		*/
		char* temp = "";
		currentWait--;
		if (currentWait <= 0)
		{
			currentGraph->deincrementLoads(previousLoc, nextHop);
			if (nextHop == destination)
			{
				return 1;
			}
			else
			{
				//cout << endl << "moving from " << previousLoc << " to " << nextHop;
				previousLoc = nextHop;
				nextHop = currentGraph->getNextNode(previousLoc, destination);
				//cout << "next node: " << nextHop << endl;
				currentWait = currentGraph->getWait(previousLoc, nextHop);
				cout << "Sending Packet " << getData() << " from " << previousLoc << " to Vertex " << nextHop << " with a wait time of " << getCurrentWait() << " at Tick " << to_string(tick) << endl;
				currentGraph->incrementLoads(previousLoc, nextHop);
				path.append(", " + std::to_string(nextHop));
			}
		}
		return 0;
	}
	void print()
	{
		cout << " |" <<this->getData();
		return;
	}
	string start()
	{
		//starts the Packets journey. Called in Messages POP
		nextHop = currentGraph->getNextNode(previousLoc, destination);
		currentWait = currentGraph->getWait(previousLoc, nextHop);
		currentGraph->incrementLoads(previousLoc, nextHop);
		path.append(", " + std::to_string(nextHop));
		string a = { char(data) };
		return "sending packet " + a +" to vertex " + std::to_string(nextHop) + "with a wait of " + std::to_string(currentWait) + " at time: ";
	}
	T getData()
	{
		return data;
	}
	string getPath()
	{
		return path;
	}
	void setCurrentWait(int eh)
	{
		this->currentWait = eh;
		return;
	}
	int getCurrentWait()
	{
		return this->currentWait;
	}
};
