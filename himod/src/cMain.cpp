#include "cMain.h"

#include "expresly.h"

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6) {
  std::ostringstream out;
  out.precision(n);
  out << std::fixed << a_value;
  return out.str();
}

cMain::cMain(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
  m_inpExpression = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(150, -1));
  m_inpExpression->SetWindowStyleFlag(wxTE_PROCESS_ENTER);
  m_inpExpression->SetHint("Enter Expression: ");

  m_lblText = new wxStaticText(this, wxID_ANY, " = None");

  wxBoxSizer* exp_sizer = new wxBoxSizer(wxHORIZONTAL);
  exp_sizer->Add(m_inpExpression);
  exp_sizer->Add(m_lblText, wxSizerFlags().CenterVertical());

  wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
  topsizer->AddStretchSpacer();
  topsizer->Add(exp_sizer, wxSizerFlags().Center());
  topsizer->AddStretchSpacer();

  SetSizer(topsizer);

  m_inpExpression->Bind(wxEVT_TEXT_ENTER, [=](wxCommandEvent&) {
    double value = 0;
    try {
      value = expresly::expression::eval({m_inpExpression->GetValue()});
    } catch (const std::exception& e) {
      m_lblText->SetLabelText(std::string{e.what()}.insert(0, " Error: "));
      topsizer->Layout();
      return;
    }
    m_lblText->SetLabelText(
        to_string_with_precision(value, 2).insert(0, " = "));
    topsizer->Layout();
  });
}

cMain::~cMain() {}
