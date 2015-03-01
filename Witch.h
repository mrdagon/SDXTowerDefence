//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "TDSystem.h"
#include "IStage.h"
#include "DataS.h"
#include "Artifact.h"

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

		/** Mainとサブ含めて.*/
		/** 初期化時、大魔法発動時、終了時、被ダメージ時、MP補正有りでMP変動時に計算すれば良い*/
		static void 全補正計算()
		{
			Main->補正計算();
			if (TDSystem::isカップル)
			{
				Sub->補正計算();
			}

			Main->ユニット補正();
		}

		/**発動中の能力補正効果.*/
		/**補正率アップ等はこっちで計算*/
		void 大魔法補正()
		{
			switch (st->種類)
			{
			case WitchType::ライナ:
				//被ダメージで効果変動
				射程補正 *= 1.0 + double(被ダメージ) / 20;
				連射補正 *= 1.0 + double(被ダメージ) / 20;
				攻撃補正 *= 1.2;
				逆境補正 *= 2.0;
				break;
			case WitchType::ナツメ:
				攻撃補正 *= 2.0;
				特殊補正[DebuffType::防壊] *= 2.0;
				break;
			case WitchType::ルコウ:
				攻撃補正 *= 1.5;
				break;
			case WitchType::ディアネラ:
				攻撃補正 *= 1.2;
				射程補正 *= 1.1;
				連射補正 *= 1.1;
				支援補正 *= 1.1;
				break;
			case WitchType::ミナエ:
				攻撃補正 *= 1.3;
				射程補正 *= 1.3;
				break;
			case WitchType::トレニア:
				攻撃補正 *= 1.2;
				炸裂加算 = 32;
				break;
			case WitchType::ロチエ:
				攻撃補正 *= 1.2;
				特殊補正[DebuffType::鈍足] *= 2.0;
				特殊補正[DebuffType::麻痺] *= 2.0;
				is継続ダメージ = true;
				break;
			case WitchType::バロゥ:
				射程補正 *= 1.5;
				連射補正 *= 1.5;
				break;
			case WitchType::フィオナ:
				射程補正 *= 1.0 + double(Hp) / 20;
				連射補正 *= 1.0 + double(Hp) / 20;
				攻撃補正 *= 1.0 + double(Hp) / 20;
				break;
			case WitchType::ナズナ:
				射程補正 *= 1.0 + double(Hp) / 20;
				連射補正 *= 1.0 + double(Hp) / 20;
				攻撃補正 *= 1.0 + double(Hp) / 20;
				break;
			case WitchType::委員長:
				攻撃補正 *= 1.2;
				弱点補正 *= 2.0;
				回収速度 = 0;
				回収率 = 1.0;
				強化速度 = 0;
				break;
			case WitchType::ミルラ:
				支援補正 *= 1.2;
				is速度支援 = true;
				is射程支援 = true;
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

		/**個別の計算.*/
		void ユニット補正(UnitType type)
		{
			//メインのみサブのみ、両方OKで計算を変える

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
					UnitDataS[type].炸裂範囲[a] = int(DefUnitDataS[type].炸裂範囲[a] * 炸裂補正) + 炸裂加算;
					UnitDataS[type].デバフ効果[a] = int(DefUnitDataS[type].デバフ効果[a] * 特殊補正[UnitDataS[type].デバフ種]);
				}
				return;
			}

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
					UnitDataS[type].炸裂範囲[a] = int(DefUnitDataS[type].炸裂範囲[a] * 炸裂補正 * Sub->炸裂補正) + 炸裂加算;
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
					UnitDataS[type].炸裂範囲[a] = int(DefUnitDataS[type].炸裂範囲[a] * 炸裂補正) + 炸裂加算;
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
					UnitDataS[type].炸裂範囲[a] = int(DefUnitDataS[type].炸裂範囲[a] * Sub->炸裂補正) + 炸裂加算;
					UnitDataS[type].デバフ効果[a] = int(DefUnitDataS[type].デバフ効果[a] * Sub->特殊補正[UnitDataS[type].デバフ種]);
				}
			}
		}

		/**通常時の性能計算.*/
		/**MP等は初期化しない*/
		void 補正計算()
		{
			種類 = st->種類;

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

			is継続ダメージ = false;//鈍足or麻痺状態のスリップダメージ
			is速度支援 = false;//速度も強化するかどうか
			is射程支援 = false;//射程も強化するかどうか
			炸裂加算 = 0;

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
		}

		/**レベルによる補正計算.*/
		void レベル補正()
		{
			//強化回数のみ影響予定
		}

		/**アイテムによる補正計算.*/
		void アイテム補正()
		{
			for (auto &it : 装備)
			{
				if (it == nullptr){ continue; }

				攻撃補正 += it->攻撃;
				連射補正 += it->連射;
				範囲補正 += it->範囲;
				射程補正 += it->射程;
				支援補正 += it->支援;
				//弾速補正 += it->弾速;

				MP消費 += it->消費;
				回収速度 += it->回収;
				強化速度 += it->強化;

				特殊補正[DebuffType::吹飛] += it->吹飛;
				特殊補正[DebuffType::防壊] += it->防壊;
				特殊補正[DebuffType::麻痺] += it->麻痺;
				特殊補正[DebuffType::鈍足] += it->鈍足;

				獲得SP += it->Sp;
				追加Hp += it->Hp;
				初期Mp += it->Mp;

				逆境補正 += it->逆境;
			}
		}

	public:
		static Witch* Main;
		static Witch* Sub;

		//変動パラメータ
		static int Hp;//共通
		static int 被ダメージ;
		static EnumArray<int, UnitType> 配置回数;
		static EnumArray<int, UnitType> 強化回数;

		bool is継続ダメージ = false;//鈍足or麻痺状態のスリップダメージ
		bool is速度支援 = false;//速度も強化するかどうか
		bool is射程支援 = false;//射程も強化するかどうか
		int 炸裂加算 = 0;//範囲攻撃追加

		double Mp = 50;
		double Sp = 0;
		const double 最大Sp = 1000;
		int 大魔法残り時間 = 0;
		EnumArray<bool, UnitType> is使用可能;
		Artifact* 装備[4];

		/**メインとサブ両方を初期化.*/
		static void InitAll()
		{
			Hp = 20;
			被ダメージ = 0;
			全補正計算();
			

			//ウィッチは1回、他は無制限に配置可能
			for (int a = 0; a < (int)UnitType::COUNT; ++a)
			{
				if ( IsWitch(UnitType(a)) )
				{
					配置回数[UnitType(a)] = 1;
				}
				else
				{
					配置回数[UnitType(a)] = 65536;
				}
			}

			for (auto & it : 強化回数)
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
		/**@todo パワーかどうかで処理変化*/
		void Init()
		{
			Hp += 追加Hp;
			Mp = 初期Mp;

			//デバッグ用
			Mp = 1000;

			Sp = 0;
			大魔法残り時間 = 0;
			被ダメージ = 0;

			名前 = st->名前;
			大魔法名 = st->大魔法名;
			魔導具名 = st->魔導具名;
			説明文 = st->説明文;

			for (int a = 0; a < 12; ++a)
			{
				if (IsWitch(職種[a]))
				{
					強化回数[職種[a]] += UnitDataS[職種[a]].基礎強化回数;
				}
				else
				{
					//カップルなら半減？
					強化回数[職種[a]] += int(UnitDataS[職種[a]].基礎強化回数 * 強化回数補正);
				}
			}
		};

		/** 大魔法時間の更新等.*/
		/**@todo 切り替え時の描画処理*/
		void Update()
		{
			大魔法残り時間--;
			if (大魔法残り時間 == 0)
			{
				//効果終了時処理
				SStage->大魔法効果(false);
				Sp = 0;

			}

			全補正計算();
		}

		/**Sp上昇処理.*/
		void AddSp(double 上昇量)
		{
			if (Sp >= 最大Sp)
			{
				return;
			}

			Sp += 上昇量;

			//最大値を超えたら効果音を鳴らす
			if (Sp >= 最大Sp)
			{
				MSound::Spチャージ完了.Play();
			}
		}

		/**被ダメージ処理.*/
		void Damage(int ダメージ量)
		{
			MSound::ダメージ.Play();

			//SPが増加し、逆境補正がかかる
			AddSp(最大Sp / 20);
			//被ダメ補正は最大で20まで
			被ダメージ = std::min(被ダメージ+ダメージ量,20);
			Hp = std::max(0, Hp - ダメージ量);
		}

		/**大魔法発動時の性能計算、効果処理.*/
		void 大魔法発動()
		{
			//使用可能かどうか判定
			if (Sp < 最大Sp || 大魔法残り時間 > 0)
			{
				return;
			}

			大魔法残り時間 = 大魔法時間;
			SStage->大魔法効果(true);
		}
	};

	Witch Witch::witchS[2];
	Witch* Witch::Main;
	Witch* Witch::Sub;

	EnumArray<int, UnitType> Witch::配置回数;
	EnumArray<int, UnitType> Witch::強化回数;
	int	  Witch::Hp;
	int   Witch::被ダメージ;
}