#include "EditorView.h"

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

EditorView::EditorView()
{
	caption("Simple Notepad - Nana C++ Library");
	textbox_.borderless(true);
	API::effects_edge_nimbus(textbox_, effects::edge_nimbus::none);
	textbox_.enable_dropfiles(true);
	textbox_.events().mouse_dropfiles([this](const arg_dropfiles& arg) {
		if (arg.files.size() && _m_ask_save())
			textbox_.load(arg.files.at(0).data());
	});

	_m_make_menus();

	place_.div("vert<menubar weight = 28><textbox>");
	place_["menubar"] << menubar_;
	place_["textbox"] << textbox_;
	place_.collocate();

	events().unload([this](const arg_unload& arg) {
		if (!_m_ask_save())
			arg.cancel = true;
	});
}


EditorView::~EditorView()
{
}

textbox& EditorView::get_tb() {
	return textbox_; 
}

string EditorView::_m_pick_file(bool is_open) const {
	filebox fbox(*this, is_open);
	fbox.add_filter("Text", "*,txt");
	fbox.add_filter("All Files", "*.*");
	return (fbox.show() ? fbox.file() : "");
}

bool EditorView::_m_ask_save() {
	if (textbox_.edited()) {
		auto fs = textbox_.filename();
		msgbox box(*this, "Simple Notepad", msgbox::button_t::yes_no_cancel);
		box << "Do you want to save these changes?";

		switch (box.show()) {
		case msgbox::pick_yes:
			if (fs.empty()) {
				fs = _m_pick_file(false);
				if (fs.empty())
					break;
				if (fs.find(".txt") == fs.npos)
					fs += ".txt";
			}
			textbox_.store(fs.data());
			break;
		case msgbox::pick_no:
			break;
		case msgbox::pick_cancel:
			return false;
		}
	}
	return true;
}

void EditorView::_m_make_menus() {
	menubar_.push_back("&FILE");
	menubar_.at(0).append("New", [this](menu::item_proxy& ip) {
		if (_m_ask_save())
			textbox_.reset();
	});
	menubar_.at(0).append("Open", [this](menu::item_proxy& ip) {
		if (_m_ask_save()) {
			{
				auto fs = _m_pick_file(true);
				if (fs.size())
					textbox_.load(fs.data());
			}
		}
	});
	menubar_.at(0).append("Save", [this](menu::item_proxy&)
	{
		auto fs = textbox_.filename();
		if (fs.empty())
		{
			fs = _m_pick_file(false);
			if (fs.empty())
				return;
		}
		textbox_.store(fs.data());
	});
	menubar_.at(0).append("Exit", [this](menu::item_proxy&)
	{
		if (_m_ask_save())
			textbox_.events().click(API::exit_all);

	});
	menubar_.push_back("F&ORMAT");
	menubar_.at(1).append("Line Wrap", [this](menu::item_proxy& ip)
	{
		textbox_.line_wrapped(ip.checked());
	});
	menubar_.at(1).check_style(0, menu::checks::highlight);
}