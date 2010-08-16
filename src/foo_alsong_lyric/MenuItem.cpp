/*
* foo_alsong_lyric														
* Copyright (C) 2007-2010 Inseok Lee <dlunch@gmail.com>
*
* This library is free software; you can redistribute it and/or modify it 
* under the terms of the GNU Lesser General Public License as published 
* by the Free Software Foundation; version 2.1 of the License.
*
* This library is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty of 
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU Lesser General Public License for more details.
*
* You can receive a copy of the GNU Lesser General Public License from 
* http://www.gnu.org/
*/

#include "stdafx.h"
#include "ConfigStore.h"
#include "UIWnd.h"
#include "LyricManager.h"
#include "AlsongLyricLinkDialog.h"

class menu_command_plugin : public mainmenu_commands 
{
	virtual t_uint32 get_command_count() 
	{
		return 2;
	}

	virtual GUID get_command(t_uint32 p_index) 
	{
		static const GUID guid_plugin_lyric_menu = { 0x66821da5, 0xfa15, 0x4002, { 0x99, 0xc5, 0x8c, 0x6a, 0x96, 0xf4, 0xe, 0xad } };
		static const GUID guid_plugin_window_config = { 0x300e3322, 0xc22, 0x4354, { 0xa7, 0x5, 0x28, 0xfb, 0x48, 0xc4, 0xc9, 0xd0 } };

		if(p_index == 0)
			return guid_plugin_lyric_menu;
		else if(p_index == 1)
			return guid_plugin_window_config;
		return pfc::guid_null;
	}

	virtual void get_name(t_uint32 p_index, pfc::string_base & p_out) 
	{
		if(p_index == 0)
			p_out = pfc::stringcvt::string_utf8_from_wide(TEXT("�˼� �ǽð� ����"), lstrlen(TEXT("�˼� �ǽð� ����")));
		if(p_index == 1)
			p_out = pfc::stringcvt::string_utf8_from_wide(TEXT("Alsong Lyric Window Config"), lstrlen(TEXT("Alsong Lyric Window Config")));
	}

	virtual bool get_description(t_uint32 p_index, pfc::string_base & p_out) 
	{
		if(p_index == 0)
			p_out = pfc::stringcvt::string_utf8_from_wide(TEXT("�˼� �ǽð� ���� â�� ���ų� �ݽ��ϴ�."), lstrlen(TEXT("�˼� �ǽð� ���� â�� ���ų� �ݽ��ϴ�.")));
		else
			return false;
		return true;
	}

	virtual GUID get_parent()
	{
		return mainmenu_groups::file_etc_preferences;
	}

	virtual void execute(t_uint32 p_index, service_ptr_t<service_base> p_callback) 
	{
		if(p_index == 0 && core_api::assert_main_thread()) 
		{
			if (cfg_outer_shown)
				WndInstance.Hide();
			else
				WndInstance.Show();
		}
		else if(p_index == 1)
		{
			cfg_outer.get_value().OpenConfigPopup(core_api::get_main_window());
		}
	}

	virtual bool get_display(t_uint32 p_index, pfc::string_base & p_text, t_uint32 & p_flags)
	{
		if(p_index == 0)
		{
			p_flags = 0;
			if(is_checked(p_index))
				p_flags |= flag_checked;
			get_name(p_index, p_text);
		}
		else
			return false;
		return true;
	}

	bool is_checked(t_uint32 p_index)
	{
		if(p_index == 0)
			return cfg_outer_shown;
		return false;
	}
};

static mainmenu_commands_factory_t<menu_command_plugin> plugin_main_menu;

class contextcommand_plugin : public contextmenu_item_simple 
{
public:
	virtual GUID get_parent()
	{
		return contextmenu_groups::root;
	}

	virtual unsigned int get_num_items() 
	{
		return 1;
	}

	virtual void get_item_name(unsigned int p_index, pfc::string_base & p_out) 
	{
		if(p_index == 0)
			p_out = pfc::stringcvt::string_utf8_from_wide(TEXT("�˼� ���� �߰�/����"), lstrlen(TEXT("�˼� ���� �߰�/����")));
	}

	virtual void context_command(unsigned int p_index, metadb_handle_list_cref p_data, const GUID& p_caller) 
	{
		if(p_index == 0 && p_data.get_count() == 1)
			AlsongLyricLinkDialog::OpenLyricLinkDialog(core_api::get_main_window(), p_data.get_item(0));
	}
	
	virtual bool context_get_display(unsigned int p_index, metadb_handle_list_cref p_data, pfc::string_base & p_out, unsigned & p_displayflags, const GUID & p_caller) 
	{
		if(p_index == 0)
		{
			p_out = pfc::stringcvt::string_utf8_from_wide(TEXT("�˼� ���� �߰�/����"), lstrlen(TEXT("�˼� ���� �߰�/����")));
			return p_data.get_count() == 1;
		}
		return false;
	}

	virtual GUID get_item_guid(unsigned int p_index) 
	{
		if(p_index == 0)
		{
			static const GUID item_guid = // {6C1CBA98-CB52-4ECA-92B6-7A8625DE1A6F}
				{ 0x6c1cba98, 0xcb52, 0x4eca, { 0x92, 0xb6, 0x7a, 0x86, 0x25, 0xde, 0x1a, 0x6f } };
			return item_guid;
		}
		static const GUID nullguid = {0,};
		return nullguid;
	}

	virtual bool get_item_description(unsigned int p_index, pfc::string_base & p_out) 
	{
		if(p_index == 0)
		{
			p_out = pfc::stringcvt::string_utf8_from_wide(TEXT("�˼� ���� �߰�/����"), lstrlen(TEXT("�˼� ���� �߰�/����")));
			return true;
		}
		return false;
	}
};

static contextmenu_item_factory_t<contextcommand_plugin> g_myitem_factory;
