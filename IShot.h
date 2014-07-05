#pragma once//☀SDXFramework
#include "IObject.h"

namespace SDX_TD
{
    struct UnitData;

    /**公開されるShot.*/
    struct ShotState
    {
        UnitData &基礎ステ;
        int    強化回数;
        double 攻撃力;

        bool   is貫通 = false;
        bool   is必中 = false;
        bool   isSmall = true;//分割当たり判定用

        int    デバフ効果;
        double デバフ率;

        double 炸裂威力 = 0;
        double 炸裂範囲 = 0;
    };

    class IShot : public IObject
    {
    public:
        virtual ShotState& State() = 0;

        /**衝突した時の特殊処理.*/
        virtual void React() = 0;

        virtual void Damaged() = 0;
    };
}