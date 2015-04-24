//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <Tiled/IGUI.h>

namespace SDX
{
	/** クラスの説明.*/
	class UI_Text : public SDX::IGUI
	{
	public:
		//@メンバー宣言
		int fontNo;
		std::string text;
		//@End

		//@コンストラクタ
		UI_Text( int id , const Rect& rect, double angle,int fontNo,const char* text):
			fontNo(fontNo),
			text(text),
			IGUI(id,rect,angle)
		{}
		//@End

		//初期化
		void Init() override
		{
			//@Init
			
			//@End
		}

		//終了時
		void Final() override
		{
			//@Final
			
			//@End
		}

		//更新
		void Update() override
		{
			//@Update
			
			//@End
		}

		//描画
		void Draw() override
		{
			//@Draw
			MFont::fontS[fontNo].Draw(rect.GetPoint(),Color::White,text);
			//@End
		}
	};
}
