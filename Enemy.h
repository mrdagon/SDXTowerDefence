//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "Shot.h"
#include "DataType.h"
#include "Design.h"

namespace SDX_TD
{
    using namespace SDX;
    class IEnemy :public IObject
    {
    public:
        const static int 判定大きさ = 14;

        EnemyData &基礎ステ;
        IEnemy*  next;//当たり判定チェイン用
        int     レベル = 0;
        int     方向   = 5;
        double  最大HP = 1000;
        double  残りHP = 1000;
        int     防御力 = 0;
        double  回避力 = 0;
        double  鈍足率 = 1.0;
        double  再生力 = 0;
        int     鈍足時間 = 0;
        int     麻痺時間 = 0;
        double  吹き飛びX = 0;
        double  吹き飛びY = 0;
        bool    isBoss = false;

        int     スコア;

        IEnemy(IShape &図形, ISprite &描画方法, EnemyData& 基礎ステ, bool isBoss) :
            IObject(図形, 描画方法, 基礎ステ.移動タイプ),
            isBoss(isBoss),
            基礎ステ(基礎ステ)
        {
            スコア = int(基礎ステ.スコア * (1.0 + レベル/30 ));
            最大HP = 基礎ステ.最大HP * (1.0 + (レベル-1)* 0.2 + (レベル-1) * (レベル-1) * 0.06);
            防御力 = int(基礎ステ.防御力 * レベル);
            レベル = Rand::Get(2)+1;

            if (isBoss)
            {
                スコア *= 16;
                最大HP *= 16;
                防御力 *= 2;
            }

            残りHP = 最大HP;
        }

        virtual ~IEnemy(){}

        /**デフォルト死亡.*/
        void Dead()
        {
            //MP&SP&スコア増
            WITCH::Main->MP += スコア;
            WITCH::Main->SP += スコア;

            isRemove = true;
            DeadSp();
        }

        /**.*/
        void Act()
        {
            //方向を更新
            方向更新();

            double speed = 基礎ステ.移動速度;
            
            if ( isBoss) speed *= 0.66;

            //異常補正
            if (麻痺時間 > 0)
            {
                speed = 0;
                --麻痺時間;
            }

            if (鈍足時間 > 0)
            {
                speed = speed * 鈍足率;
            }

            if (SLand->Get地形(GetX(), GetY()) == ChipType::沼 && 基礎ステ.移動タイプ != Belong::空)
            {
                speed /= 2;
            }

            //斜め移動補正
            if (方向 % 2 == 0) speed *= 0.7;

            double mx = (方向 % 3 - 1) * speed;
            double my = (方向 / 3 - 1) * speed;

            //吹き飛び処理
            mx += 吹き飛びX / 8;
            吹き飛びX *= 7.0 / 8;
            
            my += 吹き飛びY / 8;
            吹き飛びY *= 7.0 / 8;

            地形処理(mx , my);

            地形衝突(mx, my);

            Move(mx, my);

            //敵毎の特殊処理
            ActSp();
        }

        void 方向更新()
        {
            switch (belong)
            {
            case Belong::空:
                方向 = SLand->空路.方向計算(方向, (int)GetX(), (int)GetY());
                break;
            case Belong::陸:
                方向 = SLand->陸路.方向計算(方向, (int)GetX(), (int)GetY());
                break;
            case Belong::水:
                方向 = SLand->水路.方向計算(方向, (int)GetX(), (int)GetY());
                break;
            }

        }

        /**特殊地形の処理.*/
        void 地形処理(double &移動量X , double &移動量Y)
        {
            //飛んでる敵は影響無し
            if (基礎ステ.移動タイプ == Belong::空) return;

            auto 地形種 = SLand->Get地形(GetX(), GetY());

            switch (地形種)
            {
            case SDX_TD::ChipType::沼:
                移動量X /= 2;
                移動量Y /= 2;
                break;
            case SDX_TD::ChipType::↑:
                移動量Y -= Land::自動床速度;
                break;
            case SDX_TD::ChipType::↓:
                移動量Y += Land::自動床速度;
                break;
            case SDX_TD::ChipType::←:
                移動量X -= Land::自動床速度;
                break;
            case SDX_TD::ChipType::→:
                移動量X += Land::自動床速度;
                break;
            default:
                break;
            }

        }

