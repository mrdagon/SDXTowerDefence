#pragma once//☀Unicode
#include "Design.h"

namespace SDX_TD
{
    namespace UInfo
    {
        //名前枠と画像全体位置は共通
        const Rect F名前() { return {486,215,140,30}; };

        const Point P画像() { return {502,227}; };        
        const Point P名前() { return {530,221}; };

        const Point P説明() { return {495,259}; };
        const Rect F説明() { return {486,249,140,48}; };

        const Point P性能アイコン(int y) { return {490,F性能(y).y}; };
        const Point P性能(int y) { return {500,F性能(y).y + 7}; };

        const Rect F性能(int y) { return {486,306 + y ,140,25}; };
        const int ステ間() { return 27; };
    }

    namespace UMagic
    {
        const Rect F強化() { return {486,249,69,48}; };
        const Point P強化() { return {F強化().x+19,F強化().y+8}; };

        //X以外は強化と同じ
        const Rect F回収() { return {557,249,69,48}; };
        const Point P回収() { return {F回収().x+19,F回収().y+8}; };

        const Point Pレベル() { return {1,1}; };

        const int 強化前ステX() { return 1; };
        const int 強化後ステX() { return 1; };
        const int サンプルステX() { return 1; };
        const int 矢印X() { return 1; };
    }

    namespace UStage
    {
        const Point Pスコア() { return {36,13}; };
        const Rect Fスコア() { return {44,4,120,30}; };

        const Point P敵数() { return {162,13}; };
        const Rect F敵数() { return {168,4,60,30}; };

        const Point Pゲーム速度() { return {8,10}; };
        const Rect Fゲーム速度(int No) { return {234 + No*60,-6,60,42}; };

        const Point Pウィッチ() { return {Fウィッチ().x+20,Fウィッチ().y+20}; };
        const Rect Fウィッチ() { return {486,20,40,40}; };

        const Point Pサブウィッチ() { return {536,32}; };

        const Point P体力() { return {486,61}; };
        const Point P魔力() { return {550,61}; };

        const Point P大魔法() { return {584,44}; };
        const Rect F大魔法() { return {530, 40, 100 ,20}; };

        const Rect Fメニュー() { return {570,-6,80,42}; };
        
        const Rect F魔法一覧(int a) { return {476+a%4*40,85+a/4*40,40,40}; };

        const Rect F情報() { return {476,205,160,269}; };
    }
}