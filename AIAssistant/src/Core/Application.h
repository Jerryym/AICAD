#pragma once

namespace AICAD {

	/// @brief 初始化应用程序
	/// @param pAppID 
	/// @return 
	BOOL InitApplication(void* pAppID);
	/// @brief 卸载应用程序
	void UnLoadApplication();

	/// @brief Assistant应用程序
	class AIAssistant
	{
	public:
		/// @brief 加载命令组
		static void LoadCmdGroup();

	private:
		/// @brief 注册命令
		static void RegistCommand(LPCTSTR cmdGroup, LPCTSTR cmdInt, LPCTSTR cmdLoc, const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);
	};

}

