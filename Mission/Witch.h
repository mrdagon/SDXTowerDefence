//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "TDSystem.h"
#include "IStage.h"
#include "DataS.h"

namespace SDX_TD
{
	using namespace SDX;

	/**魔女.*/
	class Witch : public WitchData
	{
	private:
		//固定パラメータ
		static Witch witchS[2];

		WitchData *st;//レベル上昇や大魔法発動補正前のステータス

		/**発動時の追加効果.*/
		/**敵 HP半減等はこっちで計算*/
		void 大魔法効果()
		{
			switch (st->種類)
			{
			case WitchType::ライナ:

				break;
			default:
				break;
			}
		}

		/**発動中の能力補正効果.*/
		/**補正率アップ等はこっちで計算*/
		void 大魔法補正()
		{
			switch (st->種類)
			{
			case WitchType::ライナ:
				射程補正 *= 1.0 + double(被ダメージ) / 20;
				連射補正 *= 1.0 + double(被ダメージ) / 20;
				攻撃補正 *= 1.2;
				逆境補正 *= 2.0;
				break;
			default:
				break;
			}
		}

		/**ユニット性能補正.*/
		void ユニット補正()
		{
			for (int a = 0; a < int(UnitType::COUNT); ++a)
			{
				ユニット補正(UnitType(a));
			}
		}

		/**.*/
		void ユニット補正(UnitType type)
		{
			if (!TDSystem::isカップル)
			{
				if (!is使用可能[type]){ return; }

				for (int a = 0; a < UnitData::最大強化; ++a)
				{
					//メインのみ使える
					UnitDataS[type].コスト[a] = int(DefUnitDataS[type].コスト[a] * MP消費);
					UnitDataS[type].攻撃力[a] = int(DefUnitDataS[type].攻撃力[a] * 攻撃補正);
					UnitDataS[type].連射[a] = int(DefUnitDataS[type].連射[a] * 連射補正);
					UnitDataS[type].射程[a] = int(DefUnitDataS[type].射程[a] * 射程補正);
					UnitDataS[type].弾速[a] = DefUnitDataS[type].弾速[a] * 弾速補正;
					UnitDataS[type].支援効果[a] = DefUnitDataS[type].支援効果[a] * 支援補正;
					UnitDataS[type].炸裂範囲[a] = int(DefUnitDataS[type].炸裂範囲[a] * 炸裂補正);
					UnitDataS[type].デバフ効果[a] = int(DefUnitDataS[type].デバフ効果[a] * 特殊補正[UnitDataS[type].デバフ種]);
				}

				return;
			}

			//メインのみサブのみ、両方OKで計算を変える
			//両方使えない
			if (!is使用可能[type] && !Sub->is使用可能[type])
			{
				return;
			}

			for (int a = 0; a < UnitData::最大強化; ++a)
			{
				if (is使用可能[type] && Sub->is使用可能[type])
				{
					//両方使える
					UnitDataS[type].コスト[a] = int(DefUnitDataS[type].コスト[a] * MP消費 * Sub->MP消費);
					UnitDataS[type].攻撃力[a] = int(DefUnitDataS[type].攻撃力[a] * 攻撃補正 * Sub->攻撃補正);
					UnitDataS[type].連射[a] = int(DefUnitDataS[type].連射[a] * 連射補正 * Sub->連射補正);
					UnitDataS[type].射程[a] = int(DefUnitDataS[type].射程[a] * 射程補正 * Sub->射程補正);
					UnitDataS[type].弾速[a] = DefUnitDataS[type].弾速[a] * 弾速補正 * Sub->弾速補正;
					UnitDataS[type].支援効果[a] = DefUnitDataS[type].支援効果[a] * 支援補正 * 支援補正;
					UnitDataS[type].炸裂範囲[a] = int(DefUnitDataS[type].炸裂範囲[a] * 炸裂補正 * Sub->炸裂補正);
					UnitDataS[type].デバフ効果[a] = int(DefUnitDataS[type].デバフ効果[a] * 特殊補正[UnitDataS[type].デバフ種] * Sub->特殊補正[UnitDataS[type].デバフ種]);
				}
				else if (is使用可能[type])
				{
					//メインのみ使える
					UnitDataS[type].コスト[a] = int(DefUnitDataS[type].コスト[a] * MP消費);
					UnitDataS[type].攻撃力[a] = int(DefUnitDataS[type].攻撃力[a] * 攻撃補正);
					UnitDataS[type].連射[a] = int(DefUnitDataS[type].連射[a] * 連射補正);
					UnitDataS[type].射程[a] = int(DefUnitDataS[type].射程[a] * 射程補正);
					UnitDataS[type].弾速[a] = DefUnitDataS[type].弾速[a] * 弾速補正;
					UnitDataS[type].支援効果[a] = DefUnitDataS[type].支援効果[a] * 支援補正;
					UnitDataS[type].炸裂範囲[a] = int(DefUnitDataS[type].炸裂範囲[a] * 炸裂補正);
					UnitDataS[type].デバフ効果[a] = int(DefUnitDataS[type].デバフ効果[a] * 特殊補正[UnitDataS[type].デバフ種]);
				}
				else
				{
					//サブのみ使える
					UnitDataS[type].コスト[a] = int(DefUnitDataS[type].コスト[a] * Sub->MP消費);
					UnitDataS[type].攻撃力[a] = int(DefUnitDataS[type].攻撃力[a] * Sub->攻撃補正);
					UnitDataS[type].連射[a] = int(DefUnitDataS[type].連射[a] * Sub->連射補正);
					UnitDataS[type].射程[a] = int(DefUnitDataS[type].射程[a] * Sub->射程補正);
					UnitDataS[type].弾速[a] = DefUnitDataS[type].弾速[a] * Sub->弾速補正;
					UnitDataS[type].支援効果[a] = DefUnitDataS[type].支援効果[a] * Sub->支援補正;
					UnitDataS[type].炸裂範囲[a] = int(DefUnitDataS[type].炸裂範囲[a] * Sub->炸裂補正);
					UnitDataS[type].デバフ効果[a] = int(DefUnitDataS[type].デバフ効果[a] * Sub->特殊補正[UnitDataS[type].デバフ種]);
				}
			}
		}

