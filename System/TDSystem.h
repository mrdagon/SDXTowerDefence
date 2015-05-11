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
        Difficulty 難易度;
        std::string 選択ステージ = StageType::Quest[0];
        bool isトライアル = true;//notならアンリミテッド
        bool isカップル = true;//notならシングル
        int バージョン = 102;//

        //アイテム関連
        int 最大スキルポイント;
        int 残りスキルポイント;
        int 経験値;
        //ランダムステージの状況

        //フリーステージ数
        int リプレイファイル数 = 0;

        //実績関連
        Difficulty 限界難易度;

        //設定関連
        int 効果音の音量;
        int BGMの音量;

        bool isグリッド;//マスのグリッドと中央の薄い十字の表示
        bool isHPゲージ = true;//敵Hpゲージの表示ON/OFF
        bool is高速;//ゲーム速度を1,4,16,64倍速モードにする
        bool isエフェクト;//死亡時エフェクト,大魔法カットインのON/OFF
        bool is配置記録;//初期配置の記録を行なうかどうか
        bool isリプレイ保存;//常にリプレイの自動保存フラグ

        bool isタッチ;//タブレット用の操作スタイルフラグ
        bool isフルスクリーン;//フルスクリーンフラグ

        int 画面サイズ;

    }
}