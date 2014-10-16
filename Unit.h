//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "Shot.h"
#include "IStage.h"
#include "Wave.h"
#include "DataType.h"
#include "Design.h"

namespace SDX_TD
{
    using namespace SDX;
    class IUnit : public IObject
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
        int    強化or送還長さ = 1;
        bool   is配置リスト = false;
        
        IUnit(IShape &図形, ISprite &描画方法, UnitType 魔法種) :
            IObject(図形, 描画方法,Belong::砲台),
            基礎ステ(UnitDataS[魔法種])
        {
            SetWait();
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
                Drawing::Rect({GetX()-Land::ChipSize, GetY()-Land::ChipSize,Land::ChipSize*2,Land::ChipSize*2},Color::Red,true);                
                Screen::SetBlendMode(BlendMode::NoBlend,255);
                Screen::SetBright({255,128,128});
                MSystem::フレーム[1].Draw({GetX()-Land::ChipSize, GetY()-Land::ChipSize,Land::ChipSize*2,Land::ChipSize*2});            
                Screen::SetBright(Color::White);
            }else{
                MSystem::フレーム[1].Draw({GetX()-Land::ChipSize, GetY()-Land::ChipSize,Land::ChipSize*2,Land::ChipSize*2});                        
            }

            //強化中or送還中
            if( 強化時間 > 0)
            {
                int Num = 99 - 強化時間*99/強化or送還長さ;   
                MFont::BMP黒.DrawExtend({ GetX() - 14, GetY() - 12 }, 2, 2, Color::White, { std::setw(2), Num });
            }
            else if( 送還時間 > 0)
            {
                int Num = 送還時間*99/強化or送還長さ;
                MFont::BMP黒.DrawExtend({ GetX() - 14, GetY() - 12 }, 2, 2, Color::White, { std::setw(2), Num });
            }
            else
            {
                MUnit::魔女[基礎ステ.魔法種][1]->DrawRotate({GetX(),GetY()},1,0);
            }

