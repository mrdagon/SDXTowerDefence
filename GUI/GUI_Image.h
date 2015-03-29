//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Tiled/IGUI.h>

namespace SDX
{
	/** GUI.*/
	class GUI_Image : public IGUI
	{
	public:
		//@メンバー宣言
		int gID;
		Rect rect;

		//@コンストラクタ
		GUI_Image(const Rect& rect,int gID):
			rect(rect) 
		{}

	};
}
