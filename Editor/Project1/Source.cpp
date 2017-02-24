//Include nana/gui.hpp header file to enable Nana C++ Library
//for the program.
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

#include "EditorView.h"
#include "EditorData.h"
#include "EditorController.h"

int main() {
	EditorView* eView;
	EditorData* eData;
	EditorController* eController;

	eView = new EditorView();
	eData = new EditorData();
	eController = new EditorController();

	eView->show();
	exec(2, 2, [&eView]() {

	});
}

/*
class notepad_form : public form {
	place place_{ *this };
	menubar menubar_{ *this };
	textbox textbox_{ *this };

public:
	notepad_form() {
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
	textbox& get_tb() { return textbox_; }

private:
	string _m_pick_file(bool is_open) const {
		filebox fbox(*this, is_open);
		fbox.add_filter("Text", "*,txt");
		fbox.add_filter("All Files", "*.*");
		return (fbox.show() ? fbox.file() : "");
	}

	bool _m_ask_save() {
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
	
	void _m_make_menus(){
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
		menubar_.push_back("F&ORMAT");
		menubar_.at(1).append("Line Wrap", [this](menu::item_proxy& ip)
		{
			textbox_.line_wrapped(ip.checked());
		});
		menubar_.at(1).check_style(0, menu::checks::highlight);
	}
};
void Wait(unsigned wait = 0)
{
	if (wait)
		std::this_thread::sleep_for(std::chrono::seconds{ wait });
}

int main() {
	notepad_form npform;
	npform.show();
	exec(2, 2, [&npform]() {

	});
}


int main()
{
	using namespace nana;

	form fm;
	button btn(fm, nana::rectangle(20, 20, 150, 30));
	btn.caption("New Project");
	btn.events().click(API::exit_all);

	fm.show();
	exec(2, 1, [&btn]()
	{
		click(btn);
	});
}
*/

