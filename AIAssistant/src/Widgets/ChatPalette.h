#pragma once
#pragma comment(lib, "uxtheme.lib")

#include "Dialog_AIChat.h"

/// @brief AI对话面板
class ChatPalette : public CAdUiPalette
{
	DECLARE_DYNAMIC(ChatPalette)
public:
	ChatPalette(HINSTANCE hInstance = NULL);
	virtual ~ChatPalette();

	virtual void OnSetActive();
	virtual bool CanFrameworkTakeFocus();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:
	Dialog_AIChat* m_pChildDlg = nullptr;
};


