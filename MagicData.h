#pragma once//☀Unicode
#include "EnumType.h"

namespace SDX_TD
{
    using namespace SDX;
    /**魔法の基礎性能.*/
    struct MagicData
    {
        static const int 最大レベル = 6;

        MagicType 魔法種;

        int コスト[最大レベル];
        int 攻撃力[最大レベル];
        int 速度[最大レベル];
        int 射程[最大レベル];
        double 支援効果[最大レベル];

        double 炸裂範囲[最大レベル];
        double 炸裂威力[最大レベル];

        Elements 魔法属性;

        int 属性効果[最大レベル];
        double 発動率[最大レベル];
        double 半径;

        bool is対空;//空の敵に当たるかどうか
        bool is対地;//地上の敵に当たるかどうか

        bool is貫通;//命中時に消滅するかどうか

        bool is使い捨て;

        bool isウィッチ;//指揮官魔法、詠唱回数の管理が違う
    };
    namespace{MagicData MagicDataS[(int)MagicType::MAX];}
}