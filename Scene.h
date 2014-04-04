#pragma once//☀Unicode
#include <SDXFrameWork.h>
#include <Framework/IScene.h>
#include <Utility/Module.h>
#include "RouteMap.h"
#include "Layer.h"

namespace SDX
{
    /**.*/
    class Scene : public IScene
    {
    private:
        Layer<Object> backEffectS;
        Layer<Object> midEffectS;
        Layer<Object> frontEffectS;

        Layer<Object> skyEnemyS;
        Layer<Object> seaEnemyS;
        Layer<Object> groundEnemyS;

        Layer<Object> shotS;

        Layer<Object> unitS;

        std::vector<std::shared_ptr<IModule>> eventS;

        static Scene* now;

        /**レイヤー等を初期化.*/
        void Clear()
        {
            timer = 0;

            backEffectS.Clear();
            midEffectS.Clear();
            frontEffectS.Clear();

            skyEnemyS.Clear();
            groundEnemyS.Clear();
            seaEnemyS.Clear();

            shotS.Clear();
            unitS.Clear();
        }

        /**当たり判定処理を行う.*/
        void Hit()
        {
            //分割木を作成
            Object* chainFirst[24][24] = {};
            Object* chainEnd[24][24] = {};

            for (auto &&it : groundEnemyS.objectS)
            {
                const int x = (int)it->GetX() / 20;
                const int y = (int)it->GetY() / 20;
                if (chainFirst[x][y] == nullptr)
                {
                    chainFirst[x][y] = it.get();
                    chainEnd[x][y] = it.get();
                }
                else
                {
                    chainEnd[x][y]->next = it.get();
                    chainEnd[x][y] = it.get();
                }
                it->next = nullptr;
            }

            for (auto &&it : skyEnemyS.objectS)
            {
                const int x = (int)it->GetX() / 20;
                const int y = (int)it->GetY() / 20;
                if (chainFirst[x][y] == nullptr)
                {
                    chainFirst[x][y] = it.get();
                    chainEnd[x][y] = it.get();
                }
                else
                {
                    chainEnd[x][y]->next = it.get();
                    chainEnd[x][y] = it.get();
                }
                it->next = nullptr;
            }
            for (auto &&it : seaEnemyS.objectS)
            {
                const int x = (int)it->GetX() / 20;
                const int y = (int)it->GetY() / 20;
                if (chainFirst[x][y] == nullptr)
                {
                    chainFirst[x][y] = it.get();
                    chainEnd[x][y] = it.get();
                }
                else
                {
                    chainEnd[x][y]->next = it.get();
                    chainEnd[x][y] = it.get();
                }
                it->next = nullptr;
            }

            //判定開始
            for (auto && shot : shotS.objectS)
            {
                const int xa = (int)(shot->GetX() - 10) / 20;
                const int ya = (int)(shot->GetY() - 10) / 20;
                const int xb = (int)(shot->GetX() + 10) / 20;
                const int yb = (int)(shot->GetY() + 10) / 20;
                Object* it;

                if (xa >= 0 && xa < 24)
                {
                    if (ya >= 0 && ya < 24)
                    {
                        it = chainFirst[xa][ya];
                        while (it)
                        {
                            if (shot->Hit(it))
                            {
                                shot->Damaged(it->power);
                                it->Damaged(shot->power);
                            }
                            it = it->next;
                        }
                    }
                    if (yb >= 0 && yb < 24 && ya != yb)
                    {
                        it = chainFirst[xa][yb];
                        while (it)
                        {
                            if (shot->Hit(it))
                            {
                                shot->Damaged(it->power);
                                it->Damaged(shot->power);
                            }
                            it = it->next;
                        }
                    }
                }
                if (xb >= 0 && xb < 24 && xa != xb)
                {
                    if (ya >= 0 && ya < 24)
                    {
                        it = chainFirst[xb][ya];
                        while (it)
                        {
                            if (shot->Hit(it))
                            {
                                shot->Damaged(it->power);
                                it->Damaged(shot->power);
                            }
                            it = it->next;
                        }
                    }

                    if (yb >= 0 && yb < 24 && ya != yb)
                    {
                        it = chainFirst[xb][yb];
                        while (it)
                        {
                            if (shot->Hit(it))
                            {
                                shot->Damaged(it->power);
                                it->Damaged(shot->power);
                            }
                            it = it->next;
                        }
                    }
                }
            }
        }

    public:
        int timer = 0;

        std::unique_ptr<Camera> camera;
        Object *selected;//選択中のオブジェクト

        Scene() :
            camera(new Camera(400, 300, 1))
        {
            SetNow();
        }

        virtual ~Scene(){}

        /**.*/
        void Init()
        {
            if( !Land::now )Land::now = new Land::Land<24, 24>();
            Land::now->Init();
        }

        /**.*/
        void SetNow()
        {
            now = this;
            camera->SetActive();
        }

        /**.*/
        static Scene* Now()
        {
            return now;
        }

        /**地形の敵配置状態を更新.*/
        static void LandUpdate()
        {
            Land::now->InitEnemyPost();

            for (auto &&it : now->groundEnemyS.objectS)
            {
                Land::now->SetGroungPost((int)it->GetX(), (int)it->GetY());
            }

            for (auto &&it : now->seaEnemyS.objectS)
            {
                Land::now->SetSeaPost((int)it->GetX(), (int)it->GetY());
            }
        }

