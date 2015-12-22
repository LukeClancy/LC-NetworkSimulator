#include "Graph.h"
#include "Message.h"
#include "Network.h"
/*
Luke Clancy
12/10/2015
11432090

The purpose of this assignment is to create a network simulation as defined in the provided pdf by converting an inputted text file 
into a graph with weighted vertexes, and then to output data on the simulation. Some example recourse files to input are included.

I Wrote my own Message, minHeap, Packet and Network classes. I Also modified the Vertex and Graph classes which were originally created by my
teacher, Adam Carter. I Wrote my own Dijkstras algorithm in the Graph class.

A good place to start when analyzing this code is the Network class, as this is where the diffrent classes are brought together 
to create the end product. From there you can Analyze the diffrent relationships between them.
*/
void main(int argn, string argh[])
{
	
	Graph myGraph;
	Message myMessage;
	Network myNetwork;

	string done = "no";
	string input = "";
	char BLEH = '9';
	int eh = 0;
	int from;
	int to;

	if (argn >= 2)//if arguments allready inputted
	{
		input = argh[1];
	}
	else
	{
		//input = "graph4.txt";
		cout << "please enter file name \n";
		cin >> input;
	}
	myGraph = Graph(input);
	cout << "please enter message, (no spaces, use underscore)\n";
	cin >> input;
	cout << "please enter a starting node\n";
	cin >> from;
	cout << "please enter an ending node\n";
	cin >> to;
	myMessage = Message(input, from, to, &myGraph);
	myNetwork = Network(&myGraph, &myMessage);
	myNetwork.ticker();
	system("PAUSE");
	return;

}