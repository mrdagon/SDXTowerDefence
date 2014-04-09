#pragma once//☀Unicode
#include <SDXFrameWork.h>
#include <Framework/IScene.h>
#include <Utility/Module.h>
#include "RouteMap.h"
#include "Layer.h"
#include "IStage.h"

#include "Enemy.h"
#include "Unit.h"
#include "Shot.h"
#include "Wave.h"

namespace SDX_TD
{
    using namespace SDX;
    /**.*/
    class Stage : public IStage
    {
    private:
        Layer<Object> backEffectS;
        Layer<Object> midEffectS;
        Layer<Object> frontEffectS;

        Layer<Enemy> skyEnemyS;
        Layer<Enemy> seaEnemyS;
        Layer<Enemy> groundEnemyS;

        Layer<Shot> shotS;

        Layer<Unit> unitS;

        std::vector<std::shared_ptr<IModule>> eventS;

        Wave wave;

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
            Enemy* chainFirst[Land::MapSize][Land::MapSize] = {};
            Enemy* chainEnd[Land::MapSize][Land::MapSize] = {};

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
                Enemy* it;

                if (xa >= 0 && xa < 24)
                {
                    if (ya >= 0 && ya < 24)
                    {
                        it = chainFirst[xa][ya];
                        while (it)
                        {
                            if (shot->Hit(it))
                            {
                                shot->Damaged(it);
                                it->Damaged(shot.get());
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
                                shot->Damaged(it);
                                it->Damaged(shot.get());
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
                                shot->Damaged(it);
                                it->Damaged(shot.get());
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
                                shot->Damaged(it);
                                it->Damaged(shot.get());
                            }
                            it = it->next;
                        }
                    }
                }
            }
        }

        /**地形の敵配置状態を更新.*/
        void LandUpdate()
        {
            Land::now->InitEnemyPost();

            for (auto &&it : groundEnemyS.objectS)
            {
                Land::now->SetGroungPost((int)it->GetX(), (int)it->GetY());
            }

            for (auto &&it : seaEnemyS.objectS)
            {
                Land::now->SetSeaPost((int)it->GetX(), (int)it->GetY());
            }
        }

    public:
        int timer = 0;

        std::unique_ptr<Camera> camera;

        Stage() :
            camera(new Camera(400, 300, 1))
        {
            Init();
        }

        virtual ~Stage(){}

        /**.*/
        void Init()
        {
            IStage::now = this;
            if( !Land::now )Land::now = new Land::Land();
            Land::now->Init();
        }

        /**.*/
        void Update() override
        {
            IStage::now = this;
            ++timer;

            //イベント処理
            for (auto it : eventS)
            {
                it->Update();
            }

            //Wave処理
            WaveCheck();

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

            //地形の更新
            LandUpdate();

            SelectCheck();

            SetCheck();
        }

        void WaveCheck()
        {
            if (!wave.Check()) return;
            
            //発生処理
            for (int i = 0; i < 16; ++i)
            {
                int x = Land::now->塔の位置[0] % Land::MapSize;
                int y = Land::now->塔の位置[0] % Land::MapSize;

                Add(new Enemy(x, y, nullptr, Belong::水陸), i * 16);
            }
        }

        /**クリックの選択処理.*/
        void SelectCheck()
        {
            
        }

        /**配置と強化処理.*/
        void SetCheck()
        {
            if (Input::mouse.Left.on)
            {
                if (Land::now->SetCheck(Input::mouse.x / Land::ChipSize, Input::mouse.y / Land::ChipSize, 2))
                {
                    Add(new Unit(Input::mouse.x / Land::ChipSize, Input::mouse.y / Land::ChipSize, 2, nullptr));
                }
            }
        }

        /**.*/
        void Draw() override
        {
            IStage::now = this;

            Land::now->Draw();

            //Wave一覧の表示
            int x = wave.GetPosition();
            Drawing::Rect( x , 440, 60, 40, Color::Red, false);

            //スコアの表示

            //ゲーム速度の表示

            //ウィッチの表示

            //砲台一覧の表示

            //MP,HP,SPの表示

            //枠の表示

            //選択中、砲台や敵能力の表示

            backEffectS.Draw();
            unitS.Draw();
            seaEnemyS.Draw();
            groundEnemyS.Draw();

            midEffectS.Draw();
            shotS.Draw();
            skyEnemyS.Draw();
            frontEffectS.Draw();
        }

        /**.*/
        void Add(Object *追加するオブジェクト, int 待機時間 = 0) override
        {
            midEffectS.Add(追加するオブジェクト, 待機時間);
        }
        void Add(Enemy *追加するオブジェクト, int 待機時間 = 0) override
        {
            switch (追加するオブジェクト->GetBelong())
            {
                case Belong::陸: groundEnemyS.Add(追加するオブジェクト, 待機時間); break;
                case Belong::空: skyEnemyS.Add(追加するオブジェクト, 待機時間); break;
                case Belong::水中:
                case Belong::水陸:
                                 seaEnemyS.Add(追加するオブジェクト, 待機時間); break;
                default:
                    break;
            }
        }
        void Add(Unit *追加するオブジェクト, int 待機時間 = 0) override
        {
            unitS.Add(追加するオブジェクト, 待機時間);
        }
        void Add(Shot *追加するオブジェクト, int 待機時間 = 0) override
        {
            shotS.Add(追加するオブジェクト, 待機時間);
        }

        /**.*/
        void AddFront(Object *追加するオブジェクト, int 待機時間 = 0) override
        {
            frontEffectS.Add(追加するオブジェクト, 待機時間);
        }

        /**.*/
        void AddBack(Object *追加するオブジェクト, int 待機時間 = 0) override
        {
            backEffectS.Add(追加するオブジェクト, 待機時間);
        }

        /**.*/
        void AddEvent(IModule *追加する関数オブジェクト) override
        {
            eventS.emplace_back(追加する関数オブジェクト);
        }

        /**.*/
        Object* GetNearEnemy(Object* 比較対象) override
        {
            Object* 一番近いObject = nullptr;
            double  最短距離 = 9999999999;
            double  距離;

            for (auto && it : groundEnemyS.objectS)
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
            for (auto && it : skyEnemyS.objectS)
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
            for (auto && it : seaEnemyS.objectS)
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
        double GetNearDirect(Object* 比較対象) override
        {
            Object* 一番近いObject = GetNearEnemy( 比較対象 );

            if (一番近いObject) return 比較対象->GetDirect(一番近いObject);

            return 0;
        }

    };
}