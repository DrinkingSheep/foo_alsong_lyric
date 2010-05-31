#pragma once

#include "UIManager.h"

class UIWnd
{
private:
	HWND m_hWnd;
	UIManager *m_UI;
	IPropertyStore *m_Propstore;
public:
	void Show();
	void Hide();
	HWND Create();
	void Destroy(); 

	HWND GetHWND()
	{
		return m_hWnd;
	}

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

extern UIWnd WndInstance;