// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
// C++ ��Ÿ�� ��� �����Դϴ�.
//#include<iostream>


//���� ���� STL
#include<string>
//#include<vector>
//#include<list>
//#include<map>


//====================================
// ##���� ���� ������� ��⿡ �߰�!!
//====================================
#include"commonMacroFunction.h"
#include"randomFuction.h"
#include"keyManager.h"
#include"util.h"
#include"imageManager.h"
using namespace std;
using namespace MY_UTIL;
//====================================
//    ##�̱��� �߰�
//====================================
//�����Լ� ������
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
//====================================
//   ##������ �� ##(������ �ʱ�ȭ ����)
//====================================

#define WINNAME (LPTSTR)(TEXT("���尳�� 2ȣ��"))
#define WINSTARTX 0
#define WINSTARTY 0
#define WINSIZEX  1520
#define WINSIZEY  785
#define WINSTYLE  WS_CAPTION|WS_SYSMENU




//===============================================
//   ##��ũ�� �Լ� ##(���ΰ��� ������ �κп��� ���)
//===============================================

#define SAFE_DELETE(p)  {if(p) {delete(p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p)  {if(p) {delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if(p){(p)->release();(p)=nullptr;}}

//=================================================
//   ##�������� ## (�ν��Ͻ�, ������ �ڵ�, ���콺 ��ǥ)
//=================================================

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
