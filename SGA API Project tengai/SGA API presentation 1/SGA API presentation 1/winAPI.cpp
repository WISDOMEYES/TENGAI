#include"stdafx.h"
#include"mainGame.h"
//API : Application Programming Interface

HINSTANCE _hInstance;		//���� ������ȣ
HWND _hWnd;					//������



POINT _ptMouse;

LPTSTR _lpszClass = TEXT("���尳��2ȣ��");


mainGame _mg;
void setWindowsSize(int x, int y, int width, int height);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;			//�޼���
	WNDCLASS wndClass;		//������ ������ ���� ����ü

							//Salt Bae 
	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;										//������ ���� �޸� 
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ��׶��� 
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//������ Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������ ������
	wndClass.hInstance = hInstance;									//������ �ν��Ͻ� ��ȣ
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = WINNAME;							//������ Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;									//������ �޴� �̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ â ��Ÿ��

																	//������ ���� ���
	RegisterClass(&wndClass);

	//������ â ��������
	_hWnd = CreateWindow(WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,
		WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);
			
						//������ â�� ����Ϳ� �����
	//�Լ� ������ �����.
	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
	ShowWindow(_hWnd, cmdShow);

	//���ΰ����� �ʱ�ȭ�� �ȵǸ�
	if (FAILED(_mg.init()))
	{
		//����~
		return 0;
	}

	//GetMessage : �޽��� ������ ������ �׶� ����
	//PeekMessage : �޽��� ������ ������ ���� ������ ����(��� ����)
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);	//�Է��� ������ ���� �� �޽��� ó�� ���
		DispatchMessage(&message);	//������ �����쿡 �� �޽��� ����
	}
	//�޽��� ������ ���� ���� �����ض�
	_mg.release();

	return message.wParam;
}
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}



//������ ������ �缳��(Ŭ���̾�Ʈ ������ ��Ȯ�� ����ش�.)
void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;		//����ũ��
	winRect.bottom = height;	//����ũ��

	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);

}