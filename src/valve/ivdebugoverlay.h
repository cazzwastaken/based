#pragma once

#include "cvector.h"
#include "cmatrix.h"

class IVDebugOverlay
{
public:
	virtual void AddEntityTextOverlay(int entityIndex, int lineOffset, float duration, int r, int g, int b, int a, const char* fmt, ...) = 0;
	virtual void AddBoxOverlay(const CVector& origin, const CVector& min, const CVector& max, const CVector& orientation, int r, int g, int b, int a, float duration) = 0;
	virtual void AddSphereOverlay(const CVector& origin, float flRadius, int nTheta, int nPhi, int r, int g, int b, int a, float duration) = 0;
	virtual void AddTriangleOverlay(const CVector& p1, const CVector& p2, const CVector& p3, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
	virtual void AddLineOverlay(const CVector& origin, const CVector& dest, int r, int g, int b, bool noDepthTest, float duration) = 0;
	virtual void AddTextOverlay(const CVector& origin, float duration, const char* fmt, ...) = 0;
	virtual void AddTextOverlay(const CVector& origin, int lineOffset, float duration, const char* fmt, ...) = 0;
	virtual void AddScreenTextOverlay(float x, float y, float duration, int r, int g, int b, int a, const char* text) = 0;
	virtual void AddSweptBoxOverlay(const CVector& start, const CVector& end, const CVector& min, const CVector& max, const CVector& angles, int r, int g, int b, int a, float duration) = 0;
	virtual void AddGridOverlay(const CVector& origin) = 0;
	virtual void AddCoordFrameOverlay(const CMatrix3x4& frame, float scale, int colorTable[3][3] = nullptr) = 0;
	virtual int ScreenPosition(const CVector& worldPosition, CVector& screen) = 0;
};
