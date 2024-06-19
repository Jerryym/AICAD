#pragma once

/*
描    述：基本的AutoCAD命令

当前版本：v1.0
作   者：DHY
完成日期：2024/6/18

此代码对AutoCAD进行了二次开发，编写了一些自定义命令以便一键生成图形。
*/

/// @brief AICAD Command函数声明
namespace AICAD {

#define AICAD_COMMAND_Group _T("AICAD")

	//测试命令
	extern void HelloWorld();

	typedef double ads_point[3];

	template<typename T>
	struct is_ads_point : std::false_type {};

	template<>
	struct is_ads_point<ads_point> : std::true_type {};

	class CmdDrawPolyline {
	public:
		CmdDrawPolyline();

		void execute();

		template<typename T, typename U, typename V>
		static bool executeWithBool(T& pt, U& startPoint, V numSegments);

		static void command();
	};

	class CmdDrawline {
	public:
		CmdDrawline();

		void execute();

		template<typename T, typename U>
		static bool executeWithBool(T& startP, U& endP);

		static void command();
	};

	class CmdDrawCircle {
	public:
		CmdDrawCircle();

		void execute();

		template<typename T, typename U, typename V>
		static bool executeWithBool(T& center, U& vector, V radius);

		static void command();
	};

	class CmdDrawArc {
	public:
		CmdDrawArc();

		void execute();

		template<typename T, typename U, typename V, typename W>
		static bool execeuteWithBool(T& center, U radius, V startAngle, W endAngle);

		static void command();
	};

	class CmdDrawEllipse {
	public:
		CmdDrawEllipse();

		void execute();

		template<typename T, typename U, typename V, typename W>
		static bool executeWithBool(T& center, U& vector, V& majorAxis, W radiusRatio);

		static void command();
	};

	class CmdCreateText {
	public:
		CmdCreateText();

		void execute();

		template<typename T, typename U, typename V>
		static bool executeWithBool(T& point, U height, V rotation);

		static void command();
	};

	class CmdCreateLayer {
	public:
		CmdCreateLayer();

		void execute();

		template<typename T, typename U>
		static bool executeWithBool(T& layerName, U colorIndex);

		static void command();
	};

	class CmdCreateDimension {
	public:
		CmdCreateDimension();

		void execute();

		template<typename T, typename U>
		static bool executeWithBool(T& pt1, U& pt2);

		static void command();
	};

	class CmdSelectEntity {
	public:
		CmdSelectEntity();

		void execute();

		template<typename T>
		static bool executeWithBool(T& handleStr);

		static void command();
	};
}