        /**.*/
        virtual void Update()
        {
            SetNow();
            ++timer;

            //イベント処理
            for (auto it : eventS)
            {
                it->Update();
            }

            //レイヤー処理
            backEffectS.Update();
            midEffectS.Update();
            frontEffectS.Update();

            skyEnemyS.Update();
            groundEnemyS.Update();
            seaEnemyS.Update();

            shotS.Update();
            unitS.Update();

            camera->Update();

            Hit();

            //消滅処理
            backEffectS.ExeRemove();
            midEffectS.ExeRemove();
            frontEffectS.ExeRemove();

            skyEnemyS.ExeRemove();
            groundEnemyS.ExeRemove();
            seaEnemyS.ExeRemove();

            shotS.ExeRemove();
            unitS.ExeRemove();
        }

        /**.*/
        virtual void Draw()
        {
            SetNow();

            for (int i = 0; i < 481; i += 20)
            {
                Drawing::Line(i, 0, i, 480, Color::White, 1);
                Drawing::Line(0, i, 480, i, Color::White, 1);
            }

            for (int i = 0; i < 24; ++i)
            {
                for (int j = 0; j < 24; ++j)
                {
                    if (Land::now->地形[i][j] != ChipType::草)  Drawing::Rect( i * 20 , j * 20 , 20 , 20 , Color::Blue   , true);
                    if (Land::now->地形[i][j] == ChipType::塔)  Drawing::Rect( i * 20 , j * 20 , 20 , 20 , Color::Red    , true);
                    if (Land::now->砲台配置[i][j])              Drawing::Rect( i * 20 , j * 20 , 20 , 20 , Color::Yellow , true);
                    if (Land::now->地上配置[i][j])              Drawing::Rect( i * 20 , j * 20 , 20 , 20 , Color::Gray   , true);
                    if (Land::now->水上配置[i][j])              Drawing::Rect( i * 20 , j * 20 , 20 , 20 , Color::Purple , true);
                }
            }

            backEffectS.Draw();
            unitS.Draw();
            seaEnemyS.Draw();
            groundEnemyS.Draw();

            Screen::SetBright({ 0, 0, 0 });
            Screen::SetBlendMode(BlendMode::Alpha, 128);
            skyEnemyS.DrawShadow(12, 12);
            Screen::SetBlendMode(BlendMode::NoBlend, 0);
            Screen::SetBright({ 255, 255, 255 });

            midEffectS.Draw();
            shotS.Draw();
            skyEnemyS.Draw();
            frontEffectS.Draw();
        }

        /**.*/
        static void Add( Object *追加するオブジェクト , int 待機時間 = 0)
        {
            switch (追加するオブジェクト->GetBelong())
            {
            case Belong::Ground: Now()->groundEnemyS.Add(追加するオブジェクト, 待機時間); break;
            case Belong::Sea:    Now()->seaEnemyS.Add(追加するオブジェクト, 待機時間); break;
            case Belong::Sky:    Now()->skyEnemyS.Add(追加するオブジェクト, 待機時間); break;
            case Belong::Shot:   Now()->shotS.Add(追加するオブジェクト, 待機時間); break;
            case Belong::Unit:   Now()->unitS.Add(追加するオブジェクト, 待機時間); break;
            case Belong::Etc:    Now()->midEffectS.Add(追加するオブジェクト, 待機時間); break;
            default:
                break;
            }
        }

        /**.*/
        static void AddFront(Object *object, int suspendTime = 0)
        {
            Now()->frontEffectS.Add(object, suspendTime);
        }

        /**.*/
        static void AddBack(Object *object, int suspendTime = 0)
        {
            Now()->backEffectS.Add(object, suspendTime);
        }

        /**.*/
        static void AddEvent(IModule *module)
        {
            Now()->eventS.emplace_back(module);
        }

        /**.*/
        static Object* GetNearEnemy(Object* 比較対象)
        {
            Object* 一番近いObject = nullptr;
            double  最短距離 = 9999999999;
            double  距離;

            for (auto && it : now->groundEnemyS.objectS)
            {
                const double xd = it.get()->GetX() - 比較対象->GetX();
                const double yd = it.get()->GetY() - 比較対象->GetY();
                距離 = xd * xd + yd * yd;

                if (距離 < 最短距離)
                {
                    一番近いObject = it.get();
                    最短距離 = 距離;
                }
            }
            for (auto && it : now->skyEnemyS.objectS)
            {
                const double xd = it.get()->GetX() - 比較対象->GetX();
                const double yd = it.get()->GetY() - 比較対象->GetY();
                距離 = xd * xd + yd * yd;

                if (距離 < 最短距離)
                {
                    一番近いObject = it.get();
                    最短距離 = 距離;
                }
            }
            for (auto && it : now->seaEnemyS.objectS)
            {
                const double xd = it.get()->GetX() - 比較対象->GetX();
                const double yd = it.get()->GetY() - 比較対象->GetY();
                距離 = xd * xd + yd * yd;

                if (距離 < 最短距離)
                {
                    一番近いObject = it.get();
                    最短距離 = 距離;
                }
            }

            return 一番近いObject;
        }

        /**.*/
        static double GetNearDirect(Object* 比較対象)
        {
            Object* 一番近いObject = GetNearEnemy( 比較対象 );

            if (一番近いObject) return 比較対象->GetDirect(一番近いObject);

            return 0;
        }

    };
}