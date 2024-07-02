// Dialog_Login.cpp: 实现文件
#include "StdAfx.h"
#include "Dialog_Login.h"
#include "MainPaletteSet.h"

// Dialog_Login 对话框
IMPLEMENT_DYNAMIC(Dialog_Login, CDialog)
Dialog_Login::Dialog_Login(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_Login, pParent), m_Combo_LLMName(L"gemini-1.5-flash"), m_SApiKey(_T(""))
{
}

Dialog_Login::~Dialog_Login()
{
}

void Dialog_Login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_LLMType, m_Combo_LLMName);
	DDX_Text(pDX, IDC_EDIT_APIKEY, m_SApiKey);
}

BOOL Dialog_Login::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitWgt();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_Login::InitWgt()
{
	CComboBox* pComboxBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_LLMType));
	if (pComboxBox == nullptr)
	{
		return;
	}
	pComboxBox->AddString(L"gemini-1.5-flash");
	pComboxBox->AddString(L"gemini-1.5-pro");
	pComboxBox->SetCurSel(0);
	m_SApiKey = L"";
}

BEGIN_MESSAGE_MAP(Dialog_Login, CDialog)
	ON_BN_CLICKED(IDOK, &Dialog_Login::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Dialog_Login::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_LLMType, &Dialog_Login::OnCbnSelchangeComboLLMType)
END_MESSAGE_MAP()

// Dialog_Login 消息处理程序
void Dialog_Login::OnBnClickedOk()
{
	UpdateData(TRUE);
	//if (m_SApiKey.IsEmpty() == true)
	//{
	//	MessageBox(L"Api_Key is empty, please enter Api_Key", L"ALCAD", MB_ICONEXCLAMATION);
	//	return;
	//}
	
	//关闭对话框
	CDialog::OnOK();

	//打开AI聊天对话框
	CMDIFrameWnd* pAcadFrm = acedGetAcadFrame();
	if (G_pMainPane != NULL && G_pMainPane->IsWindowVisible() == TRUE)
	{
		G_pMainPane->close();
	}
	else
	{
		// 清理无效指针
		SAFE_DELETE(G_pMainPane);
		G_pMainPane = new MainPaletteSet;
		CAcModuleResourceOverride AcResources;
		if (G_pMainPane->Create(pAcadFrm) != TRUE)
		{
			AfxMessageBox(_T("Failed to open AICAD window!"));
			return;
		}
		G_pMainPane->EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
		G_pMainPane->RestoreControlBar();
		pAcadFrm->ShowControlBar(G_pMainPane, TRUE, FALSE);
	}
	return;
}

void Dialog_Login::OnBnClickedCancel()
{
	CDialog::OnCancel();
}

void Dialog_Login::OnCbnSelchangeComboLLMType()
{
	m_SApiKey = L"";
}
