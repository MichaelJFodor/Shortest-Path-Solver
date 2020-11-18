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

void ShortestPath::setBlockage(std::unordered_set<int> blockage)
{
	blockage_ = blockage;
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
std::vector<int> ShortestPath::extractBfsPath(cell& temp)
{
	std::vector<int> coords;
	while (temp.getCoord() != src_.getCoord())
	{
		int parentCoord = path_[temp.getCoord()];
		coords.push_back(parentCoord);
		temp.setCoord(parentCoord);
	}
	coords.pop_back();
	return coords;
}

int ShortestPath::initNode(cell& temp, int front, int i)
{
	// Grid directions
	std::vector<int> xDir = { -1, 0, 1, 0 };
	std::vector<int> yDir = { 0, 1, 0, -1 };

	// Init node
	temp.setCoord(front);

	// Get x and y coords
	int x = temp.extractX(width_) + xDir[i];
	int y = temp.extractY(width_) + yDir[i];

	// Set coords and calculate new coord
	temp.setXY(x, y);
	temp.calculateCoord(width_);
	
	return temp.getCoord();
}

//bool ShortestPath::isInsideGrid(int i, int j)
bool ShortestPath::isInsideGrid(int coord)
{
	//return (i >= 0 && i < width_ && j >= 0 && j < width_);
	return blockage_.find(coord) == blockage_.end();
}
#pragma endregion

#pragma region algorithms
std::vector<int> ShortestPath::dijkstra()
{
	std::unordered_set<int> S;
	std::priority_queue<std::pair<int, int>> Q;
	std::unordered_map<int, int> path;
	std::vector<int> cost(dataGrid_.size(), INT_MAX);
	std::vector<int> xDir = { -1, 0, 1, 0 };
	std::vector<int> yDir = { 0, 1, 0, -1 };
	std::vector<int> coord;

	int srcCoord = src_.getCoord();
	cost[src_.getCoord()] = 0;

	// Initialize parent path
	for (int i = 0; i < width_; i++)
	{
		for (int j = 0; j < width_; j++)
		{
			int v = j * width_ + i;
			if (v != srcCoord)
			{
				path[v] = 0;
				Q.push(std::make_pair(v, -1 * cost[v]));
			}
		}
	}

	while (!Q.empty()) // infinite loop
	{
		int u = -1 * Q.top().first; // coord
		if(S.find(u) != S.end())
			continue;

		// For each neighbor of current cell
		for (int i = 0; i < xDir.size(); i++)
		{
			cell temp = NULL;
			temp.setCoord(u);
			int x = temp.extractX(width_) + xDir[i];
			int y = temp.extractY(width_) + yDir[i];
			temp.setX(x);
			temp.setY(y);
			temp.calculateCoord(width_);
			int v = temp.getCoord();
			S.insert(v);
			//if (isInsideGrid(x, y))
			if (isInsideGrid(v))
			{
				int dist = cost[u] + dataGrid_[v];
				if (dist < cost[v])
				{
					cost[v] = dist;
					path[v] = u;
				}
			}
			
		}

	}

	cell temp = NULL;
	temp.setCoord(tgt_.getCoord());
	while (temp.getCoord() != src_.getCoord())
	{
		int parentCoord = path_[temp.getCoord()];
		coord.push_back(parentCoord);
		temp.setCoord(parentCoord);
	}
	coord.pop_back();

	return coord;
}

std::vector<int> ShortestPath::astar()
{
	std::vector<int> t;
	return t;
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
		//if (visited.insert(temp.getCoord()).second && isInsideGrid(currX, currY))
		if (visited.insert(temp.getCoord()).second && isInsideGrid(temp.getCoord()))
		{
			rdfs(visited, temp.getCoord());
			path_[temp.getCoord()] = currCoord;
		}

		currX += 1; //0 1
		currY += 1;
		temp.setX(currX);
		temp.setY(currY);
		temp.calculateCoord(width_);
		if (visited.insert(temp.getCoord()).second && isInsideGrid(temp.getCoord()))
		{
			rdfs(visited, temp.getCoord());
			path_[temp.getCoord()] = currCoord;
		}

		currX += 1; //1 0
		currY += -1;
		temp.setX(currX);
		temp.setY(currY);
		temp.calculateCoord(width_);
		if (visited.insert(temp.getCoord()).second && isInsideGrid(temp.getCoord()))
		{
			rdfs(visited, temp.getCoord());
			path_[temp.getCoord()] = currCoord;
		}

		currX += -1; //0 -1
		currY += -1;
		temp.setX(currX);
		temp.setY(currY);
		temp.calculateCoord(width_);
		if (visited.insert(temp.getCoord()).second && isInsideGrid(temp.getCoord()))
		{
			rdfs(visited, temp.getCoord());
			path_[temp.getCoord()] = currCoord;
		}
	}
}

std::vector<int> ShortestPath::bfs(wxButton** btn)
{
	std::vector<int> coord;
	std::queue<int> q;
	std::unordered_set<int> visited, frontier;

	q.push(src_.getCoord());
	visited.insert(src_.getCoord());
	while (!q.empty())
	{
		int front = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{	
			cell temp = NULL;
			int currentNode = initNode(temp, front, i);

			//if (isInsideGrid(temp.getX(), temp.getY()) && visited.insert(currentNode).second)
			if (isInsideGrid(temp.getCoord()) && (visited.insert(currentNode).second))
			{
				btn[currentNode]->SetOwnBackgroundColour("Blue");
				q.push(currentNode);
				path_[currentNode] = front;
				
				// Edit to have model view controller!
				
				//frontier.insert(currentNode);
				
			}
			
			if (currentNode == tgt_.getCoord())
			{
				return extractBfsPath(temp);
			}
		}
	}
	return coord;
}
#pragma endregion