		/**通常時の性能計算.*/
		/**MP等は初期化しない*/
		void 補正計算()
		{
			攻撃補正 = st->攻撃補正;
			連射補正 = st->連射補正;
			範囲補正 = st->範囲補正;
			射程補正 = st->射程補正;
			支援補正 = st->支援補正;
			弾速補正 = st->弾速補正;

			MP消費 = st->MP消費;
			MP獲得 = st->MP獲得;
			回収率 = st->回収率;
			回収速度 = st->回収速度;
			強化速度 = st->強化速度;

			弱点補正 = st->弱点補正;

			特殊補正[DebuffType::吹飛] = st->特殊補正[DebuffType::吹飛];
			特殊補正[DebuffType::防壊] = st->特殊補正[DebuffType::防壊];
			特殊補正[DebuffType::麻痺] = st->特殊補正[DebuffType::麻痺];
			特殊補正[DebuffType::鈍足] = st->特殊補正[DebuffType::鈍足];

			大魔法時間 = st->大魔法時間;
			獲得SP = st->獲得SP;

			逆境補正 = st->逆境補正;

			追加Hp = st->追加Hp;
			初期Mp = st->初期Mp;

			if (大魔法残り時間 > 0)
			{
				大魔法補正();
			}

			//アイテムや成長補正の有無
			if (!TDSystem::isトライアル)
			{
				レベル補正();
				アイテム補正();
			}

			//逆境補正
			攻撃補正 *= 1 + (逆境補正 * 被ダメージ);
			ユニット補正();
		}

		/**レベルによる補正計算.*/
		void レベル補正()
		{
		}

