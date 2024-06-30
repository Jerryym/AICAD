#include "StdAfx.h"
#include "MainPaletteSet.h"
#include "ChatPalette.h"

MainPaletteSet* G_pMainPane = nullptr;

// {26C23766-D839-4AB7-8B4B-FF9CFED4BA06}
static const GUID g_clsidPane = { 0x26c23766, 0xd839, 0x4ab7, { 0x8b, 0x4b, 0xff, 0x9c, 0xfe, 0xd4, 0xba, 0x6 } };

// MainPane 对话框
IMPLEMENT_DYNAMIC(MainPaletteSet, CAdUiPaletteSet)
MainPaletteSet::MainPaletteSet()
	:CAdUiPaletteSet(0)
{
}

MainPaletteSet::~MainPaletteSet()
{
}

bool MainPaletteSet::Create(CWnd* pwndParent)
{
	// 切换资源
	HINSTANCE hRes = AfxGetResourceHandle();
	AfxSetResourceHandle(_hdllInstance);

	SetToolID(&g_clsidPane);
	if (!CAdUiPaletteSet::Create(L"AICAD", WS_VISIBLE | WS_CHILD | CBRS_FLOATING,
		CRect(0, 0, 300, 500), pwndParent,
		PSS_SNAP |					// 自动吸附
		PSS_PROPERTIES_MENU |		// 右键菜单
		PSS_CLOSE_BUTTON |			// 有关闭按钮
		PSS_AUTO_ROLLUP				// 自动伸缩
	))
	{
		return false;
	}

	// 切换回资源
	AfxSetResourceHandle(hRes);

	//创建AI对话面板
	m_pChatPalette = new ChatPalette;
	this->AddPalette(m_pChatPalette);

	//显示面板
	G_pMainPane->EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
	G_pMainPane->RestoreControlBar();

	return true;
}

void MainPaletteSet::close()
{
	if (G_pMainPane == NULL)	return;

	// 检测是否需要清理
	bool bShouldClean = true;
	bool (*pfnAcadIsQuitting)() = NULL;

	*(FARPROC*)&pfnAcadIsQuitting = GetProcAddress(GetModuleHandle(NULL), "?AcadIsQuitting@@YA_NXZ");

	if (pfnAcadIsQuitting)
		bShouldClean = !pfnAcadIsQuitting();
	else
	{
		CMDIFrameWnd* pAcadFrm = acedGetAcadFrame();
		bShouldClean = (pAcadFrm != NULL && IsWindow(pAcadFrm->GetSafeHwnd()));
	}

	// 主面板实例指针有效
	if (bShouldClean && G_pMainPane != NULL)
	{
		// 主面板实例的窗口句柄有效
		if (::IsWindow(G_pMainPane->GetSafeHwnd()))
		{
			AdUiSaveDockingToolPositions(); // 在CAD激活时显式卸载面板前,需要强制保存面板状态到注册表
			G_pMainPane->DestroyWindow();
		}
		delete G_pMainPane;
		G_pMainPane = 0;

		acedGetAcadFrame()->SetFocus();
		acedGetAcadDwgView()->SetFocus();
	}
}

void MainPaletteSet::GetMinimumSize(CSize& size)
{
	//调用默认实现
	CAdUiPaletteSet::GetMinimumSize(size);
}

void MainPaletteSet::GetMaximumSize(CSize& size)
{
	//调用默认实现
	CAdUiPaletteSet::GetMaximumSize(size);
}

BEGIN_MESSAGE_MAP(MainPaletteSet, CAdUiPaletteSet)
END_MESSAGE_MAP()

// MainPane 消息处理程序
