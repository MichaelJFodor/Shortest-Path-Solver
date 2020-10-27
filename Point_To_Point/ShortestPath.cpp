#include "ShortestPath.h"

# pragma region ctors
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

void ShortestPath::setGrid(std::vector<int> dataGrid)
{
	dataGrid_ = dataGrid;
}

#pragma endregion

#pragma region helper functions
bool ShortestPath::isInsideGrid(int i, int j)
{
	return (i >= 0 && i < width_ && j >= 0 && j < width_);
}

#pragma endregion

#pragma region algorithms
std::vector<int> ShortestPath::dijkstra()
{
	std::unordered_map<int, int> prev;
	std::vector<int> cost(dataGrid_.size(), INT_MAX);
	for (int i = 0; i < width_; i++)
	{
		for (int j = 0; j < width_; j++)
		{
			prev[j * width_ + i] = 0;
		}
	}
	return bfs();
}

std::vector<int> ShortestPath::astar()
{
	return bfs();
}

std::vector<int> ShortestPath::dfs()
{
	std::vector<int> answer;
	std::vector<int> xDir = { -1, 0, 1, 0 };
	std::vector<int> yDir = { 0, 1, 0, -1 };
	std::vector<int> coord;
	std::unordered_set<int> visited;
	
	rdfs(visited, src_.getCoord());

	cell temp = NULL;
	temp = tgt_;
	temp.setCoord(tgt_.getCoord());
	while (temp.getCoord() != src_.getCoord())
	{
		int parentCoord = path_[temp.getCoord()];
		answer.push_back(parentCoord);
		temp.setCoord(parentCoord);
	}
	answer.pop_back();
	return answer;
}

void ShortestPath::rdfs(std::unordered_set<int>& visited, int currCoord)
{
	cell temp = NULL;
	temp.setCoord(currCoord);
	int currX = temp.extractX(width_);
	int currY = temp.extractY(width_);
	int targetCoord = tgt_.getCoord();
	int x = 0;
	int y = 0;

	if (currCoord == targetCoord)
	{
		return;
	}
	else
	{
		int prev = currCoord;
		currX += -1; //-1 0
		currY += 0;
		temp.setX(currX);
		temp.setY(currY);
		temp.calculateCoord(width_);
		if (visited.insert(temp.getCoord()).second && isInsideGrid(currX, currY))
		{
			rdfs(visited, temp.getCoord());
			path_[temp.getCoord()] = currCoord;
		}

		currX += 1; //0 1
		currY += 1;
		temp.setX(currX);
		temp.setY(currY);
		temp.calculateCoord(width_);
		if (visited.insert(temp.getCoord()).second && isInsideGrid(currX, currY))
		{
			rdfs(visited, temp.getCoord());
			path_[temp.getCoord()] = currCoord;
		}

		currX += 1; //1 0
		currY += -1;
		temp.setX(currX);
		temp.setY(currY);
		temp.calculateCoord(width_);
		if (visited.insert(temp.getCoord()).second && isInsideGrid(currX, currY))
		{
			rdfs(visited, temp.getCoord());
			path_[temp.getCoord()] = currCoord;
		}

		currX += -1; //0 -1
		currY += -1;
		temp.setX(currX);
		temp.setY(currY);
		temp.calculateCoord(width_);
		if (visited.insert(temp.getCoord()).second && isInsideGrid(currX, currY))
		{
			rdfs(visited, temp.getCoord());
			path_[temp.getCoord()] = currCoord;
		}
	}
}

std::vector<int> ShortestPath::bfs()
{
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
		for (int i = 0; i < xDir.size(); i++)
		{	
			cell temp = NULL;
			temp.setCoord(front);
			int x = temp.extractX(width_) + xDir[i];
			int y = temp.extractY(width_) + yDir[i];
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
#pragma endregion


