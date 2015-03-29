//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Tiled/IGUI.h>

namespace SDX
{
	/** GUI.*/
	class GUI_Text : public IGUI
	{
	public:
		//@メンバー宣言
		Rect rect;
		int fontNo;
		std::string text;

		//@コンストラクタ
		GUI_Text(const Rect& rect,int fontNo,const char* text):
			fontNo(fontNo),
			text(text),
			rect(rect) 
		{}

	};
}
