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
#include <nana/gui/widgets/listbox.hpp>

#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/label.hpp>

using namespace nana;

EditorView::EditorView(){
}

EditorView::~EditorView(){
}

void EditorView::Init() {

	form fm(rectangle(0, 0, 720,640));
	place plc(fm);
	plc.div("vert<menubar weight = 28><<weight = 20% listbox><scene_group>>");

	listbox lb_(fm, rectangle(10, 10, 60, 120));
	lb_.append_header("Project1");
	lb_.at(0).append({ std::string("<Scene 1>") });
	
	group group_{ fm, "Scene 1", true};
	group_.div("horizontal <scenegroup>");
	label lbl_{ group_, std::string("Name: ")};
	label lbl2_{ group_, std::string("Props: ") };
	textbox name{ group_ };
	textbox name2{ group_ };
	name.multi_lines(false);
	name2.multi_lines(false);
	group_["scenegroup"] << lbl_;
	group_["scenegroup"] << name;
	group_["scenegroup"] << lbl2_;
	group_["scenegroup"] << name2;
	
	menubar menubar_(fm);
	menubar_.push_back("&FILE");
	menubar_.at(0).append("New", [this](menu::item_proxy& ip) {
	});
	menubar_.at(0).append("Open", [this](menu::item_proxy& ip) {
	});
	menubar_.at(0).append("Save", [this](menu::item_proxy&) {
	});
	menubar_.at(0).append("Exit", [this](menu::item_proxy&) {
	});
	menubar_.push_back("CREATE");
	menubar_.at(1).append("Scene", [this](menu::item_proxy& ip) {
	});

	plc["menubar"] << menubar_;
	plc["listbox"] << lb_;
	plc["scene_group"] << group_;
	plc.collocate();
	fm.show();
	exec();
	
}


/*


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
	caption("BlobSonic Editor");
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
		msgbox box(*this, "blobSonic Editor", msgbox::button_t::yes_no_cancel);
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
	menubar_.push_back("CREATE");
	menubar_.at(1).append("Scene", [this](menu::item_proxy& ip)
	{

	});
	menubar_.at(1).check_style(0, menu::checks::highlight);
}
*/