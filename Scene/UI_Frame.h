//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <Tiled/IGUI.h>

namespace SDX_TD
{
	/** クラスの説明.*/
	class UI_Frame : public SDX::IGUI
	{
	public:
		//@メンバー宣言
		int frameNo;
		//@End

		//@コンストラクタ
		UI_Frame( int id , const Rect& rect, double angle,int frameNo):
			frameNo(frameNo),
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
			MSystem::frameS[frameNo].Draw(rect);
			//@End
		}

		void DrawText(Font &font, const char* 文字列, double 文字サイズ, const Color &描画色 = Color::White)
		{
			Draw();
			font.DrawRotate(rect.GetCenter(), 文字サイズ, 0, 描画色, 文字列);
		}
	};
}
