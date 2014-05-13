#pragma once//☀Unicode
#include "EnumType.h"
#include "Material.h"

namespace SDX_TD
{
    using namespace SDX;
    //パラメータ用のデータ型
    namespace Land
    {
        static const int MapSize = 30;
        static const int ChipSize = 20;
        static const int 到達不可 = 99999999;
        static const double 自動床速度 = 0.5;
    }

    /**魔法の基礎性能.*/
    struct MagicData
    {
        static const int 最大強化 = 6;

        std::string 名前;
        std::string 説明文;

        MagicType 魔法種;
        RangeType 射程種;
        Elements 魔法属性;

        int コスト[最大強化];
        int 攻撃力[最大強化];
        int 連射[最大強化];
        int 射程[最大強化];
        double 弾速[最大強化];

        double 支援効果[最大強化];
        double 連射支援[最大強化];
        double 射程支援[最大強化];

        int 炸裂範囲[最大強化];
        double 炸裂威力[最大強化];

        DebuffType デバフ種;
        int    デバフ効果[最大強化];
        double デバフ率[最大強化];

        double 半径 = 10;//当たり判定の大きさ

        bool is対空 = true;//空の敵に当たるかどうか
        bool is対地 = true;//地上の敵に当たるかどうか
        bool is支援 = false;//支援専用
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
        EnemyType 種族 = EnemyType::マーマン;
        Belong 移動タイプ = Belong::陸;
        Elements 魔法属性;

        int スコア = 50;
        int 最大HP = 100;
        double 防御力 = 0;
        double 移動速度 = 1;

        //無効 or 有効
        bool 異状耐性[4];//各属性効果への耐性

        void Set(const char* 種族名, Belong 移動タイプ, Elements 魔法属性, int スコア, int 最大HP, double 防御力, double 移動速度, std::vector<bool> 異状耐性 = { false, false, false, false })
        {
            this->種族名 = 種族名;
            this->移動タイプ = 移動タイプ;
            this->魔法属性 = 魔法属性;
            this->スコア = スコア;
            this->最大HP = 最大HP;
            this->防御力 = 防御力;
            this->移動速度 = 移動速度;
            this->異状耐性[0] = 異状耐性[0];
            this->異状耐性[1] = 異状耐性[1];
            this->異状耐性[2] = 異状耐性[2];
            this->異状耐性[3] = 異状耐性[3];
        }

    };

    /**ウィッチの基礎性能.*/
    struct WitchData
    {
        WitchData()
        {
            for (int a = 0; a < 4; ++a)
            {
                状態強化[a] = 1.0;
                属性強化[a] = 1.0;
            }
        }

        double 攻撃補正 = 1.0;
        double 連射補正 = 1.0;
        double 範囲補正 = 1.0;
        double 射程補正 = 1.0;
        double 支援補正 = 1.0;
        double 支援範囲 = 1.0;
        double 弾速補正 = 1.0;

        double 回収率   = 0.5;
        double 回収速度 = 1.0;
        double 強化速度 = 1.0;

        double 弱点補正 = 1.1;
        double 状態強化[4];
        double 属性強化[4];

        double 逆境補正 = 0.01;//ライフ-1につき1%攻撃力が上がる

        ChipType 地形補正;

        //ステージ開始時しか参照しないパラメータ
        int    初期HP = 20;
        int    初期MP = 50;

        //レベルで変化しないパラメータ
        int    大魔法時間 = 3000;
        double 必要SP = 100;
        double MP消費 = 1.0;

        MagicType 魔法タイプ[10];
        double 詠唱回数補正 = 1.0;

        int レベル;
        int 経験値;
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
        DataPack<MagicData, MagicType> MagicDataS;
        DataPack<WitchData, WitchType> WitchDataS;
        DataPack<StageData, StageType> StageDataS;
        DataPack<DifficultyData, Difficulty> TrialDataS;
        DataPack<DifficultyData, Difficulty> PowerDataS;
        DataPack<ChipData, ChipType> ChipDataS;
    }

