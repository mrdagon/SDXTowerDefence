#pragma once
#include <Tiled/GUIData.h>
#include <vector>
#include <string>
#include "UI_Image.h"
#include "UI_Button.h"
#include "UI_Frame.h"
#include "UI_Text.h"

namespace SDX
{
using namespace SDX;
	void GUI_Factory(GUIData& data, std::string& type , int id , int gid, Rect rect, double zoomW , double zoomH , double angle, std::vector<std::string>& properties)
	{
		if(type == "Image")
		{
			data.dataS.push_back(std::make_shared<UI_Image>(id,rect,angle));
		}
		else if(type == "Button")
		{
			data.dataS.push_back(std::make_shared<UI_Button>(id,rect,angle,std::atoi(properties[0].c_str())));
		}
		else if(type == "Frame")
		{
			data.dataS.push_back(std::make_shared<UI_Frame>(id,rect,angle,std::atoi(properties[0].c_str())));
		}
		else if(type == "Text")
		{
			data.dataS.push_back(std::make_shared<UI_Text>(id,rect,angle,std::atoi(properties[0].c_str()),properties[1].c_str()));
		}
	}
}
