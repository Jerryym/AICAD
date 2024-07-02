#pragma once

// Dialog_Login 对话框
class Dialog_Login : public CDialog
{
	DECLARE_DYNAMIC(Dialog_Login)

public:
	Dialog_Login(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dialog_Login();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Login };
#endif

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelchangeComboLLMType();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog() override;

	void InitWgt();

	DECLARE_MESSAGE_MAP()

private:
	// 后端大模型名称
	CString m_Combo_LLMName;
	// API_KEY
	CString m_SApiKey;
};
