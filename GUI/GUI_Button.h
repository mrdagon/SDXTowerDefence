//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Tiled/IGUI.h>

namespace SDX
{
	/** GUI.*/
	class GUI_Button : public IGUI
	{
	public:
		//@メンバー宣言
		Rect rect;
		int frameNo;

		//@コンストラクタ
		GUI_Button(const Rect& rect,int frameNo):
			frameNo(frameNo),
			rect(rect) 
		{}

	};
}
