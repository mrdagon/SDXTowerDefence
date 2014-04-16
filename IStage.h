#pragma once//☀Unicode
#include <SDXFrameWork.h>
#include <Framework/IScene.h>
#include <Utility/Module.h>

namespace SDX_TD
{
    using namespace SDX;
    class Object;
    class Enemy;
    class Magic;
    class Shot;

    /**.*/
    class IStage : public IScene
    {
    public:
        Object *selected = nullptr;//選択中のオブジェクト
        Object *popUp = nullptr;//マウスカーソルが乗っているオブジェクト

        /**敵や魔法が消滅する前に呼び出す.*/
        void 選択解除(Object* 消滅するオブジェクト)
        {
            if (selected == 消滅するオブジェクト) selected = nullptr;
        }

        /**.*/
        virtual void Add(Object *追加するオブジェクト, int 待機時間 = 0) = 0;
        virtual void Add(Magic  *追加するオブジェクト, int 待機時間 = 0) = 0;
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

    /**唯一のアクティブなStage.*/
    namespace{ IStage* SStage; }

}