//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "IStage.h"
#include "Enemy.h"
#include "Wave.h"
#include "DataS.h"
#include "Design.h"

namespace SDX_TD
{
	using namespace SDX;
	class IUnit : public IObject
	{
	protected:
		virtual void Dead(){}

		double Get射程()
		{
			if (Witch::Main->is射程支援 && 支援補正 > 1.0)
			{
				return (double)st->射程[Lv] * 支援補正;
			}

			return (double)st->射程[Lv];
		}

	public:
		static const int Size = 2;//2x2角
		static const int WAIT_TIME = 6000;

		UnitData *st;//ステータス
		int    Lv = 0;
		double 支援補正 = 1.0;//StageのSupportで再計算

		int    待機時間 = -1;//攻撃の待機
		int    残り売却時間 = -1;
		int    残り強化時間 = -1;
		int    強化or売却長さ = 1;
		bool   isジョブリスト = false;//画面左のジョブリスト用

		IUnit(IShape &図形, ISprite &描画方法, UnitType 職種 , bool isリスト) :
			IObject(図形, 描画方法),
			st(&UnitDataS[職種]),
			isジョブリスト(isリスト)
		{}

		/**配置時の描画処理.*/
		void Draw() const override
		{
			//選択中
			if (SStage->selectUnit == this)
			{
				//Drawing::Rect({ GetX() - CHIP_SIZE, GetY() - CHIP_SIZE, CHIP_SIZE * 2, CHIP_SIZE * 2 }, {255,0,0,128}, true);
				MSystem::フレーム[1].Draw({ GetX() - CHIP_SIZE, GetY() - CHIP_SIZE, CHIP_SIZE * 2, CHIP_SIZE * 2 }, {255,128,128});
			}
			else
			{
				MSystem::フレーム[1].Draw({ GetX() - CHIP_SIZE, GetY() - CHIP_SIZE, CHIP_SIZE * 2, CHIP_SIZE * 2 });
			}

			//強化中or売却中
			if (残り強化時間 > 0)
			{
				//数値が増えていく
				int Num = 99 - 残り強化時間 * 99 / 強化or売却長さ;
				MFont::BMP黒.DrawExtend({ GetX() - 12, GetY() - 10 }, 2, 2, { 255, 120, 120 }, { std::setw(2), Num });
			}
			else if (残り売却時間 > 0)
			{
				//数値が減っていく
				int Num = 残り売却時間 * 99 / 強化or売却長さ;
				MFont::BMP黒.DrawExtend({ GetX() - 12, GetY() - 10 }, 2, 2, { 120, 120, 255 }, { std::setw(2), Num });
			}
			else
			{
				MUnit::魔女[st->職種][1]->DrawRotate({ GetX(), GetY() }, 1, 0);
			}

			//レベル表示
			for (int a = 0; a < Lv; ++a)
			{
				MSystem::マーク[3]->DrawRotate({ GetX() + 6 * a - 12, GetY() + 12 }, 1, 0);
			}
		}

		/**画面右の情報.*/
		void DrawInfo() override
		{
			namespace UI = UI_Unit;

			//画像&名前
			MSystem::フレーム[5].Draw(UI::R名前);
			MUnit::魔女[st->職種][1]->DrawRotate(UI::P画像, 2, 0);
			MFont::ゴシック中.DrawShadow(UI::P名前, Color::White, Color::Gray, st->名前);

			//レベル
			if (isジョブリスト)
			{
				//説明文
				MSystem::フレーム[5].Draw(UI::R説明);
				MFont::ゴシック小.DrawShadow(UI::P説明, Color::White, Color::Gray, st->説明文);
			}
			else
			{
				int 強化費 = 0;
				int 回収費 = int( st->コスト[Lv] * Witch::Main->回収率 );

				if (Lv != 5)
				{
					強化費 = st->コスト[Lv + 1] - st->コスト[Lv];
				}

				//強化
				MSystem::フレーム[3].Draw(UI::R強化);
				MFont::ゴシック中.DrawShadow(UI::P強化, { 255, 0, 0 }, Color::Gray, "強化");
				MFont::ゴシック中.DrawExtend({ UI::P強化.x - 12, UI::P強化.y + 22 }, 1, 1, { 255, 128, 128 }, "－");
				MFont::BMP黒.DrawExtend({ UI::P強化.x - 4, UI::P強化.y + 22 }, 2, 2, Color::White , { std::setw(4), 強化費 });

				//売却or発動
				MSystem::フレーム[3].Draw(UI::R回収);
				if (st->is使い捨て)
				{
					//発動
					MFont::ゴシック中.DrawShadow(UI::P回収, Color::Blue, Color::Gray, "発動");
				}
				else
				{
					//売却
					MFont::ゴシック中.DrawShadow(UI::P回収, Color::Blue, Color::Gray, "回収");
					MFont::ゴシック中.DrawExtend({ UI::P回収.x - 12, UI::P回収.y + 22 }, 1, 1, { 128, 128, 255 }, "+");
					MFont::BMP黒.DrawExtend({ UI::P回収.x - 4, UI::P回収.y + 22 }, 2, 2, Color::White, { std::setw(4), 回収費 });
				}
			}

			//強化前後の性能
			DrawInfoState();
		}

