#pragma once//☀Unicode
#include "Object.h"

namespace SDX
{
    struct UnitData
    {
        int コスト[6];
        int 攻撃力[6];
        int 攻撃間隔[6];

        int 属性効果[6];
        double 発動率[6];

        double 支援効果;

        bool 空中;
        bool 地上;

        bool 追尾;
        bool 貫通;

        Elements 魔法属性;
    };

}