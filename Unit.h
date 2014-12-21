//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "Shot.h"
#include "ShotMotion.h"
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

		UnitData &st;//stータス

		int    Lv = 0;
		double 支援補正 = 1;

		int    待機時間 = -1;
		int    残り送還時間 = -1;
		int    残り強化時間 = -1;
		int    強化or送還長さ = 1;
		bool   is配置リスト = false;

		IUnit(IShape &図形, ISprite &描画方法, UnitType 魔法種 , bool isリスト) :
			IObject(図形, 描画方法, Belong::砲台),
			st(UnitDataS[魔法種]),
			is配置リスト(isリスト)
		{
			if ( !is配置リスト)
			{
				WITCH::Main->MP -= WITCH::Main->GetReqMP(魔法種);
				--TDSystem::詠唱回数[魔法種];

				SetWait();
			}
		}

		/**.*/
		void SetWait()
		{
			if (st.連射[Lv] == 0) st.連射[Lv] = 1;

			待機時間 = int(速度値 / st.連射[Lv]);
		}

		/**.*/
		void Draw() const
		{
			//選択中
			if (SStage->selectUnit == this)
			{
				Screen::SetBlendMode(BlendMode::Alpha, 128);
				Drawing::Rect({ GetX() - Land::ChipSize, GetY() - Land::ChipSize, Land::ChipSize * 2, Land::ChipSize * 2 }, Color::Red, true);
				Screen::SetBlendMode(BlendMode::NoBlend, 255);
				Screen::SetBright({ 255, 128, 128 });
				MSystem::フレーム[1].Draw({ GetX() - Land::ChipSize, GetY() - Land::ChipSize, Land::ChipSize * 2, Land::ChipSize * 2 });
				Screen::SetBright(Color::White);
			}
			else{
				MSystem::フレーム[1].Draw({ GetX() - Land::ChipSize, GetY() - Land::ChipSize, Land::ChipSize * 2, Land::ChipSize * 2 });
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
				MUnit::魔女[st.魔法種][1]->DrawRotate({ GetX(), GetY() }, 1, 0);
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
			MUnit::魔女[st.魔法種][1]->DrawRotate(P画像, 2, 0);
			MFont::ゴシック中.DrawShadow(P名前, Color::White, Color::Gray, st.名前);

			//レベル
			if (is配置リスト)
			{
				//説明文
				MSystem::フレーム[5].Draw(F説明);
				MFont::ゴシック小.DrawShadow(P説明, Color::White, Color::Gray, st.説明文);

				//LV1の性能
				DrawInfoState(0, false);
			}
			else
			{
				int 強化費 = 0;
				int 回収費 = int( st.コスト[Lv] * WITCH::Main->回収率 );

				if (Lv != 5)
				{
					強化費 = int( (st.コスト[Lv + 1] - st.コスト[Lv])*WITCH::Main->MP消費 );
				}

				//強化
				MSystem::フレーム[3].Draw(F強化);
				MFont::ゴシック中.DrawShadow(P強化, { 255, 0, 0 }, Color::Gray, "強化");
				MFont::ゴシック中.DrawExtend({ P強化.x - 12, P強化.y + 22 }, 1, 1, { 255, 128, 128 }, "－");
				MFont::BMP黒.DrawExtend({ P強化.x - 4, P強化.y + 20 }, 2, 2, { 255, 64, 64 }, { std::setw(4), 強化費 });

				//売却or発動
				MSystem::フレーム[3].Draw(F回収);
				if (st.is使い捨て)
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

				//強化前後の性能
				DrawInfoState(Lv, (Lv != 5));
			}
		}

		void DrawInfoState(int 表示Lv, bool 変化量表示)
		{
			using namespace UnitDraw;

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
				st.コスト[Lv],//上3つは確定、最大5つ
				st.攻撃力[Lv],
				st.連射[Lv],
				(int)(st.支援効果[Lv] * 100),
				st.デバフ効果[Lv]
			};

			const int NextLv = (Lv + 1) % 5;

			int 次性能[5] =
			{
				st.コスト[NextLv],//上3つは確定、最大5つ
				st.攻撃力[NextLv],
				st.連射[NextLv],
				(int)(st.支援効果[NextLv] * 100),
				st.デバフ効果[NextLv]
			};

			switch (st.デバフ種)
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
			if (is配置リスト){ return; }

			//射程表示
			Screen::SetBlendMode(BlendMode::Alpha, 128);
			Drawing::Circle({ GetX(), GetY(), (double)st.射程[Lv] }, Color::White, 0);
			Screen::SetBlendMode();

			Drawing::Circle({ GetX(), GetY(), (double)st.射程[Lv] }, Color::Red , 2);
		}

		/**.*/
		bool RemoveCheck() override
		{
			//送還
			if (残り送還時間 == 0)
			{
				isRemove = true;
				WITCH::Main->MP += int( st.コスト[Lv] * WITCH::Main->回収率 );
			}

			if (isRemove)
			{
				const int x = int(GetX() - Size * Land::ChipSize) / Land::ChipSize + 1;
				const int y = int(GetY() - Size * Land::ChipSize) / Land::ChipSize + 1;
				SLand->RemoveUnit(x, y, Size);

				SStage->ResetSelect(this);
				Remove();
			}

			return this->isRemove;
		}

		bool 強化開始()
		{
			if (is配置リスト) return false;
			if (Lv >= 5){ return false; }
			if (残り強化時間 > 0 || 残り送還時間 > 0){ return false; }
			if (!TDSystem::詠唱回数[st.魔法種] && !st.isウィッチ){ return false; }

			const int 必要MP = st.コスト[Lv + 1] - st.コスト[Lv];

			if (WITCH::Main->MP < 必要MP){ return false; }

			if (!st.isウィッチ)
			{
				--TDSystem::詠唱回数[st.魔法種];
			}

			WITCH::Main->MP -= 必要MP;

			残り強化時間 = int((Lv + 1) * (Lv + 1) * 60 * WITCH::Main->強化速度);
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
			if (is配置リスト) return false;
			if (残り強化時間 > 0 || 残り送還時間 > 0) return false;

			if (SStage->GetWave()->現在Wave == 0)
			{
				//開始前は即回収
				isRemove = true;
				if (st.isウィッチ){ TDSystem::詠唱回数[st.魔法種]++; }
				else{ TDSystem::詠唱回数[st.魔法種] += Lv + 1; }
				WITCH::Main->MP += int( st.コスト[Lv] * WITCH::Main->MP消費 );
				残り送還時間 = -1;
			}
			else
			{
				if (st.is使い捨て)
				{
					//使い捨て
					Shoot(0);
					isRemove = true;
				}
				else
				{
					//売却
					残り送還時間 = int((SStage->GetWave()->現在Wave + 1) * 60 * WITCH::Main->回収速度);
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

					if (距離 <= st.射程[Lv])
					{
						Shoot(GetDirect(一番近い敵));
						SetWait();
					}
				}
			}
		}

		/**攻撃処理.*/
		virtual void Shoot(double 角度) = 0;
	};

	//弾の種類
	//発射方式
	class Unit : public IUnit
	{
	public:
		Rect shape;
		SpImage sprite;

		//配置位置
		Unit(UnitType 魔法種 , int X座標,int Y座標, bool isリスト) :
			IUnit(shape, sprite, 魔法種 , isリスト),
			sprite(nullptr),
			shape(X座標, Y座標, Size * Land::ChipSize / 2, Size * Land::ChipSize / 2, Size * Land::ChipSize / 2, Size * Land::ChipSize / 2)
		{}

		using S勇者 = Shot < Circle, SpImage, MOTION::勇者 >;
		using S追尾 = Shot < Circle, SpImage, MOTION::追尾 >;
		using S曲射 = Shot < Circle, SpImage, MOTION::曲射 >;
		//using S直進 = Shot < Circle, SpImage, MOTION::ToFront<SPEED::Liner> >;
		template <class TSpeed = SPEED::Liner>
		using S直進 = Shot < Circle, SpImage, MOTION::ToFront<TSpeed> >;

		void Shoot(double 角度)
		{
//入力省略,描画方法,移動方法
#define DEF { GetX(), GetY(), st.半径 },st,Lv,角度

			switch (st.魔法種)
			{
			case UnitType::ライナ://勇者強化
				for (int a = 0; a < st.Hit数[Lv]; ++a)
				{
					角度 = PAI * 2 * a / st.Hit数[Lv];
					SStage->Add	( new S勇者(&MEffect::弾, { { GetX(), GetY() }, st.射程[Lv] * WITCH::Main->射程補正, 角度, 0.1 }, DEF) );
				}
				break;
			case UnitType::ナツメ://武闘家強化
				break;
			case UnitType::ルコウ://騎士強化
				break;
			case UnitType::ディアネラ://プリンセス強化
				break;
			case UnitType::ミナエ://賢者強化
				break;
			case UnitType::トレニア://闘士強化
				break;
			case UnitType::ロチエ://くの一強化
				break;
			case UnitType::バロゥ://狩人強化
				//ADD(Shot直進, &MEffect::弾, { 1 });
				break;
			case UnitType::フィオナ://司祭強化
				break;
			case UnitType::ナズナ://軍師強化
				break;
			case UnitType::委員長://僧侶強化
				break;
			case UnitType::ミルラ://将軍強化
				break;
			case UnitType::兵士://通路用A-単発直進
				//実装する
				SStage->Add(new S直進<>(&MEffect::弾, { 10 }, DEF));
				break;
			case UnitType::傭兵://通路用A-単発直進
				break;
			case UnitType::足軽://通路用A-単発直進
				break;
			case UnitType::技師://必中追尾A-単発型
				//実装する
				SStage->Add(new S追尾(&MEffect::弾, { 10 }, DEF));
				break;
			case UnitType::勇者://必中追尾B-周囲展開型
				break;
			case UnitType::剣士://連射A-単発直進
				//実装する
				SStage->Add(new S直進<>(&MEffect::弾, { 10 }, DEF));
				break;
			case UnitType::剣豪://連射B-乱射直進
				break;
			case UnitType::槍士://反射A-3WAY直進
				//実装する
				角度 -= (st.Hit数[Lv] - 1) * 5 * DEG;
				for (int a = 0; a < st.Hit数[Lv]; ++a)
				{
					角度 += 10*DEG;//10℃刻み
					SStage->Add(new S直進<>(&MEffect::弾, { 10 }, DEF));
				}				
				break;
			case UnitType::騎士://反射B-連射加速直進
				break;
			case UnitType::斧士://吹き飛びA-後ろ射出加速
				//実装する
				SStage->Add(new S直進<SPEED::Accel>(&MEffect::弾, { { -10, 0.1 } }, DEF));
				break;
			case UnitType::闘士://吹き飛びB-周囲回転
				break;
			case UnitType::武闘家://防御破壊A-加速弾-8WAY
				//実装する
				for (int a = 0; a < st.Hit数[Lv]; ++a)
				{
					角度 += PAI / 8;
					IShot* shot = new S直進<SPEED::AccelLimit>(&MEffect::弾, { { 10 , 1 , -1 } }, DEF);
					shot->lifeTime = 120;
					SStage->Add(shot);
				}
				break;
			case UnitType::師範://防御破壊B-炸裂弾、周りぐるぐる
				break;
			case UnitType::狩人://対空専用A-長射程、3連射
				//実装する
				SStage->Add(new S曲射(&MEffect::弾, {} , DEF));
				break;
			case UnitType::射手://対空専用B-中射程、高連射
				break;
			case UnitType::僧侶://対地範囲A-麻痺付与
				break;
			case UnitType::司祭://対地ビームB
				break;
			case UnitType::プリンス://3-8方向攻撃
				break;
			case UnitType::プリンセス://3-8方向攻撃
				break;
			case UnitType::術士://範囲A-加速弾、命中時範囲攻撃
				//実装する
				SStage->Add(new S直進<SPEED::Accel>(&MEffect::弾, { { -10, 0.1 } }, DEF));
				break;
			case UnitType::賢者://範囲B-ホーミング弾、命中時範囲攻撃
				break;
			case UnitType::踊り子://支援A-弱麻痺
				//実装する
				break;
			case UnitType::軍師://支援B-弱吹飛
				break;
			case UnitType::将軍://支援B-弱防御低下
				break;
			case UnitType::執事://使い捨てA-円形使い捨て
				//実装する
				SStage->Add(new S直進<>(&MEffect::弾, { 10 }, DEF));
				break;
			case UnitType::給仕://使い捨てB-十字使い捨て
				break;
			case UnitType::料理人://使い捨てB-円形使い捨て
				break;
			case UnitType::盗賊://鈍足A-高連射、直進弾
				//実装する
				SStage->Add(new S直進<>(&MEffect::弾, { 10 }, DEF));
				break;
			case UnitType::忍者://鈍足A-3-8方向、直進弾
				break;
			case UnitType::くノ一://鈍足B-低連射、炸裂効果
				break;
			}
		}
#undef ADD
	};

}