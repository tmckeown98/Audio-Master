#include "ProjectFrame.h"

// Outputs memory leaks after the program has closed
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h> // redefines the new() operator 
#endif

namespace AudioMaster
{
	wxBEGIN_EVENT_TABLE(ProjectFrame, wxFrame)

		EVT_CLOSE	(ProjectFrame::OnClose	)
		EVT_SIZE	(ProjectFrame::OnResize	)
		EVT_MOVE_END(ProjectFrame::OnMove	)

	wxEND_EVENT_TABLE()

    ProjectFrame::ProjectFrame(wxString title, wxPoint pos, wxSize size, bool maximised)
		: wxFrame(NULL, wxID_ANY, title, pos, size)
    {
		// Get the logger
		this->logger = Logger::GetInstance();

		this->logger->Log("Initialising Project Frame");

		// Set position and size
		this->pos = pos;
		this->size = size;

		// Set maximised state
		this->Maximize(maximised);

		// Initialise the AUI manager
		this->logger->Log("Initialising Advanced UI manager");
		this->auiManager.SetManagedWindow(this);

		// Initialise the toolbars
		this->InitToolbars();
    }

    ProjectFrame::~ProjectFrame()
    {
        this->auiManager.UnInit();
    }

	void ProjectFrame::InitToolbars()
	{
		// Create the toolbars
		this->controlBar = new ControlToolbar(this);
		this->ioBar = new IOToolbar(this);

		// Setup each toolbar's pane info
		wxAuiPaneInfo controlBarInfo;
		controlBarInfo
			.Name("ControlToolbar")
			.Caption("Control Toolbar")
			.ToolbarPane()
			.Top()
			.LeftDockable(false)
			.RightDockable(false)
			.BottomDockable(false)
			.Floatable(false);

		wxAuiPaneInfo ioBarInfo;
		ioBarInfo
			.Name("IOToolbar")
			.Caption("IO Toolbar")
			.ToolbarPane()
			.Top()
			.LeftDockable(false)
			.RightDockable(false)
			.BottomDockable(false)
			.Floatable(false);

		// Add the toolbars as AUI panes
		this->auiManager.AddPane(this->controlBar, controlBarInfo);
		this->auiManager.AddPane(this->ioBar, ioBarInfo);

		// Tell the manager to commit all the changes that were made
		this->auiManager.Update();
	}

#pragma region FRAME EVENTS

	void ProjectFrame::OnClose(wxCloseEvent& e)
	{
		// Save the new main window settings (position, size, and maximised)
		SaveSetting(MAIN_WINDOW_KEY, WINDOW_X_KEY, this->pos.x);
		SaveSetting(MAIN_WINDOW_KEY, WINDOW_Y_KEY, this->pos.y);

		SaveSetting(MAIN_WINDOW_KEY, WINDOW_WIDTH_KEY,  this->size.GetWidth ());
		SaveSetting(MAIN_WINDOW_KEY, WINDOW_HEIGHT_KEY, this->size.GetHeight());

		SaveSetting(MAIN_WINDOW_KEY, WINDOW_MAX_KEY, this->IsMaximized());

		// Call the base class close function
		e.Skip();
	}

	void ProjectFrame::OnResize(wxSizeEvent& e)
	{
		// Get the size of the frame when not maximised
		if (!this->IsMaximized())
		{
			this->size = e.GetSize();
		}
	}

	void ProjectFrame::OnMove(wxMoveEvent& WXUNUSED(e))
	{
		// Get the position of the frame when not maximised
		if (!this->IsMaximized())
		{
			this->pos = this->GetPosition();
		}
	}

#pragma endregion

}