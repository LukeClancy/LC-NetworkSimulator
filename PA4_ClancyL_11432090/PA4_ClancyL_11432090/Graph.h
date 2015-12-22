#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <queue>
#include <functional>
#include <fstream>
#include <iostream>

#include "path.h"
#include "Vertex.h"
#include "minHeap.h"
using namespace std;

class Graph
{
private:
	unordered_map<int, Vertex*> _vertices;

	char* getNextSegment(int a, int b, string c)
	{
		int x;
		char returnThis[200] = "";
		for (x = a; x < b; x++)
		{
			returnThis[x - a] = c[x];
		}
		returnThis[b] = '\0';
		return returnThis;
	}

	void processLine(char* line)
	{
		string strLine = line;
		int segment[3] = { -1,-1,-1 };

		int end = -1;
		int num = 0;
		int tracker = 0;
		//get Info
		
		do{
			end++;
			tracker = 0;
			while (line[end] != ' ' && line[end] != '\0')
			{
				tracker = tracker * 10 + line[end] - '0';
				end++;
			}
			segment[num] = tracker;
			num++;
		} while (line[end] != '\0');
		//process it
		if (segment[1] == -1)
		{
			addVertex(new Vertex(segment[0]));
		}
		else
		{
			addEdge(segment[0],segment[1],segment[2]);
		}
		return;
	}

	bool exists(path b, Vector<path> &c)
	{
		int x = 0;
		for (x = 0; x < c.getSize(); x++)
		{
			if (b.endSame(c[x])) //checks wether there is a path allready pointing to the end of path b in the Vector of paths c.
			{
				return true;
			}
		}
		return false;
	}

public:
	Graph()
	{
		_vertices = unordered_map<int, Vertex*>();
	}
	Graph(string fileName)
	{
		_vertices = unordered_map<int, Vertex*>();
		processInfo(fileName);
	}
	//two functions below deincrement/increment loads. Done in pairs as requirements say that when moving
	//from a node to anouther, deincrement the loads of the pair of nodes you were traveling between before
	//and increment the loads of the pair your traveling between now. So I found it more efficient to do it in pairs.
	void deincrementLoads(int a, int b)
	{
		_vertices.find(a)->second->deincrementLoad();
		_vertices.find(b)->second->deincrementLoad();
		return;
	}
	void incrementLoads(int a, int b)
	{
		_vertices.find(a)->second->incrementLoad();
		_vertices.find(b)->second->incrementLoad();
		return;
	}
	void processInfo(string fileName)//reads file, processes them in private method proccessLine
	{
		char line[200];
		fstream myFile;
		myFile.open(fileName);
		while (myFile.getline(line, 200))
		{
			processLine(line);
		}
		return;
	}
	void addEdge(int ID1, int ID2, int weight)
	{
		_vertices[ID1]->addEdge(_vertices.at(ID2), weight);
	}
	void addVertex(Vertex *vertex)
	{
		_vertices[vertex->getId()] = vertex;
	}

	
	//figures if the end point of the path is already led to by anouther path.
	
	int getNextNode(int from, int to)
	{
		//uses getMyPath() (below) To find the shortest pathway between from and to
		//using the Dijkistras Algorithm. Then returns the next step.
		return getMyPath(_vertices.find(from)->second, _vertices.find(to)->second).pathWay[1];
	}
	int getWait(int from, int to)
	{
		//gets the wait time between two connected nodes.
		Vertex *temp = _vertices.find(from)->second;
		for each(pair<Vertex*, int> edge in temp->getEdges())
		{
			if (edge.first->getId() == to)
			{
				return edge.first->getLoad() * edge.second;
			}
		}
		return -1;
	}

	//this is my dijkstra's Algorithm. Returns the Shortest Path (path is a class made just for this purpous).
	//This function is used by getNextNode which then returns the path[1], or the next fastest node to the destination.
	//The function may also be used to find the fastest path in general.
	path getMyPath(Vertex *from, Vertex *to) 
	{
		minHeap<path> pathMinHeap = minHeap<path>();//path(delay, int loc)
		Vector<path> inProg = Vector<path>();
		Vertex *temp = from;
		path pathOrig = path(0, from->getId());
		path pathTemp;
		inProg.addElement(pathOrig);

		while (temp != to)//while the node being evaluated is not the node we are looking for
		{
			for each(pair<Vertex*, int> edge in temp->getEdges())//add branches to the 
			{
				pathTemp = pathOrig;
				pathTemp.addData(edge.second * edge.first->getLoad(), edge.first->getId()); //adds wait time and Id to path
				pathMinHeap.add(pathTemp);
			}
			//pathMinHeap.print();
			//cout << endl;
			while (exists(pathMinHeap.getMin(), inProg))//take off all paths that lead to end allready discovered
			{
				pathTemp = pathMinHeap.removeMin();
			}
			//pathMinHeap.print();
			//cout << endl;
			pathOrig = pathMinHeap.removeMin();			
			temp = _vertices.find(pathOrig.getTop())->second;	//get path end, set it as temp
			inProg.addElement(pathOrig);
		}
		return pathOrig;
	}

};

#endif
