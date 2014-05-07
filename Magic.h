#pragma once//☀Unicode
#include "Object.h"
#include "Shot.h"
#include "IStage.h"
#include "DataType.h"

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

        int    強化回数 = 0;
        double 支援補正 = 1;
        double 速度補正 = 1;

        int    待機時間 = -1;
        int    送還時間 = -1;
        int    強化時間 = -1;
        
        Magic(int X座標, int Y座標 , MagicType 魔法種) :
            Object(new Rect( (X座標+1) * Land::ChipSize , (Y座標+1) * Land::ChipSize , Size * Land::ChipSize, Size * Land::ChipSize), nullptr , Belong::砲台),
            基礎ステ(MagicDataS[(int)魔法種])
        {
            SetWait();
            //画像の設定
        }

        /**.*/
        void SetWait()
        {
            基礎ステ.連射[強化回数] = 30;
            基礎ステ.攻撃力[強化回数] = 1;
            基礎ステ.射程[強化回数] = 60;
            基礎ステ.デバフ効果[強化回数] = 0;
            基礎ステ.デバフ率[強化回数] = 0;
            基礎ステ.魔法属性 = Elements::空;
            待機時間 = int(速度値 / 基礎ステ.連射[強化回数] / 速度補正);
        }

        /**.*/
        void Draw() const
        {

            MSystem::魔法枠[1].Draw((int)GetX()-Land::ChipSize, (int)GetY()-Land::ChipSize,Land::ChipSize*2,Land::ChipSize*2);            
            MMagic::魔法[0]->DrawRotate((int)GetX(), (int)GetY(),1,0);            
            //MUnit::魔女[WitchType::ミナエ][0]->DrawRotate((int)GetX(),(int)GetY(),2,0);

            //レベル表示
            for(int i=0;i<5;++i)
            {
                MSystem::マーク[3]->DrawRotate( (int)GetX()+6*i - 12,(int)GetY() + 12,1,0);
            }

            MFont::BMP黒.Draw(100,100,Color::White,"Test123456789");

            //強化中or送還中
            if( 強化時間 > 0)
            {
            
            }
            if( 送還時間 > 0)
            {
            
            }
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
                SLand->RemoveMagic(x, y, Size);

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
                強化回数++;
                強化時間 = -1;
                SetWait();
            }

            if (待機時間 <= 0 && 送還時間 < 0 && 強化時間 < 0)
            {
                auto 一番近い敵 = SStage->GetNearEnemy(this);

                if (一番近い敵)
                {
                    double 距離 = GetDistance(一番近い敵);
                
                    if (距離 <= 基礎ステ.射程[強化回数])
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
            SStage->Add(new Shot(GetX(), GetY(), 角度, 基礎ステ, 強化回数, 支援補正));
        }

    };
}