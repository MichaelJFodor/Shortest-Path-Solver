#include "cMain.h"
#pragma once
wxBEGIN_EVENT_TABLE(cMain, wxFrame) // Name of class, and base class
EVT_BUTTON(10001, OnButtonClicked)	// 10001 is the button ID
wxEND_EVENT_TABLE()

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

void cMain::InitDataGrid()
{
	srand(time(NULL));
	std::vector<int> temp;
	int val = 0;

	for (int i = 0; i < nFieldWidth; i++)
	{
		for (int j = 0; j < nFieldHeight; j++)
		{
			val = (rand() % 101) + 1;
			temp.push_back(val);
		}
		dataGrid.push_back(temp);
		temp.clear();
	}
}

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Shortest Path Solver - wx Widgets")
{
	btn = new wxButton*[nFieldWidth * nFieldHeight];
	wxGridSizer *grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);
	nField = new int[nFieldWidth * nFieldHeight];
	InitDataGrid();

	for (int n = 0; n < nFieldWidth; n++)
	{
		for (int m = 0; m < nFieldHeight; m++)
		{
			btn[m * nFieldHeight + n] = new wxButton(this, 10000 + (m * nFieldWidth + n));
			btn[m * nFieldHeight + n]->SetLabel(std::to_string(dataGrid[n][m]));
			grid->Add(btn[m * nFieldWidth + n], 1, wxEXPAND | wxALL);

			btn[m * nFieldHeight + n]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			nField[m * nFieldWidth + n] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();

}

cMain::~cMain()
{
	delete[]btn;
}

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

void cMain::OnButtonClicked(wxCommandEvent &evt)
{
	int coord = 0;
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldHeight;
	cell* temp = new cell(x, y, bFirstClick);
	temp->calculateCoord(nFieldWidth);
	temp->getCoord();
	
	if (bFirstClick) 
		setSourceData(*temp);
	else
		setTargetData(*temp);
	
	if (bLastClick)
	{
		sp.setWidth(nFieldWidth);
		sp.setCells(*source, *target);
		sp.setGrid(dataGrid);
		sp.setWidth(nFieldWidth);
		std::vector<int> path = sp.dfs();
		for (auto e : path)
		{
			btn[e]->SetOwnBackgroundColour("Blue");
			btn[e]->SetLabel("DFS");
			btn[e]->Enable(false);
		}

		//path = sp.bfs();
		//for (auto e : path)
		//{
		//	btn[e]->SetOwnBackgroundColour("Yellow");
		//	btn[e]->SetLabel("BFS");
		//	btn[e]->Enable(false);
		//}
		delete temp;
		//list = new wxListBox(this, wxID_ANY, wxPoint(10, 100), wxSize(100, 100));
		//list->AppendString(std::to_string(path));
	}	
	

	evt.Skip();
}