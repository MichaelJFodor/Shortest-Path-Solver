#pragma once
#include "cell.h"

class ShortestPath
{
private:
	std::map<int, int> path_;
	std::vector<std::vector<int>> dataGrid_;
	int width_;
	cell src_;
	cell tgt_;

	
public:
	// Constructors
	ShortestPath();
	ShortestPath(int width);
	
	// Setters
	void setWidth(int width);
	void setCells(cell &src, cell &tgt);
	void setGrid(std::vector<std::vector<int>> dataGrid);

	// Methods
	bool isInsideGrid(int i, int j);
	int dijkstra();
	int dfs();
	std::vector<int> bfs();
};

