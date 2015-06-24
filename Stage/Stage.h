//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3
#pragma once
#include <SDXFramework.h>
#include <Framework/IScene.h>
#include "Land.h"
#include "IStage.h"

#include "Enemy.h"
#include "Unit.h"
#include "Shot.h"
#include "Wave.h"
#include "Layer.h"
#include "../Scene/ScenePause.h"
#include "../Scene/SceneResult.h"

#include "JobUnit.h"
#include "Struct/ReplayData.h"

namespace SDX_TD
{
    using namespace SDX;
    /**.*/
    class Stage : public IStage
    {
    private:
        JobUnit jobS[12];

        Layer<IObject> backEffectS;//ここは数が少ないしこのままでもよさそう
        Layer<IObject> midEffectS;
        Layer<IObject> frontEffectS;

		Layer<Enemy> skyEnemyS;//Enemyにして静的確保で良さそう
		Layer<Enemy> groundEnemyS;

        Layer<IShot> shotS;//Shotは型によってサイズが違うので、unionLayerにする
        StaticLayer<Unit> unitS;//静的確保

        Wave wave;

        ReplayData replayData;//リプレイの保存or読み込んだデータ

        Enemy* 地上Top[MAP_SIZE][MAP_SIZE];
        Enemy* 地上End[MAP_SIZE][MAP_SIZE];
        Enemy* 空中Top[MAP_SIZE][MAP_SIZE];
        Enemy* 空中End[MAP_SIZE][MAP_SIZE];

        double 攻撃補正[MAP_SIZE][MAP_SIZE];

        /**レイヤー等を初期化.*/
        void Clear()
        {
            timer = 0;

            wave.Init();

            backEffectS.Clear();
            midEffectS.Clear();
            frontEffectS.Clear();

            skyEnemyS.Clear();
            groundEnemyS.Clear();

            shotS.Clear();
            unitS.Clear();

            land.Init();

			//あらかじめメモリを確保しておく
        }