        /**地形との衝突.*/
        void 地形衝突(double &移動量X, double &移動量Y)
        {
            const int X差 = (int)GetX() % Land::ChipSize;
            const int Y差 = (int)GetY() % Land::ChipSize;

            //各方向にはみ出ているか
            const bool is↑ = Y差 < 7;
            const bool is↓ = Y差 > 8;
            const bool is← = X差 < 7;
            const bool is→ = X差 > 8;

            bool 衝突[9] = {};

            //平面にめりこみ
            if (is↑)         衝突[1] = SLand->Check地形(GetX()    , GetY() - 7, 基礎ステ.移動タイプ);
            if (is←)         衝突[3] = SLand->Check地形(GetX() - 7, GetY()    , 基礎ステ.移動タイプ);
            if (is→)         衝突[5] = SLand->Check地形(GetX() + 7, GetY()    , 基礎ステ.移動タイプ);
            if (is↓)         衝突[6] = SLand->Check地形(GetX() - 7, GetY() + 7, 基礎ステ.移動タイプ);

            //角にめりこみ
            if (is↑ && is←) 衝突[0] = SLand->Check地形(GetX() - 7, GetY() - 7, 基礎ステ.移動タイプ);
            if (is↑ && is→) 衝突[2] = SLand->Check地形(GetX() + 7, GetY() - 7, 基礎ステ.移動タイプ);
            if (is↓ && is←) 衝突[7] = SLand->Check地形(GetX()    , GetY() + 7, 基礎ステ.移動タイプ);
            if (is↓ && is→) 衝突[8] = SLand->Check地形(GetX() + 7, GetY() + 7, 基礎ステ.移動タイプ);

            //現在のマスが移動不可能
            衝突[4] = SLand->Check地形(GetX(), GetY(), 基礎ステ.移動タイプ);

            //斜め衝突
            if (衝突[0] && 衝突[1] == 衝突[3])
            {
                移動量X += 7 - X差;
                移動量Y += 7 - Y差;
                //移動量X += 2;
                //移動量Y += 2;
                return;
            }

            if (衝突[2] && 衝突[1] == 衝突[5])
            {
                移動量X += 7 - X差;
                移動量Y += 7 - Y差;
                //移動量X -= 2;
                //移動量Y += 2;
                return;
            }

            if (衝突[6] && 衝突[3] == 衝突[7])
            {
                移動量X += 7 - X差;
                移動量Y += 7 - Y差;
                //移動量X += 2;
                //移動量Y -= 2;
                return;
            }

            if (衝突[8] && 衝突[5] == 衝突[7])
            {
                移動量X += 7 - X差;
                移動量Y += 7 - Y差;
                //移動量X -= 2;
                //移動量Y -= 2;
                return;
            }

            if ( 衝突[3] )
            {
                移動量X += 7 - X差;
                //移動量X += 2;
            }
            if ( 衝突[5] )
            {
                移動量X += 7 - X差;
                //移動量X -= 2;
            }
            if ( 衝突[1] )
            {
                移動量Y += 7 - Y差;
                //移動量Y += 2;
            }
            if ( 衝突[7] )
            {
                移動量Y += 7 - Y差;
                //移動量Y -= 2;
            }

        }

        /**デバッグ用描画処理.*/
        void Draw() const
        {
            int アニメ;
            bool 反転 = false;

            switch (方向)
            {
            case 0:
            case 1:
                アニメ = 3;
                break;
            case 2:
            case 5:
                アニメ = 6;
                反転 = true;
                break;
            case 3:
            case 6:
                アニメ = 6;
                break;
            case 7:
            case 8:
                アニメ = 0;
                break;
            }

            switch(timer/10%4)
            {
            case 0:
                break;
            case 1:
            case 3:
                アニメ += 1;
                break;
            case 2:
                アニメ += 2;
                break;
            }

            MUnit::敵[基礎ステ.種族][アニメ]->DrawRotate({ GetX(), GetY() }, 1 + isBoss, 0, 反転);

            //ターゲット
            if(SStage->selected == this)
            {
                MIcon::ターゲット[(timer / 10) % 3]->DrawRotate({ GetX(), GetY() }, 1, 0);
            }
        }

        /**Stage右に表示する情報.*/
        void DrawInfo() override
        {
            //画像&名前
            MSystem::フレーム[5].Draw( UInfo::F名前() );
            MUnit::敵[基礎ステ.種族][1]->DrawRotate( UInfo::P画像() , 2 , 0 );
            MFont::ゴシック中.DrawShadow( UInfo::P名前() , Color::White , Color::Gray , 基礎ステ.種族名);
           
            //説明文
            MSystem::フレーム[5].Draw( UInfo::F説明());
            MFont::ゴシック小.DrawShadow( UInfo::P説明() , Color::White , Color::Gray , 基礎ステ.説明文);

            //性能
            
            IconType IconNo[7] = 
            {   
                IconType::レベル,
                IconType::ライフ,
                IconType::速度,
                IconType::マナ,
                IconType::防御,
                IconType::回避,
                IconType::回復
            };
            int Num[7] =
            {
                レベル,
                (int)残りHP,
                (int)(基礎ステ.移動速度 * 10),
                スコア,
                防御力,
                (int)回避力,
                (int)再生力
            };

            int y = 0;

            for(int a=0;a<6;++a)
            {
                if(Num[a] <= 0 && a > 3) continue;//防御と回避は0なら表示しない

                Screen::SetBright({128,128,255});
                MSystem::フレーム[5].Draw( UInfo::F性能(y) );
                Screen::SetBright({255,255,255});
                MIcon::UI[IconNo[a]].Draw( UInfo::P性能アイコン(y) );
                MFont::BMP白.DrawExtend( UInfo::P性能(y) , 2 , 2 , Color::White, { std::setw(10) , Num[a]} );
                y += UInfo::ステ間();
            }
        }

