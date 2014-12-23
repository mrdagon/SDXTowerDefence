//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "IStage.h"
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
	public:
		static const int Size = 2;//2x2角
		static const int 速度値 = 6000;

		UnitData *st;//ステータス
		int    Lv = 0;
		double 支援補正 = 1;

		int    待機時間 = -1;
		int    残り送還時間 = -1;
		int    残り強化時間 = -1;
		int    強化or送還長さ = 1;
		bool   isジョブリスト = false;//画面左のジョブリスト用

		IUnit(IShape &図形, ISprite &描画方法, UnitType 職種 , bool isリスト) :
			IObject(図形, 描画方法, Belong::砲台),
			st(&UnitDataS[職種]),
			isジョブリスト(isリスト)
		{}

		/**.*/
		void SetWait()
		{
			if (st->連射[Lv] == 0) st->連射[Lv] = 1;

			待機時間 = int(速度値 / st->連射[Lv]);
		}

		/**配置時の描画処理.*/
		void Draw() const override
		{
			//選択中
			if (SStage->selectUnit == this)
			{
				Screen::SetBlendMode(BlendMode::Alpha, 128);
				Drawing::Rect({ GetX() - ChipSize, GetY() - ChipSize, ChipSize * 2, ChipSize * 2 }, Color::Red, true);
				Screen::SetBlendMode(BlendMode::NoBlend, 255);
				Screen::SetBright({ 255, 128, 128 });
				MSystem::フレーム[1].Draw({ GetX() - ChipSize, GetY() - ChipSize, ChipSize * 2, ChipSize * 2 });
				Screen::SetBright(Color::White);
			}
			else
			{
				MSystem::フレーム[1].Draw({ GetX() - ChipSize, GetY() - ChipSize, ChipSize * 2, ChipSize * 2 });
			}

			//強化中or送還中
			if (残り強化時間 > 0)
			{
				int Num = 99 - 残り強化時間 * 99 / 強化or送還長さ;
				MFont::BMP黒.DrawExtend({ GetX() - 12, GetY() - 12 }, 2, 2, { 255, 120, 120 }, { std::setw(2), Num });
			}
			else if (残り送還時間 > 0)
			{
				int Num = 残り送還時間 * 99 / 強化or送還長さ;
				MFont::BMP黒.DrawExtend({ GetX() - 12, GetY() - 12 }, 2, 2, { 120, 120, 255 }, { std::setw(2), Num });
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

		void DrawInfo() override
		{
			using namespace UnitDraw;

			//画像&名前
			MSystem::フレーム[5].Draw(F名前);
			MUnit::魔女[st->職種][1]->DrawRotate(P画像, 2, 0);
			MFont::ゴシック中.DrawShadow(P名前, Color::White, Color::Gray, st->名前);

			//レベル
			if (isジョブリスト)
			{
				//説明文
				MSystem::フレーム[5].Draw(F説明);
				MFont::ゴシック小.DrawShadow(P説明, Color::White, Color::Gray, st->説明文);
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
				MSystem::フレーム[3].Draw(F強化);
				MFont::ゴシック中.DrawShadow(P強化, { 255, 0, 0 }, Color::Gray, "強化");
				MFont::ゴシック中.DrawExtend({ P強化.x - 12, P強化.y + 22 }, 1, 1, { 255, 128, 128 }, "－");
				MFont::BMP黒.DrawExtend({ P強化.x - 4, P強化.y + 20 }, 2, 2, { 255, 64, 64 }, { std::setw(4), 強化費 });

				//売却or発動
				MSystem::フレーム[3].Draw(F回収);
				if (st->is使い捨て)
				{
					//発動
					MFont::ゴシック中.DrawShadow(P回収, Color::Blue, Color::Gray, "発動");
				}
				else
				{
					//売却
					MFont::ゴシック中.DrawShadow(P回収, Color::Blue, Color::Gray, "回収");
					MFont::ゴシック中.DrawExtend({ P回収.x - 12, P回収.y + 22 }, 1, 1, { 128, 128, 255 }, "+");
					MFont::BMP黒.DrawExtend({ P回収.x - 4, P回収.y + 20 }, 2, 2, { 128, 128, 255 }, { std::setw(4), 回収費 });
				}
			}

			//強化前後の性能
			DrawInfoState(Lv);
		}

		void DrawInfoState(int 表示Lv)
		{
			using namespace UnitDraw;

			bool 変化量表示 = isジョブリスト;
			if (表示Lv == 5){ isジョブリスト = false; }

			IconType アイコン[5] =
			{
				IconType::マナ,
				IconType::攻撃,
				IconType::連射,
				IconType::支援,
				IconType::麻痺
			};
			int 性能[5] =
			{
				st->コスト[Lv],//上3つは確定、最大5つ
				st->攻撃力[Lv],
				st->連射[Lv],
				(int)(st->支援効果[Lv] * 100),
				st->デバフ効果[Lv]
			};

			const int NextLv = (Lv + 1) % 5;

			int 次性能[5] =
			{
				st->コスト[NextLv],//上3つは確定、最大5つ
				st->攻撃力[NextLv],
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

				Screen::SetBright({ 128, 128, 255 });
				MSystem::フレーム[5].Draw(F性能[num]);
				Screen::SetBright({ 255, 255, 255 });

				//変化前
				MIcon::UI[アイコン[a]].Draw(P性能アイコン[num]);
				int 桁数 = 5;
				if (!変化量表示) 桁数 = 10;

				MFont::BMP白.DrawExtend(P性能[num], 2, 2, Color::White, { std::setw(桁数), 性能[a] });

				if (変化量表示)
				{
					MFont::ゴシック中.Draw({ 565, P性能アイコン[num].y + 8 }, Color::Yellow, "+");
					MFont::BMP白.DrawExtend(P性能[num], 2, 2, Color::Yellow, { std::setw(10), 次性能[a] - 性能[a] });
				}

				++num;
			}
		}

		/*射程を表示する*/
		void DrawRange()
		{
			if (isジョブリスト){ return; }

			//射程表示
			Screen::SetBlendMode(BlendMode::Alpha, 128);
			Drawing::Circle({ GetX(), GetY(), (double)st->射程[Lv] }, Color::White, 0);
			Screen::SetBlendMode();

			Drawing::Circle({ GetX(), GetY(), (double)st->射程[Lv] }, Color::Red , 2);
		}

		/**.*/
		bool RemoveCheck() override
		{
			//送還
			if (残り送還時間 == 0)
			{
				isRemove = true;
				Witch::Main->Mp += int( st->コスト[Lv] * Witch::Main->回収率 );
			}

			if (isRemove)
			{
				const int x = int(GetX() - Size * ChipSize) / ChipSize + 1;
				const int y = int(GetY() - Size * ChipSize) / ChipSize + 1;
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
				残り送還時間 > 0 ||
				!Witch::Main->is使用可能[st->職種] ||
				(!TDSystem::詠唱回数[st->職種] && !st->isウィッチ)
				)
			{ 
				return false; 
			}

			const int 必要MP = st->コスト[Lv + 1] - st->コスト[Lv];

			if (Witch::Main->Mp < 必要MP){ return false; }

			if (!st->isウィッチ)
			{
				--TDSystem::詠唱回数[st->職種];
			}

			Witch::Main->Mp -= 必要MP;

			残り強化時間 = int((Lv + 1) * (Lv + 1) * 60 * Witch::Main->強化速度);
			強化or送還長さ = 残り強化時間;

			//開始前は即LVアップ
			if (SStage->GetWave()->現在Wave == 0)
			{
				++Lv;
				残り強化時間 = -1;
			}

			return true;
		}

		bool 送還開始()
		{
			if (isジョブリスト) return false;
			if (残り強化時間 > 0 || 残り送還時間 > 0) return false;

			if (SStage->GetWave()->現在Wave == 0)
			{
				//開始前は即回収
				isRemove = true;
				if (st->isウィッチ){ TDSystem::詠唱回数[st->職種]++; }
				else{ TDSystem::詠唱回数[st->職種] += Lv + 1; }
				Witch::Main->Mp += st->コスト[Lv];
				残り送還時間 = -1;
			}
			else
			{
				if (st->is使い捨て)
				{
					//使い捨て
					Shoot(0);
					isRemove = true;
				}
				else
				{
					//売却
					残り送還時間 = int((SStage->GetWave()->現在Wave + 1) * 60 * Witch::Main->回収速度);
					強化or送還長さ = 残り送還時間;
				}
			}

			return true;
		}

		/**.*/
		void Act()
		{
			--残り送還時間;
			--残り強化時間;
			--待機時間;
			if (残り強化時間 == 0)
			{
				Lv++;
				残り強化時間 = -1;
				SetWait();
			}

			if (待機時間 <= 0 && 残り送還時間 < 0 && 残り強化時間 < 0)
			{
				auto 一番近い敵 = SStage->GetNearEnemy(this);

				if (一番近い敵)
				{
					double 距離 = GetDistance(一番近い敵);

					if (距離 <= st->射程[Lv])
					{
						Shoot(GetDirect(一番近い敵));
						SetWait();
					}
				}
			}
		}

		/**攻撃処理.*/
		virtual void Shoot(double 角度){};
	};

}