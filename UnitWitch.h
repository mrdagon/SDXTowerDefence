#pragma once//☀Unicode
#include "Unit.h"
#include "Shot.h"
#include "EnumType.h"

namespace SDX_TD
{
namespace UNIT
{
    using namespace SDX;

    class ライナ : public Unit
    {
    public:
        ライナ():
            Unit(UnitType::ライナ)
        {}

        void Shoot(double 角度) override
        {
        }    
    };

    class ナツメ: public Unit
    {
    public:
        ナツメ():
            Unit(UnitType::ナツメ)
        {}

        void Shoot(double 角度) override
        {
        }    
    };

    class ルコウ : public Unit
    {
    public:
        ルコウ():
            Unit(UnitType::ルコウ)
        {}

        void Shoot(double 角度) override
        {
        }    
    };

    class ディアネラ : public Unit
    {
    public:
        ディアネラ():
            Unit(UnitType::ディアネラ)
        {}

        void Shoot(double 角度) override
        {
        }    
    };

    class ミナエ : public Unit
    {
    public:
        ミナエ():
            Unit(UnitType::ミナエ)
        {}

        void Shoot(double 角度) override
        {
        }    
    };


    class トレニア : public Unit
    {
    public:
        トレニア():
            Unit(UnitType::トレニア)
        {}

        void Shoot(double 角度) override
        {
        }    
    };
        
    class ロチエ : public Unit
    {
    public:
        ロチエ():
            Unit(UnitType::ロチエ)
        {}

        void Shoot(double 角度) override
        {
        }    
    };

    class バロゥ : public Unit
    {
    public:
        バロゥ():
            Unit(UnitType::バロゥ)
        {}

        void Shoot(double 角度) override
        {
        }    
    };

    class フィオナ : public Unit
    {
    public:
        フィオナ():
            Unit(UnitType::フィオナ)
        {}

        void Shoot(double 角度) override
        {
        }    
    };

    class ナズナ : public Unit
    {
    public:
        ナズナ():
            Unit(UnitType::ナズナ)
        {}

        void Shoot(double 角度) override
        {
        }    
    };

    class 委員長 : public Unit
    {
    public:
        委員長():
            Unit(UnitType::委員長)
        {}

        void Shoot(double 角度) override
        {
        }    
    };

    class ミルラ : public Unit
    {
    public:
        ミルラ():
            Unit(UnitType::ミルラ)
        {}

        void Shoot(double 角度) override
        {
        }    
    };
}
}