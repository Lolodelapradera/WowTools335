#pragma once
#include "Headers.h"


class Drawing
{
public:

	static bool bDisplay;
	static bool bInit;
	static bool bSetPos;
	static bool packet;




	static HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 D3D9Device);

	static void InternalRender(float* target);
	




private:
	static ImVec2 vWindowPos;
	static ImVec2 vWindowSize;

	static void InitImGui(LPDIRECT3DDEVICE9 pDevice);
};



//static std::vector<Circle3D> circles;
//static std::vector<Line3D> lines;
//static std::vector<BoundCircle3D> boundCircles;
//static std::vector<BoundLine3D> boundLines;
//static Vector Position;
//static Vector PositionCircle;
//static void DrawLine(Vector from, Vector to, D3DCOLOR color);
//static void DrawTriangle(Vector b, Vector c, Vector d, D3DCOLOR color);
////Vector LerpByDistance(Vector start, Vector end, float scale);
//static void DrawArrowOnTarget(Vector unit, Vector target, int color);
//
//static void DrawCircle(Vector to, double radius, D3DCOLOR color);
