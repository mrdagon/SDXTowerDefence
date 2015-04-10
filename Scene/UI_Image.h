//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <Tiled/IGUI.h>

namespace SDX
{
	/** クラスの説明.*/
	class UI_Image : public SDX::IGUI
	{
	public:
		//@メンバー宣言
		//@End

		//@コンストラクタ
		UI_Image( int id , const Rect& rect, double angle):
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
			imageS[gID]->DrawRotate(rect.GetCenter(),1,0);
			//@End
		}
	};
}
