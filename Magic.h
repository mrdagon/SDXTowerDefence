#pragma once//☀Unicode
#include "Object.h"
#include "Shot.h"
#include "IStage.h"
#include "MagicData.h"

namespace SDX_TD
{
    using namespace SDX;
    class Magic : public Object
    {
    protected:
        virtual void Dead(){}
    public:
        static const int Size = 2;//2x2角
        static const int 速度値 = 6000;

        MagicData &基礎ステ;//基礎ステータス

        int    レベル = 0;
        double 支援補正 = 1;
        double 速度補正 = 1;

        int    待機時間 = -1;
        int    送還時間 = -1;
        int    強化時間 = -1;

        Elements 魔法属性 = Elements::無;

        Magic(int X座標, int Y座標 , MagicType 魔法種) :
            Object(new Rect(X座標 * Land::ChipSize + Size * 10, Y座標 * Land::ChipSize + Size * 10, Size * Land::ChipSize, Size * Land::ChipSize), nullptr , Belong::砲台),
            基礎ステ(MagicDataS[(int)魔法種])
        {
            SetWait();
            //画像の設定

        }

        /**.*/
        void SetWait()
        {
            待機時間 = int( 速度値 / 基礎ステ.速度[レベル] / 速度補正);
        }

        /**.*/
        void Draw() const
        {
            shape->Draw(Color::Green, 128);
            Drawing::String((int)GetX() + 2, (int)GetY() + 2, Color::Red, { レベル });
            //強化中or送還中
        }

        /**.*/
        bool RemoveCheck() override
        {
            //送還
            if (送還時間 == 0) isRemove = true;

            if (isRemove)
            {
                const int x = int(GetX() - Size * 10) / 20;
                const int y = int(GetY() - Size * 10) / 20;
                Land::now->RemoveMagic(x, y, Size);

                SStage->選択解除(this);
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
                auto   一番近い敵 = SStage->GetNearEnemy(this);

                if (一番近い敵)
                {
                    double 距離 = GetDistance(一番近い敵);
                
                    if (距離 <= 基礎ステ.射程[レベル])
                    {
                        Shoot( GetDirect(一番近い敵) );
                        SetWait();
                    }
                }

            }
        }

        /**攻撃処理.*/
        virtual void Shoot(double 角度)
        {
            MakeShot( 角度 );
        }

        void MakeShot(double 角度)
        {
            SStage->Add(new Shot(GetX(), GetY(), 角度 , 基礎ステ, レベル, 支援補正));
        }

    };
}