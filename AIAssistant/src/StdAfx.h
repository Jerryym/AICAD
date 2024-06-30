#pragma once

#define _WIN32_WINNT 0x0600

//-----------------------------------------------------------------------------
//- Standard headers
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//- MFC headers
#include <afxwin.h>
#include <afxext.h>         // MFC extensions
#include <afxole.h>
#include <afxdisp.h>        // MFC OLE automation classes
#include <afxtempl.h>
#include <afxdlgs.h>

#ifndef _AFX_NO_AFXCMN_SUPPORT
	#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//- Include ObjectDBX/ObjectARX headers
#include <arxHeaders.h>
#include <ads.h>
#include <rxmfcapi.h>
#include <AcExtensionModule.h>
#include <adui.h>
#include <acui.h>
//-----------------------------------------------------------------------------

#include "resource.h"
#include <AICAD.h>

//代替项目属性->连接器->输入->模块定义文件：[..\..\ObjectArx\ObjectArx2010\inc\AcRxDefault.def] [..\..\ObjectArx\ObjectArx2013\inc\AcRxDefault.def]
#pragma comment(linker, "/export:acrxEntryPoint,PRIVATE")
