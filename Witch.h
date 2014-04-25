#pragma once//☀Unicode
#include "DataType.h"

namespace SDX_TD
{
    using namespace SDX;
    /**魔女.*/
    class Witch
    {
    public:
        WitchType 種類;

        //補正後のパラメータ
        double 攻撃補正 = 1.0;
        double 連射補正 = 1.0;
        double 範囲補正 = 1.0;
        double 射程補正 = 1.0;
        double 支援補正 = 1.0;
        double 弾速補正 = 1.0;

        double 回収率   = 0.5;
        double 回収速度 = 1.0;
        double 強化速度 = 1.0;

        double 弱点補正 = 1.1;
        double 状態強化[4];
        double 属性強化[4];

        //変動パラメータ
        double MP;
        double SP;
        int    大魔法残り時間;
        int    詠唱回数[10];
    };

    namespace
    {
        Witch* MainWitch;//現在アクティブなウィッチ
        Witch* SubWitch;//控えのウィッチ
    }

}