#pragma    once//☀Unicode
#include    "Object.h"

namespace    SDX
{
class    Enemy    :public    Object
{
public:
                Enemy*    next;//当たり判定チェイン用
                int    方向    =    5;
                double    体力    =    1000;

                Enemy(    double    x,    double    y,    Image    *image    ,    Belong    所属    =    Belong::Ground)    :
                                Object(new    Rect(x,    y,    14,    14),    nullptr,所属)
                {}

                ///デフォルト死亡
                void    Dead()
                {
                                isRemove    =    true;
                                DeadSp();
                }

                //
                void    Act()
                {
                                switch    (belong)
                                {
                                case    Belong::Sky:
                                                方向    =    Land::now->空路.CulculateDistance(    方向    ,    (int)GetX(),    (int)GetY());
                                                break;
                                case    Belong::Sea:
                                                方向    =    Land::now->水路.CulculateDistance(方向,    (int)GetX(),    (int)GetY());
                                                break;
                                case    Belong::Ground:
                                                方向    =    Land::now->陸路.CulculateDistance(方向,    (int)GetX(),    (int)GetY());
                                                break;
                                }

                                double    speed    =    1;
                                if    (方向    %    2    ==    0)    speed    *=    0.7;
                                double    mx    =    (方向    %    3    -    1);
                                double    my    =    (方向    /    3    -    1);

                                Move(mx,    my);
                }

                //デバッグ用描画処理
                void    Draw()    const
                {
                                Drawing::Rect((int)GetX()-7,    (int)GetY()-7,    14,    14,    Color::Red,    false);
                }

                //消滅判定
                virtual    bool    RemoveCheck()
                {
                                int    x    =    (int)GetX()    /    20;
                                int    y    =    (int)GetY()    /    20;

                                if    (Land::now->地形[x][y]    ==    ChipType::塔)    isRemove    =    true;
                                if    (体力    <=    0)    Dead();
                                if    (isRemove)    Remove();

                                return    isRemove;
                }

                //攻撃された時の処理
                void    Damaged(double    damage)
                {
                                体力    -=    damage;
                                React();
                }

                //ダメージを受けた時の特殊処理
                virtual    void    React(){}

                //死亡時の特殊処理
                virtual    void    DeadSp(){};
};
}