#include "StdAfx.h"
#include "ChatPalette.h"
#include <resource.h>

IMPLEMENT_DYNAMIC(ChatPalette, CAdUiPalette)
ChatPalette::ChatPalette(HINSTANCE hInstance)
	:CAdUiPalette()
{
	SetName(L"AIAssistant");
}

ChatPalette::~ChatPalette()
{
	m_pChildDlg->DestroyWindow();
}

void ChatPalette::OnSetActive()
{
	CAdUiPalette::OnSetActive();
}

bool ChatPalette::CanFrameworkTakeFocus()
{
	CRect rc;
	GetWindowRect(&rc);
	CPoint pt(GetMessagePos());
	return rc.PtInRect(pt) ? false : true;
}

BEGIN_MESSAGE_MAP(ChatPalette, CAdUiPalette)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// ChatPalette 消息处理程序
int ChatPalette::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CAdUiPalette::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	if (m_pChildDlg == nullptr)
	{
		m_pChildDlg = new Dialog_AIChat;
		if (m_pChildDlg->Create(IDD_DIALOG_Chat, this) != TRUE)
		{
			return -1;
		}
		CRect rect;
		GetWindowRect(&rect);
		m_pChildDlg->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
		return 0;
	}
	return -1;
}

void ChatPalette::OnSize(UINT nType, int cx, int cy)
{
	CAdUiPalette::OnSize(nType, cx, cy);
	if (::IsWindow(m_pChildDlg->GetSafeHwnd()))
	{
		m_pChildDlg->MoveWindow(2, 2, cx - 2 * 2, cy - 2 * 2, TRUE);
	}
}
