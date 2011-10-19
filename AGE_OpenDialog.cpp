/* AGE_OpenDialog.cpp */

#include "AGE_OpenDialog.h"

AGE_OpenDialog::AGE_OpenDialog(wxWindow * parent, bool MustHaveDat)
: wxDialog(parent, -1, "Open files...", wxDefaultPosition, wxSize(500, 250), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxNO_DEFAULT)
{
	OpenArea = new wxBoxSizer(wxVERTICAL);
	MainOpen = new wxBoxSizer(wxHORIZONTAL);
	OpenDefaults = new wxBoxSizer(wxHORIZONTAL);
	OpenLayout = new wxFlexGridSizer(2, 2, 2);
	OpenButtons = new wxBoxSizer(wxHORIZONTAL);

	OpenButtonOK = new wxButton(this, wxID_OK, "OK");
	OpenButtonCancel = new wxButton(this, wxID_CANCEL, "Cancel");

	Button_DefaultAoE = new wxButton(this, wxID_ANY, "AoE Defaults");
	Button_DefaultRoR = new wxButton(this, wxID_ANY, "RoR Defaults");
	Button_DefaultAoK = new wxButton(this, wxID_ANY, "AoK Defaults");
	Button_DefaultTC = new wxButton(this, wxID_ANY, "TC Defaults");
	Button_DefaultSWGB = new wxButton(this, wxID_ANY, "SWGB Defaults");
	Button_DefaultCC = new wxButton(this, wxID_ANY, "CC Defaults");
//	Button_DefaultSWGB->Disable();
//	Button_DefaultCC->Disable();

	OpenDefaults->Add(Button_DefaultAoE, 1, wxEXPAND);
	OpenDefaults->Add(Button_DefaultRoR, 1, wxEXPAND);
	OpenDefaults->Add(Button_DefaultAoK, 1, wxEXPAND);
	OpenDefaults->Add(Button_DefaultTC, 1, wxEXPAND);
	OpenDefaults->Add(Button_DefaultSWGB, 1, wxEXPAND);
	OpenDefaults->Add(Button_DefaultCC, 1, wxEXPAND);

	Text_GenieVer = new wxStaticText(this, wxID_ANY, "      Genie Version:");
	CheckBox_GenieVer = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
	CheckBox_GenieVer->Append("Age of Empires");
	CheckBox_GenieVer->Append("Rise of Rome");
	CheckBox_GenieVer->Append("Age of Kings");
	CheckBox_GenieVer->Append("The Conquerors");
	CheckBox_GenieVer->Append("Star Wars Galactic Battlegrounds");
	CheckBox_GenieVer->Append("Clone Campaigns");

	DriveText = new wxStaticText(this, wxID_ANY, "      Drive Letter:");
	DriveLetterArea = new wxBoxSizer(wxVERTICAL);
	DriveLetterBox = new wxTextCtrl(this, wxID_ANY, "C", wxDefaultPosition, wxDefaultSize, 0/*, wxDefaultValidator, wxTextCtrlNameStr*/);
	Radio_DatFileLocation = new wxRadioButton(this, wxID_ANY, "Compressed Dat File (*.dat):", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	Path_DatFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Compressed Dat File (*.dat)|*.dat", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	Radio_UnzFileLocation = new wxRadioButton(this, wxID_ANY, "Decompressed Dat File (*.unz):");
	Path_UnzFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Decompressed Dat File (*.unz)|*.unz", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	Path_UnzFileLocation->Disable();
	Radio_ApfFileLocation = new wxRadioButton(this, wxID_ANY, "Patch File (*.apf):");
	Path_ApfFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Patch File (*.apf)|*.apf", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	Path_ApfFileLocation->Disable();
	Radio_NoFile = new wxRadioButton(this, wxID_ANY, "No Dat File");
	
	if(MustHaveDat)
	{
	    Radio_ApfFileLocation->Disable();
	    Radio_NoFile->Disable();
	}
	
	CheckBox_LangFileLocation = new wxCheckBox(this, wxID_ANY, "Language.dll Location:");
	CheckBox_LangFileLocation->SetValue(true);
	Path_LangFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Dynamic Link Library (*.dll)|*.dll", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	CheckBox_LangX1FileLocation = new wxCheckBox(this, wxID_ANY, "Language_x1.dll Location:");
	CheckBox_LangX1FileLocation->SetValue(true);
	Path_LangX1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Dynamic Link Library (*.dll)|*.dll", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	CheckBox_LangX1P1FileLocation = new wxCheckBox(this, wxID_ANY, "Language_x1_p1.dll Location:");
	CheckBox_LangX1P1FileLocation->SetValue(true);
	Path_LangX1P1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Dynamic Link Library (*.dll)|*.dll", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);

	wxString Path;
	Path = DriveLetterBox->GetValue();
	
	if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\Microsoft Games\\";
	}
	else
	{
	    Path += ":\\Program Files\\Microsoft Games\\";
	}

	CheckBox_GenieVer->SetSelection(3);
	Path_DatFileLocation->SetPath(wxString(Path + "Age of Empires II\\data\\Empires2_x1_p1.dat"));
	Path_UnzFileLocation->SetPath(wxT("TC.unz"));
	Path_LangFileLocation->SetPath(wxString(Path + "Age of Empires II\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "Age of Empires II\\language_x1.dll"));
	Path_LangX1P1FileLocation->SetPath(wxString(Path + "Age of Empires II\\language_x1_p1.dll"));
/*	
	CheckBox_LangFileLocation->SetValue(false);
	CheckBox_LangFileLocation->Show(false);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1FileLocation->Show(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->Show(false);
	Path_LangFileLocation->Show(false);
	Path_LangX1FileLocation->Show(false);
	Path_LangX1P1FileLocation->Show(false);
*/
	OpenLayout->Add(Text_GenieVer, 1, wxEXPAND);
	OpenLayout->Add(CheckBox_GenieVer, 1, wxEXPAND);
	OpenLayout->Add(DriveText, 1, wxEXPAND);
	DriveLetterArea->Add(DriveLetterBox, 0);
	DriveLetterArea->AddStretchSpacer(1);
	OpenLayout->Add(DriveLetterArea, 1, wxEXPAND);
	OpenLayout->AddSpacer(15);
	OpenLayout->AddSpacer(15);
	OpenLayout->Add(Radio_DatFileLocation, 1, wxEXPAND);
	OpenLayout->Add(Path_DatFileLocation, 1, wxEXPAND);
	OpenLayout->Add(Radio_UnzFileLocation, 1, wxEXPAND);
	OpenLayout->Add(Path_UnzFileLocation, 1, wxEXPAND);
	OpenLayout->Add(Radio_ApfFileLocation, 1, wxEXPAND);
	OpenLayout->Add(Path_ApfFileLocation, 1, wxEXPAND);
	OpenLayout->Add(Radio_NoFile, 1, wxEXPAND);
	OpenLayout->AddSpacer(15);
	OpenLayout->AddSpacer(15);
	OpenLayout->AddSpacer(15);
	OpenLayout->Add(CheckBox_LangFileLocation, 1, wxEXPAND);
	OpenLayout->Add(Path_LangFileLocation, 1, wxEXPAND);
	OpenLayout->Add(CheckBox_LangX1FileLocation, 1, wxEXPAND);
	OpenLayout->Add(Path_LangX1FileLocation, 1, wxEXPAND);
	OpenLayout->Add(CheckBox_LangX1P1FileLocation, 1, wxEXPAND);
	OpenLayout->Add(Path_LangX1P1FileLocation, 1, wxEXPAND);
	OpenLayout->AddSpacer(15);
	OpenLayout->AddSpacer(15);
//	OpenLayout->AddSpacer(0);
//	OpenLayout->AddSpacer(0);
//	OpenLayout->Add(chDrsFileLocation, 1, wxEXPAND);
//	OpenLayout->Add(fpDrsFileLocation, 1, wxEXPAND);
	
	OpenLayout->AddGrowableCol(1, 1);
	OpenLayout->AddGrowableRow(1, 1);
	OpenLayout->AddGrowableRow(6, 1);
	OpenLayout->AddGrowableRow(10, 1);

	OpenButtons->Add(OpenButtonOK, 1, wxEXPAND);
	OpenButtons->Add(OpenButtonCancel, 1, wxEXPAND);

	OpenArea->AddSpacer(5);
	OpenArea->Add(OpenDefaults, 0, wxALIGN_CENTRE);
	OpenArea->AddSpacer(15);
	OpenArea->Add(OpenLayout, 1, wxEXPAND);
	OpenArea->AddSpacer(15);
	OpenArea->Add(OpenButtons, 0, wxALIGN_RIGHT);
	OpenArea->AddSpacer(5);
	
	MainOpen->AddSpacer(5);
	MainOpen->Add(OpenArea, 1, wxEXPAND);
	MainOpen->AddSpacer(5);

	this->SetSizerAndFit(MainOpen);
	
	SetDefaultItem(OpenButtonOK);
	
	Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnOK));
	Connect(Button_DefaultAoE->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDefaultAoE));
	Connect(Button_DefaultRoR->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDefaultRoR));
	Connect(Button_DefaultAoK->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDefaultAoK));
	Connect(Button_DefaultTC->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDefaultTC));
	Connect(Button_DefaultSWGB->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDefaultSWGB));
	Connect(Button_DefaultCC->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDefaultCC));
	Connect(Radio_DatFileLocation->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(AGE_OpenDialog::OnChangeDatRadio));
	Connect(Radio_UnzFileLocation->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(AGE_OpenDialog::OnChangeDatRadio));
	Connect(Radio_ApfFileLocation->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(AGE_OpenDialog::OnChangeDatRadio));
	Connect(Radio_NoFile->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(AGE_OpenDialog::OnChangeDatRadio));
	Connect(CheckBox_LangFileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnSelectLang));
	Connect(CheckBox_LangX1FileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnSelectLangX1));
	Connect(CheckBox_LangX1P1FileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnSelectLangX1P1));
