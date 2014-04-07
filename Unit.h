#pragma once//☀Unicode
#include "Object.h"
#include "Shot.h"
#include "Scene.h"
#include "UnitData.h"

namespace SDX
{
    class Unit : public Object
    {
    protected:
        virtual void Dead(){}
    public:
        UnitData 性能;
        int    レベル = 0;
        double 攻撃力補正 = 1;
        double 速度補正 = 1;

        int    待機時間 = -1;
        int    送還時間 = -1;
        int    強化時間 = -1;
        int    大きさ = 2;//2x2
        Elements 魔法属性 = Elements::無;

        Unit(int X座標, int Y座標, int 大きさ, Sprite *sprite) :
            Object(new Rect(X座標 * 20 + 大きさ * 10, Y座標 * 20 + 大きさ * 10, 大きさ * 20, 大きさ * 20), sprite, Belong::砲台)
        {
            SetWait();
        }

        /**.*/
        void SetWait()
        {
            待機時間 =  int(性能.攻撃間隔[レベル] * 速度補正);
        }

        /**.*/
        void Draw() const
        {
            shape->Draw(Color::Green, 128);
            Drawing::String((int)GetX() + 2, (int)GetY() + 2, Color::Red, { レベル });
        }

        /**.*/
        bool RemoveCheck() override
        {
            //送還
            if (送還時間 == 0) isRemove = true;

            if (isRemove)
            {
                const int x = int(GetX() - 大きさ * 10) / 20;
                const int y = int(GetY() - 大きさ * 10) / 20;
                Land::now->RemoveUnit(x, y, 大きさ);
                Remove();
            }

            return this->isRemove;
        }

        /**.*/
        void Act()
        {
            --送還時間;
            --強化時間;
            --待機時間;
            if (強化時間 == 0)
            {
                レベル++;
                強化時間 = -1;
                SetWait();
            }

            if (待機時間 <= 0 && 送還時間 < 0 && 強化時間 < 0)
            {
                Scene::Add(new    Shot((int)GetX(), (int)GetY(), Scene::GetNearDirect(this), (1 + レベル) * 100));
                SetWait();
                if (Rand::Get(9)) 強化時間 = 120;
            }
        }
    };
}