#pragma once
#include "cApp.h"

wxIMPLEMENT_APP(cApp);


cApp::cApp()
{
}

cApp::~cApp()
{
}


bool cApp::OnInit()
{
	mainWindow = new cMain();
	mainWindow->Show();
	SetTopWindow(mainWindow);
	return true;
}