		/**画面右の情報その2.*/
		void DrawInfoState()
		{
			namespace UI = UI_Unit;

			const bool 変化量表示 = (Lv != 5);

			IconType アイコン[5] =
			{
				IconType::レベル,
				IconType::攻撃,
				IconType::連射,
				IconType::支援,
				IconType::麻痺
			};
			int 性能[5] =
			{
				st->コスト[Lv],//上3つは確定、最大5つ
				(int)(st->攻撃力[Lv] * 支援補正),
				st->連射[Lv],
				(int)(st->支援効果[Lv] * 100),
				st->デバフ効果[Lv]
			};

			const int NextLv = (Lv + 1) % 5;

			int 次性能[5] =
			{
				st->コスト[NextLv],//上3つは確定、最大5つ
				(int)(st->攻撃力[NextLv] * 支援補正),
				st->連射[NextLv],
				(int)(st->支援効果[NextLv] * 100),
				st->デバフ効果[NextLv]
			};

			switch (st->デバフ種)
			{
			case DebuffType::鈍足:アイコン[4] = IconType::鈍足; break;
			case DebuffType::麻痺:アイコン[4] = IconType::麻痺; break;
			case DebuffType::吹飛:アイコン[4] = IconType::吹飛; break;
			case DebuffType::防壊:アイコン[4] = IconType::防壊; break;
			}

			int num = 0;

			//性能、現在値&次レベル値
			for (int a = 0; a < 5; ++a)
			{
				if (a >= 3 && 性能[a] <= 0) continue;

				MSystem::フレーム[5].Draw(UI::R性能[num], { 128, 128, 255 });

				//変化前
				MIcon::UI[アイコン[a]].Draw(UI::P性能アイコン[num]);
				int 桁数 = 5;
				if (!変化量表示) 桁数 = 10;

				MFont::BMP白.DrawExtend(UI::P性能[num], 2, 2, Color::White, { std::setw(桁数), 性能[a] });

				if (変化量表示)
				{
					MFont::ゴシック中.Draw({ 565, UI::P性能アイコン[num].y + 8 }, Color::Yellow, "+");
					MFont::BMP白.DrawExtend(UI::P性能[num], 2, 2, Color::Yellow, { std::setw(10), 次性能[a] - 性能[a] });
				}

				++num;
			}
		}

		/**射程を表示する.*/
		void DrawRange()
		{
			double 射程 = Get射程();

			if (isジョブリスト)
			{
				const double x = ( Input::mouse.x - CHIP_SIZE / 2) / CHIP_SIZE * CHIP_SIZE + CHIP_SIZE;
				const double y = ( Input::mouse.y - CHIP_SIZE / 2) / CHIP_SIZE * CHIP_SIZE + CHIP_SIZE;

				Drawing::Circle({ x, y, 射程 }, { 255, 255, 255, 128 }, 0);
				Drawing::Circle({ x, y, 射程 }, Color::Red, 2);
			}
			else
			{
				//射程表示
				Drawing::Circle({ GetX(), GetY(), 射程 }, { 255, 255, 255, 128 }, 0);
				Drawing::Circle({ GetX(), GetY(), 射程 }, Color::Red, 2);
			}
		}

