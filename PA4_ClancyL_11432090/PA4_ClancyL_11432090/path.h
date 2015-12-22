#pragma once

using namespace std;
class path
{
public:
	//used in Graph.h to find the right path and next node for Packets.
	int delay;
	int pathWay[100];
	int pathNum;
	int getOrder()
	{
		return delay;
	}
	path()
	{
		delay = 0;
		pathNum = 0;
	}
	path(int adelay, int Junction)
	{
		this->pathWay[0] = Junction;
		pathNum = 1;
		this->delay = adelay;
	}
	path(int adelay, int otherPathWay[100], int pathNum)
	{
		int x = 0;
		this->delay = adelay;
		this->pathNum = pathNum;
		for (x = 0; x < pathNum; x++)
		{
			this->pathWay[x] = otherPathWay[x];
		}
		
	}
	path& operator = (path &other)
	{
		int x = 0;
		this->delay = other.delay;
		for (x = 0; x < other.pathNum; x++)
		{
			this->pathWay[x] = other.pathWay[x];
		}
		this->pathNum = other.pathNum;
		return *this;
	}
	bool endSame(path &other)
	{
		//figures if there is allready a path to there.
		//DOES NOT CHECK ALL OF THE VARIABLES FOR EQUALITY JUST THAT THEY END IN SAME PLACE
		return this->pathWay[pathNum - 1] == other.pathWay[other.pathNum - 1];
	}
	void addData(int delay, int point)
	{
		pathWay[pathNum] = point;
		pathNum++;
		this->delay += delay;
		return;
	}
	int getTop()
	{
		return this->pathWay[pathNum - 1];
	}
	void print()
	{
		int x;
		for (x = 0; x < pathNum; x++)
		{
			cout << pathWay[x] << "|";
		}
		cout <<"||" << delay << endl;
		return;
	}
};