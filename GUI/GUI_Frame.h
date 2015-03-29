//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Tiled/IGUI.h>

namespace SDX
{
	/** GUI.*/
	class GUI_Frame : public IGUI
	{
	public:
		//@メンバー宣言
		Rect rect;
		int frameNo;

		//@コンストラクタ
		GUI_Frame(const Rect& rect,int frameNo):
			frameNo(frameNo),
			rect(rect) 
		{}

	};
}
