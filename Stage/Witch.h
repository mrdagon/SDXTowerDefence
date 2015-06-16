//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "System/TDSystem.h"
#include "IStage.h"
#include "Struct/DataS.h"

namespace SDX_TD
{
    using namespace SDX;

    /**魔女.*/
    class Witch : public WitchData
    {
    private:
        //固定パラメータ

        WitchData *st;//レベル上昇や大魔法発動補正前のステータス

        /**発動中の能力補正効果.*/
        /**補正率アップ等はこっちで計算*/
        void 大魔法補正()
        {
            switch (st->種類)
            {
            case WitchType::ライナ:
                //被ダメージで効果変動
                射程補正 *= 2.0 - double(Witch::Hp) / Witch::最大Hp;
                連射補正 *= 2.0 - double(Witch::Hp) / Witch::最大Hp;
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
			//@todo 配置可能ユニット+ウィッチ用だけで良さそう
            for (int a = 0; a < int(UnitType::COUNT); ++a)
            {
                ユニット補正(UnitType(a));
            }
        }

        /**個別の計算.*/
        void ユニット補正(UnitType type)
        {			
            for (int a = 0; a < UnitData::最大強化; ++a)
            {
                //メインの補正のみ有効
                UnitDataS[type].コスト[a] = DefUnitDataS[type].コスト[a] - int(DefUnitDataS[type].コスト[a] * (1.0 - MP消費) );
                UnitDataS[type].攻撃力[a] = int(DefUnitDataS[type].攻撃力[a] * 攻撃補正);
                UnitDataS[type].連射[a] = int(DefUnitDataS[type].連射[a] * 連射補正);
                UnitDataS[type].射程[a] = int(DefUnitDataS[type].射程[a] * 射程補正);
                UnitDataS[type].弾速[a] = DefUnitDataS[type].弾速[a] * 弾速補正;
                UnitDataS[type].支援効果[a] = DefUnitDataS[type].支援効果[a] * 支援補正;
                UnitDataS[type].炸裂範囲[a] = int(DefUnitDataS[type].炸裂範囲[a] * 炸裂補正) + 炸裂加算;
                UnitDataS[type].デバフ効果[a] = int(DefUnitDataS[type].デバフ効果[a] * 特殊補正[DefUnitDataS[type].デバフ種]);
				if (UnitDataS[type].デバフ種 == DebuffType::鈍足)
				{
					UnitDataS[type].デバフ率[a] = DefUnitDataS[type].デバフ率[a] * 特殊補正[DefUnitDataS[type].デバフ種];
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

			スコア補正 = 1.0;
            逆境補正 = st->逆境補正;

            追加Hp = st->追加Hp;
            追加Mp = st->追加Mp;

            is継続ダメージ = false;//鈍足or麻痺状態のスリップダメージ
            is速度支援 = false;//速度も強化するかどうか
            is射程支援 = false;//射程も強化するかどうか
            炸裂加算 = 0;

            種族特攻[SubEnemyType::闇] = 1.0;
            種族特攻[SubEnemyType::亜人] = 1.0;
            種族特攻[SubEnemyType::自然] = 1.0;
            種族特攻[SubEnemyType::獣] = 1.0;
            種族特攻[SubEnemyType::水棲] = 1.0;
            種族特攻[SubEnemyType::竜] = 1.0;

            if (大魔法残り時間 > 0)
            {
                大魔法補正();
            }

            //成長補正の有無
            if ( TDSystem::isスキル )
            {
                スキル補正();
            }

            //逆境補正
            if (Hp < 最大Hp)
            {
				//Hp = 0で 1+逆境補正になる
                攻撃補正 *= 1 + (逆境補正 * (1 - double(Hp) / 最大Hp));
            }

            //補正効果をユニットに反映
            ユニット補正();
        }

        /**スキルによる補正計算.*/
        void スキル補正()
        {
            for (int a = 0; a < (int)SkillType::COUNT; ++a)
            {
                auto type = SkillType(a);

                double pt = 0;

                if (スキルLv[type] < 100)
                {
                    //レベル1で2%上昇
                    for (int b = 0; b < スキルLv[type]; ++b)
                    {
                        //レベル5毎に+補正-0.1%
                        pt += (20 - b / 5);
                    }
                    pt = pt/1000;
                }
                else
                {
                    //レベル100で105%上昇
                    //レベル100以降は+0.1%される
                    pt = 1.05 + (スキルLv[type] - 100) * 0.001;
                }

                switch (type)
                {
                    case SkillType::攻撃:攻撃補正 *= (1.0+pt); break;
                    case SkillType::連射:連射補正 *= (1.0+pt); break;
                    case SkillType::射程:射程補正 *= (1.0 + pt); break;
                    case SkillType::支援:支援補正 *= (1.0 + pt); break;
                    case SkillType::拡散:炸裂補正 *= (1.0 + pt); break;
                    case SkillType::麻痺:特殊補正[DebuffType::麻痺] *= (1.0 + pt);
                    case SkillType::鈍足:特殊補正[DebuffType::鈍足] *= (1.0 + pt);
                    case SkillType::吹飛:特殊補正[DebuffType::吹飛] *= (1.0 + pt);
                    case SkillType::防壊:特殊補正[DebuffType::防壊] *= (1.0 + pt);
                    case SkillType::回収:回収速度 /= (1.0 + pt); break;
                    case SkillType::強化:強化速度 /= (1.0 + pt); break;
                    case SkillType::逆境:逆境補正 *= (1.0 + pt); break;
                    case SkillType::集中:MP獲得 *= (1.0 + pt); break;
                    case SkillType::体力:
                        if (this == Main){ 追加Hp += スキルLv[type];}
                        break;
                    case SkillType::魔力:
                        if (this == Main){ 追加Mp += スキルLv[type] * 5; }
                        break;
                    case SkillType::必殺:獲得SP *= (1.0 + pt); break;
                    case SkillType::対竜:種族特攻[SubEnemyType::竜] *= (1.0 + pt*2); break;
                    case SkillType::対獣:種族特攻[SubEnemyType::獣] *= (1.0 + pt*2); break;
                    case SkillType::対人:種族特攻[SubEnemyType::亜人] *= (1.0 + pt*2); break;
                    case SkillType::対闇:種族特攻[SubEnemyType::闇] *= (1.0 + pt*2); break;
                    case SkillType::対水:種族特攻[SubEnemyType::水棲] *= (1.0 + pt*2); break;
                    case SkillType::対樹:種族特攻[SubEnemyType::自然] *= (1.0 + pt*2); break;
                    case SkillType::試練:break;
					case SkillType::幸運:スコア補正 *= 1.0 + スキルLv[type]*0.02; break;
                }
            }
        }

    public:
        static Witch witchS[2];
        static Witch* Main;
        static Witch* Sub;

        //変動パラメータ
        static const int 基本Hp = 20;
        static const int 基本Mp = 50;
		static const int 基本Sp = 1000;
		static int 最大Hp;//共通
		static int Hp;//共通
        static int Mp;//共通
        static double Sp;//共通
        static double 最大Sp;//共通
        static int 大魔法残り時間;

        static EnumArray<int, UnitType> 配置回数;//実質的に無意味
        static EnumArray<int, UnitType> 強化回数;

        bool is継続ダメージ = false;//鈍足or麻痺状態のスリップダメージ
        bool is速度支援 = false;//速度も強化するかどうか
        bool is射程支援 = false;//射程も強化するかどうか
        int 炸裂加算 = 0;//範囲攻撃追加
        double スコア補正;
        EnumArray<double, SubEnemyType> 種族特攻;

        /**メインとサブ両方を初期化.*/
        static void InitAll()
        {
            Main = &witchS[0];
            Sub = &witchS[1];

            Hp = 基本Hp;
            最大Hp = 基本Hp;
			Sp = 0;
			最大Sp = 基本Sp;
            Mp = 基本Mp;
            Main->補正計算();

            //ウィッチは1回、他は無制限に配置可能
            for (int a = 0; a < (int)UnitType::COUNT; ++a)
            {
                if ( a <= (int)UnitType::ミルラ )
                {
                    配置回数[UnitType(a)] = 1;
                }
                else
                {
                    配置回数[UnitType(a)] = 65536;
                }
            }

            //強化回数再計算
            //初期MPとHP再計算
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
        }

        static void SetSub(WitchType ウィッチ種)
        {
            Sub = &witchS[1];
			
            Sub->st = &WitchDataS[ウィッチ種];

            for (int a = 0; a < 12; ++a)
            {
                Sub->職種[a] = WitchDataS[ウィッチ種].職種[a];
            }
        }

        /**戦闘開始時の初期化処理.*/
        /**@todo パワーかどうかで処理変化*/
        void Init()
        {
            Hp += 追加Hp;
			最大Hp += 追加Hp;
            Mp += 追加Mp;

            Sp = 0;
            大魔法残り時間 = 0;

            名前 = st->名前;
            大魔法名 = st->大魔法名;
            魔導具名 = st->魔導具名;
            説明文 = st->説明文;
			種類 = st->種類;

            for (int a = 0; a < 12; ++a)
            {
                強化回数[職種[a]] += int(UnitDataS[職種[a]].基礎強化回数 * 強化回数補正);
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
			//@todo 大魔法開始/終了、非ダメージ時、初期化時だけ補正計算すれば良さそう
            補正計算();
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
            Hp = std::max(0, Hp - ダメージ量);
        }

        /**大魔法発動時の性能計算、効果処理.*/
		/** 実際の処理はStage.hで殆ど実装*/
        void 大魔法発動()
        {
            //使用可能かどうか判定
            if (Sp < 最大Sp || 大魔法残り時間 > 0)
            {
                return;
            }

            大魔法残り時間 = 大魔法時間;
			最大Sp *= 2;
            SStage->大魔法効果(true);
        }
    };

    Witch Witch::witchS[2];
    Witch* Witch::Main;
    Witch* Witch::Sub;

    EnumArray<int, UnitType> Witch::配置回数;
    EnumArray<int, UnitType> Witch::強化回数;
    int Witch::最大Hp;
    int	Witch::Hp;
    int Witch::Mp;//共通
    double Witch::Sp = 0;//共通
    double Witch::最大Sp = 1000;
    int Witch::大魔法残り時間 = 0;
}