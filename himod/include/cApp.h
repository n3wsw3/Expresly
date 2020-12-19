#pragma once

#include <memory>

#include "wx/wx.h"

#include "cMain.h"

class cApp : public wxApp
{
public:
    cApp();
    ~cApp();

private:
	cMain* m_frame1;

public:
		virtual bool OnInit() override;
};