#pragma  once//☀Unicode
#include "Object.h"
#include "Shot.h"
#include "DataType.h"

namespace SDX_TD
{
    using namespace SDX;
    class Enemy :public Object
    {
    public:
        const static int 判定大きさ = 14;

        EnemyData &基礎ステ;
        Enemy*  next;//当たり判定チェイン用
        double  レベル = 0;
        int     方向   = 5;
        double  最大HP = 1000;
        double  残りHP = 1000;
        int     防御力 = 0;
        double  痺れ率 = 1.0;
        int     痺れ時間 = 0;
        int     眠り時間 = 0;
        double  吹き飛びX = 0;
        double  吹き飛びY = 0;
        bool    isボス = false;

        int     スコア;

        Enemy(double x, double y, EnemyData& 基礎ステ , bool isボス = false) :
            Object(new Rect( (x+0.5)*Land::ChipSize, (y+0.5)*Land::ChipSize, 14, 14), nullptr, 基礎ステ.移動タイプ),
            isボス(isボス),
            基礎ステ(基礎ステ)
        {
            スコア = int(基礎ステ.スコア * (1.0 + レベル/30 ));
            最大HP = 基礎ステ.最大HP * (1.0 + (レベル-1)* 0.2 + (レベル-1) * (レベル-1) * 0.06);
            防御力 = int(基礎ステ.防御力 * レベル);
            レベル = Rand::Get(2)+1;

            if (isボス)
            {
                スコア *= 16;
                最大HP *= 16;
                防御力 *= 2;
            }

            残りHP = 最大HP;
        }

        /**デフォルト死亡.*/
        void Dead()
        {
            //MP&SP&スコア増
            MainWitch->MP += スコア;
            MainWitch->SP += スコア;

            isRemove = true;
            DeadSp();
        }

        /**.*/
        void Act()
        {
            //方向を更新
            方向更新();

            double speed = 基礎ステ.移動速度;
            
            if ( isボス) speed *= 0.66;

            //痺れ、凍結補正
            if (眠り時間 > 0)
            {
                speed = 0;
                --眠り時間;
            }

            if (痺れ時間 > 0)
            {
                speed = speed * 痺れ率;
            }

            if (SLand->Get地形(GetX(), GetY()) == ChipType::沼 && 基礎ステ.移動タイプ != Belong::空)
            {
                speed /= 2;
            }

            //斜め移動補正
            if (方向 % 2 == 0) speed *= 0.7;

            double mx = (方向 % 3 - 1) * speed * 基礎ステ.移動速度;
            double my = (方向 / 3 - 1) * speed * 基礎ステ.移動速度;

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
            case Belong::水陸:
                方向 = SLand->水路.方向計算(方向, (int)GetX(), (int)GetY());
                break;
            case Belong::水中:
                方向 = SLand->海路.方向計算(方向, (int)GetX(), (int)GetY());
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

            MUnit::敵[基礎ステ.種族][アニメ]->DrawRotate(int(GetX()),int(GetY()),2+isボス,0,反転);

            //Drawing::Rect((int)GetX() - 7, (int)GetY() - 7, 14, 14, Color::Red, false);
        }

        /**消滅判定.*/
        bool RemoveCheck() override
        {
            const int x = (int)GetX() / Land::ChipSize;
            const int y = (int)GetY() / Land::ChipSize;

            //ゴール判定
            if ( SLand->地形[x][y] == ChipType::畑)
            {
                isRemove = true;
                SStage->選択解除(this);
            }

            if (残りHP <= 0) Dead();
            if (isRemove)  Remove();

            return isRemove;
        }

        /**攻撃された時の処理.*/
        void Damaged(Shot* 衝突相手)
        {
            double ダメージ量 = 衝突相手->攻撃力;

            //属性効果判定
            if (衝突相手->デバフ効果 > 0)
            {
                switch (衝突相手->基礎ステ.デバフ種)
                {
                    case DebuffType::痺れ: 痺れ付与(衝突相手); break;
                    case DebuffType::眠り: 眠り付与(衝突相手); break;
                    case DebuffType::吹飛: 吹飛付与(衝突相手); break;
                    case DebuffType::防壊: 防壊付与(衝突相手); break;
                    default:break;
                }
            }

            //弱点補正
            if ( 弱点判定(衝突相手) )
            {
                ダメージ量 *= MainWitch->弱点補正;
            }

            //防御補正
            ダメージ量 = std::max( ダメージ量 - 防御力 , 1.0);

            残りHP -= ダメージ量;
            React( ダメージ量 );
        }

        void 眠り付与(Shot* 衝突相手)
        {
            //判定
            if (!Rand::Coin(衝突相手->デバフ率)) return;
            if ( 基礎ステ.異状耐性[(int)DebuffType::眠り] ) return;

            //付与処理
            眠り時間 = std::max(衝突相手->デバフ効果, 眠り時間);
        }
        void 痺れ付与(Shot* 衝突相手)
        {
            //判定
            if ( 基礎ステ.異状耐性[(int)DebuffType::痺れ]) return;

            if (痺れ時間 <= 0) 痺れ率 = 1.0;

            //付与処理
            痺れ率 = std::min( 1-衝突相手->デバフ率 , 痺れ率);
            痺れ時間 = std::max(衝突相手->デバフ効果, 痺れ時間);
        }
        void 吹飛付与(Shot* 衝突相手)
        {
            //判定
            if (基礎ステ.異状耐性[(int)DebuffType::吹飛] ) return;

            //付与処理
            const double 吹き飛び距離 = 衝突相手->デバフ効果;

            吹き飛びX += std::cos(衝突相手->GetAngle()) * 吹き飛び距離;
            吹き飛びY += std::sin(衝突相手->GetAngle()) * 吹き飛び距離;
        }
        void 防壊付与(Shot* 衝突相手)
        {
            //判定
            if (基礎ステ.異状耐性[(int)DebuffType::吹飛]) return;

            //付与処理
            防御力 = std::max(0, 防御力 - 衝突相手->デバフ効果);
        }


        bool 弱点判定(Shot* 衝突相手)
        {
            return
                (
                    (衝突相手->基礎ステ.魔法属性 == Elements::炎 && 基礎ステ.魔法属性 == Elements::氷) ||
                    (衝突相手->基礎ステ.魔法属性 == Elements::氷 && 基礎ステ.魔法属性 == Elements::炎) ||
                    (衝突相手->基礎ステ.魔法属性 == Elements::樹 && 基礎ステ.魔法属性 == Elements::空) ||
                    (衝突相手->基礎ステ.魔法属性 == Elements::空 && 基礎ステ.魔法属性 == Elements::樹)
                );
        }

        /**ダメージを受けた時の特殊処理.*/
        virtual void React(double ダメージ量){}

        /**死亡時の特殊処理.*/
        virtual void DeadSp(){}

        /**敵別の特殊処理.*/
        virtual void ActSp(){}

    };
}