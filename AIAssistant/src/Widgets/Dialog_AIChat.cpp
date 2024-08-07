// Dialog_AIChat.cpp: 实现文件
#include "StdAfx.h"
#include "Dialog_AIChat.h"

// Dialog_AIChat 对话框
IMPLEMENT_DYNAMIC(Dialog_AIChat, CAcUiDialog)
Dialog_AIChat::Dialog_AIChat(CWnd* pParent /*=nullptr*/)
	: CAcUiDialog(IDD_DIALOG_Chat, pParent)
{

}

Dialog_AIChat::~Dialog_AIChat()
{
}

void Dialog_AIChat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT_Record, m_RichEdit_Record);
	DDX_Control(pDX, IDC_EDIT_Msg, m_EditMsg);
	DDX_Control(pDX, IDC_BUTTON_Send, m_Button_Send);
}

BOOL Dialog_AIChat::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

BOOL Dialog_AIChat::PreTranslateMessage(MSG* pMsg)
{
	//屏蔽ESC键, 防止对话框消失
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		//不做任何操作
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(Dialog_AIChat, CAcUiDialog)
	ON_BN_CLICKED(IDC_BUTTON_Send, &Dialog_AIChat::OnBnClickedButtonSend)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// Dialog_AIChat 消息处理程序
void Dialog_AIChat::OnBnClickedButtonSend()
{
	CString SMsg;
	m_EditMsg.GetWindowTextW(SMsg);
	SMsg.TrimLeft();
	SMsg.TrimRight();
	if (SMsg.IsEmpty() == true)
	{
		return;
	}

	CString SRecord;
	SRecord = L"You: " + SMsg;
	m_EditMsg.SetWindowTextW(L"");

	int nLength = m_RichEdit_Record.GetWindowTextLength();
	m_RichEdit_Record.SetSel(nLength, -1);
	m_RichEdit_Record.ReplaceSel(SRecord + "\n");
}

void Dialog_AIChat::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rect, RecordRect, EditRect, ButtonRect;
	GetClientRect(&rect);
	m_RichEdit_Record.GetWindowRect(&RecordRect);
	m_EditMsg.GetWindowRect(&EditRect);
	m_Button_Send.GetWindowRect(&ButtonRect);

	m_RichEdit_Record.SetWindowPos(this, 2, 2, rect.Width() - 5, RecordRect.Height(), SWP_NOZORDER);
	m_EditMsg.SetWindowPos(this, 2, RecordRect.Height() + 5, rect.Width() - 5, EditRect.Height(), SWP_NOZORDER);
	m_Button_Send.SetWindowPos(this, rect.Width() - ButtonRect.Width() - 5, RecordRect.Height() + EditRect.Height() + 5 , ButtonRect.Width(), ButtonRect.Height(), SWP_NOZORDER);
}
