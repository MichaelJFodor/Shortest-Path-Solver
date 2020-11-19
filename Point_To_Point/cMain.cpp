#include "cMain.h"
#pragma once
wxBEGIN_EVENT_TABLE(cMain, wxFrame) // Name of class, and base class
	EVT_BUTTON(10001, OnButtonClicked)	// 10001 is the button ID
	EVT_MENU(100, setBFS)
	EVT_MENU(101, setDFS)
	EVT_MENU(102, setDijkstra)
	EVT_MENU(103, setASTAR)
	//EVT_MENU(105, setStart)
	//EVT_MENU(106, setTarget)
	EVT_MENU(106, setBlocks)
wxEND_EVENT_TABLE()

#pragma region overload
bool operator <(cell& a, cell& b)
{
	if (a.getVal() == b.getVal())
	{
		if (a.getX() != b.getX())
		{
			return a.getX() < b.getX();
		}
		else
		{
			return a.getY() < b.getY();
		}
	}
	return a.getVal() < b.getVal();
}

bool operator !=(cell& a, cell& b)
{
	return (a.getX() != b.getX() || a.getY() != b.getY());
}

#pragma endregion

#pragma region ctors

// Constructor Helper Functions
void cMain::InitStatusBar()
{
	m_pMenuBar = new wxMenuBar();
	// File Menu
	m_pFileMenu = new wxMenu();
	m_pOtherMenu = new wxMenu();
	m_pFileMenu->Append(100, _T("&BFS"));
	m_pFileMenu->Append(101, _T("&DFS"));
	m_pFileMenu->Append(102, _T("&Dijkstra"));
	m_pFileMenu->Append(103, _T("&A*"));
	m_pFileMenu->AppendSeparator();
	m_pFileMenu->Append(wxID_EXIT, _T("&Quit"));
	m_pOtherMenu->Append(104, _T("&Set Start"));
	m_pOtherMenu->Append(105, _T("&Set Target"));
	m_pOtherMenu->AppendSeparator();
	m_pOtherMenu->Append(106, _T("&Set Blockage"));

	m_pMenuBar->Append(m_pFileMenu, _T("&Change Algorithm"));
	m_pMenuBar->Append(m_pOtherMenu, _T("&Set Blocks"));
	SetMenuBar(m_pMenuBar);

	// Set Algorithm
	algorithm algo = BFS;
}

void cMain::setBounds()
{
	for (int m = 0; m < nFieldHeight; m++)
	{
		blockage.insert(m * nFieldWidth - 1);
		blockage.insert(m * nFieldWidth + nFieldWidth);
	}
	for (int n = 0; n < nFieldWidth; n++)
	{
		blockage.insert(-1 * nFieldWidth + n);
		blockage.insert(nFieldHeight * nFieldWidth + n);
	}
}

void cMain::createButtonGrid()
{
	setBounds();
	btn = new wxButton*[nFieldWidth * nFieldHeight];
	wxGridSizer *grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);
	nField = new int[nFieldWidth * nFieldHeight];

	for (int n = 0; n < nFieldWidth; n++)
	{
		for (int m = 0; m < nFieldHeight; m++)
		{
			btn[m * nFieldHeight + n] = new wxButton(this, 10000 + (m * nFieldWidth + n));
			grid->Add(btn[m * nFieldWidth + n], 1, wxEXPAND | wxALL);
			btn[m * nFieldHeight + n]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
		}
	}

	this->SetSizer(grid);

	grid->Layout();
}

// Constuctor
cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Shortest Path Solver - wx Widgets")
{
	// Create Status Bar
	InitStatusBar();

	// Assign grid with numbers
	//generateDataValues();

	// Create grid of N x N buttons
	createButtonGrid();
}

// Destructor
cMain::~cMain()
{
	delete[]btn;
}

#pragma endregion

#pragma region algorithm setup
void cMain::setSourceData(cell &temp)
{
	source = &temp;
	int coord = source->getCoord();

	btn[coord]->SetOwnBackgroundColour(*startColor);
	btn[coord]->SetLabel("Start");
	btn[coord]->Enable(false);
	bFirstClick = false;
}

void cMain::setTargetData(cell &temp)
{
	target = &temp;
	int coord = target->getCoord();

	btn[coord]->SetOwnBackgroundColour(*lastColor);
	btn[coord]->SetLabel("End");
	btn[coord]->Enable(false);
	bLastClick = true;
}

void cMain::runAlgorithm()
{
	
	
	
	sp.setBlockage(blockage);
	sp.setWidth(nFieldWidth);
	sp.setCells(*source, *target);
	switch (algo)
	{
		case BFS:
		{
			algoName = "BFS";
			algoColor = new wxColour("Yellow");
			path = sp.bfs(btn);
			break;
		}
		case DFS:
		{
			algoName = "DFS";
			algoColor = new wxColour("Blue");
			path = sp.dfs();
			break;
		}
		case DIJKSTRA:
		{
			algoName = "Dijkstra";
			algoColor = new wxColour("Purple");
			path = sp.dijkstra();
			break;
		}
		case ASTAR:
		{
			algoName = "A*";
			algoColor = new wxColour("Pink");
			path = sp.astar();
			break;
		}
		default:
		{
			algoName = "BFS";
			algoColor = new wxColour("Yellow");
			path = sp.bfs(btn);
			break;
		}
	}

	for (auto e : path)
	{
		btn[e]->SetOwnBackgroundColour(*algoColor);
		btn[e]->SetLabel(algoName);
		btn[e]->Enable(false);
	}
}

#pragma endregion

void cMain::OnButtonClicked(wxCommandEvent &evt)
{
	int coord = 0;
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldHeight;
	cell* temp = new cell(x, y, bFirstClick);
	temp->calculateCoord(nFieldWidth);
	if (!isBlock) 
	{
		if (bFirstClick) 
			setSourceData(*temp);
		else
			setTargetData(*temp);
	
		if (bLastClick)
		{

			//sp.setGrid(dataGrid);

			runAlgorithm();
			delete temp;
		}	
	}
	else
	{
		int cell = temp->getCoord();
		blockage.insert(cell);
		btn[cell]->SetBackgroundColour("Black");
		btn[cell]->Enable(false);	
	}

	evt.Skip();
}

#pragma region status bar options 
// Status Bar Options
void cMain::setBFS(wxCommandEvent &evt)
{
	isBlock = false;
	algo = BFS;
}

void cMain::setDFS(wxCommandEvent &evt)
{
	isBlock = false;
	algo = DFS;
}

void cMain::setDijkstra(wxCommandEvent &evt)
{
	isBlock = false;
	algo = DIJKSTRA;
}

void cMain::setASTAR(wxCommandEvent &evt)
{
	isBlock = false;
	algo = ASTAR;
}

void cMain::setBlocks(wxCommandEvent &evt)
{
	isBlock = true;
}

# pragma endregion