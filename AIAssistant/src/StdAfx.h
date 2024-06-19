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
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//- Include ObjectDBX/ObjectARX headers
//- Uncomment one of the following lines to bring a given library in your project.
//#define _BREP_SUPPORT_			//- Support for the BRep API
//#define _HLR_SUPPORT_				//- Support for the Hidden Line Removal API
//#define _AMODELER_SUPPORT_		//- Support for the AModeler API
//#define _ASE_SUPPORT_				//- Support for the ASI/ASE API
//#define _RENDER_SUPPORT_			//- Support for the AutoCAD Render API
//#define _ARX_CUSTOM_DRAG_N_DROP_	//- Support for the ObjectARX Drag'n Drop API
//#define _INC_LEAGACY_HEADERS_		//- Include legacy headers in this project
#include <arxHeaders.h>
#include <AcExtensionModule.h>
//-----------------------------------------------------------------------------

//代替项目属性->连接器->输入->模块定义文件：[..\..\ObjectArx\ObjectArx2010\inc\AcRxDefault.def] [..\..\ObjectArx\ObjectArx2013\inc\AcRxDefault.def]
#pragma comment(linker, "/export:acrxEntryPoint,PRIVATE")
