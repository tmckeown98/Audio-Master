#ifndef INC_WAVEFORM_DISPLAY_H
#define INC_WAVEFORM_DISPLAY_H

#include "..\..\..\Sound\SoundManager.h"

#include <wx/frame.h>
#include <wx/scrolwin.h>
#include <wx/panel.h>
#include <wx/dc.h>
#include <wx/dcclient.h>
#include <wx/event.h>

namespace AudioMaster
{

	class WaveformDisplay final : public wxScrolled<wxPanel>
	{
	private:
		float scrollMultiplier;
		float minScrollMultiplier;
		int scrolled;
		bool ctrlScroll;

		int displayHeight;

		float zoom;
		int zoomMultiplier;
		float minZoom;
		float maxZoom;

		Sound* cachedWaveData;

	public:
		WaveformDisplay(wxFrame* parent, wxSize size);
		~WaveformDisplay();

		void ForceRepaint();

		void OnPaint(wxPaintEvent& e);
		void OnScroll(wxMouseEvent& e);
		void OnResize(wxSizeEvent& e);
		void OnDClick(wxMouseEvent& e);
		void OnKeyDown(wxKeyEvent& e);
		void OnKeyUp(wxKeyEvent& e);

	private:
		void Render(wxDC& dc);
		void UpdateVirtualSize(wxSize newSize);

		wxDECLARE_EVENT_TABLE();
	};
	
}

#endif