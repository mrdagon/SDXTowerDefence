#pragma once//☀Unicode
#include "EnumType.h"

namespace SDX_TD
{
    using namespace SDX;
    struct EnemyData
    {
        //基礎ステータス
        int スコア;//MPの量
        int 体力;
        double 防御力;
        double 移動速度;

        //高い程ききやすい 0_無効 1_通常 2_倍
        int 突風耐性;//吹き飛び量
        int 麻痺耐性;//移動速度低下率増加
        int 冷凍耐性;//移動不可能時間
        int 火傷耐性;//炎上時間
        Belong 移動タイプ = Belong::陸;
        Elements 魔法属性;
    } EnemyDataS[(int)EnemyType::MAX];
}