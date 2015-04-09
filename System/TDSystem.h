//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Struct/DataS.h"

namespace SDX_TD
{
	using namespace SDX;
	class IUnit;

	/**グローバル変数用.*/
	namespace TDSystem
	{
		//この4つはStageSelectとStageで共通なのでグローバル変数
		Difficulty 難易度;
		int 選択ステージ = 0;
		bool isトライアル = true;//notならアンリミテッド
		bool isカップル = true;//notならシングル
		int バージョン = 102;//

		//アイテム関連
		int 資金;
		int 素材数[4];
		//特殊アイテム
		int 工房レベル;
		int 工房経験;
		//ランダムステージの状況

		//実績関連
		Difficulty 限界難易度;

		//設定関連
		double 効果音の音量;
		double BGMの音量;

		bool isグリッド;//マスのグリッドと中央の薄い十字の表示
		bool isHPゲージ = true;//敵Hpゲージの表示ON/OFF
		bool is高速;//ゲーム速度を1,4,16,64倍速モードにする
		bool isエフェクト;//死亡時エフェクト,大魔法カットインのON/OFF

		bool isタッチ;//タブレット用の操作スタイルフラグ

		int 画面サイズ;

		enum ReplaySaveType
		{
			クリア時保存,
			更新時保存,
			自動保存無し
		};

		ReplaySaveType リプレイ保存;//常にリプレイの自動保存フラグ
	}
}