		/**アイテムによる補正計算.*/
		void アイテム補正()
		{
		}

	public:
		static Witch* Main;
		static Witch* Sub;

		//変動パラメータ
		static int Hp;//共通
		static int 被ダメージ;
		static	EnumArray<int, UnitType> 詠唱回数;

		double Mp = 50;
		double Sp = 0;
		const double 最大Sp = 1000;
		int 大魔法残り時間 = 0;
		EnumArray<bool, UnitType> is使用可能;

		/**メインとサブ両方を初期化.*/
		static void InitAll()
		{
			Hp = 20;
			被ダメージ = 0;

			for (auto & it : 詠唱回数)
			{
				it = 0;
			}

			Main->Init();
			if (TDSystem::isカップル)
			{
				Sub->Init();
			}
			SStage->ResetJobList();
		}

		/**ウィッチ種を設定.*/
		static void SetMain(WitchType ウィッチ種)
		{
			Main = &witchS[0];

			Main->st = &WitchDataS[ウィッチ種];

			for (int a = 0; a < 12; ++a)
			{
				Main->職種[a] = WitchDataS[ウィッチ種].職種[a];
			}
			for (auto &it : Main->is使用可能)
			{
				it = false;
			}

			for (auto &it : Main->職種)
			{
				Main->is使用可能[it] = true;
			}
		}

		static void SetSub(WitchType ウィッチ種)
		{
			Sub = &witchS[1];

			Sub->st = &WitchDataS[ウィッチ種];

			for (auto &it : Main->is使用可能)
			{
				it = false;
			}

			for (auto &it : Main->職種)
			{
				Main->is使用可能[it] = true;
			}
		}

		/**戦闘開始時の初期化処理.*/
		void Init()
		{
			補正計算();
			Hp += 追加Hp;
			Mp = 初期Mp;
			Sp = 0;
			大魔法残り時間 = 0;
			被ダメージ = 0;

			for (int a = 0; a < 12; ++a)
			{
				詠唱回数[職種[a]] += int(UnitDataS[職種[a]].基礎詠唱回数 * 詠唱回数補正);
			}
		};

		/** 大魔法時間の更新等.*/
		/**@todo 切り替え時の描画処理*/
		void Update()
		{
			大魔法残り時間--;
			if (大魔法残り時間 == 0)
			{
				Sp = 0;
				補正計算();//ステータスを元に戻す

				if (TDSystem::isカップル)
				{
					std::swap(Main, Sub);
					SStage->ResetJobList();
				}
			}
		}

		/**被ダメージ処理.*/
		void Damage(int ダメージ量)
		{
			//SPが増加し、逆境補正がかかる
			Sp += 最大Sp / 20;
			被ダメージ += ダメージ量;
			Hp = std::max(0, Hp - ダメージ量);
			補正計算();

			if (TDSystem::isカップル)
			{
				Sub->Sp += 最大Sp / 20;
				Sub->補正計算();
			}
		}

		/**大魔法発動時の性能計算、効果処理.*/
		void 大魔法発動()
		{
			if (Sp < 最大Sp || 大魔法残り時間 > 0)
			{
				return;
			}
			//演出
			for (int a = 0; a < 250; ++a)
			{
				Screen::SetBright(Color::Gray);
				SStage->Draw();
				Screen::SetBright(Color::White);
				//@todo 演出は仮
				MFont::ゴシック中.DrawRotate({ 800 - a * 6, 300 }, 5, 0, Color::White, false, "大魔法 フォルドアーカレイト");
				System::Update();
			}

			大魔法残り時間 = 大魔法時間;
			補正計算();
			大魔法効果();
		}
	};

	Witch Witch::witchS[2];
	Witch* Witch::Main;
	Witch* Witch::Sub;

	EnumArray<int, UnitType> Witch::詠唱回数;
	int	  Witch::Hp;
	int   Witch::被ダメージ;
}