		/**.*/
		bool RemoveCheck() override
		{
			if (isRemove)
			{
				const int x = int(GetX() - Size * CHIP_SIZE) / CHIP_SIZE + 1;
				const int y = int(GetY() - Size * CHIP_SIZE) / CHIP_SIZE + 1;
				SStage->land.RemoveUnit(x, y, Size);
				SStage->ResetSelect(this);
				Remove();
			}

			return this->isRemove;
		}

		bool 強化開始()
		{
			if (	
				isジョブリスト ||
				Lv >= 5 ||
				残り強化時間 > 0 ||
				残り売却時間 > 0 ||
				!Witch::Main->is使用可能[st->職種] ||
				(!Witch::詠唱回数[st->職種] && !st->isウィッチ)
				)
			{ 
				return false; 
			}

			const int 必要MP = st->コスト[Lv + 1] - st->コスト[Lv];

			if (Witch::Main->Mp < 必要MP){ return false; }

			if (!st->isウィッチ)
			{
				--Witch::詠唱回数[st->職種];
			}

			Witch::Main->Mp -= 必要MP;

			残り強化時間 = int((Lv + 1) * (Lv + 1) * 60 * Witch::Main->強化速度);
			強化or売却長さ = 残り強化時間;

			//開始前、or強化速度=0の時は即LVアップ
			if (SStage->GetWave() == 0 || Witch::Main->強化速度 <= 0)
			{
				++Lv;
				残り強化時間 = -1;
			}

			return true;
		}

		/** 売却処理or発動処理.*/
		bool 売却開始()
		{
			if (isジョブリスト) return false;
			if (残り強化時間 > 0 || 残り売却時間 > 0) return false;

			//開始前or回収速度=0の時は即回収
			if (SStage->GetWave() == 0 || Witch::Main->回収速度 <= 0)
			{
				isRemove = true;
				if (st->isウィッチ){ Witch::詠唱回数[st->職種]++; }
				else{ Witch::詠唱回数[st->職種] += Lv + 1; }
				Witch::Main->Mp += st->コスト[Lv];
				残り売却時間 = -1;
			}
			else
			{
				if (st->is使い捨て)
				{
					//使い捨て
					Shoot(nullptr);
					isRemove = true;
				}
				else
				{
					//売却
					残り売却時間 = int((SStage->GetWave() + 1) * 60 * Witch::Main->回収速度);
					強化or売却長さ = 残り売却時間;
				}
			}

			return true;
		}

		/**.*/
		void Act()
		{
			--残り売却時間;
			--残り強化時間;
			待機時間 -= st->連射[Lv];

			if (残り強化時間 == 0 )
			{
				MSound::強化.Play();
				Lv++;
				待機時間 = WAIT_TIME;
				return;
			}

			if (残り売却時間 == 0 )
			{
				MSound::売却.Play();
				Witch::Main->Mp += st->コスト[Lv] * Witch::Main->回収率;
				isRemove = true;
				return;
			}


			if (待機時間 <= 0 && 残り売却時間 < 0 && 残り強化時間 < 0 && !st->is使い捨て )
			{
				IEnemy* 対象 = nullptr;
				double 射程 = Get射程();
				//敵を選択中
				if ( SStage->selectEnemy )
				{
					const bool 地形対応 = (SStage->selectEnemy->st->移動種 == MoveType::空 && st->is対空) || (SStage->selectEnemy->st->移動種 != MoveType::空 && st->is対地);

					if ( 地形対応 && GetDistance(SStage->selectEnemy) <= 射程)
					{
						対象 = SStage->selectEnemy;
					}
				}

				//選択した敵が範囲外 or 敵を未選択
				if ( 対象 == nullptr)
				{
					対象 = SStage->GetNearEnemy(this , st->is対地 , st->is対空);
					if ( !対象 || GetDistance(対象) > 射程)
					{
						対象 = nullptr;
					}
				}

				if ( 対象 )
				{
					//射程内に敵がいるなら攻撃					
					Shoot(対象);
					待機時間 = WAIT_TIME;
				}
			}
		}

		/**攻撃処理.*/
		virtual void Shoot(IEnemy* 対象){};
	};
}