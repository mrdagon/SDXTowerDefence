#pragma once
#include <Tiled/GUIData.h>
#include <vector>
#include <string>
#include "GUI_Text.h"
#include "GUI_Frame.h"
#include "GUI_Button.h"
#include "GUI_Image.h"

namespace SDX
{
	void GUI_Factory(GUIData& data, std::string& type , int gid, Rect rect, double r, std::vector<std::string>& properties)
	{
		if(type == "GUI_Text")
		{
			data.dataS.push_back(std::make_shared<GUI_Text>(rect,std::atoi(properties[0].c_str()),properties[1].c_str()));
		}
		else if(type == "GUI_Frame")
		{
			data.dataS.push_back(std::make_shared<GUI_Frame>(rect,std::atoi(properties[0].c_str())));
		}
		else if(type == "GUI_Button")
		{
			data.dataS.push_back(std::make_shared<GUI_Button>(rect,std::atoi(properties[0].c_str())));
		}
		else if(type == "GUI_Image")
		{
			data.dataS.push_back(std::make_shared<GUI_Image>(rect,gid));
		}
	}
}
