#pragma once//☀Unicode
#include <SDXFrameWork.h>
#include <Framework/IScene.h>
#include <Utility/Module.h>
#include "RouteMap.h"
#include "Layer.h"
#include "IStage.h"

#include "Enemy.h"
#include "Magic.h"
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

        Layer<Magic> unitS;

        std::vector<std::shared_ptr<IModule>> eventS;

        Wave wave;

        Enemy* 地上Top[Land::MapSize][Land::MapSize];
        Enemy* 地上End[Land::MapSize][Land::MapSize];
        Enemy* 空中Top[Land::MapSize][Land::MapSize];
        Enemy* 空中End[Land::MapSize][Land::MapSize];

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

        void AddChainList(Layer<Enemy> &処理するレイヤ, Enemy* 始点[Land::MapSize][Land::MapSize], Enemy* 終点[Land::MapSize][Land::MapSize])
        {
            for (auto &&it : 処理するレイヤ.objectS)
            {
                const int x = (int)it->GetX() / Land::ChipSize;
                const int y = (int)it->GetY() / Land::ChipSize;
                if ( 始点[x][y] == nullptr)
                {
                    始点[x][y] = it.get();
                    終点[x][y] = it.get();
                }
                else
                {
                    終点[x][y]->next = it.get();
                    終点[x][y] = it.get();
                }
                it->next = nullptr;
            }
        }

        void HitShotEnemy(Shot* 弾, Enemy* 敵)
        {
            while (敵)
            {
                if (弾->Hit(敵))
                {
                    弾->Damaged(敵);
                    敵->Damaged(弾);
                }
                敵 = 敵->next;
            }

        }

        /**大型弾の判定.*/
        void HitLine(Shot* 弾, Enemy* 始点[Land::MapSize][Land::MapSize])
        {
            for (int x = 0; x < Land::MapSize; ++x)
            for (int y = 0; y < Land::MapSize; ++y)
            {
                HitShotEnemy(弾, 始点[x][y]);
            }
        }
        /**小型弾の判定.*/
        void HitCircle(Shot* 弾, Enemy* 始点[Land::MapSize][Land::MapSize])
        {
            const int xa = (int)(弾->GetX() - Land::ChipSize / 2) / Land::ChipSize;
            const int ya = (int)(弾->GetY() - Land::ChipSize / 2) / Land::ChipSize;
            const int xb = (int)(弾->GetX() + Land::ChipSize / 2) / Land::ChipSize;
            const int yb = (int)(弾->GetY() + Land::ChipSize / 2) / Land::ChipSize;

            if (xa >= 0 && xa < Land::MapSize)
            {
                if (ya >= 0 && ya < Land::MapSize)
                {
                    HitShotEnemy(弾, 始点[xa][ya]);
                }

                if (yb >= 0 && yb < Land::MapSize && ya != yb)
                {
                    HitShotEnemy(弾, 始点[xa][yb]);
                }
            }

            if (xa == xb) return;//X座標同じなら以降処理しない

            if (xb >= 0 && xb < Land::MapSize)
            {
                if (ya >= 0 && ya < Land::MapSize)
                {
                    HitShotEnemy(弾, 始点[xb][ya]);
                }

                if (yb >= 0 && yb < Land::MapSize && ya != yb)
                {
                    HitShotEnemy(弾, 始点[xb][yb]);
                }
            }
        }

        /**当たり判定処理を行う.*/
        void Hit()
        {
            //空と地上の分割木を初期化
            for (int a = 0; a < Land::MapSize; ++a )
            for (int b = 0; b < Land::MapSize; ++b )
            {
                地上Top[a][b] = nullptr;
                空中Top[a][b] = nullptr;
            }

            AddChainList(groundEnemyS, 地上Top, 地上End);
            AddChainList(skyEnemyS, 空中Top, 空中End);
            AddChainList(seaEnemyS, 地上Top, 地上End);

            //判定開始
            for (auto && shot : shotS.objectS)
            {
                if (shot->isSmall)
                {
                    if (shot->基礎ステ.is対地) HitCircle(shot.get() , 地上Top);
                    if (shot->基礎ステ.is対空) HitCircle(shot.get() , 空中Top);
                }
                else
                {
                    if (shot->基礎ステ.is対地) HitLine(shot.get(), 地上Top);
                    if (shot->基礎ステ.is対空) HitLine(shot.get(), 空中Top);
                }
            }
        }

        /**地形の敵配置状態を更新.*/
        void LandUpdate()
        {
            SLand->InitEnemyPos();

            for (auto &&it : groundEnemyS.objectS)
            {
                SLand->Update陸の敵((int)it->GetX(), (int)it->GetY());
            }

            for (auto &&it : seaEnemyS.objectS)
            {
                SLand->Update水の敵((int)it->GetX(), (int)it->GetY());
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

        /**Stageを初期化する.*/
        void Init()
        {
            SStage = this;
            if( !SLand )SLand = new Land::Land();
            SLand->Init();
        }

        /**毎フレーム実行される更新処理.*/
        void Update() override
        {
            SStage = this;
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

        /**Waveの処理.*/
        void WaveCheck()
        {
            if (!wave.Check()) return;
            
            //発生処理
            for (int a = 0; a < 16; ++a)
            {
                int x = SLand->穴の位置[0] % Land::MapSize;
                int y = SLand->穴の位置[0] / Land::MapSize;

                Add(new Enemy(x, y, EnemyDataS[EnemyType::ゼリー]), a * 16);
            }
        }

        /**クリックの選択処理.*/
        void SelectCheck()
        {
            //敵を選択

            //ポーズを選択

            //Wave送り

            //配置された魔法を選択

            //一覧の魔法を選択

            //大魔法を発動

            //強化or送還or発動or配置
        }

        /**配置と強化処理.*/
        void SetCheck()
        {
            if (Input::mouse.Left.on)
            {
                const int x = (Input::mouse.x - Land::ChipSize/2) / Land::ChipSize;
                const int y = (Input::mouse.y - Land::ChipSize/2) / Land::ChipSize;

                if (SLand->SetMagic( x , y , 2))
                {
                    Add(new Magic( x , y ,MagicType::炎基礎1));
                }
            }
        }

        /**画面の描画.*/
        void Draw() override
        {
            SStage = this;

            SLand->Draw();
            MSystem::背景.DrawPart(0,0,0,0,480,40);
            MSystem::背景.DrawPart(0,0,0,0,40,480);
            MSystem::背景.DrawPart(0,472,0,472,480,40);
            MSystem::背景.DrawPart(472,0,472,0,168,480);

            //Wave一覧の表示
            wave.Draw();

            //スコアの表示
            MSystem::フレーム[5].Draw(44,4,120,30);
            MFont::BMP黒.Draw(46,2,Color::White,"SCORE");
            MFont::BMP白.DrawExtend(46,12,2,2,Color::White,12345678);
            
            MSystem::フレーム[5].Draw(168,4,60,30);
            MFont::BMP黒.Draw(170,2,Color::White,"ENEMY");
            MFont::BMP白.DrawExtend(170,12,2,2,Color::White,1234);

            //難易度

            //ゲーム速度の表示
            int spd = 1;
            for(int a=0; a<4;++a)
            {
                int x = 234 + a*60;

                MSystem::フレーム[8].Draw(x,-6,60,42);
                
                MFont::BMP黒.DrawExtend( x+8 ,10,2,2,Color::White,"x");
                MFont::BMP黒.DrawExtend( x+36, 8,2,2,Color::White,spd);

                spd *= 2;
            }


            //ウィッチの表示
            MSystem::フレーム[5].Draw( 476 ,  4 , 160 , 96);
            
            MSystem::フレーム[7].Draw(590,-6,50,42);//メニュー

            MFont::BMP黒.Draw(   480 , 2 ,Color::White,"WITCH");

            MSystem::フレーム[8].Draw(486,20,40,40);
            MUnit::魔女[WitchType::ディアネラ][1]->DrawRotate(506,40,2,0);            
            MUnit::魔女[WitchType::バロゥ][1]->DrawRotate(536,30,1,0);

            //MP,HP,SPの表示
            MSystem::フレーム[5].Draw(530, 40, 100 ,20);
            MFont::BMP白.DrawExtend(584,44,2,2,{120,120,255},100);//SP

            MFont::BMP白.DrawExtend(520,72,2,2,{255,60,60},100);//HP
            MFont::BMP白.DrawExtend(584,72,2,2,{255,255,0},100);//MP

            //砲台一覧の表示
            MSystem::フレーム[5].Draw(476, 100, 160 ,120);
            for(int a=0;a<12;++a)
            {
                int x = 476 + a%4*40;
                int y = 100 + a/4*40;
                MSystem::フレーム[1].Draw(x , y,40,40);
                MUnit::魔女[WitchType::ライナ][1]->DrawRotate(x+20,y+20,1,0);
            }


            //MFont::BMP黒.DrawExtend(548,10,2,2,Color::White,"Menu");

            //枠の表示

            //選択中、砲台や敵能力の表示            
            MSystem::フレーム[5].Draw( 476 , 220 , 160 , 254);

            backEffectS.Draw();
            unitS.Draw();
            seaEnemyS.Draw();
            groundEnemyS.Draw();

            midEffectS.Draw();
            shotS.Draw();
            skyEnemyS.Draw();
            frontEffectS.Draw();
        }
        /**エフェクト等を追加.*/
        void Add(Object *追加するオブジェクト, int 待機時間 = 0) override
        {
            midEffectS.Add(追加するオブジェクト, 待機時間);
        }
        /**敵を追加.*/
        void Add(Enemy *追加するオブジェクト, int 待機時間 = 0) override
        {
            switch (追加するオブジェクト->GetBelong())
            {
                case Belong::陸: groundEnemyS.Add(追加するオブジェクト, 待機時間); break;
                case Belong::空: skyEnemyS.Add(追加するオブジェクト, 待機時間); break;
                case Belong::水: seaEnemyS.Add(追加するオブジェクト, 待機時間); break;
                default:
                    break;
            }
        }
        /**魔法陣を追加.*/
        void Add(Magic *追加するオブジェクト, int 待機時間 = 0) override
        {
            unitS.Add(追加するオブジェクト, 待機時間);
        }
        /**自弾を追加.*/
        void Add(Shot *追加するオブジェクト, int 待機時間 = 0) override
        {
            shotS.Add(追加するオブジェクト, 待機時間);
        }

        /**前景オブジェクトを追加.*/
        void AddFront(Object *追加するオブジェクト, int 待機時間 = 0) override
        {
            frontEffectS.Add(追加するオブジェクト, 待機時間);
        }

        /**背景オブジェクトを追加.*/
        void AddBack(Object *追加するオブジェクト, int 待機時間 = 0) override
        {
            backEffectS.Add(追加するオブジェクト, 待機時間);
        }

        /**Stageにイベントを追加.*/
        void AddEvent(IModule *追加する関数オブジェクト) override
        {
            eventS.emplace_back(追加する関数オブジェクト);
        }

        /**一番近いEnemyを返す.*/
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

        /**一番近いEnemyの方向を返す.*/
        /**Enemyがいない場合0を返す*/
        double GetNearDirect(Object* 比較対象) override
        {
            Object* 一番近いObject = GetNearEnemy( 比較対象 );

            if (一番近いObject) return 比較対象->GetDirect(一番近いObject);

            return 0;
        }

        Wave* GetWave()
        {
            return &wave;
        }

    };
}