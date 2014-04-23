#pragma  once//☀Unicode
#include "Object.h"
#include "Shot.h"
#include "EnemyData.h"

namespace SDX_TD
{
    using namespace SDX;
    class Enemy :public Object
    {
    public:
        EnemyData &基礎ステ;
        Enemy*  next;//当たり判定チェイン用
        int     レベル = 0;
        int     方向   = 5;
        double  最大HP = 1000;
        double  体力   = 1000;
        int     防御力 = 0;
        int     麻痺時間 = 0;
        int     凍結時間 = 0;
        int     炎上時間 = 0;
        double  吹き飛びX = 0;
        double  吹き飛びY = 0;
        bool    isボス = false;

        Enemy(double x, double y, EnemyData& 基礎ステ , bool isボス = false) :
            Object(new Rect( (x+0.5)*Land::ChipSize, (y+0.5)*Land::ChipSize, 14, 14), nullptr, 基礎ステ.移動タイプ),
            isボス(isボス),
            基礎ステ(基礎ステ)
        {}

        /**デフォルト死亡.*/
        void Dead()
        {
            //MP&SP&スコア増

            isRemove = true;
            DeadSp();
        }

        /**.*/
        void Act()
        {
            //炎上による方向固定

            switch (belong)
            {
            case Belong::空:
                方向 = SLand->空路.距離計算(方向, (int)GetX(), (int)GetY());
                break;
            case Belong::陸:
                方向 = SLand->陸路.距離計算(方向, (int)GetX(), (int)GetY());
                break;
            case Belong::水陸:
                方向 = SLand->水路.距離計算(方向, (int)GetX(), (int)GetY());
                break;
            case Belong::水中:
                方向 = SLand->海路.距離計算(方向, (int)GetX(), (int)GetY());
                break;
            }

            double speed = 1;

            //痺れ、凍結補正

            //斜め移動補正
            if (方向 % 2 == 0) speed *= 0.7;

            double mx = (方向 % 3 - 1);
            double my = (方向 / 3 - 1);

            //吹き飛び処理
            if (吹き飛びX > 0)
            {
                mx += 吹き飛びX / 8;
                吹き飛びX *= 7.0 / 8;
            }
            if (吹き飛びY > 0)
            {
                my += 吹き飛びX / 8;
                吹き飛びY *= 7.0 / 8;
            }

            //地形衝突処理

            //移動処理
            Move(mx, my);

            //敵毎の特殊処理
            ActSp();
        }

        /**デバッグ用描画処理.*/
        void Draw() const
        {
            Drawing::Rect((int)GetX() - 7, (int)GetY() - 7, 14, 14, Color::Red, false);
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

            if (体力 <= 0) Dead();
            if (isRemove)  Remove();

            return isRemove;
        }

        /**攻撃された時の処理.*/
        void Damaged(Object* 衝突相手) override
        {
        }

        /**攻撃された時の処理.*/
        void Damaged(Shot* 衝突相手)
        {
            double ダメージ量 = 衝突相手->攻撃力;
            //弱点補正
            
            //防御補正

            //属性効果判定

            //最低ダメージ補正

            体力 -= ダメージ量;

            React( ダメージ量 );
        }

        /**ダメージを受けた時の特殊処理.*/
        virtual void React(double ダメージ量){}

        /**死亡時の特殊処理.*/
        virtual void DeadSp(){}

        /**敵別の特殊処理.*/
        virtual void ActSp(){}

    };
}