        void AddChainList(Layer<Enemy> &処理するレイヤ, Enemy* 始点[MAP_SIZE][MAP_SIZE], Enemy* 終点[MAP_SIZE][MAP_SIZE])
        {
            for (auto &&it : 処理するレイヤ.objectS)
            {
                const int x = (int)it->GetX() / CHIP_SIZE;
                const int y = (int)it->GetY() / CHIP_SIZE;

				if (x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE){ continue; }

                if (始点[x][y] == nullptr)
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

        bool HitShotEnemy(IShot* 弾, Enemy* 敵)
        {
            while (敵)
            {
                if (弾->Hit(敵))
                {
                    弾->Damaged(敵);
                    敵->Damaged(弾);
                    if ( !弾->is貫通 )
                    {
                        return true;
                    }
                }
                敵 = 敵->next;
            }
            return false;
        }

        /**貫通弾の判定.*/	
        void HitArea(IShot* 弾, Enemy* 始点[MAP_SIZE][MAP_SIZE])
        {
            //大雑把な分割処理をしない
            for (int x = 0; x < MAP_SIZE; ++x){
                for (int y = 0; y < MAP_SIZE; ++y)
                {
                    HitShotEnemy(弾, 始点[x][y]);
                }
            }
        }

        /**通常弾の判定.*/
        void HitSingle(IShot* 弾, Enemy* 始点[MAP_SIZE][MAP_SIZE])
        {
            //大雑把に分割してから判定を行う
            const int xa = (int)(弾->GetX() - CHIP_SIZE / 2) / CHIP_SIZE;
            const int ya = (int)(弾->GetY() - CHIP_SIZE / 2) / CHIP_SIZE;
            const int xb = (int)(弾->GetX() + CHIP_SIZE / 2) / CHIP_SIZE;
            const int yb = (int)(弾->GetY() + CHIP_SIZE / 2) / CHIP_SIZE;

            if (xa >= 0 && xa < MAP_SIZE)
            {
                if (ya >= 0 && ya < MAP_SIZE)
                {
                    if (HitShotEnemy(弾, 始点[xa][ya])){ return; }
                }

                if (yb >= 0 && yb < MAP_SIZE && ya != yb)
                {
                    if (HitShotEnemy(弾, 始点[xa][yb])){ return; }
                }
            }

            if (xa == xb) return;//X座標同じなら以降処理しない

            if (xb >= 0 && xb < MAP_SIZE)
            {
                if (ya >= 0 && ya < MAP_SIZE)
                {
                    if (HitShotEnemy(弾, 始点[xb][ya])){ return; }
                }

                if (yb >= 0 && yb < MAP_SIZE && ya != yb)
                {
                    if (HitShotEnemy(弾, 始点[xb][yb])){ return; }
                }
            }
        }

        /**当たり判定処理を行う.*/
        void Hit()
        {
            //空と地上の敵のリストを初期化
            for (int a = 0; a < MAP_SIZE; ++a){
                for (int b = 0; b < MAP_SIZE; ++b)
                {
                    地上Top[a][b] = nullptr;
                    空中Top[a][b] = nullptr;
                }
            }

            AddChainList(groundEnemyS, 地上Top, 地上End);
            AddChainList(skyEnemyS, 空中Top, 空中End);

            //判定開始
            for (int a = 0; a < shotS.GetCount(); ++a)
            {
                if ( !shotS[a]->isHitCheck ){ continue; }

                if (shotS[a]->is貫通)
                {
                    if (shotS[a]->st->is対地){ HitArea(shotS[a], 地上Top); }
                    if (shotS[a]->st->is対空){ HitArea(shotS[a], 空中Top); }
                }
                else
                {
                    if (shotS[a]->st->is対地){ HitSingle(shotS[a], 地上Top); }
                    if (shotS[a]->st->is対空){ HitSingle(shotS[a], 空中Top); }
                }
            }
        }

        /**地形の敵配置状態を更新.*/
        void LandUpdate()
        {
            SStage->land.InitEnemyPos();

            for (auto &&it : groundEnemyS.objectS)
            {
                SStage->land.UpdateEnemy((int)it->GetX(), (int)it->GetY(), it->移動種);
            }
        }

        /**Waveの進行と敵の発生.*/
        void NextWave()
        {
            //一時停止解除判定
            if (!wave.Check()){ return; }

            //発生処理
            int waveNo = wave.現在Wave % 100;
            int enemyCount;
            int lv;

            MSound::Wave.Play();
            lv = int((wave.現在Wave + 1) * DifficultyDataS[TDSystem::難易度].レベル補正[TDSystem::isスキル]);

            if (wave.isBoss[waveNo])
            {
                enemyCount = int(DifficultyDataS[TDSystem::難易度].ボス召喚数[TDSystem::isスキル] * EnemyDataS[wave.敵種類[waveNo]].出現数);
            }
            else
            {
                enemyCount = int(DifficultyDataS[TDSystem::難易度].雑魚召喚数[TDSystem::isスキル] * EnemyDataS[wave.敵種類[waveNo]].出現数);
            }

            for (int a = 0; a < enemyCount; ++a)			
            {
                //@todo この辺り偏らないようにする
                const int no = Rand::Get((int)SStage->land.穴の位置.size() - 1);
                const int x = int((SStage->land.穴の位置[no] % MAP_SIZE + 0.5 ) * CHIP_SIZE);
				const int y = int((SStage->land.穴の位置[no] / MAP_SIZE + 0.5) * CHIP_SIZE);
                //発生感覚 旧作だと40～80
                Add(new Enemy(x, y, wave.敵種類[waveNo], lv, wave.isBoss[waveNo]), a * 60);
            }

            ++wave.現在Wave;
        }

        /**各種操作、クリックの選択処理.*/
        void InputCheck()
        {
            namespace UI = UI_Stage;

            const Point point = { Input::mouse.x , Input::mouse.y };
            //タブレットでは指を離した時、デスクトップはクリック時に操作
            bool isClick = Input::mouse.Left.on;

            if (TDSystem::isタッチ)
            {
                isClick = Input::mouse.Left.off;
            }

            Command comType = Command::null;
            int comNo = 0;

            //速度変更
			if (TDSystem::is高速 || isReplay)
			{
				if (Input::mouse.Whell > 0){ gameSpeed *= 4; }
				if (Input::mouse.Whell < 0){ gameSpeed /= 4; }
				gameSpeed = std::min(gameSpeed, 64);
				gameSpeed = std::max(gameSpeed, 1);
			}
			else
			{
				if (Input::mouse.Whell > 0){ gameSpeed *= 2; }
				if (Input::mouse.Whell < 0){ gameSpeed /= 2; }
				gameSpeed = std::min(gameSpeed, 8);
				gameSpeed = std::max(gameSpeed, 1);
			}

            int sp = 1;

            for (int a = 0; a < 4; ++a)
            {
                if (UI::Rゲーム速度[a].Hit(&point) && isClick)
                {
                    gameSpeed = sp;
                }
                sp *= 2 + isReplay*2;
            }

            //ポーズ
            if (UI::Rメニュー.Hit(&point) && isClick)
            {
                int num = ScenePause::Call();
                switch (num)
                {
                case 0://あきらめる
                    isEnd = true;
                    return;
                case 1://やり直す
                    Init();
                    return;
                case 2://続ける
                    break;
                }
				if (!isReplay){ return; }
            }

            //ここより上はリプレイ時も共通
            if (isReplay)
            {
                DoReplay();
                return;
            }

            //右クリックで解除
            if (Input::mouse.Right.on)
            {
                DoCommand(Command::選択解除, 0 , Input::mouse.GetPoint());
                return;
            }

            //ショートカットキーの入力チェック
            if (InputShortCut()){ return; };

            //左クリックしていなければ、処理しない
            if (!isClick){ return; }

            //新規配置		
            comType = Command::新規配置;

            if (InputCheckEnemy(&point)){ return; }

            if (UI::R大魔法.Hit(&point))
            {
                comType = Command::大魔法発動;
            }

            if (point.x < 38 )
            {
                comType = Command::Wave送り;
            }

            //配置された魔法を選択、一覧選択中は不可能
            if (!selectUnit || !selectUnit->isジョブリスト)
            {
                for (int a = 0; a < unitS.GetCount(); ++a)
                {
                    if (unitS[a].Hit(&point))
                    {
                        comType = Command::ユニット選択;
                        comNo = a;
                        break;
                    }
                }
            }

            //一覧の魔法を選択
            for (int a = 0; a < 12; ++a)
            {
                if (UI::R魔法一覧[a].Hit(&point))
                {
                    comType = Command::種別選択;
                    comNo = a;
                    break;
                }
            }

            //強化
            if (UI_Unit::R強化.Hit(&point))
            {
                comType = Command::強化;
            }
            //売却or必殺
            if (UI_Unit::R回収.Hit(&point))
            {
                comType = Command::売却;
            }

            //コマンド実行
            if (comType != Command::null)
            {
                DoCommand(comType, comNo, Input::mouse.GetPoint());
            }
        }

        //リプレイの再生処理
        void DoReplay()
        {
			//@todo すでに実行した部分飛ばせば処理をやや改善出来そう
            for (auto &it : replayData.commandS)
            {
                if (it.操作した時間 == timer)
                {
                    DoCommand(it.種類, it.操作情報, it.マウス座標);
                }
            }
        }

        /**ショートカットキーのチェック.*/
        bool InputShortCut()
        {
            //各種ショートカット
            if (Input::key.B.on)
            {
                DoCommand(Command::大魔法発動, 0, Input::mouse.GetPoint());
                return true;
            }
            if (Input::key.N.on || Input::key.Space.hold)
            {
                DoCommand(Command::Wave送り, 0, Input::mouse.GetPoint());
                return true;
            }
            if (Input::key.U.on)
            {
                DoCommand(Command::強化, 0, Input::mouse.GetPoint());
                return true;
            }
            if (Input::key.S.on)
            {
                DoCommand(Command::売却, 0, Input::mouse.GetPoint());
                return true;
            }
            return false;
        }

        /**敵選択のチェック.*/
        bool InputCheckEnemy(const Point *マウス座標)
        {
            //敵を選択、Shift押しながらだと選択不可能
            if (Input::key.LShift.hold || Input::key.RShift.hold)
            {
                return false;
            }

            if (selectEnemy)
            {
                if (selectEnemy->移動種 == MoveType::空)
                {
                    if (InputCheckEnemyS(true, マウス座標, true)){ return true; }
                    if (InputCheckEnemyS(false, マウス座標, false)){ return true; }
                    if (InputCheckEnemyS(true, マウス座標, false)){ return true; }
                }
                else
                {
                    if (InputCheckEnemyS(true, マウス座標, true)){ return true; }
                    if (InputCheckEnemyS(true, マウス座標, false)){ return true; }
                    if (InputCheckEnemyS(false, マウス座標, false)){ return true; }
                }
            }
            else
            {
                if (InputCheckEnemyS(true, マウス座標, false)){ return true; }
                if (InputCheckEnemyS(false, マウス座標, false)){ return true; }
            }

            return false;
        }

        /**敵選択のチェック.*/
        bool InputCheckEnemyS(bool is地上 ,const Point *マウス座標, bool 検査位置判定)
        {
            int index = 0;
            Layer<Enemy> *enemyS;
            if ( is地上)
            {
                enemyS = &groundEnemyS;
            }
            else
            {
                enemyS = &skyEnemyS;
            }


            if (検査位置判定)
            {
                for (int a = 0; a < enemyS->GetCount(); ++a)
                {
                    if (a == enemyS->GetCount() - 1){ return false; }

                    if ( enemyS[0][a] == SStage->selectEnemy )
                    {
                        index = a + 1;						
                        break;
                    }
                }
            }

            for (int a = index; a < enemyS->GetCount(); ++a)
            {
                if (enemyS[0][a]->Hit(マウス座標))
                {
                    if (is地上)
                    {
                        DoCommand(Command::地上敵選択, a, Input::mouse.GetPoint());
                    }
                    else
                    {
                        DoCommand(Command::空中敵選択, a, Input::mouse.GetPoint());
                    }
                    return true;
                }
            }
            return false;
        }

        /**操作を実行.*/
        void DoCommand(Command 操作, int param , const Point& 座標)
        {
            //コマンドの記録
            if ( !isReplay && (timer != 0 || 操作 == Command::Wave送り))
            {
				replayData.commandS.push_back({ 操作, 座標, param, timer });
            }

            switch (操作)
            {
            case Command::選択解除:
                selected = nullptr;
                selectEnemy = nullptr;
                selectUnit = nullptr;
                break;
            case Command::ユニット選択:
                SetSelect( &unitS[param]);
                break;
            case Command::地上敵選択:
                SetSelect( groundEnemyS[param]);
                break;
            case Command::空中敵選択:
                SetSelect( skyEnemyS[param]);
                break;
            case Command::大魔法発動:
                Witch::Main->大魔法発動();
                break;
            case Command::Wave送り:
                if (wave.現在Wave == 0)
                {
                    wave.isStop = false;
					SaveUnitS();
                }
                if( wave.最終Wave != wave.現在Wave )
                {
                    wave.待ち時間 = 0;              
                }
                break;
            case Command::強化:
                if (!selectUnit ){ break; }
                selectUnit->強化開始();
                break;
            case Command::売却://使い捨て発動も含む
                if (!selectUnit){ break; }
                selectUnit->売却開始();
                break;
            case Command::種別選択:
                SetSelect(&jobS[param]);
                break;
            case Command::新規配置:
                if (!selectUnit || !selectUnit->isジョブリスト){ break; }
                SetCheck(selectUnit->st->職種 , 座標);
                break;
            }
        }

        /**初期配置を記憶.*/
        void SaveUnitS()
        {
			if (isReplay){ return; }

            auto* place = &StageDataS[TDSystem::選択ステージ].初期配置[(int)Witch::Main->種類][TDSystem::isカップル];
            place->clear();

            for (int a = 0; a < unitS.GetCount(); ++a)
            {
                Point pt = { unitS[a].GetX(), unitS[a].GetY() };
                place->push_back({ pt, unitS[a].Lv, unitS[a].st->職種 });
            }

			replayData.初期配置 = StageDataS[TDSystem::選択ステージ].初期配置[(int)Witch::Main->種類][TDSystem::isカップル];
        }

        /**初期配置を読み込む.*/
        /**装備変更等でMp or 強化回数が不足すると途中で打ち切り*/
        void LoadUnitS()
        {
			if ( !isReplay && !TDSystem::is配置記録){ return; }

			auto* place = &StageDataS[TDSystem::選択ステージ].初期配置[(int)Witch::Main->種類][TDSystem::isカップル];

			if (isReplay)
			{
				place = &replayData.初期配置;
			}
            
            for (auto & it : *place)
            {
                if (Witch::Main->Mp < UnitDataS[it.職種].コスト[it.Lv]) { break; }
                if (Witch::強化回数[it.職種] < it.Lv){ break; }

				SStage->land.SetUnit( int(it.座標.x / CHIP_SIZE) - 1, int(it.座標.y / CHIP_SIZE) - 1, 2);
                Add(Unit((int)it.座標.x, (int)it.座標.y, it.職種, false, it.Lv));				
            }
        }

        /**配置処理.*/
        void SetCheck(UnitType 職種 , const Point &座標)
        {
            if (!selectUnit || !selectUnit->isジョブリスト){ return; }

            //資金不足
            if (selectUnit->st->コスト[0] > Witch::Main->Mp || Witch::配置回数[職種] <= 0)
            {
                return;
            }
            const int x = int( 座標.x - CHIP_SIZE / 2) / CHIP_SIZE;
            const int y = int(座標.y - CHIP_SIZE / 2) / CHIP_SIZE;

            //敵の位置を更新
            LandUpdate();

            //配置可能かチェック
            if (SStage->land.SetUnit(x, y, 2))
            {
                Add( Unit((x+1) * CHIP_SIZE , (y+1) * CHIP_SIZE , 職種 , false , 0));
            }
        }

        /**UIの描画.*/
        void DrawUI()
        {
            namespace UI = UI_Stage;

            MSystem::背景.DrawPart({ 0, 0 }, { 0, 0, 480, 40 });
            MSystem::背景.DrawPart({ 0, 0 }, { 0, 0, 40, 480 });
            MSystem::背景.DrawPart({ 0, 472 }, { 0, 472, 480, 40 });
            MSystem::背景.DrawPart({ 472, 0 }, { 472, 0, 168, 480 });

            //Wave一覧の表示
            wave.Draw();

            //スコアの表示
            MSystem::フレーム[5].Draw(UI::Rスコア);
            MFont::fontS[FontType::BMP黒].Draw(UI::Pスコア + UI::P差分[0], Color::White, "SCORE");
            MFont::fontS[FontType::BMP白].DrawExtend(UI::Pスコア, 2, 2, Color::White, { std::setw(10), score });

            int 敵数 = skyEnemyS.GetCount() + groundEnemyS.GetCount();
            MSystem::フレーム[5].Draw(UI::R敵数);
            MFont::fontS[FontType::BMP黒].Draw(UI::P敵数 + UI::P差分[0], Color::White, "ENEMY");
            MFont::fontS[FontType::BMP白].DrawExtend(UI::P敵数, 2, 2, Color::White, { std::setw(5), 敵数 });

            //ゲーム速度の表示
            int spd = 1;
            for (int a = 0; a < 4; ++a)
            {
                if (spd == gameSpeed)
                {
                    MSystem::フレーム[3].Draw(UI::Rゲーム速度[a], Color::White);
                }
                else
                {
                    MSystem::フレーム[3].Draw(UI::Rゲーム速度[a], Color::Gray);
                }
                
                MFont::fontS[FontType::BMP黒].Draw(UI::Rゲーム速度[a].GetPoint() + UI::P差分[7], Color::White, "x");
                MFont::fontS[FontType::BMP黒].DrawExtend(UI::Rゲーム速度[a].GetPoint() + UI::P差分[6], 2, 2, Color::White, { std::setw(2), spd });

                spd *= 2 + 2 * (isReplay || TDSystem::is高速);
            }

            //全体枠
            MSystem::フレーム[5].Draw(UI::R右全体);

            int no = 1;

            if (timer % 40 < 10)
            {
                no = 0;
            }
            else if (timer % 40 < 20)
            {
                no = 1;
            }
            else if (timer % 40 < 30)
            {
                no = 2;
            }

            //ウィッチの表示
            if (TDSystem::isカップル)
            {
                MUnit::魔女[(UnitType)Witch::Main->種類][no]->DrawRotate(UI::Pカップルウィッチ[0], 2, 0);
                MUnit::魔女[(UnitType)Witch::Sub->種類][1]->DrawRotate(UI::Pカップルウィッチ[1], 2, 0);
            }
            else
            {
                MUnit::魔女[(UnitType)Witch::Main->種類][no]->DrawRotate(UI::Pシングルウィッチ, 2, 0);
            }

            //モードと難易度
            MFont::fontS[FontType::BMP黒].DrawExtend(UI::P難易度名, 1, 1, Color::White, DifficultyDataS[TDSystem::難易度].名前);
            MFont::fontS[FontType::BMP黒].DrawExtend(UI::Pモード名, 1, 1, Color::White, { "single" });

            //SP,HP,MPの表示
            if (Witch::Main->大魔法残り時間 > 0)
            {
                const Color color = {timer%64*2+64,timer%64*2+64,timer%64*3+64};
                const int SP値 = int(Witch::Main->大魔法残り時間 * 100 / Witch::Main->大魔法時間);

                MIcon::UI[IconType::マナ].Draw(UI::PＳＰ);
                MFont::fontS[FontType::BMP白].DrawExtend(UI::PＳＰ + UI::P差分[1], 2, 2, color, { std::setw(5), SP値 });//大魔法チャージ量
            }
            else
            {
                const int SP値 = std::min(int(Witch::Main->Sp * 100 / Witch::Main->最大Sp), 100);
                
                MIcon::UI[IconType::マナ].Draw(UI::PＳＰ);
                MFont::fontS[FontType::BMP白].DrawExtend(UI::PＳＰ + UI::P差分[1], 2, 2, { 128, 128, 255 }, { std::setw(5), SP値 });//大魔法チャージ量
            }

            MIcon::UI[IconType::ライフ].Draw(UI::P体力);
            MFont::fontS[FontType::BMP白].DrawExtend(UI::P体力 + UI::P差分[1], 2, 2, { 255, 60, 60 }, { std::setw(5), Witch::Main->Hp });//HP

            MIcon::UI[IconType::レベル].Draw(UI::P魔力);
            MFont::fontS[FontType::BMP白].DrawExtend(UI::P魔力 + UI::P差分[1], 2, 2, { 255, 255, 0 }, { std::setw(5), (int)Witch::Main->Mp });//MP

            //設定ボタン
            MSystem::フレーム[3].Draw(UI::Rメニュー);
            MFont::fontS[FontType::ゴシック中].DrawShadow(UI::Rメニュー.GetPoint() + UI::P差分[2], Color::Black, Color::Gray, "ポーズ");

            MSystem::フレーム[3].Draw(UI::R大魔法);
            MFont::fontS[FontType::ゴシック中].DrawShadow(UI::R大魔法.GetPoint() + UI::P差分[2], Color::Black, Color::Gray, "大魔法");

            //魔法一覧の表示
            for (auto &&it : jobS)
            {
                it.Draw();
            }

            //情報の表示
            MSystem::フレーム[5].Draw(UI::R情報);

            if (selected)
            {
                selected->DrawInfo();
            }
        }

    public:
        int timer = 0;//フレームスキップとリプレイ管理用のカウンタ
        int gameSpeed = 1;

        static Stage& Call( bool isReplay , ReplayData* replayData = nullptr)
        {
            static Stage single;
            single.isReplay = isReplay;

			if (isReplay)
			{
				single.replayData.commandS = replayData->commandS;
				single.replayData.初期配置 = replayData->初期配置;
			}

            single.Init();

            do
            {
                single.Update();
                if (Director::IsDraw()){ single.Draw(); }
            } while (System::Update(Director::IsDraw()) && !single.isEnd);

            return single;
        }

        Stage()
        {
        }

        virtual ~Stage(){}

        /**Stageを初期化する.*/
        void Init()
        {
            Clear();

            //地形データ初期化
            SStage = this;

            selected = nullptr;
            selectEnemy = nullptr;
            selectUnit = nullptr;

            land.Init();

            score = 0;
            timer = 0;
			isEnd = false;

            //ウィッチ初期化
            Witch::InitAll();

            //BGM開始
            MMusic::通常.Play();

            //非リプレイモード
			if ( !isReplay )
			{
				replayData.commandS.clear();
				replayData.乱数初期化子 = 0;//@todo とりあえず固定				
			}

			Rand::Reset(replayData.乱数初期化子);

			//初期配置読み込み
			LoadUnitS();
        }

        /**毎フレーム実行される更新処理.*/
        void Update() override
        {
            SStage = this;

            if (wave.現在Wave != 0)
            {
                ++timer;
                Director::IsDraw() = (timer % gameSpeed == 0);
            }
            else
            {
                Director::IsDraw() = true;
            }

            InputCheck();

            if (gameSpeed == 0)
            {
                Director::IsDraw() = true;
                return;
            }
            //■停止中は処理ここまで■

            NextWave();

            Witch::Main->Update();

            //レイヤー処理
            backEffectS.Update();
            midEffectS.Update();
            frontEffectS.Update();

            if (!wave.isStop)
            {
                skyEnemyS.Update();
                groundEnemyS.Update();
            }

            shotS.Update();
            unitS.Update();

            Hit();
            //離陸判定
            auto  it = groundEnemyS.objectS.begin();
            while (it != groundEnemyS.objectS.end())
            {
                if ((*it)->移動種 == MoveType::空)
                {
                    skyEnemyS.objectS.push_back(*it);
                    it = groundEnemyS.objectS.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            //消滅処理
            backEffectS.ExeRemove();
            midEffectS.ExeRemove();
            frontEffectS.ExeRemove();

            skyEnemyS.ExeRemove();
            groundEnemyS.ExeRemove();

            shotS.ExeRemove();
            unitS.ExeRemove();

            //補正計算
            Support();

            if (Witch::Hp <= 0)
            {				
                GameOver( false );//敗北
            }
            else if (groundEnemyS.GetCount() == 0 && skyEnemyS.GetCount() == 0 && (int)groundEnemyS.suspendS.size() == 0 && (int)skyEnemyS.suspendS.size() == 0 && wave.現在Wave == wave.最終Wave)
            {
                GameOver( true);//勝利
            }
        }

        /**クリアor全滅処理.*/
        void GameOver(bool is勝利)
        {
            bool isRetry = SceneResult::Call();
            
            if (isRetry)
            {
                Init();
            }
            else
            {
                isEnd = true;
            }
        }

        /**リプレイ保存処理.*/
        void SaveReplay( ResultType 結果, double スコア )
        {
            auto time = Time::GetDateString();
            time += ".rep";
            replayData.SaveOrLoad( time.c_str() , false, FileMode::Write, 結果, スコア);
        }

        /**画面の描画.*/
        void Draw() override
        {
            if ( !Director::IsDraw()) { return; };

            SStage = this;

            SStage->land.Draw();

            if (selectUnit && selectUnit->isジョブリスト){ SStage->land.DrawSetPos(); }

            //敵等の表示
            backEffectS.Draw();
            unitS.Draw();
            groundEnemyS.Draw();

            midEffectS.Draw();
            shotS.Draw();
            skyEnemyS.Draw();
            frontEffectS.Draw();

            //射程の表示
            if (selectUnit){ selectUnit->DrawRange(); }

            DrawUI();
        }

        void SetSelect(Enemy* 選択した敵)
        {
            selected = 選択した敵;
            selectEnemy = 選択した敵;
            selectUnit = nullptr;
        }

        void SetSelect(Unit* 選択したユニット)
        {
            selected = 選択したユニット;
            selectEnemy = nullptr;
            selectUnit = 選択したユニット;
        }

        /**Unit一覧を更新.*/
        void ResetJobList() override
        {
            //ウィッチリスト12種初期化
            jobS[0].SetType((UnitType)Witch::Main->種類);
            jobS[0].shape = UI_Stage::R魔法一覧[0];

            for (int a = 1; a < 12; ++a)
            {
                jobS[a].SetType(Witch::witchS[0].職種[a]);
                jobS[a].shape = UI_Stage::R魔法一覧[a];
            }
        }

        /**エフェクト等を追加.*/
        void Add(IObject* 追加するオブジェクト, int 待機時間 = 0) override
        {
            midEffectS.Add(追加するオブジェクト, 待機時間);
        }
        /**敵を追加.*/
        void Add( Enemy *追加するオブジェクト, int 待機時間 = 0) override
        {
            switch (追加するオブジェクト->移動種)
            {
            case MoveType::空:
                skyEnemyS.Add(追加するオブジェクト, 待機時間);
                break;
            default:
                groundEnemyS.Add(追加するオブジェクト, 待機時間);
                break;
            }
        }
        /**ユニットを追加.*/
        void Add( const Unit &追加するオブジェクト, int 待機時間 = 0) override
        {
            unitS.Add( std::move(追加するオブジェクト), 待機時間);
        }
        /**自弾を追加.*/
        void Add(IShot* 追加するオブジェクト, int 待機時間 = 0) override
        {
            shotS.Add(追加するオブジェクト, 待機時間);
        }

        /**前景オブジェクトを追加.*/
        void AddFront(IObject *追加するオブジェクト, int 待機時間 = 0) override
        {
            frontEffectS.Add(追加するオブジェクト, 待機時間);
        }

        /**背景オブジェクトを追加.*/
        void AddBack(IObject *追加するオブジェクト, int 待機時間 = 0) override
        {
            backEffectS.Add(追加するオブジェクト, 待機時間);
        }

        /**一番近いEnemyを返す.*/
        Enemy* GetNearEnemy(const IPosition* 比較対象 , bool is地上 , bool is空中) override
        {
            Enemy* 一番近い敵 = nullptr;
            double  最短距離 = 9999999999;//適当に大きな値
            double  距離;

            if (is地上)
            {
                for (auto && it : groundEnemyS.objectS)
                {
                    const double xd = it->GetX() - 比較対象->GetX();
                    const double yd = it->GetY() - 比較対象->GetY();
                    距離 = xd * xd + yd * yd;

                    if (距離 < 最短距離)
                    {
                        一番近い敵 = it.get();
                        最短距離 = 距離;
                    }
                }
            }
            if (is空中)
            {
                for (auto && it : skyEnemyS.objectS)
                {
                    const double xd = it->GetX() - 比較対象->GetX();
                    const double yd = it->GetY() - 比較対象->GetY();
                    距離 = xd * xd + yd * yd;

                    if (距離 < 最短距離)
                    {
                        一番近い敵 = it.get();
                        最短距離 = 距離;
                    }
                }
            }

            return 一番近い敵;
        }
        
        /**十字射程内で一番近いEnemyを返す.*/
        Enemy* GetNearEnemyCloss(const IPosition* 比較対象, bool is地上, bool is空中 , int 幅 , double 射程) override
        {
            Enemy* 一番近い敵 = nullptr;
            double  最短距離 = 9999999999;//適当に大きな値
            double  距離;

            if (is地上)
            {
                for (auto && it : groundEnemyS.objectS)
                {
                    距離 = GetClossDistance( it.get() , 比較対象, 幅, 射程);

                    if (距離 >= 0 && 距離 < 最短距離)
                    {					
                        一番近い敵 = it.get();
                        最短距離 = 距離;
                    }
                }
            }
            if (is空中)
            {
                for (auto && it : skyEnemyS.objectS)
                {
                    距離 = GetClossDistance( it.get(), 比較対象, 幅, 射程);

                    if (距離 >= 0 && 距離 < 最短距離)
                    {
                        一番近い敵 = it.get();
                        最短距離 = 距離;
                    }
                }
            }

            return 一番近い敵;
        }

        /**AとBが十字射程内にあるなら距離を返す、いないなら-1を返す.*/
        int GetClossDistance(const IPosition* 対象A, const IPosition* 対象B, int 幅, double 射程) override
        {
            const double xd = std::abs(対象A->GetX() - 対象B->GetX());
            const double yd = std::abs(対象A->GetY() - 対象B->GetY());

            if (
                (xd <= 幅 && yd <= 射程) ||
                (xd <= 射程 && yd <= 幅)
                )
            {
                return int(xd * xd + yd * yd);
            }
            return -1;
        }

        /**ユニットの支援再計算.*/
        void Support() override
        {
            const int Max = unitS.GetCount();

            //初期値に戻す
            for (int a = 0; a < Max; ++a)
            {
                unitS[a].支援補正 = 1.0;
            }

            for (int a = 0; a < Max ; ++a)
            {
                const double 支援 = unitS[a].st->支援効果[unitS[a].Lv];
                if (支援 <= 0)
                {
                    continue;
                }

                for (int b = 0; b < Max ; ++b)
                {
                    if (a == b)
                    {
                        continue;
                    }

                    if ( 
                        std::abs(unitS[a].GetX() - unitS[b].GetX()) <= CHIP_SIZE * 2 &&
                        std::abs(unitS[a].GetY() - unitS[b].GetY()) <= CHIP_SIZE * 2
                        )
                    {
						unitS[b].支援補正 = std::max( 1.0 + 支援, unitS[b].支援補正);
                    }
                }
            }
        }

        /**現在のWave数を取得.*/
        int GetWave()
        {
            return wave.現在Wave;
        }

        /** 大魔法発動時の瞬間的な効果.*/
        /** 敵HP減少等の依存関係でStageの関数で処理*/
        void 大魔法効果(bool is発動)
        {
            if (!is発動)
            {
                //終了時処理
                wave.isStop = false;

                if (TDSystem::isカップル)
                {
                    std::swap(Witch::Main, Witch::Sub);
                    ResetJobList();
                }

                MMusic::通常.Play();//BGMを元に戻す
                return;
            }
            else if ( !TDSystem::isエフェクト省略 )
            {
                //開始時処理
                MMusic::大魔法.Play();
				Director::IsDraw() = true;

                //演出
                for (int a = 0; a < 250; ++a)
                {
                    Screen::SetBright(Color::Gray);
                    SStage->Draw();
                    Screen::SetBright(Color::White);
                    //@todo 演出は仮
                    MFont::fontS[FontType::ゴシック中].DrawRotate({ 800 - a * 6, 300 }, 5, 0, Color::White, Witch::Main->大魔法名);
                    System::Update();
                }
            }

            //全体ダメージ
            //地上or空中のみダメージ
            //ボスorザコのみ
            //特定種類だけダメージ
            //全体異常
            //MP増加
            //HP増加
            //防御/再生/低下
            switch (Witch::Main->種類)
            {
            case WitchType::ライナ:
                //アクティベート時、ライナが大量連射
                //被ダメにより攻撃量が変化
                break;
            case WitchType::ナツメ:
                //アクティベート時、ナツメが大範囲攻撃
                break;
            case WitchType::ルコウ:
                //全敵のHP半減
                for (auto it : groundEnemyS)
                {
                    it->残りHP /= 2;
                }
                for (auto it : skyEnemyS)
                {
                    it->残りHP /= 2;
                }
                break;
            case WitchType::ディアネラ:
                //アクティベート時、ディアネラが大量発射
                break;
            case WitchType::ミナエ:
                //アクティベート時、ミナエが大量発射
                break;
            case WitchType::トレニア:
                //アクティベート時、極太ビーム発射
                //全攻撃に炸裂追加
                break;
            case WitchType::ロチエ:
                //全体に耐性無視の鈍足
                //鈍足状態の敵に継続ダメージ
                for (auto it : groundEnemyS)
                {
                    it->鈍足時間 = Witch::Main->大魔法時間;
                    it->鈍足率 = std::min(it->鈍足率,0.25);
                }
                for (auto it : skyEnemyS)
                {
                    it->鈍足時間 = Witch::Main->大魔法時間;
					it->鈍足率 = std::min(it->鈍足率, 0.25);
                }
                break;
            case WitchType::バロゥ:
                //Wave停止
                wave.isStop = true;
                break;
            case WitchType::フィオナ:
                //HP+5
                //残りHPに応じて攻撃
                Witch::Hp += 5;
                break;
            case WitchType::ナズナ:
                //MP+20%
                Witch::Main->Mp += int(Witch::Main->Mp * 0.2);
                break;
            case WitchType::委員長:
                //アクティブ攻撃
                //即強化＆回収
                for (auto && it : unitS)
                {
                    if (it.残り強化時間 > 0){ it.残り強化時間 = 1; }
                    if (it.残り売却時間 > 0){ it.残り売却時間 = 1; }
                }
                break;
            case WitchType::ミルラ:
                //アクティブ攻撃のみ
                break;
            default:
                break;
            }
        }
    };
}