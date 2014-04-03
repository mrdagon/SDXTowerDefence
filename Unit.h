#pragma    once//☀Unicode
#include    "Object.h"
#include    "Shot.h"
#include    "Scene.h"

namespace    SDX
{
class    Unit    :    public    Object
{
protected:
                virtual    void    Dead(){}
public:
                int    レベル    =    0;
                int    攻撃力    =    100;
                double    攻撃補正    =    1;
                int    攻撃間隔    =    60;
                int    待機時間;
                int    属性    =    0;
                int    送還時間    =    -1;
                int    強化時間    =    -1;
                int    大きさ;

                Unit(    int    X座標    ,    int    Y座標    ,    int    大きさ    ,    Sprite    *sprite    ):
                                Object(    new    Rect(X座標*20+大きさ*10,Y座標*20+大きさ*10,大きさ*20,大きさ*20)    ,    sprite    ,    Belong::Unit),
                                大きさ(大きさ)
                {
                                待機時間    =    攻撃間隔;
                }

                void    Draw()    const
                {
                                shape->Draw(Color::Green,    128);
                                Drawing::String(    (int)GetX()+2,    (int)GetY()+2,    Color::Red,    {    レベル    });
                }

                virtual    bool    RemoveCheck()
                {
                                //送還
                                if    (送還時間    ==    0)    isRemove    =    true;
                                if    (強化時間    ==    0)
                                {
                                                ++レベル;
                                                待機時間    =    攻撃間隔;
                                }

                                if    (isRemove    )
                                {
                                                const    int    x    =    int(GetX()    -    大きさ    *    10)    /    20;
                                                const    int    y    =    int(GetY()    -    大きさ    *    10)    /    20;
                                                Land::now->RemoveUnit(x,    y,    大きさ);
                                                Remove();
                                }

                                return    this->isRemove;
                }

                void    Act()
                {
                                --送還時間;
                                --強化時間;
                                --待機時間;
                                if    (強化時間    ==    0)
                                {
                                                レベル++;
                                                強化時間    =    -1;
                                                待機時間    =    攻撃間隔;
                                }

                                if    (待機時間    <=    0    &&    送還時間    <    0    &&    強化時間    <    0)
                                {
                                                Scene::Add(new    Shot((int)GetX(),    (int)GetY(),    Scene::GetNearDirect(this),    (1+レベル)    *    100    ));
                                                待機時間    =    攻撃間隔;
                                                if    (Rand::Get(9)    ==    0)    強化時間    =    (1    +    レベル)    *    120;
                                }
                }
};
}