    void LoadMagicS()
    {
        File magicFile("data.txt", FileMode::Read, true);

        for (int i = 0; i<(int)MagicType::MAX; ++i)
        {
            magicFile.Read(MagicDataS[i].名前);
            magicFile.Read(MagicDataS[i].説明文);

            magicFile.Read(MagicDataS[i].魔法属性);
            magicFile.Read(MagicDataS[i].射程種);

            int param;
            magicFile.Read(param);
            if (param % 3 == 1) MagicDataS[i].is対空 = false;
            if (param % 3 == 2) MagicDataS[i].is対地 = false;
            if (param % 3 >= 3) MagicDataS[i].is貫通 = true;
            if (param == 6) MagicDataS[i].is支援 = true;
            if (param == 7) MagicDataS[i].is使い捨て = true;

            magicFile.Read(MagicDataS[i].基礎詠唱回数);
            magicFile.Read(MagicDataS[i].デバフ種);

            magicFile.Read(MagicDataS[i].コスト, 6);
            magicFile.Read(MagicDataS[i].攻撃力, 6);
            magicFile.Read(MagicDataS[i].射程, 6);
            magicFile.Read(MagicDataS[i].連射, 6);

            magicFile.Read<int>(MagicDataS[i].弾速, 6 , 100);

            magicFile.Read<int>(MagicDataS[i].連射支援 , 6 , 100);
            magicFile.Read<int>(MagicDataS[i].射程支援 , 6 , 100);
            magicFile.Read<int>(MagicDataS[i].炸裂威力 , 6 , 100);

            magicFile.Read(MagicDataS[i].炸裂範囲,6);

            magicFile.Read(MagicDataS[i].デバフ効果,6);
            magicFile.Read<int>(MagicDataS[i].デバフ率 , 6 , 100);
            magicFile.Read(MagicDataS[i].Hit数, 6);
        }

    }

    void LoadEnemyS()
    {
        for (int a = 0; a < (int)EnemyType::MAX; ++a)
        {
            EnemyDataS[a].種族 = (EnemyType)a;
        }

        EnemyDataS[EnemyType::ゼリー    ].Set("", Belong::陸  , Elements::氷, 50, 50, 0.0, 1.0);
        EnemyDataS[EnemyType::ゴブリン  ].Set("", Belong::陸, Elements::樹, 50, 50, 0.0, 1.0);
        EnemyDataS[EnemyType::ケットシー].Set("", Belong::陸, Elements::空, 50, 50, 0.0, 1.0);
        EnemyDataS[EnemyType::オーガ    ].Set("", Belong::陸, Elements::炎, 50, 50, 0.0, 1.0);
        EnemyDataS[EnemyType::マーマン  ].Set("", Belong::水, Elements::氷, 50, 50, 0.0, 1.0);
        EnemyDataS[EnemyType::ゴーレム  ].Set("", Belong::陸, Elements::樹, 50, 50, 0.0, 1.0);
        EnemyDataS[EnemyType::ケルベロス].Set("", Belong::陸, Elements::炎, 50, 50, 0.0, 1.0);
        EnemyDataS[EnemyType::スケルトン].Set("", Belong::陸, Elements::氷, 50, 50, 0.0, 1.0);
        EnemyDataS[EnemyType::シャーマン].Set("", Belong::陸, Elements::炎, 50, 50, 0.0, 1.0);
        EnemyDataS[EnemyType::コボルド  ].Set("", Belong::陸, Elements::樹, 50, 50, 0.0, 1.0);
        EnemyDataS[EnemyType::ゼリー王  ].Set("", Belong::陸, Elements::氷, 50, 50, 0.0, 1.0);
        EnemyDataS[EnemyType::ドラゴン  ].Set("", Belong::陸, Elements::炎, 50, 50, 0.0, 1.0);
        EnemyDataS[EnemyType::インプ    ].Set("", Belong::空, Elements::空, 50, 50, 0.0, 1.0);
        EnemyDataS[EnemyType::ゴースト  ].Set("", Belong::空, Elements::氷, 50, 50, 0.0, 1.0);
        EnemyDataS[EnemyType::グリフィン].Set("", Belong::陸, Elements::空, 50, 50, 0.0, 1.0);
    }

    void LoadWitchS()
    {
        //ライナ

        WitchDataS[WitchType::ライナ].魔法タイプ[0] = MagicType::ライナ1;


    }

    void LoadStageS()
    {


    }

    void LoadDifficultyS()
    {
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