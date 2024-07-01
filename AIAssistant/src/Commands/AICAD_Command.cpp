#include "StdAfx.h"
#include "AICAD_Command.h"

#include "Widgets/Dialog_Login.h"
#include "Widgets/MainPaletteSet.h"

#define PI 3.14159265

namespace AICAD {

	CmdDrawPolyline::CmdDrawPolyline()
	{
	}

	template<typename T, typename U, typename V>
	bool CmdDrawPolyline::executeWithBool(T& pt, U& startPoint, V numSegments)
	{
		static_assert(is_ads_point<T>::pt, "pt must be an ads_point.");
		static_assert(is_ads_point<U>::startPoint, "startPoint must be an ads_point.");
		static_assert(std::is_integral<V>::numSegments, "numSegments must be an integral type.");

		acutPrintf(_T("Enter the number of segments: "));
		if (acedGetInt(_T("\nNumber of segments: "), &numSegments) != RTNORM || numSegments < 1)
		{
			acutPrintf(_T("Invalid number of segments.\n"));
			return false;
		}

		int ret = acedGetPoint(NULL, _T("Please specify the start point: "), startPoint);
		if (ret != RTNORM)
		{
			acutPrintf(_T("No valid start point provided.\n"));
			return false;
		}

		AcDbPolyline* pPoly = new AcDbPolyline();
		pPoly->addVertexAt(0, AcGePoint2d(startPoint[X], startPoint[Y]));

		for (int i = 1; i <= numSegments; ++i)
		{
			ret = acedGetPoint(startPoint, _T("Specify next point: "), pt);
			if (ret != RTNORM)
			{
				delete pPoly;
				acutPrintf(_T("Failed to get a valid point.\n"));
				return false;;
			}
			pPoly->addVertexAt(i, AcGePoint2d(pt[X], pt[Y]));
			startPoint[X] = pt[X];
			startPoint[Y] = pt[Y];
		}

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		pBlockTableRecord->appendAcDbEntity(pPoly);

		pPoly->close();
		pBlockTableRecord->close();

		return true;
	}

	void CmdDrawPolyline::execute()
	{
		ads_point pt;
		ads_point startPoint;

		int numSegments = 0;
		acutPrintf(_T("Enter the number of segments: "));
		if (acedGetInt(_T("\nNumber of segments: "), &numSegments) != RTNORM || numSegments < 1)
		{
			acutPrintf(_T("Invalid number of segments.\n"));
			return;
		}

		int ret = acedGetPoint(NULL, _T("Please specify the start point: "), startPoint);
		if (ret != RTNORM)
		{
			acutPrintf(_T("No valid start point provided.\n"));
			return;
		}

		AcDbPolyline* pPoly = new AcDbPolyline();
		pPoly->addVertexAt(0, AcGePoint2d(startPoint[X], startPoint[Y]));

		for (int i = 1; i <= numSegments; ++i)
		{
			ret = acedGetPoint(startPoint, _T("Specify next point: "), pt);
			if (ret != RTNORM)
			{
				delete pPoly;
				acutPrintf(_T("Failed to get a valid point.\n"));
				return;
			}
			pPoly->addVertexAt(i, AcGePoint2d(pt[X], pt[Y]));
			startPoint[X] = pt[X];
			startPoint[Y] = pt[Y];
		}

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		pBlockTableRecord->appendAcDbEntity(pPoly);

		pPoly->close();
		pBlockTableRecord->close();
	}

	void CmdDrawPolyline::command()
	{
		CmdDrawPolyline cmd;
		cmd.execute();
	}


	CmdDrawline::CmdDrawline()
	{
	}

