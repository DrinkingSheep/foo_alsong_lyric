inline static t_font_description get_def_font();

extern cfg_bool cfg_enabled;
extern cfg_bool cfg_topmost;
extern cfg_window_placement cfg_popup_window_placement;
extern cfg_bool cfg_save_to_lrc;
extern cfg_bool cfg_load_from_lrc;
extern cfg_string cfg_lrc_save_path;
extern cfg_int cfg_outer_transparency;

struct Alsong_Setting
{
	t_font_description font;
	COLORREF bkColor;
	COLORREF fgColor;
	WCHAR bgImage[MAX_PATH];
	BOOL bgType; //false: ��, true: �̹���

	DWORD nLine;

	DWORD LineMargin;//%����

	BYTE bReserved[1024]; //����ü ũ�Ⱑ ���ϸ� ������ �ʱ�ȭ�ȴ�. ���߿� ���� �߰��Ҷ� ���⼭ ����
};

extern cfg_struct_t<Alsong_Setting> cfg_outer;
extern cfg_struct_t<Alsong_Setting> cfg_panel;