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
class EditorView
{
public:
	EditorView(std::vector<std::pair<std::string, Scene>> m_vScene);
	~EditorView();
	void Init();

private:
	void ev_makeMenu();


};
