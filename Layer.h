#pragma once//©SDXFramework http://sourceforge.jp/projects/dxframework/
#include "Object.h"

namespace SDX_TD
{
    using namespace SDX;
    /**Objectのコンテナクラス.*/
    template <class TObject>
    class Layer
    {
    public:
        std::vector<std::shared_ptr<TObject>> objectS;
        std::vector<std::shared_ptr<TObject>> suspendS;

        /**.*/
        void Add(TObject *挿入するObject, int 待機フレーム数 = 0)
        {
            挿入するObject->SetTimer(-待機フレーム数);

            if (挿入するObject->GetTimer() >= 0)
            {
                this->objectS.push_back( std::shared_ptr<TObject>(挿入するObject) );
            }
            else{
                this->suspendS.push_back( std::shared_ptr<TObject>(挿入するObject) );
            }
        }

        /**.*/
        void Update()
        {
            auto it = suspendS.begin();

            while (it != suspendS.end())
            {
                (*it)->SetTimer((*it)->GetTimer() + 1);
                if ((*it)->GetTimer() >= 0)
                {
                    objectS.push_back((*it));
                    it = suspendS.erase(it);
                    continue;
                }
                ++it;
            }

            for (auto && it : objectS)
            {
                it->Update();
            }
        }

        /**.*/
        void Draw() const
        {
            for (auto &&it : objectS)
            {
                it->Draw();
            }
        }

        /**.*/
        void DrawShadow(double X座標ずれ, double Y座標ずれ) const
        {
            for (auto it : objectS)
            {
                it->DrawShadow(X座標ずれ, Y座標ずれ);
            }
        }

        /**.*/
        void ExeRemove()
        {
            for (auto && it : objectS)
            {
                it->RemoveCheck();
            }

            auto  it = objectS.begin();
            while (it != objectS.end())
            {
                if ((*it)->GetRemoveFlag())
                {
                    it = objectS.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        /**.*/
        void Clear()
        {
            objectS.clear();
            suspendS.clear();
        }

        /**.*/
        int GetCount()
        {
            return (int)objectS.size();
        }

        /**.*/
        TObject* GetNearest(IObject* 比較対象)
        {
            double   nearest = -1;
            TObject* nearObject = nullptr;

            for (auto it : objectS)
            {
                double dist = 比較対象->GetDistance(it.get());
                if (dist < nearest || nearest == -1)
                {
                    nearest    = dist;
                    nearObject = it.get();
                }
            }

            return nearObject;
        }

        /**.*/
        TObject* operator[](int index)
        {
            return objectS[index].get();
        }
    };
}