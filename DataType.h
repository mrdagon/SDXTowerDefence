#pragma once//☀Unicode
#include "EnumType.h"
#include "Material.h"

namespace SDX_TD
{
    using namespace SDX;
    //パラメータ用のデータ型
    namespace Land
    {
        static const int MapSize = 32;
        static const int ChipSize = 16;
        static const int 到達不可 = 99999999;
        static const double 自動床速度 = 0.5;
    }

    /**魔法の基礎性能.*/
    struct UnitData
    {
        static const int 最大強化 = 6;

        std::string 名前;
        std::string 説明文;

        UnitType 魔法種;
        RangeType 射程種;
        Element 属性;

        int コスト[最大強化];
        int 攻撃力[最大強化];
        int 連射[最大強化];
        int 射程[最大強化];
        double 弾速[最大強化];

        double 支援効果[最大強化];

        int 炸裂範囲[最大強化];
        double 炸裂威力[最大強化];

        DebuffType デバフ種;
        int    デバフ効果[最大強化];
        double デバフ率[最大強化];

        double 半径 = 10;//当たり判定の大きさ

        bool is対空 = true;//空の敵に当たるかどうか
        bool is対地 = true;//地上の敵に当たるかどうか
        bool is使い捨て = false;

        bool is貫通 = true;//命中時に消滅するかどうか

        bool isウィッチ = false;//指揮官魔法、詠唱回数の管理が違う

        int  Hit数[最大強化];

        int  基礎詠唱回数;
    };

    /**敵の基礎性能.*/
    struct EnemyData
    {
        //基礎ステータス
        std::string 種族名;
        std::string 説明文;
        EnemyType 種族 = EnemyType::マーマン;
        Belong 移動タイプ = Belong::陸;
        Element 属性;

        int スコア = 50;
        int 最大HP = 100;
        double 防御力 = 0;
        double 移動速度 = 1;
        double 回避力 = 0;

        //無効 or 有効
        DataPack<bool, DebuffType> 特殊耐性;

        void Set(Belong 移動タイプ, Element 属性, int 最大HP, int スコア, double 移動速度, double 防御力, double 回避力)
        {
            this->移動タイプ = 移動タイプ;
            this->属性 = 属性;
            this->スコア = スコア;
            this->最大HP = 最大HP;
            this->防御力 = 防御力;
            this->回避力 = 回避力;
            this->移動速度 = 移動速度;
            this->特殊耐性[DebuffType::鈍足] = false;
            this->特殊耐性[DebuffType::麻痺] = false;
            this->特殊耐性[DebuffType::吹飛] = false;
            this->特殊耐性[DebuffType::防壊] = false;
        }

        void SetInfo(const char* 種族名, const char* 説明文)
        {
            this->種族名 = 種族名;
            this->説明文 = 説明文;
        }


    };

    /**ウィッチの基礎性能.*/
    struct WitchData
    {
        WitchData()
        {
            特殊補正[DebuffType::吹飛] = 1.0;
            特殊補正[DebuffType::防壊] = 1.0;
            特殊補正[DebuffType::麻痺] = 1.0;
            特殊補正[DebuffType::鈍足] = 1.0;
        }

        double 攻撃補正 = 1.0;
        double 連射補正 = 1.0;
        double 範囲補正 = 1.0;
        double 射程補正 = 1.0;
        double 支援補正 = 1.0;
        double 弾速補正 = 1.0;

        double MP消費   = 1.0;
        double 回収率   = 0.7;
        double 回収速度 = 1.0;
        double 強化速度 = 1.0;

        double 弱点補正 = 1.1;

        DataPack<double, DebuffType> 特殊補正;

        int    大魔法時間 = 3000;
        double 必要SP = 1.0;

        double 逆境補正 = 0.01;//ライフ-1につき1%攻撃力が上がる

        //ステージ開始時しか参照しないパラメータ
        int    初期HP = 20;
        int    初期MP = 50;

        double 詠唱回数補正 = 1.0;
    };

