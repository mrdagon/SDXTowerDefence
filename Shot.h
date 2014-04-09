#pragma once//☀Unicode
#include "Object.h"

namespace SDX_TD
{
    using namespace SDX;
    class Shot : public Object
    {
    public:
        bool is貫通 = false;
        bool isSmall = true;//分割木用

        int 属性効果;
        int 発動率;

        Elements  魔法属性;
        std::unique_ptr<ISpeed> 速度;

        Shot(int X座標, int Y座標, double 角度, double 攻撃力):
            Object(new Rect(X座標, Y座標, 10, 10), nullptr, Belong::弾, 攻撃力),
            速度(new Speed::Liner(2))
        {
            SetAngle(角度);
        }

        /**消滅判定.*/
        virtual bool RemoveCheck()
        {
            const double x = GetX();
            const double y = GetY();

            if (x < -10 || x > Land::MapSize * Land::ChipSize + 10 || y < -10 || y > Land::MapSize * Land::ChipSize + 10) isRemove = true;

            return isRemove;
        }

        /**描画処理.*/
        void Draw() const
        {
            shape->Draw(Color::Yellow, 255);
        }

        /**ダメージを受けた時の処理.*/
        virtual void Damaged(Object* 衝突相手)
        {
            if (!is貫通)
            {
                this->isRemove = true;
            }
            React();
        }

        /**衝突した時の特殊処理.*/
        virtual void React() {};

        /**毎フレームの処理.*/
        virtual void Act()
        {
            if (速度)
            {
                MoveFront(速度->Ease());
            }
        }
    };
}