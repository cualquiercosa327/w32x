/*
 * Copyright (c) 2017 Devin Smith <devin@devinsmith.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

static LRESULT CALLBACK
MainWindowProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(wnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(wnd, msg, wParam, lParam);
	}
	return 0;
}

int
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR pCmdLine,
    int nCmdShow)
{
	HWND top;
	WNDCLASS myClass;
	MSG msg;
	BOOL bRet;
	HMENU menu;

	memset(&myClass, 0, sizeof(WNDCLASS));

	myClass.lpszClassName = "TopWindow";
	myClass.hbrBackground = (HBRUSH)(COLOR_BTNSHADOW + 1);
	myClass.cbWndExtra = 0;
	myClass.lpfnWndProc = MainWindowProc;
	RegisterClass(&myClass);

	menu = CreateMenu();

	/* parent window */
	top = CreateWindowEx(0, "TopWindow", "Test1",
	    WS_OVERLAPPEDWINDOW, 200, 200, 500, 300, NULL, menu, hInstance, NULL);

	/* XXX: Needs to be moved to menu.c */
	CreateWindow("#32768", "Nothing", WS_CHILD | WS_VISIBLE, 0, 0, 500,
	    GetSystemMetrics(SM_CYMENU), top, NULL, hInstance, NULL);

	CreateWindow("RadioButton", "Radio 1",
	    WS_CHILD | WS_BORDER | WS_VISIBLE, 5, 30, 100, 25, top, NULL,
	    hInstance, NULL);
	CreateWindow("RadioButton", "Radio 2",
	    WS_CHILD | WS_BORDER | WS_VISIBLE, 5, 60, 100, 25, top, NULL,
	    hInstance, NULL);

	ShowWindow(top, nCmdShow);
	UpdateWindow(top);

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		DispatchMessage(&msg);
	}

	return 0;
}
