#include <vector>
#include <set>
#include <iostream>
#include "ShortestPath.h"
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	// Constructors
	cMain();
	~cMain();

	// GUI
	wxListBox* list;
	wxButton **btn;

	int nFieldWidth = 35;
	int nFieldHeight = 35;
	int *nField = nullptr;
	bool bStartClick = true;
	bool bFirstClick = true;
	bool bLastClick = false;

	// Shortest Path
	cell *source = nullptr;
	cell *target = nullptr;
	ShortestPath sp;
	std::vector<std::vector<int>> dataGrid;

	// Methods
	void setSourceData(cell &temp);
	void setTargetData(cell &temp);
	wxColour* startColor = new wxColour("Green");
	wxColour* lastColor = new wxColour("Red");



	// GUI Methods
	void InitDataGrid();
	void OnButtonClicked(wxCommandEvent &evt);
	wxDECLARE_EVENT_TABLE();
};

bool operator < (cell& a, cell& b);
bool operator !=(cell& a, cell& b);
bool operator ==(cell& a, cell& b);


