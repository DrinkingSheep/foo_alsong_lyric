#pragma once

class Window_Setting
{
public:
	Window_Setting() {}
	~Window_Setting() {}

	enum AlignPosition
	{
		ALIGN_LEFT = 1,
		ALIGN_TOP = 1,
		ALIGN_MODDLE = 2,
		ALIGN_BOTTOM = 3,
		ALIGN_RIGHT = 3,
	};
	
	enum BgType
	{
		BG_SOLIDCOLOR = 0,
		BG_IMAGE = 1,
		BG_TRANSPARENT = 2,
	};

	HFONT CreateFont()
	{
		return font.create();
	}
	COLORREF GetBkColor()
	{
		return bkColor;
	}
	COLORREF GetFgColor()
	{
		return fgColor;
	}
	std::wstring GetBgImagePath()
	{
		return std::wstring(bgImage);
	}
	BgType GetBgType()
	{
		return bgType;
	}
	unsigned int GetnLine()
	{
		return nLine;
	}
	unsigned int GetLineMargin()
	{
		return LineMargin;
	}
	AlignPosition GetVerticalAlign()
	{
		return static_cast<AlignPosition>(VerticalAlign);
	}
	AlignPosition GetHorizentalAlign()
	{
		return static_cast<AlignPosition>(HorizentalAlign);
	}
	int OpenFontPopup(HWND hWndFrom)
	{
		return font.popup_dialog(hWndFrom);
	}
	int OpenFgColorPopup(HWND hWndFrom)
	{
		COLORREF color;
		if(color = OpenColorPopup(hWndFrom, fgColor) != -1)
		{
			fgColor = color;
			return color;
		}
		return -1;
	}
	int OpenBkColorPopup(HWND hWndFrom)
	{
		COLORREF color;
		if(color = OpenColorPopup(hWndFrom, fgColor) != -1)
		{
			bgType = BG_SOLIDCOLOR;
			bkColor = color;
			return color;
		}
		return -1;
	}
	int OpenBgImagePopup(HWND hWndFrom)
	{
		OPENFILENAME ofn;
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.lpstrFile = bgImage;
		ofn.lpstrFilter = TEXT("�׸� ����(*.bmp;*.png;*.jpg;*.gif;*.jpeg)\0*.bmp;*.png;*.jpg;*.gif;*.jpeg\0\0");
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
		ofn.nMaxFile = 255;

		if(GetOpenFileName(&ofn))
		{
			bgType = BG_IMAGE;
			return true;
		}
		return false;
	}
	void SetDefault()
	{
		font = t_font_description::g_from_font((HFONT)GetStockObject(DEFAULT_GUI_FONT));
		bkColor = RGB(0, 0, 0);
		fgColor = RGB(255, 255, 255);
		bgImage[0] = 0;
		bgType = BG_SOLIDCOLOR;
		nLine = 3;
		LineMargin = 100;
		VerticalAlign = ALIGN_MODDLE;
		HorizentalAlign = ALIGN_MODDLE;
	}

	void OpenConfigPopup(HWND hParent);
	static BOOL CALLBACK ConfigProcDispatcher(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
private:
	COLORREF OpenColorPopup(HWND hWndFrom, COLORREF color)
	{
		static COLORREF acrCustClr[16] = {RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255), 
			RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255), 
			RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255), 
			RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255)};

		CHOOSECOLOR choosecolor;
		ZeroMemory(&choosecolor, sizeof(choosecolor));
		choosecolor.lStructSize = sizeof(CHOOSECOLOR);
		choosecolor.Flags = CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT ;
		choosecolor.hwndOwner = hWndFrom;
		choosecolor.lpCustColors = (LPDWORD)acrCustClr;
		choosecolor.rgbResult = color;
		if(ChooseColor(&choosecolor))
			return choosecolor.rgbResult;
		return -1;
	}
	BOOL UIConfigProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam, HWND hParent);

	t_font_description font;
	COLORREF bkColor;
	COLORREF fgColor;
	WCHAR bgImage[MAX_PATH];
	BgType bgType; //0: ��, 1: �̹���, 2:������ ���

	DWORD nLine;
	DWORD LineMargin;//%����

	BYTE VerticalAlign; //��������. 1:�� 2:��� 3:�Ʒ�
	BYTE HorizentalAlign; //�¿�����. 1:���� 2:��� 3:������

	BYTE bReserved[1022]; //����ü ũ�Ⱑ ���ϸ� ������ �ʱ�ȭ�ȴ�. ���߿� ���� �߰��Ҷ� ���⼭ ����
};