        /**消滅判定.*/
        bool RemoveCheck() override
        {
            const int x = (int)GetX() / Land::ChipSize;
            const int y = (int)GetY() / Land::ChipSize;

            //ゴール判定
            if ( SLand->地形[x][y] == ChipType::畑)
            {
                WITCH::Main->Damage();
                isRemove = true;
                SStage->選択解除(this);
            }

            if (残りHP <= 0) Dead();
            if (isRemove)  Remove();

            return isRemove;
        }

        /**攻撃された時の処理.*/
        void Damaged(IShot* 衝突相手)
        {
            double ダメージ量 = 衝突相手->攻撃力;

            //属性効果判定
            if (衝突相手->デバフ効果 > 0 && !基礎ステ.特殊耐性[衝突相手->基礎ステ.デバフ種])
            {
                switch (衝突相手->基礎ステ.デバフ種)
                {
                case DebuffType::鈍足: 鈍足付与(衝突相手); break;
                case DebuffType::麻痺: 麻痺付与(衝突相手); break;
                    case DebuffType::吹飛: 吹飛付与(衝突相手); break;
                    case DebuffType::防壊: 防壊付与(衝突相手); break;
                    default:break;
                }
            }

            //弱点補正
            if ( 弱点判定(衝突相手) )
            {
                ダメージ量 *= WITCH::Main->実ステ.弱点補正;
            }

            //防御補正
            ダメージ量 = std::max( ダメージ量 - 防御力 , 1.0);

            残りHP -= ダメージ量;
            React( ダメージ量 );
        }

        void 麻痺付与(IShot* 衝突相手)
        {
            //判定
            if (!Rand::Coin(衝突相手->デバフ率)) return;

            //付与処理
            麻痺時間 = std::max(衝突相手->デバフ効果, 麻痺時間);
        }
        void 鈍足付与(IShot* 衝突相手)
        {
            if (鈍足時間 <= 0) 鈍足率 = 1.0;

            //付与処理
            鈍足率 = std::min( 1-衝突相手->デバフ率 , 鈍足率);
            鈍足時間 = std::max(衝突相手->デバフ効果, 鈍足時間);
        }
        void 吹飛付与(IShot* 衝突相手)
        {
            //付与処理
            const double 吹き飛び距離 = 衝突相手->デバフ効果;

            吹き飛びX += std::cos(衝突相手->GetAngle()) * 吹き飛び距離;
            吹き飛びY += std::sin(衝突相手->GetAngle()) * 吹き飛び距離;
        }
        void 防壊付与(IShot* 衝突相手)
        {
            //付与処理
            防御力 = std::max(0, 防御力 - 衝突相手->デバフ効果);
        }

        bool 弱点判定(IShot* 衝突相手)
        {
            return
                (
                    (衝突相手->基礎ステ.属性 == Element::炎 && 基礎ステ.属性 == Element::氷) ||
                    (衝突相手->基礎ステ.属性 == Element::氷 && 基礎ステ.属性 == Element::炎) ||
                    (衝突相手->基礎ステ.属性 == Element::樹 && 基礎ステ.属性 == Element::空) ||
                    (衝突相手->基礎ステ.属性 == Element::空 && 基礎ステ.属性 == Element::樹)
                );
        }

        /**ダメージを受けた時の特殊処理.*/
        virtual void React(double ダメージ量){}

        /**死亡時の特殊処理.*/
        virtual void DeadSp(){}

        /**敵別の特殊処理.*/
        virtual void ActSp(){}
    };
    
    class Enemy : public IEnemy
    {
    public:
        Rect shape;
        SpNull 描画方法;

        Enemy(double X座標 , double Y座標 , EnemyType 敵種類 , bool isBoss):
            IEnemy(shape,描画方法,EnemyDataS[敵種類],isBoss),
            shape( (X座標+0.5)*Land::ChipSize, (Y座標+0.5)*Land::ChipSize, 14, 14)
        {
            
        }
    };
}