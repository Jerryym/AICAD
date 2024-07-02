#include "StdAfx.h"
#include "Application.h"

#include "Commands/AICAD_Command.h"
#include "Widgets/MainPaletteSet.h"

#if _MSC_VER >= 1920
#pragma comment(lib, "AcPal.lib")
#pragma comment(lib, "acgeoment.lib")
#endif

HINSTANCE _hdllInstance;
AC_IMPLEMENT_EXTENSION_MODULE(AIAssistant_DLL);

namespace AICAD {

	BOOL InitApplication(void* pAppID)
	{
		// Register the command group.
		AIAssistant::LoadCmdGroup();
		acutPrintf(_T("\nAIAssistant loaded."));
		return TRUE;
	}

	void UnLoadApplication()
	{
		acedRegCmds->removeGroup(AICAD_COMMAND_Group);
		acutPrintf(_T("\nAIAssistant unloaded."));

		if (G_pMainPane)
		{
			if (G_pMainPane->m_hWnd != NULL && IsWindow(G_pMainPane->GetSafeHwnd()))
			{
				CMDIFrameWnd* pAcadFrame = acedGetAcadFrame();
				pAcadFrame->RemoveControlBar(G_pMainPane);
				pAcadFrame->RecalcLayout();
				G_pMainPane->DestroyWindow();
			}
			SAFE_DELETE(G_pMainPane);
		}
	}

	void AIAssistant::LoadCmdGroup()
	{
		RegistCommand(AICAD_COMMAND_Group, _T("EI_StartPanel"), _T("EI_StartPanel"), ACRX_CMD_MODAL, AICAD::CmdStartPanel);
		RegistCommand(AICAD_COMMAND_Group, _T("EI_DrawPolyline"), _T("EI_DrawPolyline"), ACRX_CMD_MODAL, AICAD::CmdDrawPolyline::command);
		RegistCommand(AICAD_COMMAND_Group, _T("EI_DrawPolyline"), _T("EI_DrawPolyline"), ACRX_CMD_MODAL, AICAD::CmdDrawPolyline::command);
		RegistCommand(AICAD_COMMAND_Group, _T("EI_Drawline"), _T("EI_Drawline"), ACRX_CMD_MODAL, AICAD::CmdDrawline::command);
		RegistCommand(AICAD_COMMAND_Group, _T("EI_DrawCircle"), _T("EI_DrawCircle"), ACRX_CMD_MODAL, AICAD::CmdDrawCircle::command);
		RegistCommand(AICAD_COMMAND_Group, _T("EI_DrawArc"), _T("EI_DrawArc"), ACRX_CMD_MODAL, AICAD::CmdDrawArc::command);
		RegistCommand(AICAD_COMMAND_Group, _T("EI_DrawEllipse"), _T("EI_DrawEllipse"), ACRX_CMD_MODAL, AICAD::CmdDrawEllipse::command);
		RegistCommand(AICAD_COMMAND_Group, _T("EI_CreateText"), _T("EI_CreateText"), ACRX_CMD_MODAL, AICAD::CmdCreateText::command);
		RegistCommand(AICAD_COMMAND_Group, _T("EI_CreateLayer"), _T("EI_CreateLayer"), ACRX_CMD_MODAL, AICAD::CmdCreateLayer::command);
		RegistCommand(AICAD_COMMAND_Group, _T("EI_CreateDimension"), _T("EI_CreateDimension"), ACRX_CMD_MODAL, AICAD::CmdCreateDimension::command);
		RegistCommand(AICAD_COMMAND_Group, _T("EI_SelectEntity"), _T("EI_SelectEntity"), ACRX_CMD_MODAL, AICAD::CmdSelectEntity::command);
	}

	void AIAssistant::RegistCommand(LPCTSTR cmdGroup, LPCTSTR cmdInt, LPCTSTR cmdLoc, const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal)
	{
		TCHAR cmdLocRes[65];
		if (idLocal != -1)
		{
			// HMODULE hModule = GetModuleHandle(GSEicadPMArxName);
			// Load strings from the string table and register the command.
			::LoadString(_hdllInstance, idLocal, cmdLocRes, 64);
			acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLocRes, cmdFlags, cmdProc);
		}
		else
		{
			// idLocal is -1, so the 'hard coded' localized function name is used.
			acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLoc, cmdFlags, cmdProc);
		}
		return;
	}
}

/////////////////////////////////////////////////////////////////////////////
// DLL EntryPoint 
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_hdllInstance = hInstance;
		// Extension DLL one time initialization
		AIAssistant_DLL.AttachInstance(hInstance);
		//InitAcUiDLL();
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		// Terminate the library before destructors are called
		AIAssistant_DLL.DetachInstance();
	}
	return TRUE;    // ok
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ObjectARX EntryPoint
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	AcRxDynamicLinker* pLinker = acrxDynamicLinker;
	switch (msg)
	{
	case AcRx::kInitAppMsg:
	{
		pLinker->unlockApplication(pkt);
		pLinker->registerAppMDIAware(pkt);
		if (AICAD::InitApplication(pkt) != TRUE)
		{
			return AcRx::kRetError;
		}
		break;
	}
	case AcRx::kQuitMsg:
		AICAD::UnLoadApplication();
		break;
	case AcRx::kUnloadAppMsg:
		AICAD::UnLoadApplication();
		break;
	}
	return AcRx::kRetOK;
}
/////////////////////////////////////////////////////////////////////////////
