//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Menu.h"

namespace SDX_TD
{
	using namespace SDX;

	/** 設定変更画面*/
	/** @todo .*/
	class MenuConfig : public IScene
	{
	public:
		void Update() override
		{
			namespace UI = UI_Config;
		}

		void Draw() override
		{
			namespace UI = UI_Config;
			//設定項目の表示
			//BGM音量
			//SE音量
			//HPゲージ表示フラグ
			//マス目表示の有無
			//エフェクトの有無
			//タッチ操作モード
			//リプレイ保存//1攻略したら保存,2更新したら保存,3毎回選択
		}
	};
}