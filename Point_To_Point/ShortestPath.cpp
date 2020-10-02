#include "ShortestPath.h"


ShortestPath::ShortestPath() 
{}

ShortestPath::ShortestPath(int width)
{
	width_ = width;
}

void ShortestPath::setWidth(int width)
{
	width_ = width;
}

void ShortestPath::setCells(cell &src, cell &tgt)
{
	src_ = src;
	tgt_ = tgt;
}

void ShortestPath::setGrid(std::vector<std::vector<int>> dataGrid)
{
	dataGrid_ = dataGrid;
}

bool ShortestPath::isInsideGrid(int i, int j)
{
	return (i >= 0 && i < width_ && j >= 0 && j < width_);
}

int ShortestPath::dijkstra()
{
	return 1;
}

int ShortestPath::dfs()
{
	return 1;
}

std::vector<int> ShortestPath::bfs()
{
	int x = 0;
	int y = 0;
	std::vector<int> xDir = { -1, 0, 1, 0 };
	std::vector<int> yDir = { 0, 1, 0, -1 };
	std::vector<int> coord;
	std::queue<int> q;
	std::unordered_set<int> st;

	q.push(src_.getCoord());
	st.insert(src_.getCoord());
	while (!q.empty())
	{
		int front = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{	
			cell temp = NULL;
			temp.setCoord(front);
			x = temp.extractX(width_) + xDir[i];
			y = temp.extractY(width_) + yDir[i];
			temp.setX(x);
			temp.setY(y);
			temp.calculateCoord(width_);
			int c = temp.getCoord();

			if (isInsideGrid(x, y) && st.insert(c).second)
			{
				q.push(c);
				path_[c] = front;
			}

			if (c == tgt_.getCoord())
			{
				while (temp.getCoord() != src_.getCoord())
				{
					int parentCoord = path_[temp.getCoord()];
					coord.push_back(parentCoord);
					temp.setCoord(parentCoord);
				}
				coord.pop_back();
				return coord;
			}
		}
	}
	return coord;
}