            //レベル表示
            for(int a=0;a<Lv;++a)
            {
                MSystem::マーク[3]->DrawRotate({ GetX() + 6 * a - 12, GetY() + 12 }, 1, 0);
            }
        }

        void DrawInfo() override
        {
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
                MFont::ゴシック中.DrawExtend({ UUnit::P強化().x - 16, UUnit::P強化().y + 13 }, 2, 2, Color::Red, "-");
                MFont::BMP白.DrawExtend({ UUnit::P強化().x - 6, (int)UUnit::P強化().y + 20 }, 2, 2, Color::White, { std::setw(4), 123 });

                //売却or発動
                MSystem::フレーム[8].Draw(UUnit::F回収());
                MFont::ゴシック中.DrawShadow( UUnit::P回収() , Color::White , Color::Gray , "回収");
                MFont::ゴシック中.DrawExtend({ UUnit::P回収().x - 12, UUnit::P回収().y + 13 }, 2, 2, Color::Blue, "+");
                MFont::BMP白.DrawExtend({ UUnit::P回収().x - 6, UUnit::P回収().y + 20 }, 2, 2, Color::White, { std::setw(4), 123 });

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
                    MFont::ゴシック中.Draw({ 565, UInfo::P性能アイコン(y).y + 8 }, Color::Yellow, "+");
                    //変化量
                    MIcon::UI[アイコン[a]].Draw( UInfo::P性能アイコン(y) );
                    MFont::BMP白.DrawExtend( UInfo::P性能(y) , 2 , 2 , Color::Yellow, {std::setw(10),次性能[a]-性能[a]} );
                }

                y += UInfo::ステ間();
            }

        }

        /*射程を表示する*/
        void DrawRange()
        {
                //射程表示
                Screen::SetBlendMode(BlendMode::Alpha,128);
                Drawing::Circle({GetX(),GetY(),(double)基礎ステ.射程[Lv]},Color::White,true);
                Screen::SetBlendMode(BlendMode::NoBlend,128);
                
                Screen::SetBright({255,0,0});
                Drawing::Circle({GetX(),GetY(),(double)基礎ステ.射程[Lv]},Color::Red,false);                
                Screen::SetBright({255,255,255});
        }

        /**.*/
        bool RemoveCheck() override
        {
            //送還
            if (送還時間 == 0) isRemove = true;

            if (isRemove)
            {
                const int x = int(GetX() - Size * Land::ChipSize) / Land::ChipSize + 1;
                const int y = int(GetY() - Size * Land::ChipSize) / Land::ChipSize + 1;
                SLand->RemoveUnit(x, y, Size);

                SStage->選択解除(this);
                Remove();
            }

            return this->isRemove;
        }

        bool 強化開始()
        {
            if (Lv >= 5) return false;
            if (強化時間 >0 || 送還時間 > 0) return false;
            

            int 必要MP = 基礎ステ.コスト[Lv+1] - 基礎ステ.コスト[Lv];

            強化時間 = int((Lv + 1) * (Lv + 1) * 60 * WITCH::Main->実ステ.強化速度);
            強化or送還長さ = 強化時間;

            return true;
        }

        bool 送還開始()
        {
            if (強化時間 >0 || 送還時間 > 0) return false;

            送還時間 = int( (SStage->GetWave()->現在Wave+1) * 60 * WITCH::Main->実ステ.回収速度 );
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
        virtual void Shoot(double 角度) = 0;
    };

    //弾の種類
    //発射方式
    class Unit : public IUnit
    {
    public:       
        Rect shape;
        SpImage sprite;

        //配置位置
        Unit(UnitType 魔法種):
            IUnit( shape,sprite, 魔法種 ),
            sprite(nullptr),
            shape( ((Input::mouse.x - Land::ChipSize/2) / Land::ChipSize+1) * Land::ChipSize , ((Input::mouse.y - Land::ChipSize/2) / Land::ChipSize+1) * Land::ChipSize , Size * Land::ChipSize/2, Size * Land::ChipSize/2 ,  Size * Land::ChipSize/2, Size * Land::ChipSize/2 )
        {

        }

        using ShotType = Shot<Circle,SpImage,MOTION::ToFront<SPEED::Liner>>;

        void Shoot(double 角度)
        {
            //SStage->Add( new ShotType({GetX(),GetY(),10,10},nullptr,角度,基礎ステ,{1.0},{1.0}));

            switch(基礎ステ.魔法種)
            {
            case UnitType::ライナ://防御低下3-8方向、師範強化
                break;
            case UnitType::ナツメ://周囲範囲攻撃、僧兵強化
                break;
            case UnitType::ルコウ://反射連射攻撃、騎士強化
                break;
            case UnitType::ディアネラ://チャージ攻撃、執事強化
                    SStage->Add( new ShotType({GetX(),GetY(),10},&MEffect::弾,{{1}},角度,基礎ステ));
                break;
            case UnitType::ミナエ://角度乱射、剣豪強化
                break;
            case UnitType::トレニア://レーザー攻撃、司祭強化
                break;
            case UnitType::ロチエ://長射程凍結、くの一強化
                break;
            case UnitType::バロゥ://ホーミング弾、勇者強化                
                    SStage->Add( new ShotType({GetX(),GetY(),10},&MEffect::弾,{{1}},角度,基礎ステ));
                break;
            case UnitType::フィオナ://吹き飛び付きレーザー、司祭強化
                break;
            case UnitType::ナズナ://高支援ユニット、軍師強化
                break;
            case UnitType::委員長://確定麻痺ホーミング弾、賢者強化
                break;
            case UnitType::ミルラ://高支援ユニット、将軍強化
                break;
            case UnitType::兵士://通路用A-単発直進
                break;
            case UnitType::傭兵://通路用A-単発直進
                break;
            case UnitType::足軽://通路用A-単発直進
                break;
            case UnitType::技師://必中追尾A-単発型
                break;
            case UnitType::勇者://必中追尾B-周囲展開型
                break;
            case UnitType::剣士://連射A-単発直進
                break;
            case UnitType::剣豪://連射B-乱射直進
                break;
            case UnitType::槍士://反射A-3WAY直進
                break;
            case UnitType::騎士://反射B-連射加速直進
                break;
            case UnitType::斧士://吹き飛びA-後ろ射出加速
                break;
            case UnitType::闘士://吹き飛びB-周囲回転
                break;
            case UnitType::武闘家://防御破壊A-加速弾
                break;
            case UnitType::師範://防御破壊B-炸裂弾
                break;
            case UnitType::狩人://対空専用A-長射程、3連射
                break;
            case UnitType::射手://対空専用B-中射程、高連射
                break;
            case UnitType::僧侶://対地範囲A-麻痺付与
                break;
            case UnitType::司祭://対地ビームB
                break;
            case UnitType::プリンス://3-8方向攻撃
                break;
            case UnitType::プリンセス://3-8方向攻撃
                break;
            case UnitType::魔術師://範囲A-加速弾、命中時範囲攻撃
                break;
            case UnitType::賢者://範囲B-ホーミング弾、命中時範囲攻撃
                break;
            case UnitType::踊り子://支援A-弱麻痺
                break;
            case UnitType::軍師://支援B-弱吹飛
                break;
            case UnitType::将軍://支援B-弱防御低下
                break;
            case UnitType::執事://使い捨てA-円形使い捨て
                break;
            case UnitType::給仕://使い捨てB-十字使い捨て
                break;
            case UnitType::料理人://使い捨てB-円形使い捨て
                break;
            case UnitType::盗賊://鈍足A-高連射、直進弾
                break;
            case UnitType::忍者://鈍足A-3-8方向、直進弾
                break;
            case UnitType::くノ一://鈍足B-低連射、炸裂効果
                break;
            }

            
        }

    };
}