//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "../Struct/DataS.h"
#include "../System/EnumType.h"

namespace SDX_TD
{
    using namespace SDX;
    class IUnit;

    /**グローバル変数用.*/
    namespace TDSystem
    {
        //この4つはStageSelectとStageで共通なのでグローバル変数
        Difficulty 難易度 = Difficulty::Easy;
        std::string 選択ステージ = StageType::Quest[0];
        bool isトライアル = true;//notならアンリミテッド
        bool isカップル = true;//notならシングル
        int バージョン = 102;//

        //アイテム関連
		int レベル = 1;
        int 最大スキルポイント = 5;
        int 残りスキルポイント = 5;
        int 経験値 = 0;
        //ランダムステージの状況

        //実績関連
        Difficulty 限界難易度;

        //設定関連
        int 効果音の音量;//0～10
        int BGMの音量;//0～10

        bool isグリッド;//マスのグリッドと中央の薄い十字の表示
        bool isHPゲージ = true;//敵Hpゲージの表示ON/OFF
        bool is高速;//ゲーム速度を1,4,16,64倍速モードにする
        bool isエフェクト省略;//死亡時エフェクト,大魔法カットインのON/OFF
        bool is配置記録;//初期配置の記録を行なうかどうか
        bool isリプレイ保存;//常にリプレイの自動保存フラグ

        bool isタッチ;//タブレット用の操作スタイルフラグ
        bool isフルスクリーン;//フルスクリーンフラグ

		//Lvアップ判定処理
		int CheckLVUp()
		{
			int num = 0;

			while ( 経験値 >= レベル * 10000)
			{
				経験値 -= レベル * 10000;
				++レベル;
				++最大スキルポイント;
				++残りスキルポイント;
				++num;
			}

			return num;
		}

    }
}