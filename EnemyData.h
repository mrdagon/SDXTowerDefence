#pragma once//☀Unicode
#include "EnumType.h"

namespace SDX_TD
{
    using namespace SDX;
    struct EnemyData
    {
        int スコア;
        int 体力;
        int 防御力;
        double 移動速度;

        //高い程ききやすい
        int 突風耐性;
        int 麻痺耐性;//移動速度低下
        int 冷凍耐性;//移動不可能
        int 火傷耐性;//
        MoveType 移動タイプ;
        Elements 魔法属性;
    };

}