#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init(void)
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
	}

	return S_OK;
}

void gameNode::release(void)
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update(void)
{
	InvalidateRect(_hWnd, NULL, false);
}

void gameNode::render(void)
{

}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		this->render();

		EndPaint(hWnd, &ps);
	}
	break;

	//마우스 좌표를 읽어오는 함수
	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>LOWORD(lParam);
		_ptMouse.y = static_cast<float>HIWORD(lParam);

		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;

		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}