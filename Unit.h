#pragma once//☀Unicode
#include "Object.h"
#include "Shot.h"
#include "IStage.h"
#include "Wave.h"
#include "DataType.h"
#include "Design.h"

namespace SDX_TD
{
    using namespace SDX;
    class Unit : public Object
    {
    protected:
        virtual void Dead(){}
    public:
        static const int Size = 2;//2x2角
        static const int 速度値 = 6000;

        UnitData &基礎ステ;//基礎ステータス

        int    Lv = 0;
        double 支援補正 = 1;

        int    待機時間 = -1;
        int    送還時間 = -1;
        int    強化時間 = -1;
        int    強化or送還長さ;
        bool   is配置リスト = false;
        
        Unit(int X座標, int Y座標 , UnitType 魔法種) :
            Object(new Rect( (X座標+1) * Land::ChipSize , (Y座標+1) * Land::ChipSize , Size * Land::ChipSize, Size * Land::ChipSize), nullptr , Belong::砲台),
            基礎ステ(UnitDataS[魔法種])
        {
            SetWait();
            //画像の設定
        }
        
        /**.*/
        void SetWait()
        {
            基礎ステ.連射[Lv] = 30;
            基礎ステ.攻撃力[Lv] = 1;
            基礎ステ.射程[Lv] = 60;
            基礎ステ.連射[Lv+1] = 60;
            基礎ステ.攻撃力[Lv+1] = 1000;
            基礎ステ.射程[Lv+1] = 120;

            基礎ステ.デバフ効果[Lv] = 0;
            基礎ステ.デバフ率[Lv] = 0;
            基礎ステ.属性 = Element::空;
            待機時間 = int(速度値 / 基礎ステ.連射[Lv]);
        }

        /**.*/
        void Draw() const
        {            
            //選択中
            if(SStage->selectUnit == this)
            {
                Screen::SetBlendMode(BlendMode::Alpha,128);
                Drawing::Rect((int)GetX()-Land::ChipSize, (int)GetY()-Land::ChipSize,Land::ChipSize*2,Land::ChipSize*2,Color::Red,true);                
                Screen::SetBlendMode(BlendMode::NoBlend,255);
                Screen::SetBright({255,128,128});
                MSystem::フレーム[1].Draw((int)GetX()-Land::ChipSize, (int)GetY()-Land::ChipSize,Land::ChipSize*2,Land::ChipSize*2);            
                Screen::SetBright(Color::White);
            }else{
                MSystem::フレーム[1].Draw((int)GetX()-Land::ChipSize, (int)GetY()-Land::ChipSize,Land::ChipSize*2,Land::ChipSize*2);                        
            }

            //強化中or送還中
            if( 強化時間 > 0)
            {
                int Num = 99 - 強化時間*99/強化or送還長さ;   
                MFont::BMP黒.DrawExtend((int)GetX()-14,(int)GetY()-12,2,2,Color::White,{std::setw(2),Num});
            }
            else if( 送還時間 > 0)
            {
                int Num = 送還時間*99/強化or送還長さ;
                MFont::BMP黒.DrawExtend((int)GetX()-14,(int)GetY()-12,2,2,Color::White,{std::setw(2),Num});
            }
            else
            {
                MUnit::魔女[UnitType::ディアネラ][1]->DrawRotate((int)GetX(),(int)GetY(),1+0.2*Lv,0);            
            }

            //レベル表示
            for(int a=0;a<Lv;++a)
            {
                MSystem::マーク[3]->DrawRotate( (int)GetX()+6*a - 12,(int)GetY() + 12,1,0);
            }
        }

        void DrawInfo() override
        {
            基礎ステ.名前 = "炎斬り";
            基礎ステ.説明文 = "炎できりつけるぞ\n強い!";

            //画像&名前
            MSystem::フレーム[5].Draw( UInfo::F名前() );
            MUnit::魔女[基礎ステ.魔法種][1]->DrawRotate( UInfo::P画像() , 2 , 0 );
            MFont::ゴシック中.DrawShadow( UInfo::P名前() , Color::White , Color::Gray  , 基礎ステ.名前);
            
            //レベル
            if(is配置リスト)
            {
                //説明文
                MSystem::フレーム[5].Draw( UInfo::F説明() );
                MFont::ゴシック小.DrawShadow( UInfo::P説明() , Color::White , Color::Gray , 基礎ステ.説明文);

                //LV1の性能
                DrawInfoState( 0 , false );
                        
            }else{               
                //強化
                MSystem::フレーム[8].Draw(UUnit::F強化());
                MFont::ゴシック中.DrawShadow( UUnit::P強化(),Color::White , Color::Gray , "強化");
                MFont::ゴシック中.DrawExtend((int)UUnit::P強化().x-16,(int)UUnit::P強化().y+13,2,2,Color::Red,"-");
                MFont::BMP白.DrawExtend((int)UUnit::P強化().x-6,(int)UUnit::P強化().y+20,2,2,Color::White,{std::setw(4),123});

                //売却or発動
                MSystem::フレーム[8].Draw(UUnit::F回収());
                MFont::ゴシック中.DrawShadow( UUnit::P回収() , Color::White , Color::Gray , "回収");
                MFont::ゴシック中.DrawExtend((int)UUnit::P回収().x-12,(int)UUnit::P回収().y+13,2,2,Color::Blue,"+");
                MFont::BMP白.DrawExtend((int)UUnit::P回収().x-6,(int)UUnit::P回収().y+20,2,2,Color::White,{std::setw(4),123});

                //強化前後の性能
                DrawInfoState(Lv, (Lv!=5) );

                //支援補正
                int y = UInfo::ステ間()*5;
                MSystem::フレーム[5].Draw( UInfo::F性能(y));
                MIcon::UI[IconType::強化].Draw( UInfo::P性能アイコン(y) );         
                MFont::BMP白.DrawExtend( UInfo::P性能(y) , 2 , 2 , Color::White, { std::setw(10) , (int)(支援補正*100)} );
            }
        }

