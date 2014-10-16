//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include <SDXFramework.h>
#include <Framework/IScene.h>

namespace SDX_TD
{
    using namespace SDX;
    class IObject;
    class IEnemy;
    class IUnit;
    class IShot;
    class Wave;

    /**.*/
    class IStage : public IScene
    {
    public:
        IObject* selected = nullptr;//選択中のオブジェクト
        IEnemy* selectEnemy = nullptr;//選択中の敵
        IUnit* selectUnit = nullptr;//選択中の魔法

        /**敵や魔法が消滅する前に呼び出す.*/
        void 選択解除(IObject* 消滅するオブジェクト)
        {
            if (selected == 消滅するオブジェクト)
            {
                selected = nullptr;
                selectUnit = nullptr;
                selectEnemy = nullptr;
            }
        }

        virtual void Add( IObject *追加するオブジェクト, int 待機時間 = 0) = 0;
        virtual void Add( IUnit *追加するオブジェクト, int 待機時間 = 0) = 0;
        virtual void Add( IEnemy *追加するオブジェクト, int 待機時間 = 0) = 0;
        virtual void Add( IShot *追加するオブジェクト, int 待機時間 = 0) = 0;

        /**.*/
        virtual void AddFront( IObject* 追加するオブジェクト, int 待機時間 = 0) = 0;

        /**.*/
        virtual void AddBack( IObject* 追加するオブジェクト, int 待機時間 = 0) = 0;

        /**.*/
        virtual IObject* GetNearEnemy(IObject* 比較対象) = 0;

        /**.*/
        virtual double GetNearDirect(IObject* 比較対象) = 0;

        virtual Wave* GetWave() = 0;
    };

    /**唯一のアクティブなStage.*/
    namespace
    {
        IStage* SStage;

        template<class T>
        void SStageAdd(T &&追加オブジェクト)
        {
            SStage->Add(std::make_shared<T>(追加オブジェクト));
        }

    }

}