    struct StageData
    {
        std::string 名前;
        std::string 説明;

        int シングルのハイスコア[(int)WitchType::MAX];

        int タッグのハイスコア[3];        
        std::tuple<WitchType,WitchType> タッグの組み合わせ[3];

        Difficulty シングルの達成難易度[(int)WitchType::MAX];
        Difficulty タッグの達成難易度[3];

        double Wave速度;

        EnemyType 敵発生リスト[100];
        ChipType  地形情報[30][30];
    };

    struct DifficultyData
    {
        int Wave数;
        double レベル補正;
        double HP補正;
        int 雑魚召喚数;
        int ボス召喚数;

        void Set(int Wave数, int 雑魚召喚数, int ボス召喚数, double HP補正, double レベル補正)
        {
            this->Wave数 = Wave数;
            this->雑魚召喚数 = 雑魚召喚数;
            this->ボス召喚数 = ボス召喚数;
            this->HP補正 = HP補正;
            this->レベル補正 = レベル補正;
        }
    };

    struct ChipData
    {
        bool is配置可能;
        bool is陸移動;
        bool is水上移動;

        void Set(bool is配置可能, bool is陸移動, bool is水上移動)
        {
            this->is配置可能 = is配置可能;
            this->is陸移動 = is陸移動;
            this->is水上移動 = is水上移動;
        }

    };

    namespace
    {
        DataPack<EnemyData, EnemyType> EnemyDataS;
        DataPack<UnitData, UnitType> UnitDataS;
        DataPack<StageData, StageType> StageDataS;
        DataPack<DifficultyData, Difficulty> TrialDataS;
        DataPack<DifficultyData, Difficulty> PowerDataS;
        DataPack<ChipData, ChipType> ChipDataS;
    }

    void LoadUnitS()
    {
        File UnitFile("data.txt", FileMode::Read, true);

        for (auto &it : UnitDataS)
        {
            UnitFile.Read(it.名前);
            UnitFile.Read(it.説明文);

            UnitFile.Read(it.属性);
            UnitFile.Read(it.射程種);

            int param;
            UnitFile.Read(param);
            if (param % 3 == 1) it.is対空 = false;
            if (param % 3 == 2) it.is対地 = false;
            if (param % 3 >= 3) it.is貫通 = true;
            if (param == 7) it.is使い捨て = true;

            UnitFile.Read(it.基礎詠唱回数);
            UnitFile.Read(it.デバフ種);

            UnitFile.Read(it.コスト, 6);
            UnitFile.Read(it.攻撃力, 6);
            UnitFile.Read(it.射程, 6);
            UnitFile.Read(it.連射, 6);

            UnitFile.Read<int>(it.弾速, 6, 100);

            UnitFile.Read<int>(it.炸裂威力, 6, 100);

            UnitFile.Read(it.炸裂範囲, 6);

            UnitFile.Read(it.デバフ効果, 6);
            UnitFile.Read<int>(it.デバフ率, 6, 100);
            UnitFile.Read(it.Hit数, 6);
        }
    }

