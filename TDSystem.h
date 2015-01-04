//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

#include "DataS.h"

namespace SDX_TD
{
	using namespace SDX;
	class IUnit;

	namespace TDSystem
	{
		Difficulty 難易度;
		StageType 選択ステージ = StageType::一面;
		bool isトライアル = true;//notならパワー
		bool isカップル = true;//notならシングル
		bool isリプレイ = false;

		//アイテム関連
		int 素材数[4];

		//実績関連

		//設定関連
		double 効果音の音量;
		double BGMの音量;
		bool isグリッド;
		bool isHPゲージ;
		bool isエフェクト;

		static void SaveAndLoad(FileMode 読み込みor書込)
		{

			SaveOrLoadScore(読み込みor書込);

		}
	}
}