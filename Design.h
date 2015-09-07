//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3
#pragma once
#include "Framework/Shape.h"
#include "System/EnumType.h"
#include "Utility/EnumArray.h"

namespace SDX_TD
{
    using namespace SDX;

    //UI用の定数
    //エディットコンティニュ時のコンパイル時間削減のためcppファイルを分離
    namespace UI_Stage
    {
        void Reset();
        Point P差分[8];

        Rect Rスコア;
        Point Pスコア;

        Rect R敵数;
        Point P敵数;

        Rect R右全体;

        Point Pゲーム速度[4];
        Rect Rゲーム速度[4];

        Point Pシングルウィッチ;//シングル時
        Point Pカップルウィッチ[2];//カップル時

        Point Pモード名;
        Point P難易度名;

        Point PＳＰ;
        Point P体力;
        Point P魔力;

        Rect R大魔法;
        Rect Rメニュー;

        Rect R魔法一覧[12];
        Rect R情報;
    }

    namespace UI_Unit
    {
        void Reset();

        Rect R名前;

        Point P画像;
        Point P名前;
        Point P詠唱数;

        Point P説明;
        Rect R説明;

        Point P性能アイコン[5];
        Point P性能[5];

        Rect R性能[5];

        Rect R強化;
        Point P強化;
        Rect R回収;
        Point P回収;
    }

#undef EXT

    //void UI_Reset();

    void UI_Unit::Reset()
    {
        //名前枠と画像全体位置は共通
        const int stY = 27;//X基準

        R名前 = { 486, stY + 215, 140, 30 };

        P画像 = { 504, stY + 227 };
        P名前 = { 530, stY + 221 };
        P詠唱数 = { 510, stY + 220 };

        P説明 = { 495, stY + 259 };
        R説明 = { 486, stY + 249, 140, 48 };

        for (int a = 0; a < 5; ++a)
        {
            R性能[a] = { 486, stY + 306 + a * 27, 140, 25 };
            P性能アイコン[a] = { 490, R性能[a].y };
            P性能[a] = { 500, R性能[a].y + 7 };
        }

        R強化 = { 486, stY + 249, 69, 48 };
        P強化 = { R強化.x + 19, R強化.y + 6 };

        //X以外は強化と同じ
        R回収 = { 557, stY + 249, 69, 48 };
        P回収 = { R回収.x + 19, R回収.y + 6 };
    }

    void UI_Stage::Reset()
    {
        P差分[0] = { 10, -10 };
        Pスコア = { 36, 13 };
        Rスコア = { 44, 4, 120, 30 };

        P敵数 = { 162, 13 };
        R敵数 = { 168, 4, 60, 30 };

        P差分[6] = { 22, 17 };
        P差分[7] = { 10, 22 };
        for (int a = 0; a < 4; ++a)
        {
            Pゲーム速度[a] = { 8, 10 };
            Rゲーム速度[a] = { 234 + a * 58, -6, 58, 42, 0, 0 };
        }

        R右全体 = { 472, 0, 168, 100 + 105 + 27 };

        Pシングルウィッチ = { 511, 65 };
        Pカップルウィッチ[0] = { 496, 65 };
        Pカップルウィッチ[1] = { 526, 65 };

        Pモード名 = { 480, 90 };
        P難易度名 = { 480, 100 };

        P差分[1] = { 20, 6 };
        PＳＰ = { 550, 17 + 27 };
        P体力 = { 550, 39 + 27 };
        P魔力 = { 550, 61 + 27 };

        P差分[2] = { 10, 10 };
        R大魔法 = { 556 - 74, 4, 70, 36, 0, 0 };
        Rメニュー = { 556 + 4, 4, 70, 36, 0, 0 };

        P差分[3] = { 20, 12 };//ユニット画像位置
        P差分[4] = { 12, 20 };//残り配置回数
        P差分[5] = { 2, 24 };//×の位置
        for (int a = 0; a < 12; ++a)
        {
            R魔法一覧[a] = { 476 + a % 4 * 40, 112 + a / 4 * 40, 40, 40, 0, 0 };
        }

        R情報 = { 472, 205 + 27, 168, 269 - 27, 0, 0 };
    }

	/**StageのUI位置を修正.*/
    void UI_Reset()
    {
        UI_Stage::Reset();
        UI_Unit::Reset();
    }
}