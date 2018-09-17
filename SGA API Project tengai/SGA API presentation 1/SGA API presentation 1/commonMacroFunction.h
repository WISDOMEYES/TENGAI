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
//���α׸���
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//rect
//������ǥ �������� �����.������ǥx   ������ǥy   ����ũ��width ����ũ��height
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y, x + width, y + height };

	return rc;
}
//���� ��ǥ �������� �����. ������ǥx   ������ǥy   ����ũ��width ����ũ��height
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
