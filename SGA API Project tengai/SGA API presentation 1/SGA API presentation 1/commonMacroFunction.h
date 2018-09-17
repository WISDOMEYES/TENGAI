#pragma once
//=================================================
//   ##commonMacroFunction##
//=================================================

//POINT

inline POINT pointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}
//라인그리기
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//rect
//시작좌표 기점으로 만든다.시작좌표x   시작좌표y   가로크기width 세로크기height
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y, x + width, y + height };

	return rc;
}
//중점 좌표 기점으로 만든다. 중점좌표x   중점좌표y   가로크기width 세로크기height
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2),y - (height / 2), x + (width / 2),y + (height / 2) };

	return rc;
}
//Rectangle
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//Ellipse
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}
