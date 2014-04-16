#pragma once//☀Unicode
#include "EnumType.h"

namespace SDX_TD
{
    using namespace SDX;
    /**魔女.*/
    class Witch
    {
    public:
        static Witch* now;//現在アクティブなウィッチ
        static Witch* sub;//控えのウィッチ

        WitchType 種類;

        //固定パラメータ
        double 攻撃補正 = 1.0;
        double 連射補正 = 1.0;
        double 範囲補正 = 1.0;
        double 射程補正 = 1.0;
        double 弾速補正 = 1.0;

        double 回収率   = 0.5;
        double 回収速度 = 1.0;
        double 強化速度 = 1.0;

        int    大魔法時間 = 3000;
        double 初期SP率 = 1.0;

        int    初期HP = 20;
        int    初期MP = 50;
        double MP補正 = 1.0;

        double 弱点補正 = 1.1;
        double 火傷強化 = 1.0;
        double 凍結強化 = 1.0;
        double 麻痺強化 = 1.0;
        double 突風強化 = 1.0;

        MagicType 魔法タイプ[10];
        int       初期詠唱回数[10];

        //変動パラメータ
        double    MP;
        double    SP;
        double    SP率;

        int       詠唱回数[10];
    };
}