        void DrawInfoState(int 表示Lv , bool 変化量表示 )
        {
            IconType アイコン[5] =
            {
                IconType::レベル,
                IconType::攻撃,
                IconType::連射,
                IconType::支援,
                IconType::麻痺
            };
            int 性能[5] =
            {
                Lv,//上3つは確定、最大5つ
                基礎ステ.攻撃力[Lv],
                基礎ステ.連射[Lv],
                (int)(基礎ステ.支援効果[Lv]*100),
                基礎ステ.デバフ効果[Lv]
            };
            int 次性能[5] =
            {
                (Lv+1)%5,//上3つは確定、最大5つ
                基礎ステ.攻撃力[(Lv+1)%5],
                基礎ステ.連射[(Lv+1)%5],
                (int)(基礎ステ.支援効果[(Lv+1)%5]*100),
                基礎ステ.デバフ効果[(Lv+1)%5]
            };

            switch (基礎ステ.デバフ種 )
            {
                case DebuffType::鈍足:アイコン[4] = IconType::鈍足;break;
                case DebuffType::麻痺:アイコン[4] = IconType::麻痺;break;
                case DebuffType::吹飛:アイコン[4] = IconType::吹飛;break;
                case DebuffType::防壊:アイコン[4] = IconType::防壊;break;
            }

            int y = 0;
            
            //性能、現在値&次レベル値
            for(int a=0;a<5;++a)
            {               
                Screen::SetBright({128,128,255});
                MSystem::フレーム[5].Draw( UInfo::F性能(y) );
                Screen::SetBright({255,255,255});

                //変化前
                MIcon::UI[アイコン[a]].Draw( UInfo::P性能アイコン(y) );
                int 桁数 = 5;
                if( !変化量表示 ) 桁数 = 10;

                MFont::BMP白.DrawExtend( UInfo::P性能(y) , 2 , 2 , Color::White, {std::setw(桁数),性能[a]} );

                if(変化量表示)
                {
                    MFont::ゴシック中.Draw(565,(int)UInfo::P性能アイコン(y).y+8,Color::Yellow,"+");
                    //変化量
                    MIcon::UI[アイコン[a]].Draw( UInfo::P性能アイコン(y) );
                    MFont::BMP白.DrawExtend( UInfo::P性能(y) , 2 , 2 , Color::Yellow, {std::setw(10),次性能[a]-性能[a]} );
                }

                y += UInfo::ステ間();
            }

        }

        /**.*/
        bool RemoveCheck() override
        {
            //送還
            if (送還時間 == 0) isRemove = true;

            if (isRemove)
            {
                const int x = int(GetX() - Size * Land::ChipSize) / Land::ChipSize;
                const int y = int(GetY() - Size * Land::ChipSize) / Land::ChipSize;
                SLand->RemoveUnit(x, y, Size);

                SStage->選択解除(this);
                Remove();
            }

            return this->isRemove;
        }

        bool 強化開始()
        {
            if (Lv >= 5) return false;

            int 必要MP = 基礎ステ.コスト[Lv+1] - 基礎ステ.コスト[Lv];

            強化時間 = int((Lv + 1) * (Lv + 1) * 60 * MainWitch->実ステ.強化速度);
            強化or送還長さ = 強化時間;

            return true;
        }

        bool 送還開始()
        {
            送還時間 = int( (SStage->GetWave()->現在Wave) * 60 * MainWitch->実ステ.回収速度 );
            強化or送還長さ = 送還時間;
            return true;
        }

        /**.*/
        void Act()
        {
            --送還時間;
            --強化時間;
            --待機時間;
            if (強化時間 == 0)
            {
                Lv++;
                強化時間 = -1;
                SetWait();
            }

            if (待機時間 <= 0 && 送還時間 < 0 && 強化時間 < 0)
            {
                auto 一番近い敵 = SStage->GetNearEnemy(this);

                if (一番近い敵)
                {
                    double 距離 = GetDistance(一番近い敵);
                
                    if (距離 <= 基礎ステ.射程[Lv])
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
            SStage->Add(new Shot(GetX(), GetY(), 角度, 基礎ステ, Lv, 支援補正));
        }

    };
}