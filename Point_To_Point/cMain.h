#include <vector>
#include <set>
#include <iostream>
#include "ShortestPath.h"
#include "wx/wx.h"
#include "wx/wxprec.h"

// Add black boxes for illegal cells
// Create Dijkstra and A* algorithms
// Optimize DFS a little

class cMain : public wxFrame
{
public:
	// Constructors
	cMain();
	~cMain();

	// GUI
	wxListBox* list;
	wxButton **btn;

	int nFieldWidth = 40;
	int nFieldHeight = nFieldWidth;
	int *nField = nullptr;
	bool bStartClick = true;
	bool bFirstClick = true;
	bool bLastClick = false;

	// Shortest Path
	enum algorithm {BFS, DFS, DIJKSTRA, ASTAR} algo;
	bool isBlock = false;
	std::unordered_set<int> blockage;
	void runAlgorithm();
	cell *source = nullptr;
	cell *target = nullptr;
	ShortestPath sp;
	std::vector<int> dataGrid;

	// Methods
	void setSourceData(cell &temp);
	void setTargetData(cell &temp);
	wxColour* startColor = new wxColour("Green");
	wxColour* lastColor = new wxColour("Red");

	// GUI Methods
	void generateDataValues();
	void InitStatusBar();
	void createButtonGrid();
	void OnButtonClicked(wxCommandEvent &evt);
	void setDFS(wxCommandEvent &evt);
	void setBFS(wxCommandEvent &evt);
	void setDijkstra(wxCommandEvent &evt);
	void setASTAR(wxCommandEvent &evt);
	void setBlocks(wxCommandEvent &evt);

	wxMenuBar *m_pMenuBar;
	wxMenu *m_pFileMenu;
	wxMenu *m_pOtherMenu;


protected:
	wxDECLARE_EVENT_TABLE();
};

bool operator <(cell& a, cell& b);
bool operator !=(cell& a, cell& b);
bool operator ==(cell& a, cell& b);