    void LoadEnemyS()
    {
        for (int a = 0; a < (int)EnemyType::MAX; ++a)
        {
            EnemyDataS[(EnemyType)a].種族 = (EnemyType)a;
        }

        //スコア HP 防御 移動速度
        EnemyDataS[EnemyType::ゼリー    ].Set(Belong::陸, Element::氷, 50, 15, 0.4, 0.0, 0.0);
        EnemyDataS[EnemyType::ゴブリン  ].Set(Belong::陸, Element::樹, 50, 10, 0.0, 1.0, 0.0);
        EnemyDataS[EnemyType::オーガ    ].Set(Belong::陸, Element::炎, 50, 20, 0.0, 1.0, 0.0);
        EnemyDataS[EnemyType::コボルド  ].Set(Belong::陸, Element::樹, 50, 15, 0.0, 1.0, 0.0);
        EnemyDataS[EnemyType::ケットシー].Set(Belong::陸, Element::空, 50, 15, 0.0, 1.0, 0.0);
        EnemyDataS[EnemyType::シャーマン].Set(Belong::陸, Element::炎, 50, 20, 0.0, 1.0, 0.0);
        EnemyDataS[EnemyType::スケルトン].Set(Belong::陸, Element::氷, 50, 15, 0.0, 1.0, 0.0);
        EnemyDataS[EnemyType::インプ    ].Set(Belong::空, Element::空, 50, 15, 0.0, 1.0, 0.0);
        EnemyDataS[EnemyType::グリフィン].Set(Belong::陸, Element::空, 50, 20, 0.0, 1.0, 0.0);
        EnemyDataS[EnemyType::ケルベロス].Set(Belong::陸, Element::炎, 50, 20, 0.0, 1.0, 0.0);
        EnemyDataS[EnemyType::ゴーレム  ].Set(Belong::陸, Element::樹, 50, 20, 0.0, 1.0, 0.0);
        EnemyDataS[EnemyType::ドラゴン  ].Set(Belong::陸, Element::炎, 50, 25, 0.0, 1.0, 0.0);
        EnemyDataS[EnemyType::ゼリー王  ].Set(Belong::陸, Element::氷, 50, 20, 0.0, 1.0, 0.0);
        EnemyDataS[EnemyType::マーマン  ].Set(Belong::水, Element::氷, 50, 15, 0.0, 1.0, 0.0);
        EnemyDataS[EnemyType::ゴースト  ].Set(Belong::空, Element::氷, 50, 20, 0.0, 1.0, 0.0);


    }

    void LoadStageS()
    {


    }

    void LoadDifficultyS()
    {
        //Wave数,雑魚数,ボス数,HP補正,Lv補正
        TrialDataS[Difficulty::Easy      ].Set( 20, 16 , 2, 1.00 , 1.00 );
        TrialDataS[Difficulty::Normal    ].Set(30, 20, 2, 1.25, 1.10);
        TrialDataS[Difficulty::Hard      ].Set(40, 24, 2, 1.50, 1.20);
        TrialDataS[Difficulty::Maniac    ].Set(60, 28, 2, 1.75, 1.30);
        TrialDataS[Difficulty::Hell      ].Set(80, 32, 2, 2.00, 1.40);
        TrialDataS[Difficulty::DeathMarch].Set(100, 44, 2, 2.50, 1.50);

        PowerDataS[Difficulty::Easy      ].Set(25, 24, 3, 1.00, 1.00);
        PowerDataS[Difficulty::Normal    ].Set(50, 24, 3, 1.30, 1.20);
        PowerDataS[Difficulty::Hard      ].Set(75, 24, 3, 1.60, 1.40);
        PowerDataS[Difficulty::Maniac    ].Set(100, 32, 4, 2.00, 1.60);
        PowerDataS[Difficulty::Hell      ].Set(300, 32, 4, 3.00, 1.80);
        PowerDataS[Difficulty::DeathMarch].Set(1000, 40, 5, 5.00, 2.00);
    }

    void LoadChipS()
    {
        //配置,陸,海
        ChipDataS[ChipType::草].Set(true, true, true);
        ChipDataS[ChipType::沼].Set(true, true, true);
        ChipDataS[ChipType::森].Set(true, false, false);
        ChipDataS[ChipType::道].Set(false, true, true);
        ChipDataS[ChipType::橋].Set(false, true, true);
        ChipDataS[ChipType::↑].Set(true, true, true);
        ChipDataS[ChipType::↓].Set(true, true, true);
        ChipDataS[ChipType::←].Set(true, true, true);
        ChipDataS[ChipType::→].Set(true, true, true);
        ChipDataS[ChipType::山].Set(false, false, false);
        ChipDataS[ChipType::水].Set(false, false, true);
        ChipDataS[ChipType::穴].Set(false, true, true);
        ChipDataS[ChipType::畑].Set(false, true, true);
        ChipDataS[ChipType::高山].Set(false,false,false);
    }
}