	template<typename T, typename U>
	bool CmdDrawline::executeWithBool(T& startP, U& endP)
	{
		static_assert(is_ads_point<T>::startP, "startP must be an ads_point.");
		static_assert(is_ads_point<U>::endP, "endP must be an ads_point.");

		AcGePoint3d startPoint;
		AcGePoint3d endPoint;

		acedInitGet(RSG_NONULL, _T("Close"));

		if (acedGetPoint(NULL, _T("Please enter the start point: "), startP) == RTNORM)
		{
			startPoint.x = startP[0];
			startPoint.y = startP[1];
			startPoint.z = startP[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		if (acedGetPoint(NULL, _T("Please enter the end point: "), endP) == RTNORM)
		{
			endPoint.x = endP[0];
			endPoint.y = endP[1];
			endPoint.z = endP[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		AcDbLine* pLine = new AcDbLine(startPoint, endPoint);

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		pBlockTableRecord->appendAcDbEntity(pLine);

		pLine->close();
		pBlockTableRecord->close();

		return true;
	}

	void CmdDrawline::execute()
	{
		AcGePoint3d startPoint;
		ads_point startP;
		AcGePoint3d endPoint;
		ads_point endP;

		acedInitGet(RSG_NONULL, _T("Close"));

		if (acedGetPoint(NULL, _T("Please enter the start point: "), startP) == RTNORM)
		{
			startPoint.x = startP[0];
			startPoint.y = startP[1];
			startPoint.z = startP[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		if (acedGetPoint(NULL, _T("Please enter the end point: "), endP) == RTNORM)
		{
			endPoint.x = endP[0];
			endPoint.y = endP[1];
			endPoint.z = endP[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		AcDbLine* pLine = new AcDbLine(startPoint, endPoint);

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		pBlockTableRecord->appendAcDbEntity(pLine);

		pLine->close();
		pBlockTableRecord->close();
	}

	void CmdDrawline::command()
	{
		CmdDrawline cmd;
		cmd.execute();
	}


	CmdDrawCircle::CmdDrawCircle()
	{
	}

	template<typename T, typename U, typename V>
	bool CmdDrawCircle::executeWithBool(T& center, U& vector, V radius)
	{
		static_assert(is_ads_point<T>::center, "center must be an ads_point.");
		static_assert(is_ads_point<U>::vector, "vector must be an ads_point.");
		static_assert(std::is_same<V, double>::radius, "radius must be a double.");

		AcGePoint3d pCenter;
		AcGePoint3d pVector;

		if (acedGetPoint(NULL, _T("Please enter the center of the circle: "), center) == RTNORM)
		{
			pCenter.x = center[0];
			pCenter.y = center[1];
			pCenter.z = center[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		if (acedGetPoint(NULL, _T("Please enter the vector of the circle: "), vector) == RTNORM)
		{
			pVector.x = vector[0];
			pVector.y = vector[1];
			pVector.z = vector[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		if (acedGetReal(_T("Please enter the radius of the circle: "), &radius) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		AcDbCircle* pCircle = new AcDbCircle(pCenter, pVector, radius);

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		pBlockTableRecord->appendAcDbEntity(pCircle);

		pCircle->close();
		pBlockTableRecord->close();

		return true;
	}

	void CmdDrawCircle::execute()
	{
		ads_point center;
		AcGePoint3d pCenter;
		ads_point vector;
		AcGeVector3d pVector;
		double radius;

		if (acedGetPoint(NULL, _T("Please enter the center of the circle: "), center) == RTNORM)
		{
			pCenter.x = center[0];
			pCenter.y = center[1];
			pCenter.z = center[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		if (acedGetPoint(NULL, _T("Please enter the vector of the circle: "), vector) == RTNORM)
		{
			pVector.x = vector[0];
			pVector.y = vector[1];
			pVector.z = vector[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		if (acedGetReal(_T("Please enter the radius of the circle: "), &radius) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		AcDbCircle* pCircle = new AcDbCircle(pCenter, pVector, radius);

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		pBlockTableRecord->appendAcDbEntity(pCircle);

		pCircle->close();
		pBlockTableRecord->close();
	}

	void CmdDrawCircle::command()
	{
		CmdDrawCircle cmd;
		cmd.execute();
	}


	CmdDrawArc::CmdDrawArc()
	{
	}

	template<typename T, typename U, typename V, typename W>
	bool CmdDrawArc::execeuteWithBool(T& center, U radius, V startAngle, W endAngle)
	{
		static_assert(is_ads_point<T>::center, "center must be an ads_point.");
		static_assert(std::is_same<T, double>::radius, "radius must be a double.");
		static_assert(std::is_same<T, double>::startAngle, "start angle must be a double.");
		static_assert(std::is_same<T, double>::endAngle, "end angle must be a double.");

		AcGePoint3d pCenter;

		if (acedGetPoint(NULL, _T("Please enter the center of the arc: "), center) == RTNORM)
		{
			pCenter.x = center[0];
			pCenter.y = center[1];
			pCenter.z = center[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		if (acedGetReal(_T("Please enter the radius of the arc: n"), &radius) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		if (acedGetReal(_T("Please enter the start angle of the arc: "), &startAngle) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		if (acedGetReal(_T("Please enter the end angle of the arc: "), &endAngle) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		AcDbArc* pArc = new AcDbArc(pCenter, radius, startAngle * PI / 180, endAngle * PI / 180);

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		pBlockTableRecord->appendAcDbEntity(pArc);

		pArc->close();
		pBlockTableRecord->close();

		return true;
	}

	void CmdDrawArc::execute()
	{
		ads_point center;
		AcGePoint3d pCenter;
		double radius;
		double startAngle;
		double endAngle;

		if (acedGetPoint(NULL, _T("Please enter the center of the arc: "), center) == RTNORM)
		{
			pCenter.x = center[0];
			pCenter.y = center[1];
			pCenter.z = center[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		if (acedGetReal(_T("Please enter the radius of the arc: n"), &radius) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		if (acedGetReal(_T("Please enter the start angle of the arc: "), &startAngle) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		if (acedGetReal(_T("Please enter the end angle of the arc: "), &endAngle) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		AcDbArc* pArc = new AcDbArc(pCenter, radius, startAngle * PI / 180, endAngle * PI / 180);

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		pBlockTableRecord->appendAcDbEntity(pArc);

		pArc->close();
		pBlockTableRecord->close();
	}

	void CmdDrawArc::command()
	{
		CmdDrawArc cmd;
		cmd.execute();
	}


	CmdDrawEllipse::CmdDrawEllipse()
	{
	}

	template<typename T, typename U, typename V, typename W>
	bool CmdDrawEllipse::executeWithBool(T& center, U& vector, V& majorAxis, W radiusRatio)
	{
		static_assert(is_ads_point<T>::center, "center must be an ads_point.");
		static_assert(is_ads_point<T>::vector, "radius must be an ads_point.");
		static_assert(is_ads_point<T>::majorAxis, "major axis must be an ads_point.");
		static_assert(std::is_same<T, double>::radiusRatio, "radius ratio must be a double.");

		AcGePoint3d pCenter;
		AcGeVector3d pVector;
		AcGeVector3d pMajorAxis;

		if (acedGetPoint(NULL, _T("Please enter the center of the ellipse: "), center) == RTNORM)
		{
			pCenter.x = center[0];
			pCenter.y = center[1];
			pCenter.z = center[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		if (acedGetReal(_T("Please enter the radius ratio of the ellipse: "), &radiusRatio) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		if (acedGetPoint(NULL, _T("Please enter the vector of the ellipse: "), vector) == RTNORM)
		{
			pVector.x = vector[0];
			pVector.y = vector[1];
			pVector.z = vector[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		if (acedGetPoint(NULL, _T("Please enter the vector of the ellipse: "), majorAxis) == RTNORM)
		{
			pMajorAxis.x = majorAxis[0];
			pMajorAxis.y = majorAxis[1];
			pMajorAxis.z = majorAxis[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		AcDbEllipse* pEllipse = new AcDbEllipse(pCenter, pVector, pMajorAxis, radiusRatio);

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		pBlockTableRecord->appendAcDbEntity(pEllipse);

		pEllipse->close();
		pBlockTableRecord->close();

		return true;
	}

	void CmdDrawEllipse::execute()
	{
		ads_point center;
		AcGePoint3d pCenter;
		ads_point vector;
		AcGeVector3d pVector;
		ads_point majorAxis;
		AcGeVector3d pMajorAxis;
		double radiusRatio;

		if (acedGetPoint(NULL, _T("Please enter the center of the ellipse: "), center) == RTNORM)
		{
			pCenter.x = center[0];
			pCenter.y = center[1];
			pCenter.z = center[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		if (acedGetReal(_T("Please enter the radius ratio of the ellipse: "), &radiusRatio) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		if (acedGetPoint(NULL, _T("Please enter the vector of the ellipse: "), vector) == RTNORM)
		{
			pVector.x = vector[0];
			pVector.y = vector[1];
			pVector.z = vector[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		if (acedGetPoint(NULL, _T("Please enter the vector of the ellipse: "), majorAxis) == RTNORM)
		{
			pMajorAxis.x = majorAxis[0];
			pMajorAxis.y = majorAxis[1];
			pMajorAxis.z = majorAxis[2];
		}
		else
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		AcDbEllipse* pEllipse = new AcDbEllipse(pCenter, pVector, pMajorAxis, radiusRatio);

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		pBlockTableRecord->appendAcDbEntity(pEllipse);

		pEllipse->close();
		pBlockTableRecord->close();
	}

	void CmdDrawEllipse::command()
	{
		CmdDrawEllipse cmd;
		cmd.execute();
	}


	CmdCreateText::CmdCreateText()
	{
	}

	template<typename T, typename U, typename V>
	bool CmdCreateText::executeWithBool(T& point, U height, V rotation)
	{
		AcGePoint3d textPosition;

		static_assert(is_ads_point<T>::point, "point must be an ads_point.");
		static_assert(std::is_same<T, double>::height, "height must be a double.");
		static_assert(std::is_same<T, double>::rotation, "rotation must be a double.");

		if (acedGetPoint(NULL, _T("Enter the text position: "), point) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		textPosition.x = point[0];
		textPosition.y = point[1];
		textPosition.z = point[2];

		TCHAR textString[1024];

		if (acedGetString(0, _T("Enter the text content: "), textString) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		if (acedGetReal(_T("Enter the height of the text: "), &height) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		if (acedGetReal(_T("Enter the rotation of the text: "), &rotation) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return false;
		}

		AcDbText* pText = new AcDbText(textPosition, textString, AcDbObjectId::kNull, height, rotation);

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		pBlockTableRecord->appendAcDbEntity(pText);

		pText->close();
		pBlockTableRecord->close();

		return true;
	}

	void CmdCreateText::execute()
	{
		AcGePoint3d textPosition;
		ads_point point;
		double height;
		double rotation;

		if (acedGetPoint(NULL, _T("Enter the text position: "), point) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		textPosition.x = point[0];
		textPosition.y = point[1];
		textPosition.z = point[2];

		TCHAR textString[1024];

		if (acedGetString(0, _T("Enter the text content: "), textString) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
			return;
		}

		if (acedGetReal(_T("Enter the height of the text: "), &height) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
		}

		if (acedGetReal(_T("Enter the rotation of the text: "), &rotation) != RTNORM)
		{
			acutPrintf(_T("Invalid\n"));
		}

		AcDbText* pText = new AcDbText(textPosition, textString, AcDbObjectId::kNull, height, rotation);

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		pBlockTableRecord->appendAcDbEntity(pText);

		pText->close();
		pBlockTableRecord->close();
	}

	void CmdCreateText::command()
	{
		CmdCreateText cmd;
		cmd.execute();
	}


	CmdCreateLayer::CmdCreateLayer()
	{
	}

	template<typename T, typename U>
	bool CmdCreateLayer::executeWithBool(T& layerName, U colorIndex)
	{
		static_assert(std::is_same<T, std::string>::layerName, "layer name must be a std::string.");
		static_assert(std::is_integral<U>::colorName, "color index must be an integral type.");

		Acad::ErrorStatus es;
		AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
		AcDbLayerTable* pLayerTable;

		es = pDb->getLayerTable(pLayerTable, AcDb::kForWrite);
		if (es != Acad::eOk)
		{
			acutPrintf(_T("\nUnable to open layer table"));
			return false;
		}

		acutPrintf(_T("\nEnter layer name: "));
		if (acedGetString(1, _T(""), layerName) != RTNORM)
		{
			acutPrintf(_T("Failed to get layer name.\n"));
			pLayerTable->close();
			return false;
		}

		AcCmColor color;
		acutPrintf(_T("\nEnter color index (1-7): "));
		if (acedGetInt(NULL, &colorIndex) != RTNORM)
		{
			acutPrintf(_T("Failed to get color index.\n"));
			pLayerTable->close();
			return false;
		}

		AcDbLayerTableRecord* pLayerRecord = new AcDbLayerTableRecord;
		pLayerRecord->setName(layerName);
		color.setColorIndex(colorIndex);
		pLayerRecord->setColor(color);

		if (pLayerTable->has(layerName))
		{
			acutPrintf(_T("\nLayer already exists."));
			return false;
		}
		else
		{
			es = pLayerTable->add(pLayerRecord);
			if (es != Acad::eOk)
			{
				acutPrintf(_T("\nFailed to add layer to the table: %s"));
				return false;
			}
			else
			{
				acutPrintf(_T("\nLayer created successfully."));
			}
		}

		pLayerRecord->close();
		pLayerTable->close();

		return true;
	}

	void CmdCreateLayer::execute()
	{
		Acad::ErrorStatus es;
		AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
		AcDbLayerTable* pLayerTable;

		es = pDb->getLayerTable(pLayerTable, AcDb::kForWrite);
		if (es != Acad::eOk)
		{
			acutPrintf(_T("\nUnable to open layer table"));
			return;
		}

		TCHAR layerName[64];
		acutPrintf(_T("\nEnter layer name: "));
		if (acedGetString(1, _T(""), layerName) != RTNORM)
		{
			acutPrintf(_T("Failed to get layer name.\n"));
			pLayerTable->close();
			return;
		}

		int colorIndex;
		AcCmColor color;
		acutPrintf(_T("\nEnter color index (1-7): "));
		if (acedGetInt(NULL, &colorIndex) != RTNORM)
		{
			acutPrintf(_T("Failed to get color index.\n"));
			pLayerTable->close();
			return;
		}

		AcDbLayerTableRecord* pLayerRecord = new AcDbLayerTableRecord;
		pLayerRecord->setName(layerName);
		color.setColorIndex(colorIndex);
		pLayerRecord->setColor(color);

		if (pLayerTable->has(layerName))
		{
			acutPrintf(_T("\nLayer already exists."));
		}
		else
		{
			es = pLayerTable->add(pLayerRecord);
			if (es != Acad::eOk)
			{
				acutPrintf(_T("\nFailed to add layer to the table: %s"));
			}
			else
			{
				acutPrintf(_T("\nLayer created successfully."));
			}
		}

		pLayerRecord->close();
		pLayerTable->close();
	}

	void CmdCreateLayer::command()
	{
		CmdCreateLayer cmd;
		cmd.execute();
	}


	CmdCreateDimension::CmdCreateDimension()
	{
	}

	template<typename T, typename U>
	bool CmdCreateDimension::executeWithBool(T& pt1, U& pt2)
	{
		static_assert(is_ads_point<T>::pt1, "pt1 must be an ads_point.");
		static_assert(is_ads_point<U>::pt2, "pt2 must be an ads_point.");
		AcGePoint3d point1;
		AcGePoint3d point2;

		if (acedGetPoint(NULL, _T("\nSpecify first point: "), pt1) != RTNORM)
		{
			acutPrintf(_T("\nFailed to get the first point."));
			return false;
		}
		point1.set(pt1[0], pt1[1], pt1[2]);

		if (acedGetPoint(NULL, _T("\nSpecify second point: "), pt2) != RTNORM)
		{
			acutPrintf(_T("\nFailed to get the second point."));
			return false;
		}
		point2.set(pt2[0], pt2[1], pt2[2]);

		AcDbAlignedDimension* pDim = new AcDbAlignedDimension();
		pDim->setDimLinePoint(point1);
		pDim->setXLine1Point(point1);
		pDim->setXLine2Point(point2);

		AcDbObjectId styleId = acdbHostApplicationServices()->workingDatabase()->dimstyle();
		pDim->setDimensionStyle(styleId);

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		pBlockTableRecord->appendAcDbEntity(pDim);
		pDim->close();
		pBlockTableRecord->close();
		pBlockTable->close();

		return true;
	}

	void CmdCreateDimension::execute()
	{
		ads_point pt1;
		ads_point pt2;
		AcGePoint3d point1;
		AcGePoint3d point2;

		if (acedGetPoint(NULL, _T("\nSpecify first point: "), pt1) != RTNORM)
		{
			acutPrintf(_T("\nFailed to get the first point."));
			return;
		}
		point1.set(pt1[0], pt1[1], pt1[2]);

		if (acedGetPoint(NULL, _T("\nSpecify second point: "), pt2) != RTNORM)
		{
			acutPrintf(_T("\nFailed to get the second point."));
			return;
		}
		point2.set(pt2[0], pt2[1], pt2[2]);

		AcDbAlignedDimension* pDim = new AcDbAlignedDimension();
		pDim->setDimLinePoint(point1);
		pDim->setXLine1Point(point1);
		pDim->setXLine2Point(point2);

		AcDbObjectId styleId = acdbHostApplicationServices()->workingDatabase()->dimstyle();
		pDim->setDimensionStyle(styleId);

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		pBlockTableRecord->appendAcDbEntity(pDim);
		pDim->close();
		pBlockTableRecord->close();
		pBlockTable->close();
	}

	void CmdCreateDimension::command()
	{
		CmdCreateDimension cmd;
		cmd.execute();
	}


	void listAllEntityHandles()
	{
		// 获取当前文档的数据库
		AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
		AcDbBlockTable* pBlockTable;
		AcDbBlockTableRecord* pBlockTableRecord;

		// 获取块表和模型空间块表记录
		pDb->getSymbolTable(pBlockTable, AcDb::kForRead);
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForRead);

		// 创建一个迭代器来遍历模型空间中的所有实体
		AcDbBlockTableRecordIterator* pIter;
		pBlockTableRecord->newIterator(pIter);

		// 遍历模型空间中的所有实体
		for (pIter->start(); !pIter->done(); pIter->step())
		{
			AcDbEntity* pEntity;
			pIter->getEntity(pEntity, AcDb::kForRead);

			// 获取实体的句柄
			AcDbHandle handle;
			pEntity->getAcDbHandle(handle);

			// 将句柄转换为字符串
			TCHAR handleBuffer[17];
			handle.getIntoAsciiBuffer(handleBuffer);

			// 获取实体的类型
			const TCHAR* entityType = pEntity->isA()->name();

			// 获取实体的名字
			const TCHAR* entityName = pEntity->isA()->name();

			// 输出实体的类型、名字和句柄
			acutPrintf(_T("Entity type: %s, Name: %s, Handle: %s\n"), entityType, entityName, handleBuffer);

			// 关闭实体对象
			pEntity->close();
		}

		// 清理
		delete pIter;
		pBlockTableRecord->close();
		pBlockTable->close();
	}

	CmdSelectEntity::CmdSelectEntity()
	{
	}

	template<typename T>
	bool CmdSelectEntity::executeWithBool(T& handleStr)
	{
		static_assert(std::is_same<T, std::string>::handleStr, "handle string must be a std::string.");

		listAllEntityHandles();

		acutPrintf(_T("Enter the entity handle: "));
		acedGetString(Adesk::kTrue, nullptr, handleStr);

		if (_tcslen(handleStr) == 0 || _tcslen(handleStr) > 16)
		{
			acutPrintf(_T("\nInvalid handle length."));
			return false;
		}

		ads_name ename;
		if (acdbHandEnt(handleStr, ename) != RTNORM)
		{
			acutPrintf(_T("\nFailed to get object ID from handle: %s"), handleStr);
			return false;
		}

		AcDbObjectId objId;
		acdbGetObjectId(objId, ename);

		AcDbEntity* pEntity;
		if (acdbOpenAcDbEntity(pEntity, objId, AcDb::kForRead) != Acad::eOk)
		{
			acutPrintf(_T("\nFailed to open entity."));
			return false;
		}

		AcDbHandle handle;
		pEntity->getAcDbHandle(handle);

		TCHAR handleBuffer[17];
		handle.getIntoAsciiBuffer(handleBuffer);

		acutPrintf(_T("\nSelected entity type: %s"), pEntity->isA()->name());
		acutPrintf(_T("\nHandle: %s"), handleBuffer);

		pEntity->close();

		return true;
	}

	void CmdSelectEntity::execute()
	{
		listAllEntityHandles();

		TCHAR handleStr[17];
		acutPrintf(_T("Enter the entity handle: "));
		acedGetString(Adesk::kTrue, nullptr, handleStr);

		if (_tcslen(handleStr) == 0 || _tcslen(handleStr) > 16)
		{
			acutPrintf(_T("\nInvalid handle length."));
			return;
		}

		ads_name ename;
		if (acdbHandEnt(handleStr, ename) != RTNORM)
		{
			acutPrintf(_T("\nFailed to get object ID from handle: %s"), handleStr);
			return;
		}

		AcDbObjectId objId;
		acdbGetObjectId(objId, ename);

		AcDbEntity* pEntity;
		if (acdbOpenAcDbEntity(pEntity, objId, AcDb::kForRead) != Acad::eOk)
		{
			acutPrintf(_T("\nFailed to open entity."));
			return;
		}

		AcDbHandle handle;
		pEntity->getAcDbHandle(handle);

		TCHAR handleBuffer[17];
		handle.getIntoAsciiBuffer(handleBuffer);

		acutPrintf(_T("\nSelected entity type: %s"), pEntity->isA()->name());
		acutPrintf(_T("\nHandle: %s"), handleBuffer);

		pEntity->close();
	}

	void CmdSelectEntity::command()
	{
		CmdSelectEntity cmd;
		cmd.execute();
	}

	void CmdStartPanel()
	{
		CAcModuleResourceOverride resOverride;
		Dialog_Login Dlg(CWnd::FromHandle(adsw_acadMainWnd()));
		if (Dlg.DoModal() != IDOK)
		{
			return;
		}
	}
}
