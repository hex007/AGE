/* AGEFrame_cpp/PlayerColors.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

string AGE_Frame::GetPlayerColorName(int Index)
{
	string Name = "";
	if(GameVersion <= 1)
	{
		Name = GenieFile->PlayerColours[Index].Name;
	}
	else
	{
		Name = "Color ";
		Name += lexical_cast<string>(GenieFile->PlayerColours[Index].ID);
	}
	return Name;
}

void AGE_Frame::ListPlayerColors()
{
	string Name;
	wxString SearchText = wxString(Colors_Colors_Search->GetValue()).Lower();
	string CompareText;
	
	short ColorID = Colors_Colors_List->GetSelection();

	if(!Colors_Colors_List->IsEmpty())
	{
		Colors_Colors_List->Clear();
	}
	
	if(ColorID == wxNOT_FOUND)
	{
		ColorID = 0;
	}
	
	for(short loop = 0;loop < GenieFile->PlayerColours.size();loop++)
	{
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetPlayerColorName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetPlayerColorName(loop)).Lower();
		if((SearchText.IsEmpty()) || (CompareText.find(SearchText) != string::npos))
		{
			Colors_Colors_List->Append(Name, (void*)&GenieFile->PlayerColours[loop]);
		}
	}
	
	Colors_Colors_List->SetSelection(0);
	Colors_Colors_List->SetSelection(ColorID);
	
	wxCommandEvent E;
	OnPlayerColorsSelect(E);
}

void AGE_Frame::OnPlayerColorsSearch(wxCommandEvent& Event)
{
	ListPlayerColors();
}

void AGE_Frame::OnPlayerColorsSelect(wxCommandEvent& Event)
{
	short ColorID = Colors_Colors_List->GetSelection();
	if(ColorID != wxNOT_FOUND)
	{
		gdat::PlayerColour * PlayerColorPointer = (gdat::PlayerColour*)Colors_Colors_List->GetClientData(ColorID);
		Colors_ID->SetValue(lexical_cast<string>(PlayerColorPointer->ID));
		Colors_ID->Container = &PlayerColorPointer->ID;
		// Color shows oddly high values in AoE and RoR. It is supposed to be short in them.
		Colors_Color->SetValue(lexical_cast<string>(PlayerColorPointer->Colour));
		Colors_Color->Container = &PlayerColorPointer->Colour;
		if(GameVersion <= 1)	//	AoE and RoR
		{
			Colors_Name->SetValue(PlayerColorPointer->Name);
			Colors_Name->Container = PlayerColorPointer->Name;
		}
		else	//	Above AoE and RoR
		{
			Colors_Palette->SetValue(lexical_cast<string>(PlayerColorPointer->Palette));
			Colors_Palette->Container = &PlayerColorPointer->Palette;
			Colors_MinimapColor->SetValue(lexical_cast<string>(PlayerColorPointer->MinimapColour));
			Colors_MinimapColor->Container = &PlayerColorPointer->MinimapColour;
			Colors_Unknown1->SetValue(lexical_cast<string>(PlayerColorPointer->Unknown1));
			Colors_Unknown1->Container = &PlayerColorPointer->Unknown1;
			Colors_Unknown2->SetValue(lexical_cast<string>(PlayerColorPointer->Unknown2));
			Colors_Unknown2->Container = &PlayerColorPointer->Unknown2;
			Colors_Unknown3->SetValue(lexical_cast<string>(PlayerColorPointer->Unknown3));
			Colors_Unknown3->Container = &PlayerColorPointer->Unknown3;
			Colors_Unknown4->SetValue(lexical_cast<string>(PlayerColorPointer->Unknown4));
			Colors_Unknown4->Container = &PlayerColorPointer->Unknown4;
			Colors_Unknown5->SetValue(lexical_cast<string>(PlayerColorPointer->Unknown5));
			Colors_Unknown5->Container = &PlayerColorPointer->Unknown5;
		}
	}
}

void AGE_Frame::OnPlayerColorsAdd(wxCommandEvent& Event)
{
	gdat::PlayerColour Temp;
	GenieFile->PlayerColours.push_back(Temp);
	for(short loop = 0;loop < GenieFile->PlayerColours.size();loop++)	//	ID fix
	{
		GenieFile->PlayerColours[loop].ID = lexical_cast<long>(loop);
	}
	ListPlayerColors();
	Colors_Colors_List->SetSelection(Colors_Colors_List->GetCount() - 1);
	wxCommandEvent E;
	OnPlayerColorsSelect(E);
}

void AGE_Frame::OnPlayerColorsDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short ColorID = Colors_Colors_List->GetSelection();
	if(ColorID != wxNOT_FOUND)
	{
		gdat::PlayerColour * PlayerColorPointer = (gdat::PlayerColour*)Colors_Colors_List->GetClientData(ColorID);
		GenieFile->PlayerColours.erase(GenieFile->PlayerColours.begin() + (PlayerColorPointer - (&GenieFile->PlayerColours[0])));
		for(short loop = 0;loop < GenieFile->PlayerColours.size();loop++)	//	ID fix
		{
			GenieFile->PlayerColours[loop].ID = lexical_cast<long>(loop);
		}
		ListPlayerColors();
		Colors_Colors_List->SetSelection(Colors_Colors_List->GetCount() - 1);
		Colors_Colors_List->SetSelection(ColorID - 1);
		Colors_Colors_List->SetSelection(ColorID);
	}
}

void AGE_Frame::OnPlayerColorsCopy(wxCommandEvent& Event)
{
	short ColorID = Colors_Colors_List->GetSelection();
	if(ColorID != wxNOT_FOUND)
	{
		PlayerColorCopy = *(gdat::PlayerColour*)Colors_Colors_List->GetClientData(ColorID);
	}
}

void AGE_Frame::OnPlayerColorsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short ColorID = Colors_Colors_List->GetSelection();
	if(ColorID != wxNOT_FOUND)
	{
		*(gdat::PlayerColour*)Colors_Colors_List->GetClientData(ColorID) = PlayerColorCopy;
		for(short loop = 0;loop < GenieFile->PlayerColours.size();loop++)	//	ID fix
		{
			GenieFile->PlayerColours[loop].ID = lexical_cast<long>(loop);
		}
		ListPlayerColors();
		Colors_Colors_List->SetSelection(ColorID + 3);
		Colors_Colors_List->SetSelection(ColorID);
	}
}

void AGE_Frame::CreatePlayerColorControls()
{
	Colors_Main = new wxBoxSizer(wxHORIZONTAL);
	Colors_ListArea = new wxBoxSizer(wxVERTICAL);
	Colors_Colors_Buttons = new wxGridSizer(2, 0, 0);
	Tab_PlayerColors = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(-1, 350));

	Colors_Colors = new wxStaticBoxSizer(wxVERTICAL, Tab_PlayerColors, "Player Color Slot");
	Colors_Colors_Search = new wxTextCtrl(Tab_PlayerColors, wxID_ANY);
	Colors_Colors_List = new wxListBox(Tab_PlayerColors, wxID_ANY, wxDefaultPosition, wxSize(-1, 70));
	Colors_Add = new wxButton(Tab_PlayerColors, wxID_ANY, "Add", wxDefaultPosition, wxSize(-1, 20));
	Colors_Delete = new wxButton(Tab_PlayerColors, wxID_ANY, "Delete", wxDefaultPosition, wxSize(-1, 20));
	Colors_Copy = new wxButton(Tab_PlayerColors, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	Colors_Paste = new wxButton(Tab_PlayerColors, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));

	Colors_DataArea = new wxBoxSizer(wxVERTICAL);
	Colors_Holder_Name = new wxBoxSizer(wxVERTICAL);
	Colors_Holder_ID = new wxBoxSizer(wxVERTICAL);
	Colors_Holder_Palette = new wxBoxSizer(wxVERTICAL);
	Colors_Holder_Color = new wxBoxSizer(wxVERTICAL);
	Colors_Holder_MinimapColor = new wxBoxSizer(wxVERTICAL);
	Colors_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	Colors_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	Colors_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	Colors_Holder_Unknown4 = new wxBoxSizer(wxVERTICAL);
	Colors_Holder_Unknown5 = new wxBoxSizer(wxVERTICAL);
	Colors_Text_Name = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Name", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Text_ID = new wxStaticText(Tab_PlayerColors, wxID_ANY, " ID", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Text_Palette = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Palette", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Text_Color = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Color", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Text_MinimapColor = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Minimap Color", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Text_Unknown1 = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Unknown 1", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Text_Unknown2 = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Unknown 2", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Text_Unknown3 = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Unknown 3", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Text_Unknown4 = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Unknown 4", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Text_Unknown5 = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Unknown 5", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Name = new TextCtrl_String(Tab_PlayerColors, "0", NULL, 30);
	Colors_ID = new TextCtrl_Long(Tab_PlayerColors, "0", NULL);
	Colors_Palette = new TextCtrl_Long(Tab_PlayerColors, "0", NULL);
	Colors_Color = new TextCtrl_Long(Tab_PlayerColors, "0", NULL);
	Colors_MinimapColor = new TextCtrl_Long(Tab_PlayerColors, "0", NULL);
	Colors_Unknown1 = new TextCtrl_Long(Tab_PlayerColors, "0", NULL);
	Colors_Unknown2 = new TextCtrl_Long(Tab_PlayerColors, "0", NULL);
	Colors_Unknown3 = new TextCtrl_Long(Tab_PlayerColors, "0", NULL);
	Colors_Unknown4 = new TextCtrl_Long(Tab_PlayerColors, "0", NULL);
	Colors_Unknown5 = new TextCtrl_Long(Tab_PlayerColors, "0", NULL);
	
	Colors_Colors_Buttons->Add(Colors_Add, 1, wxEXPAND);
	Colors_Colors_Buttons->Add(Colors_Delete, 1, wxEXPAND);
	Colors_Colors_Buttons->Add(Colors_Copy, 1, wxEXPAND);
	Colors_Colors_Buttons->Add(Colors_Paste, 1, wxEXPAND);

	Colors_Colors->Add(Colors_Colors_Search, 0, wxEXPAND);
	Colors_Colors->Add(-1, 2);
	Colors_Colors->Add(Colors_Colors_List, 1, wxEXPAND);
	Colors_Colors->Add(-1, 2);
	Colors_Colors->Add(Colors_Colors_Buttons, 0, wxEXPAND);

	Colors_ListArea->Add(-1, 10);
	Colors_ListArea->Add(Colors_Colors, 1, wxEXPAND);
	Colors_ListArea->Add(-1, 10);

	Colors_Holder_Name->Add(Colors_Text_Name, 0, wxEXPAND);
	Colors_Holder_Name->Add(-1, 2);
	Colors_Holder_Name->Add(Colors_Name, 1, wxEXPAND);
	Colors_Holder_ID->Add(Colors_Text_ID, 0, wxEXPAND);
	Colors_Holder_ID->Add(-1, 2);
	Colors_Holder_ID->Add(Colors_ID, 1, wxEXPAND);
	Colors_Holder_Palette->Add(Colors_Text_Palette, 0, wxEXPAND);
	Colors_Holder_Palette->Add(-1, 2);
	Colors_Holder_Palette->Add(Colors_Palette, 1, wxEXPAND);
	Colors_Holder_Color->Add(Colors_Text_Color, 0, wxEXPAND);
	Colors_Holder_Color->Add(-1, 2);
	Colors_Holder_Color->Add(Colors_Color, 1, wxEXPAND);
	Colors_Holder_MinimapColor->Add(Colors_Text_MinimapColor, 0, wxEXPAND);
	Colors_Holder_MinimapColor->Add(-1, 2);
	Colors_Holder_MinimapColor->Add(Colors_MinimapColor, 1, wxEXPAND);
	Colors_Holder_Unknown1->Add(Colors_Text_Unknown1, 0, wxEXPAND);
	Colors_Holder_Unknown1->Add(-1, 2);
	Colors_Holder_Unknown1->Add(Colors_Unknown1, 1, wxEXPAND);
	Colors_Holder_Unknown2->Add(Colors_Text_Unknown2, 0, wxEXPAND);
	Colors_Holder_Unknown2->Add(-1, 2);
	Colors_Holder_Unknown2->Add(Colors_Unknown2, 1, wxEXPAND);
	Colors_Holder_Unknown3->Add(Colors_Text_Unknown3, 0, wxEXPAND);
	Colors_Holder_Unknown3->Add(-1, 2);
	Colors_Holder_Unknown3->Add(Colors_Unknown3, 1, wxEXPAND);
	Colors_Holder_Unknown4->Add(Colors_Text_Unknown4, 0, wxEXPAND);
	Colors_Holder_Unknown4->Add(-1, 2);
	Colors_Holder_Unknown4->Add(Colors_Unknown4, 1, wxEXPAND);
	Colors_Holder_Unknown5->Add(Colors_Text_Unknown5, 0, wxEXPAND);
	Colors_Holder_Unknown5->Add(-1, 2);
	Colors_Holder_Unknown5->Add(Colors_Unknown5, 1, wxEXPAND);
	
	Colors_DataArea->Add(-1, 10);
	Colors_DataArea->Add(Colors_Holder_Name, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Colors_DataArea->Add(-1, 5);
	Colors_DataArea->Add(Colors_Holder_ID, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Colors_DataArea->Add(-1, 5);
	Colors_DataArea->Add(Colors_Holder_Palette, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Colors_DataArea->Add(-1, 5);
	Colors_DataArea->Add(Colors_Holder_Color, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Colors_DataArea->Add(-1, 5);
	Colors_DataArea->Add(Colors_Holder_MinimapColor, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Colors_DataArea->Add(-1, 5);
	Colors_DataArea->Add(Colors_Holder_Unknown1, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Colors_DataArea->Add(-1, 5);
	Colors_DataArea->Add(Colors_Holder_Unknown2, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Colors_DataArea->Add(-1, 5);
	Colors_DataArea->Add(Colors_Holder_Unknown3, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Colors_DataArea->Add(-1, 5);
	Colors_DataArea->Add(Colors_Holder_Unknown4, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Colors_DataArea->Add(-1, 5);
	Colors_DataArea->Add(Colors_Holder_Unknown5, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Colors_DataArea->Add(-1, 10);

	Colors_Main->Add(10, -1);
	Colors_Main->Add(Colors_ListArea, 1, wxEXPAND);
	Colors_Main->Add(10, -1);
//	Colors_Main->Add(-1, -1, 3, wxEXPAND);
	Colors_Main->Add(Colors_DataArea, 1, wxEXPAND);
	Colors_Main->AddStretchSpacer(2);
	Colors_Main->Add(10, -1);
	
	Colors_ID->Enable(false);

	Tab_PlayerColors->SetSizer(Colors_Main);
	
	Connect(Colors_Colors_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsSearch));
	Connect(Colors_Colors_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsSelect));
	Connect(Colors_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsAdd));
	Connect(Colors_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsDelete));
	Connect(Colors_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsCopy));
	Connect(Colors_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsPaste));
	Colors_Name->Connect(Colors_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);

}