//	Connect(chDrsFileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnSelectDrs));
}

void AGE_OpenDialog::OnOK(wxCommandEvent& Event)
{
	if(Event.GetId() == Radio_DatFileLocation->GetId())
	{
		Path_DatFileLocation->Enable(true);
		Path_UnzFileLocation->Enable(false);
		Path_ApfFileLocation->Enable(false);
    }
	else if(Event.GetId() == Radio_UnzFileLocation->GetId())
	{
		Path_DatFileLocation->Enable(false);
		Path_UnzFileLocation->Enable(true);
		Path_ApfFileLocation->Enable(false);
    }
	else if(Event.GetId() == Radio_ApfFileLocation->GetId())
	{
		Path_DatFileLocation->Enable(false);
		Path_UnzFileLocation->Enable(false);
		Path_ApfFileLocation->Enable(true);
    }
	else
	{
		Path_DatFileLocation->Enable(false);
		Path_UnzFileLocation->Enable(false);
		Path_ApfFileLocation->Enable(false);
	}
	EndModal(wxID_OK);
}

void AGE_OpenDialog::OnDefaultAoE(wxCommandEvent& Event)
{
	wxString Path;
	Path = DriveLetterBox->GetValue();

	if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\Microsoft Games\\";
	}
	else
	{
	    Path += ":\\Program Files\\Microsoft Games\\";
	}

	CheckBox_GenieVer->SetSelection(0);
	Path_DatFileLocation->SetPath(wxString(Path + "Age of Empires\\data\\Empires.dat"));
	Path_UnzFileLocation->SetPath(wxT("AoE.unz"));
	Path_LangFileLocation->SetPath(wxString(Path + "Age of Empires\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxT(""));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	wxCommandEvent Selected(wxEVT_COMMAND_RADIOBUTTON_SELECTED, Radio_DatFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetInt(true);
	Selected.SetId(CheckBox_LangFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetInt(false);
	Selected.SetId(CheckBox_LangX1FileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1P1FileLocation->GetId());
	ProcessEvent(Selected);
}

void AGE_OpenDialog::OnDefaultRoR(wxCommandEvent& Event)
{
	wxString Path;
	Path = DriveLetterBox->GetValue();

	if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\Microsoft Games\\";
	}
	else
	{
	    Path += ":\\Program Files\\Microsoft Games\\";
	}

	CheckBox_GenieVer->SetSelection(1);
	Path_DatFileLocation->SetPath(wxString(Path + "Age of Empires\\data2\\Empires.dat"));
	Path_UnzFileLocation->SetPath(wxT("RoR.unz"));
	Path_LangFileLocation->SetPath(wxString(Path + "Age of Empires\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "Age of Empires\\languagex.dll"));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	wxCommandEvent Selected(wxEVT_COMMAND_RADIOBUTTON_SELECTED, Radio_DatFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetInt(true);
	Selected.SetId(CheckBox_LangFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1FileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetInt(false);
	Selected.SetId(CheckBox_LangX1P1FileLocation->GetId());
	ProcessEvent(Selected);
}

void AGE_OpenDialog::OnDefaultAoK(wxCommandEvent& Event)
{
	wxString Path;
	Path = DriveLetterBox->GetValue();

	if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\Microsoft Games\\";
	}
	else
	{
	    Path += ":\\Program Files\\Microsoft Games\\";
	}

	CheckBox_GenieVer->SetSelection(2);
	Path_DatFileLocation->SetPath(wxString(Path + "Age of Empires II\\data\\Empires2.dat"));
	Path_UnzFileLocation->SetPath(wxT("AoK.unz"));
	Path_LangFileLocation->SetPath(wxString(Path + "Age of Empires II\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxT(""));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	wxCommandEvent Selected(wxEVT_COMMAND_RADIOBUTTON_SELECTED, Radio_DatFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetInt(true);
	Selected.SetId(CheckBox_LangFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetInt(false);
	Selected.SetId(CheckBox_LangX1FileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1P1FileLocation->GetId());
	ProcessEvent(Selected);
}

void AGE_OpenDialog::OnDefaultTC(wxCommandEvent& Event)
{
	wxString Path;
	Path = DriveLetterBox->GetValue();

	if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\Microsoft Games\\";
	}
	else
	{
	    Path += ":\\Program Files\\Microsoft Games\\";
	}

	CheckBox_GenieVer->SetSelection(3);
	Path_DatFileLocation->SetPath(wxString(Path + "Age of Empires II\\data\\Empires2_x1_p1.dat"));
	Path_UnzFileLocation->SetPath(wxT("TC.unz"));
	Path_LangFileLocation->SetPath(wxString(Path + "Age of Empires II\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "Age of Empires II\\language_x1.dll"));
	Path_LangX1P1FileLocation->SetPath(wxString(Path + "Age of Empires II\\language_x1_p1.dll"));
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(true);
	wxCommandEvent Selected(wxEVT_COMMAND_RADIOBUTTON_SELECTED, Radio_DatFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetInt(true);
	Selected.SetId(CheckBox_LangFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1FileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1P1FileLocation->GetId());
	ProcessEvent(Selected);
}

void AGE_OpenDialog::OnDefaultSWGB(wxCommandEvent& Event)
{
	wxString Path;
	Path = DriveLetterBox->GetValue();

	if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\LucasArts\\Star Wars Galactic Battlegrounds Saga\\";
	}
	else
	{
	    Path += ":\\Program Files\\LucasArts\\Star Wars Galactic Battlegrounds Saga\\";
	}

	CheckBox_GenieVer->SetSelection(3);
	Path_DatFileLocation->SetPath(wxString(Path + "Game\\Data\\GENIE.DAT"));
	Path_UnzFileLocation->SetPath(wxT("SWGB.unz"));
	Path_LangFileLocation->SetPath(wxString(Path + "Game\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxT(""));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	wxCommandEvent Selected(wxEVT_COMMAND_RADIOBUTTON_SELECTED, Radio_DatFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetInt(true);
	Selected.SetId(CheckBox_LangFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetInt(false);
	Selected.SetId(CheckBox_LangX1FileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1P1FileLocation->GetId());
	ProcessEvent(Selected);
}

void AGE_OpenDialog::OnDefaultCC(wxCommandEvent& Event)
{
	wxString Path;
	Path = DriveLetterBox->GetValue();

	if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\LucasArts\\Star Wars Galactic Battlegrounds Saga\\";
	}
	else
	{
	    Path += ":\\Program Files\\LucasArts\\Star Wars Galactic Battlegrounds Saga\\";
	}

	CheckBox_GenieVer->SetSelection(3);
	Path_DatFileLocation->SetPath(wxString(Path + "Game\\Data\\genie_x1.dat"));
	Path_UnzFileLocation->SetPath(wxT("CC.unz"));
	Path_LangFileLocation->SetPath(wxString(Path + "Game\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "Game\\language_x1.dll"));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	wxCommandEvent Selected(wxEVT_COMMAND_RADIOBUTTON_SELECTED, Radio_DatFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetInt(true);
	Selected.SetId(CheckBox_LangFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1FileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetInt(false);
	Selected.SetId(CheckBox_LangX1P1FileLocation->GetId());
	ProcessEvent(Selected);
}

void AGE_OpenDialog::OnChangeDatRadio(wxCommandEvent& Event)
{
	if(Event.GetId() == Radio_DatFileLocation->GetId())
	{
		Path_DatFileLocation->Enable(true);
		Path_UnzFileLocation->Enable(false);
		Path_ApfFileLocation->Enable(false);
    }
	else if(Event.GetId() == Radio_UnzFileLocation->GetId())
	{
		Path_DatFileLocation->Enable(false);
		Path_UnzFileLocation->Enable(true);
		Path_ApfFileLocation->Enable(false);
    }
	else if(Event.GetId() == Radio_ApfFileLocation->GetId())
	{
		Path_DatFileLocation->Enable(false);
		Path_UnzFileLocation->Enable(false);
		Path_ApfFileLocation->Enable(true);
    }
	else
	{
		Path_DatFileLocation->Enable(false);
		Path_UnzFileLocation->Enable(false);
		Path_ApfFileLocation->Enable(false);
	}
}

void AGE_OpenDialog::OnSelectLang(wxCommandEvent& Event)
{
	if(Event.IsChecked())
	{
	    Path_LangFileLocation->Enable(true);
	}
	else
	{
	    Path_LangFileLocation->Enable(false);
	}
}

void AGE_OpenDialog::OnSelectLangX1(wxCommandEvent& Event)
{
	if(Event.IsChecked())
	{
	    Path_LangX1FileLocation->Enable(true);
	}
	else
	{
	    Path_LangX1FileLocation->Enable(false);
	}
}

void AGE_OpenDialog::OnSelectLangX1P1(wxCommandEvent& Event)
{
	if(Event.IsChecked())
	{
	    Path_LangX1P1FileLocation->Enable(true);
	}
	else
	{
	    Path_LangX1P1FileLocation->Enable(false);
	}
}
/*
void AGE_OpenDialog::OnSelectDrs(wxCommandEvent& Event)
{
	if(Event.IsChecked())
	{
	    fpDrsFileLocation->Enable(true);
	}
	else
	{
	    fpDrsFileLocation->Enable(false);
	}
}
*/