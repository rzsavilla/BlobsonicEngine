#include <iostream>
#include <fstream>
using namespace std;

#include <nana/gui.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/msgbox.hpp>
#include <nana/gui/filebox.hpp>
#include <thread>

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>

using namespace nana;

#pragma once
class EditorView : public form
{
	place place_{ *this };
	menubar menubar_{ *this };
	textbox textbox_{ *this };

public:
	EditorView();
	~EditorView();
	textbox& get_tb();

private:
	string _m_pick_file(bool is_open) const;
	bool _m_ask_save();
	void _m_make_menus();
};
