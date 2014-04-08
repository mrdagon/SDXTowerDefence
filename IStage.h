#pragma once//☀Unicode
#include <SDXFrameWork.h>
#include <Framework/IScene.h>
#include <Utility/Module.h>
#include "RouteMap.h"
#include "Layer.h"

namespace SDX
{
    class Enemy;
    class Unit;
    class Shot;

    /**.*/
    class IStage : public IScene
    {
    public:
        static IStage* now;

        /**.*/
        virtual void Add(Object *追加するオブジェクト, int 待機時間 = 0) = 0;
        virtual void Add(Unit   *追加するオブジェクト, int 待機時間 = 0) = 0;
        virtual void Add(Enemy  *追加するオブジェクト, int 待機時間 = 0) = 0;
        virtual void Add(Shot   *追加するオブジェクト, int 待機時間 = 0) = 0;

        /**.*/
        virtual void AddFront(Object *追加するオブジェクト, int 待機時間 = 0) = 0;

        /**.*/
        virtual void AddBack(Object *追加するオブジェクト, int 待機時間 = 0) = 0;

        /**.*/
        virtual void AddEvent(IModule *追加する関数オブジェクト) = 0;

        /**.*/
        virtual Object* GetNearEnemy(Object* 比較対象) = 0;

        /**.*/
        virtual double GetNearDirect(Object* 比較対象) = 0;

    };
}