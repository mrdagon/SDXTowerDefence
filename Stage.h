﻿//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3
#pragma once
#include <SDXFramework.h>
#include <Framework/IScene.h>
#include "RouteMap.h"
#include "Layer.h"
#include "IStage.h"

#include "Enemy.h"
#include "Unit.h"
#include "Shot.h"
#include "Wave.h"

namespace SDX_TD
{
	//ステージ中での操作一覧
	enum class Command
	{
		//リプレイに残る
		選択解除,
		ユニット選択,
		地上敵選択,
		空中敵選択,
		大魔法発動,
		Wave送り,
		強化,
		売却,
		発動,
		種別選択,
		新規配置,
		null,
	};

	using namespace SDX;
	/**.*/
	class Stage : public IStage
	{
	private:
		Layer<IObject> backEffectS;
		Layer<IObject> midEffectS;
		Layer<IObject> frontEffectS;

		Layer<IEnemy> skyEnemyS;
		Layer<IEnemy> groundEnemyS;

		Layer<IShot> shotS;
		Layer<IUnit> unitS;

		Wave wave;

		IEnemy* 地上Top[Land::MapSize][Land::MapSize];
		IEnemy* 地上End[Land::MapSize][Land::MapSize];
		IEnemy* 空中Top[Land::MapSize][Land::MapSize];
		IEnemy* 空中End[Land::MapSize][Land::MapSize];

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
		}

