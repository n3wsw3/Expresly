#pragma once
#include <string>

#include "wx/wx.h"

class cMain : public wxFrame {
 public:
  cMain(const wxString& title);
  ~cMain();

 private:
	 wxStaticText* m_lblText;
	 wxTextCtrl* m_inpExpression;
};