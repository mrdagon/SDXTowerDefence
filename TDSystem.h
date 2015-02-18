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
		int 資金;

		//実績関連


		//設定関連
		double 効果音の音量;
		double BGMの音量;
		
		bool isグリッド;//マスのグリッドと中央の薄い十字の表示
		bool isHPゲージ = true;//敵Hpゲージの表示ON/OFF
		bool is高速;//ゲーム速度を1,4,16,64倍速モードにする
		bool isエフェクト;//死亡時エフェクト,大魔法カットインのON/OFF

		bool isタッチ;//タブレット用の操作スタイルフラグ

		//ウィッチの経験値とステージの最高記録は、WitchDataS,StageDataSで
		static void SaveAndLoad(FileMode 読み込みor書込)
		{
			SaveOrLoadScore(読み込みor書込);
		}
	}
}