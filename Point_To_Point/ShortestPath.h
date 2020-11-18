#pragma once
#include "cell.h"
#include "wx/wx.h"
class ShortestPath
{
private:
	std::unordered_set<int> blockage_;
	std::map<int, int> path_;
	std::vector<int> dataGrid_;
	int width_;
	cell src_;
	cell tgt_;
	
public:
	// Constructors
	ShortestPath();
	ShortestPath(int width);
	
	// Setters
	void setWidth(int width);
	void setBlockage(std::unordered_set<int> blockage);
	void setCells(cell &src, cell &tgt);
	void setGrid(std::vector<int> dataGrid);

	// Methods
	std::vector<int> extractBfsPath(cell& temp);
	int initNode(cell& temp, int front, int i);
	// bool isInsideGrid(int i, int j);
	bool isInsideGrid(int coord);

	std::vector<int> dijkstra();
	std::vector<int> astar();
	std::vector<int> dfs();
	void rdfs(std::unordered_set<int>& visited, int currCoord);
	std::vector<int> bfs(wxButton** btn);
};

