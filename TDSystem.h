//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "DataS.h"

namespace SDX_TD
{
	using namespace SDX;
	class IUnit;

	/**グローバル変数用.*/
	namespace TDSystem
	{
		//この4つはStageSelectとStageで共通なのでグローバル変数
		Difficulty 難易度;
		StageType 選択ステージ = StageType::一面;
		bool isトライアル = true;//notならパワー
		bool isカップル = true;//notならシングル

		//アイテム関連
		int 素材数[4];
		int 特殊素材数[4];
		//特殊アイテム
		//レシピのレア度が分かるようになる
		int 工房レベル;
		int 工房経験;
		//ランダムステージの状況

		//実績関連

		//設定関連
		double 効果音の音量;
		double BGMの音量;
		
		bool isグリッド;//マスのグリッドと中央の薄い十字の表示
		bool isHPゲージ = true;//敵Hpゲージの表示ON/OFF
		bool is高速;//ゲーム速度を1,4,16,64倍速モードにする
		bool isエフェクト;//死亡時エフェクト,大魔法カットインのON/OFF

		bool isタッチ;//タブレット用の操作スタイルフラグ

		bool is常時リプレイ保存;//常にリプレイの自動保存フラグ
		bool is更新リプレイ保存;//スコア更新時にリプレイの自動保存フラグ
		bool is勝利リプレイ保存;//勝利時にリプレイの自動保存フラグ
	}
}