#pragma once//☀Unicode
#include "Unit.h"

namespace SDX_TD
{
    using namespace SDX;

    struct ActLiner
    {
        void CAct(Object *obj)
        {
            obj->MoveFront(2);
        }
    };

    struct ReactNone
    {
        void CReact(Object *obj)
        {}
    };

    template <class TAct = ActLiner , class TReact = ReactNone>
    class MyShot : public Shot , public TAct , public TReact
    {
    public:
        MyShot(double X座標, double Y座標, double 角度, UnitData &基礎ステ, int 強化回数, double 支援補正):
            Shot(X座標,Y座標, 角度, 基礎ステ, 強化回数, 支援補正)
        {}

        void Act() override
        {
            CAct(this);
        }
    
        void React() override
        {
            CReact(this);
        }
    };

    class 兵士 : public Unit
    {
    public:
        void Shoot(double 角度)
        {
            //シンプルな直進弾の場合ShotでOK
            MakeShot<MyShot<ActLiner,ReactNone>>(角度);
        }
    };


}