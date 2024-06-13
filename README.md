# AICAD

AICAD是一个基于通用大语言模型和AutoCAD平台开发的应用程序。该项目目标为，通过对LLM进行微调，实现自然语言指令的识别和执行，使其能够理解并执行用户的自然语言指令，简化用户操作流程。

## Environment

* **IDE**：Visual Studio 2022
* **CAD Version**：AutoCAD2021、AutoCAD2022
* **ObjectArx Version**：[ObjectArx2022](https://download.autodesk.com/esd/objectarx/2022/objectarx_for_autocad_2022_win_64bit_dlm.sfx.exe)

## Getting Started

1. 下载[ObjectArx2022](https://download.autodesk.com/esd/objectarx/2022/objectarx_for_autocad_2022_win_64bit_dlm.sfx.exe)，并安装至 `vendor`文件夹中。
2. 在Visual Studio中打开 `AICAD.sln`，并编译项目。
3. 在AutoCAD2021或AutoCAD2022中，加载 `AIAssistant.arx`。

## Dependencies

* MFC
* ObjectArx
