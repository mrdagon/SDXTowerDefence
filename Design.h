#pragma once//☀Unicode
#include "Framework/Shape.h"

namespace SDX_TD
{
    using namespace SDX;

    namespace UInfo
    {
        //名前枠と画像全体位置は共通
        const Rect F名前();

        const Point P画像();            
        const Point P名前();

        const Point P説明();
        const Rect F説明();

        const Point P性能アイコン(int y = 0);
        const Point P性能(int y = 0);

        const Rect F性能(int y = 0);
        const int ステ間();
    }

    namespace UUnit
    {
        const Rect F強化();
        const Point P強化();

        //X以外は強化と同じ
        const Rect F回収();
        const Point P回収();

        const Point Pレベル();

        const int 強化前ステX();
        const int 強化後ステX();
        const int サンプルステX();
        const int 矢印X();
    }

    namespace UStage
    {
        const Point Pスコア();
        const Rect Fスコア();

        const Point P敵数();
        const Rect F敵数();

        const Point Pゲーム速度();
        const Rect Fゲーム速度(int a);

        const Point Pウィッチ();
        const Rect Fウィッチ();

        const Point Pサブウィッチ();

        const Point P体力();
        const Point P魔力();

        const Point P大魔法();
        const Rect F大魔法();

        const Rect Fメニュー();
        
        const Rect F魔法一覧(int a );

        const Rect F情報();
    }
}