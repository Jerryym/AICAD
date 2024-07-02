#pragma once

// Dialog_AIChat 对话框
class Dialog_AIChat : public CAcUiDialog
{
	DECLARE_DYNAMIC(Dialog_AIChat)

public:
	Dialog_AIChat(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dialog_AIChat();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Chat };
#endif

public:
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog() override;
	virtual BOOL PreTranslateMessage(MSG* pMsg) override;

	DECLARE_MESSAGE_MAP()

private:
	CRichEditCtrl m_RichEdit_Record;
	CEdit m_EditMsg;
	CButton m_Button_Send;
};
