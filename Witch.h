#pragma once//☀Unicode

namespace SDX
{
    /**魔女.*/
    class Witch
    {
    public:
        //固定パラメータ
        double 攻撃補正;
        double 連射補正;
        double 範囲補正;
        double 射程補正;

        double 回収率;
        double 回収速度;
        double 強化速度;

        double 大魔法時間;
        double 大魔法必要SP;
        double 必要SP増加率;

        int    初期HP;
        double 初期MP;
        double MP補正;

        double 弱点補正;
        double 火傷強化;
        double 凍結強化;
        double 麻痺強化;
        double 突風強化;

        //変動パラメータ
        int    HP;
        double MP;
        double SP;

        int    召喚タイプ[12];
        int    召喚回数[12];
    };
}