		void AddChainList(Layer<IEnemy> &処理するレイヤ, IEnemy* 始点[Land::MapSize][Land::MapSize], IEnemy* 終点[Land::MapSize][Land::MapSize])
		{
			for (auto &&it : 処理するレイヤ.objectS)
			{
				const int x = (int)it->GetX() / Land::ChipSize;
				const int y = (int)it->GetY() / Land::ChipSize;
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

		bool HitShotEnemy(IShot* 弾, IEnemy* 敵)
		{
			while (敵)
			{
				if (弾->Hit(敵))
				{
					弾->Damaged(敵);
					敵->Damaged(弾);
					return true;
				}
				敵 = 敵->next;
			}
			return false;
		}

		/**貫通弾の判定.*/
		void HitLine(IShot* 弾, IEnemy* 始点[Land::MapSize][Land::MapSize])
		{
			for (int x = 0; x < Land::MapSize; ++x)
				for (int y = 0; y < Land::MapSize; ++y)
				{
					HitShotEnemy(弾, 始点[x][y]);
				}
		}
		/**小型弾の判定.*/
		void HitCircle(IShot* 弾, IEnemy* 始点[Land::MapSize][Land::MapSize])
		{
			const int xa = (int)(弾->GetX() - Land::ChipSize / 2) / Land::ChipSize;
			const int ya = (int)(弾->GetY() - Land::ChipSize / 2) / Land::ChipSize;
			const int xb = (int)(弾->GetX() + Land::ChipSize / 2) / Land::ChipSize;
			const int yb = (int)(弾->GetY() + Land::ChipSize / 2) / Land::ChipSize;

			if (xa >= 0 && xa < Land::MapSize)
			{
				if (ya >= 0 && ya < Land::MapSize)
				{
					if (HitShotEnemy(弾, 始点[xa][ya])){ return; }
				}

				if (yb >= 0 && yb < Land::MapSize && ya != yb)
				{
					if (HitShotEnemy(弾, 始点[xa][yb])){ return; }
				}
			}

			if (xa == xb) return;//X座標同じなら以降処理しない

			if (xb >= 0 && xb < Land::MapSize)
			{
				if (ya >= 0 && ya < Land::MapSize)
				{
					if (HitShotEnemy(弾, 始点[xb][ya])){ return; }
				}

				if (yb >= 0 && yb < Land::MapSize && ya != yb)
				{
					if (HitShotEnemy(弾, 始点[xb][yb])){ return; }
				}
			}
		}

		/**当たり判定処理を行う.*/
		void Hit()
		{
			//空と地上の分割木を初期化
			for (int a = 0; a < Land::MapSize; ++a)
				for (int b = 0; b < Land::MapSize; ++b)
				{
					地上Top[a][b] = nullptr;
					空中Top[a][b] = nullptr;
				}

			AddChainList(groundEnemyS, 地上Top, 地上End);
			AddChainList(skyEnemyS, 空中Top, 空中End);

			//判定開始
			for (auto && shot : shotS.objectS)
			{
				if (shot->is貫通)
				{
					if (shot->基礎ステ.is対地){ HitLine(shot.get(), 地上Top); }
					if (shot->基礎ステ.is対空){ HitLine(shot.get(), 空中Top); }
				}
				else
				{
					if (shot->基礎ステ.is対地){ HitCircle(shot.get(), 地上Top); }
					if (shot->基礎ステ.is対空){ HitCircle(shot.get(), 空中Top); }
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
		}

	public:
		int timer = 0;
		int gamespeed = 1;

		std::unique_ptr<Camera> camera;

		Stage() :
			camera(new Camera({ 400, 300 }, 1))
		{
			Init();
		}

		virtual ~Stage(){}

		/**Stageを初期化する.*/
		void Init()
		{
			Clear();

			SStage = this;
			//地形データ初期化
			if (!SLand)SLand = new Land::Land();
			SLand->Init();

			//ウィッチ初期化

			//ウィッチリスト12種初期化
			TDSystem::魔法リスト.clear();
			for (int a = 0; a < 12; ++a)
			{
				TDSystem::魔法リスト.emplace_back(new Unit(WITCH::Main->魔法タイプ[a]));
				TDSystem::詠唱回数[WITCH::Main->魔法タイプ[a]] = 10;
			}

			for (auto& it : TDSystem::魔法リスト)
			{
				it->is配置リスト = true;
			}
		}

		/**毎フレーム実行される更新処理.*/
		void Update() override
		{
			SStage = this;
			++timer;
			Director::IsDraw() = (timer % gamespeed == 0);

			NextWave();

			//レイヤー処理
			backEffectS.Update();
			midEffectS.Update();
			frontEffectS.Update();

			skyEnemyS.Update();
			groundEnemyS.Update();

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

			shotS.ExeRemove();
			unitS.ExeRemove();

			//地形の更新
			LandUpdate();

			InputCheck();
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

			if (TDSystem::isトライアル)
			{
				lv = int((wave.現在Wave + 1) * TrialDataS[TDSystem::難易度].レベル補正);

				if (wave.isBoss[waveNo]){ enemyCount = TrialDataS[TDSystem::難易度].ボス召喚数; }
				else { enemyCount = TrialDataS[TDSystem::難易度].雑魚召喚数; }
			}
			else
			{
				lv = int((wave.現在Wave + 1) * PowerDataS[TDSystem::難易度].レベル補正);

				if (wave.isBoss[waveNo]){ enemyCount = PowerDataS[TDSystem::難易度].ボス召喚数; }
				else { enemyCount = PowerDataS[TDSystem::難易度].雑魚召喚数; }
			}

			if (wave.敵種類[waveNo] == EnemyType::ゴブリン)
			{
				enemyCount *= 2;
			}

			for (int a = 0; a < enemyCount; ++a)
			{
				int x = SLand->穴の位置[0] % Land::MapSize;
				int y = SLand->穴の位置[0] / Land::MapSize;

				Add(new Enemy(x, y, wave.敵種類[waveNo], lv, wave.isBoss[waveNo]), a * 16);
			}

			++wave.現在Wave;
		}

		/**各種操作、クリックの選択処理.*/
		void InputCheck()
		{
			using namespace StageDraw;

			Point マウス座標(Input::mouse.x, Input::mouse.y);
			Command comType = Command::null;
			int comNo = 0;

			//UI位置の更新
			if (Input::key._1.on)
			{
				UnitDraw::Reset();
				StageDraw::Reset();
			}

			//速度変更
			if (Input::mouse.Whell > 0){ gamespeed *= 2; }
			if (Input::mouse.Whell < 0){ gamespeed /= 2; }
			gamespeed = std::min(gamespeed, 8);
			gamespeed = std::max(gamespeed, 1);

			//ポーズ
			if (Fメニュー.Hit(&マウス座標) && Input::mouse.Left.on)
			{

			}

			//↑はリプレイ時も共通
			
			//右クリックで解除
			if (Input::mouse.Right.on)
			{
				DoCommand(Command::選択解除, 0);
				return;
			}

			//ショートカットキーの入力チェック
			if (InputShortCut()){ return; };

			//左クリック系操作
			if (!Input::mouse.Left.on){ return; }

			//新規配置		
			comType = Command::新規配置;

			if (InputCheckEnemy(&マウス座標)){ return; }

			if (F大魔法.Hit(&マウス座標) )
			{
				comType = Command::大魔法発動;
			}

			if (マウス座標.x < 38 )
			{
				comType = Command::Wave送り;
			}

			//配置された魔法を選択、一覧選択中は不可能
			if (!selectUnit || !selectUnit->is配置リスト)
			{
				for (int a = 0; a < unitS.GetCount(); ++a)
				{
					if (unitS[a]->Hit(&マウス座標))
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
				if (F魔法一覧[a].Hit(&マウス座標))
				{
					comType = Command::種別選択;
					comNo = a;
					break;
				}
			}

			//強化
			if (UnitDraw::F強化.Hit(&マウス座標))
			{
				comType = Command::強化;
			}
			//売却or必殺
			if (UnitDraw::F回収.Hit(&マウス座標))
			{
				comType = Command::売却;
			}

			//コマンド実行
			if (comType != Command::null)
			{
				DoCommand(comType, comNo);
			}
		}

		/**ショートカットキーのチェック.*/
		bool InputShortCut()
		{
			//各種ショートカット
			if (Input::key.B.on)
			{
				DoCommand(Command::大魔法発動,0);
				return true;
			}
			if (Input::key.N.on || Input::key.Space.hold)
			{
				DoCommand(Command::Wave送り, 0);
				return true;
			}
			if (Input::key.U.on)
			{
				DoCommand(Command::強化, 0);
				return true;
			}
			if (Input::key.S.on)
			{
				DoCommand(Command::売却, 0);
				return true;
			}
			return false;
		}

		/**敵選択のチェック.*/
		bool InputCheckEnemy(Point *マウス座標)
		{
			//敵を選択、Shift押しながらだと選択不可能
			if (Input::key.LShift.hold || Input::key.RShift.hold)
			{
				return false;
			}

			if (selectEnemy)
			{
				if (selectEnemy->基礎ステ.移動タイプ == Belong::空)
				{
					if (InputCheckEnemyS(groundEnemyS,マウス座標, true)){ return true; }
					if (InputCheckEnemyS(skyEnemyS,マウス座標, false)){ return true; }
					if (InputCheckEnemyS(groundEnemyS, マウス座標, false)){ return true; }
				}
				else
				{
					if (InputCheckEnemyS(groundEnemyS, マウス座標, true)){ return true; }
					if (InputCheckEnemyS(groundEnemyS, マウス座標, false)){ return true; }
					if (InputCheckEnemyS(skyEnemyS, マウス座標, false)){ return true; }
				}
			}
			else
			{
				if (InputCheckEnemyS(groundEnemyS, マウス座標, false)){ return true; }
				if (InputCheckEnemyS(skyEnemyS, マウス座標, false)){ return true; }
			}

			return false;
		}

		/**敵選択のチェック.*/
		bool InputCheckEnemyS(Layer<IEnemy> &enemyS,Point *マウス座標, bool 検査位置判定)
		{
			int index = 0;
			if (検査位置判定)
			{
				for (int a = 0; a < enemyS.GetCount(); ++a)
				{
					if (a == enemyS.GetCount() - 1){ return false; }

					if (enemyS[a] == SStage->selectEnemy )
					{
						index = a + 1;						
						break;
					}
				}
			}

			for (int a = index; a < enemyS.GetCount(); ++a)
			{
				if (enemyS[a]->Hit(マウス座標))
				{
					DoCommand(Command::地上敵選択, a);
					return true;
				}
			}
			return false;
		}

		/**操作を実行.*/
		void DoCommand(Command 操作, int param)
		{
			switch (操作)
			{
			case Command::選択解除:
				selected = nullptr;
				selectEnemy = nullptr;
				selectUnit = nullptr;
				break;
			case Command::ユニット選択:
				SetSelect(unitS[param]);
				break;
			case Command::地上敵選択:
				SetSelect(groundEnemyS[param]);
				break;
			case Command::空中敵選択:
				SetSelect(skyEnemyS[param]);
				break;
			case Command::大魔法発動:
				WITCH::Main->大魔法発動();
				break;
			case Command::Wave送り:
				wave.isStop = false;
				wave.待ち時間 = 0;
				break;
			case Command::強化:
				if (!selectUnit ){ break; }
				selectUnit->強化開始();
				break;
			case Command::売却://使い捨ても
				if (!selectUnit){ break; }
				selectUnit->送還開始();
				break;
			case Command::種別選択:
				SetSelect(TDSystem::魔法リスト[param].get());
				break;
			case Command::新規配置:
				if (!selectUnit || !selectUnit->is配置リスト){ break; }
				SetCheck(selectUnit->基礎ステ.魔法種);
				break;
			}
		}

		void SetSelect(IEnemy* 選択した敵)
		{
			selected = 選択した敵;
			selectEnemy = 選択した敵;
			selectUnit = nullptr;
		}

		void SetSelect(IUnit* 選択した魔法)
		{
			selected = 選択した魔法;
			selectEnemy = nullptr;
			selectUnit = 選択した魔法;
		}

		/**配置と強化処理.*/
		void SetCheck(UnitType 魔法種)
		{
			if (!selectUnit || !selectUnit->is配置リスト){ return; }

			const int x = (Input::mouse.x - Land::ChipSize / 2) / Land::ChipSize;
			const int y = (Input::mouse.y - Land::ChipSize / 2) / Land::ChipSize;

			if (WITCH::Main->GetReqMP(魔法種) > WITCH::Main->MP || TDSystem::詠唱回数[魔法種] <= 0)
			{
				return;
			}

			if (SLand->SetUnit(x, y, 2))
			{
				Add(new Unit(魔法種));
			}
		}

		/**画面の描画.*/
		void Draw() override
		{
			SStage = this;

			SLand->Draw();

			if (selectUnit && selectUnit->is配置リスト){ SLand->DrawSetPos(); }

			//敵等の表示
			backEffectS.Draw();
			unitS.Draw();
			groundEnemyS.Draw();

			midEffectS.Draw();
			shotS.Draw();
			skyEnemyS.Draw();
			frontEffectS.Draw();

			DrawUI();

			//射程の表示
			if (selectUnit){ selectUnit->DrawRange(); }
		}

		/**UIの描画.*/
		void DrawUI()
		{
			using namespace StageDraw;

			MSystem::背景.DrawPart({ 0, 0 }, { 0, 0, 480, 40 });
			MSystem::背景.DrawPart({ 0, 0 }, { 0, 0, 40, 480 });
			MSystem::背景.DrawPart({ 0, 472 }, { 0, 472, 480, 40 });
			MSystem::背景.DrawPart({ 472, 0 }, { 472, 0, 168, 480 });

			//Wave一覧の表示
			wave.Draw();

			//スコアの表示
			MSystem::フレーム[5].Draw(Fスコア);
			MFont::BMP黒.Draw({ Pスコア.x + 10, Pスコア.y - 10 }, Color::White, "SCORE");
			MFont::BMP白.DrawExtend(Pスコア, 2, 2, Color::White, { std::setw(10), TDSystem::スコア });

			int 敵数 = skyEnemyS.GetCount() + groundEnemyS.GetCount();
			MSystem::フレーム[5].Draw(F敵数);
			MFont::BMP黒.Draw({ P敵数.x + 10, P敵数.y - 10 }, Color::White, "ENEMY");
			MFont::BMP白.DrawExtend( P敵数, 2, 2, Color::White, { std::setw(5), 敵数 });

			//ゲーム速度の表示
			int spd = 1;
			for (int a = 0; a < 4; ++a)
			{
				int x = (int)Fゲーム速度[a].x;
				const int SIZE = 2;

				if (gamespeed != spd){ Screen::SetBright(Color::Gray); }
				MSystem::フレーム[3].Draw(Fゲーム速度[a]);
				if (gamespeed != spd){ Screen::SetBright(Color::White); }

				MFont::BMP黒.DrawExtend({ x + 8, 10 }, SIZE, SIZE, Color::White, "x");
				MFont::BMP黒.DrawExtend({ x + 36, 8 }, SIZE, SIZE, Color::White, spd);

				spd *= 2;
			}

			//全体枠
			MSystem::フレーム[5].Draw({ 472, 0, 168, 100 + 105 + 27 });

			//ウィッチの表示

			if (TDSystem::isシングル)
			{


			}
			else
			{
			
			}

			MUnit::魔女[(UnitType)WITCH::Sub->種類][1]->DrawRotate(Pサブウィッチ, 2, 0);
			MUnit::魔女[(UnitType)WITCH::Main->種類][1]->DrawRotate(Pウィッチ, 2, 0);

			//モードと難易度
			MFont::BMP黒.DrawExtend({ 480, Pウィッチ.y + 40 }, 1, 1, Color::White, { "normal" });//大魔法チャージ量

			//SP,HP,MPの表示
			const int SP値 = std::min(int(WITCH::Main->SP * 100 / WITCH::Main->最大SP), 100);
			MIcon::UI[IconType::マナ].Draw(P大魔法);
			MFont::BMP白.DrawExtend({ P大魔法.x + 20, P大魔法.y + 6 }, 2, 2, { 120, 120, 255 }, { std::setw(5), SP値 });//大魔法チャージ量

			MIcon::UI[IconType::ライフ].Draw(P体力);
			MFont::BMP白.DrawExtend({ P体力.x + 20, P体力.y + 6 }, 2, 2, { 255, 60, 60 }, { std::setw(5), TDSystem::Hp });//HP

			MIcon::UI[IconType::レベル].Draw(P魔力);
			MFont::BMP白.DrawExtend({ P魔力.x + 20, P魔力.y + 6 }, 2, 2, { 255, 255, 0 }, { std::setw(5), WITCH::Main->MP });//MP

			//設定ボタン
			MSystem::フレーム[3].Draw(Fメニュー);
			MFont::ゴシック中.DrawShadow({ Fメニュー.x + 8, Fメニュー.y + 8 }, Color::Black, Color::Gray, "ポーズ");

			MSystem::フレーム[3].Draw(F大魔法);
			MFont::ゴシック中.DrawShadow({ F大魔法.x + 8, F大魔法.y + 8 }, Color::Black, Color::Gray, "大魔法");

			//魔法一覧の表示
			for (int a = 0; a < 12; ++a)
			{
				if (TDSystem::魔法リスト[a].get() == selected){ Screen::SetBright({ 255, 120, 120 }); }
				if (TDSystem::詠唱回数[WITCH::Main->魔法タイプ[a]] <= 0){ Screen::SetBright(Color::Gray); }
				MSystem::フレーム[3].Draw(F魔法一覧[a]);
				Screen::SetBright({ 255, 255, 255 });
				MUnit::魔女[WITCH::Main->魔法タイプ[a]][1]->DrawRotate({ F魔法一覧[a].x + 20, F魔法一覧[a].y + 12 }, 1, 0);
				MFont::英語[26]->Draw({ F魔法一覧[a].x + 2, F魔法一覧[a].y + 24 });
				MFont::BMP黒.DrawExtend({ F魔法一覧[a].x + 12, F魔法一覧[a].y + 20 }, 2, 2, Color::White, { std::setw(2), TDSystem::詠唱回数[WITCH::Main->魔法タイプ[a]] });
			}

			//情報の表示
			MSystem::フレーム[5].Draw(F情報);

			if (selected)
			{
				selected->DrawInfo();
			}
		}

		/**エフェクト等を追加.*/
		void Add(IObject* 追加するオブジェクト, int 待機時間 = 0) override
		{
			midEffectS.Add(追加するオブジェクト, 待機時間);
		}
		/**敵を追加.*/
		void Add(IEnemy* 追加するオブジェクト, int 待機時間 = 0) override
		{
			switch (追加するオブジェクト->GetBelong())
			{
			case Belong::空:
				skyEnemyS.Add(追加するオブジェクト, 待機時間);
				break;
			default:
				groundEnemyS.Add(追加するオブジェクト, 待機時間);
				break;
			}
		}
		/**ユニットを追加.*/
		void Add(IUnit* 追加するオブジェクト, int 待機時間 = 0) override
		{
			unitS.Add(追加するオブジェクト, 待機時間);
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
		IObject* GetNearEnemy(IObject* 比較対象) override
		{
			IObject* 一番近いObject = nullptr;
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

			return 一番近いObject;
		}

		/**一番近いEnemyの方向を返す.*/
		/**Enemyがいない場合0を返す*/
		double GetNearDirect(IObject* 比較対象) override
		{
			IObject* 一番近いObject = GetNearEnemy(比較対象);

			if (一番近いObject) return 比較対象->GetDirect(一番近いObject);

			return 0;
		}

		Wave* GetWave()
		{
			return &wave;
		}
	};
}