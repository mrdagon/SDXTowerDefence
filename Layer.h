#pragma    once//☀Unicode
#include    "Object.h"

namespace    SDX
{
///                <summary>Objectのコンテナクラス</summary>
///                \include
template    <class    TObject>
class    Layer
{
public:
                std::vector<std::shared_ptr<TObject>>    objects;
                std::vector<std::shared_ptr<TObject>>    suspend;

                void    Add(TObject    *object    ,    int    suspend    =    0)
                {
                                object->SetTimer(-suspend);

                                if(    object->GetTimer()    >=    0    )
                                {
                                                this->objects.push_back(    std::shared_ptr<TObject>(object)    );
                                }else{
                                                this->suspend.push_back(    std::shared_ptr<TObject>(object)    );
                                }
                }

                void    Update(    )
                {
                                auto    it    =    suspend.begin();

                                while(    it    !=    suspend.end()    )
                                {
                                                (*it)->SetTimer(    (*it)->GetTimer()    +    1    );
                                                if(    (*it)->GetTimer()    >=    0    )
                                                {
                                                                objects.push_back(    (*it)    );
                                                                it    =    suspend.erase(    it    );
                                                                continue;
                                                }
                                                ++it;
                                }

                                for    (auto    &&    it    :    objects)
                                {
                                                it->Update();
                                }
                }

                void    Draw()
                {
                                for(    auto    it    :    objects    )
                                {
                                                it->Draw();
                                }
                }

                void    DrawShadow(double    X座標ずれ    ,    double    Y座標ずれ    )
                {
                                for(    auto    it    :    objects    )
                                {
                                                it->DrawShadow(    X座標ずれ    ,    Y座標ずれ);
                                }
                }

                void    ExeRemove()
                {

                                for    (auto    &&    it    :    objects)
                                {
                                                it->RemoveCheck();
                                }

                                auto    it    =    objects.begin();
                                while(    it    !=    objects.end()    )
                                {
                                                if(    (*it)->GetRemoveFlag()    )
                                                {
                                                                it    =    objects.erase(    it    );                                                                                
                                                }else{
                                                                ++it;
                                                }
                                }
                }

                void    Clear()
                {
                                objects.clear();
                                suspend.clear();
                }

                int    GetCount()
                {
                                return    (int)objects.size();
                }

                TObject*    GetNearest(Object*    object)
                {
                                double    nearest    =    -1;
                                TObject*    nearObject    =    nullptr;

                                for(    auto    it    :    objects    )
                                {
                                                double    dist    =    object->GetDistance(    it.get()    );
                                                if(    dist    <    nearest    ||    nearest    ==    -1)
                                                {
                                                                nearest    =    dist;
                                                                nearObject    =    it.get();
                                                }
                                }

                                return    nearObject;
                }

                TObject*    operator[](int    index)
                {
                                return    objects[index].get();
                }
};
}