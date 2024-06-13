#include "StdAfx.h"
#include "Application.h"

#include "Commands/AICAD_Command.h"

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
	}
	
	void AIAssistant::LoadCmdGroup()
	{
		RegistCommand(AICAD_COMMAND_Group, _T("Test"), _T("Test"), ACRX_CMD_MODAL, AICAD::HelloWorld);
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
