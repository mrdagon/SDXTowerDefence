#pragma once//☀Unicode
#include "EnumType.h"
#include "Material.h"
#include "RouteMap.h"

namespace SDX_TD
{
    using namespace SDX;
    //パラメータ用のデータ型

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

            状態強化[0] = 1.0;
            状態強化[0] = 1.0;
            状態強化[0] = 1.0;
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
        ChipType  地形情報[Land::MapSize][Land::MapSize];
    };

    struct DifficultyData
    {
        int Wave数;
        double レベル補正;
        double HP補正;
        int 雑魚召喚数;
        int ボス召喚数;

        void SetData(int Wave数, int 雑魚召喚数, int ボス召喚数, double HP補正, double レベル補正)
        {
            this->Wave数 = Wave数;
            this->雑魚召喚数 = 雑魚召喚数;
            this->ボス召喚数 = ボス召喚数;
            this->HP補正 = HP補正;
            this->レベル補正 = レベル補正;
        }
    };

    namespace
    {
        DataPack<EnemyData, EnemyType> EnemyS;
        DataPack<MagicData, MagicType> MagicS;
        DataPack<WitchData, WitchType> WitchS;
        DataPack<StageData, StageType> StageS;
        DataPack<DifficultyData, Difficulty> TrialS;
        DataPack<DifficultyData, Difficulty> PowerS;
    }

    void LoatIntToDouble(File& 読み込むファイル, double 読み込み先[] , int 分母 = 100)
    {
        int paramS[6];
        読み込むファイル.Read(paramS, 6);

        for (int i = 0; i < 6; ++i)
        {
            読み込み先[i] = double(paramS[i]) / 分母;
        }
    }

    void LoadMagicS()
    {
        File magicFile("data.txt", FileMode::Read, true);

        for (int i = 0; i<(int)MagicType::MAX; ++i)
        {
            magicFile.Read(MagicS[i].名前);
            magicFile.Read(MagicS[i].説明文);

            magicFile.Read(MagicS[i].魔法属性);
            magicFile.Read(MagicS[i].射程種);

            int param;
            magicFile.Read(param);
            if (param % 3 == 1) MagicS[i].is対空 = false;
            if (param % 3 == 2) MagicS[i].is対地 = false;
            if (param % 3 >= 3) MagicS[i].is貫通 = true;
            if (param == 6) MagicS[i].is支援 = true;
            if (param == 7) MagicS[i].is使い捨て = true;

            magicFile.Read(MagicS[i].基礎詠唱回数);
            magicFile.Read(MagicS[i].デバフ種);

            magicFile.Read(MagicS[i].コスト, 6);
            magicFile.Read(MagicS[i].攻撃力, 6);
            magicFile.Read(MagicS[i].射程, 6);
            magicFile.Read(MagicS[i].連射, 6);

            LoatIntToDouble(magicFile, MagicS[i].弾速 );

            LoatIntToDouble(magicFile, MagicS[i].連射支援 );
            LoatIntToDouble(magicFile, MagicS[i].射程支援 );
            LoatIntToDouble(magicFile, MagicS[i].炸裂威力 );
            magicFile.Read(MagicS[i].炸裂範囲,6);

            magicFile.Read(MagicS[i].デバフ効果,6);
            LoatIntToDouble(magicFile, MagicS[i].デバフ率 );
            magicFile.Read(MagicS[i].Hit数, 6);
        }

    }

    void SetEnemyData(EnemyType 種族, const char* 種族名 ,Belong 移動タイプ, Elements 魔法属性, int スコア, int 最大HP, double 防御力, double 移動速度, std::vector<bool> 異状耐性 = { false, false, false, false })
    {
        EnemyS[種族].種族 = 種族;
        EnemyS[種族].種族名 = 種族名;
        EnemyS[種族].移動タイプ = 移動タイプ;
        EnemyS[種族].魔法属性 = 魔法属性;
        EnemyS[種族].スコア = スコア;
        EnemyS[種族].最大HP = 最大HP;
        EnemyS[種族].防御力 = 防御力;
        EnemyS[種族].移動速度 = 移動速度;
        EnemyS[種族].異状耐性[0] = 異状耐性[0];
        EnemyS[種族].異状耐性[1] = 異状耐性[1];
        EnemyS[種族].異状耐性[2] = 異状耐性[2];
        EnemyS[種族].異状耐性[3] = 異状耐性[3];
    }

    void LoadEnemyS()
    {
        for (int a = 0; a < (int)EnemyType::MAX; ++a)
        {
            EnemyS[a].種族 = (EnemyType)a;
        }

        EnemyS[EnemyType::ゼリー    ].Set("", Belong::陸  , Elements::氷, 50, 50, 0.0, 1.0);
        EnemyS[EnemyType::ゴブリン  ].Set("", Belong::陸, Elements::樹, 50, 50, 0.0, 1.0);
        EnemyS[EnemyType::ケットシー].Set("", Belong::陸, Elements::空, 50, 50, 0.0, 1.0);
        EnemyS[EnemyType::オーガ    ].Set("", Belong::陸, Elements::炎, 50, 50, 0.0, 1.0);
        EnemyS[EnemyType::マーマン  ].Set("", Belong::水陸, Elements::氷, 50, 50, 0.0, 1.0);
        EnemyS[EnemyType::ゴーレム  ].Set("", Belong::陸, Elements::樹, 50, 50, 0.0, 1.0);
        EnemyS[EnemyType::ケルベロス].Set("", Belong::陸, Elements::炎, 50, 50, 0.0, 1.0);
        EnemyS[EnemyType::スケルトン].Set("", Belong::陸, Elements::氷, 50, 50, 0.0, 1.0);
        EnemyS[EnemyType::シャーマン].Set("", Belong::陸, Elements::炎, 50, 50, 0.0, 1.0);
        EnemyS[EnemyType::コボルド  ].Set("", Belong::陸, Elements::樹, 50, 50, 0.0, 1.0);
        EnemyS[EnemyType::ゼリー王  ].Set("", Belong::陸, Elements::氷, 50, 50, 0.0, 1.0);
        EnemyS[EnemyType::ドラゴン  ].Set("", Belong::陸, Elements::炎, 50, 50, 0.0, 1.0);
        EnemyS[EnemyType::インプ    ].Set("", Belong::空, Elements::空, 50, 50, 0.0, 1.0);
        EnemyS[EnemyType::ゴースト  ].Set("", Belong::空, Elements::氷, 50, 50, 0.0, 1.0);
        EnemyS[EnemyType::グリフィン].Set("", Belong::陸, Elements::空, 50, 50, 0.0, 1.0);
    }

    void LoadWitchS()
    {
        //ライナ

        WitchS[WitchType::ライナ].魔法タイプ[0] = MagicType::ライナ1;


    }

    void LoadStageS()
    {


    }

    void LoadDifficultyS()
    {
        TrialS[Difficulty::Easy      ].SetData( 20, 16 , 2, 1.00 , 1.00 );
        TrialS[Difficulty::Normal    ].SetData( 30, 20 , 2, 1.25 , 1.10 );
        TrialS[Difficulty::Hard      ].SetData( 40, 24 , 2, 1.50 , 1.20 );
        TrialS[Difficulty::Maniac    ].SetData( 60, 28 , 2, 1.75 , 1.30 );
        TrialS[Difficulty::Hell      ].SetData( 80, 32 , 2, 2.00 , 1.40 );
        TrialS[Difficulty::DeathMarch].SetData(100, 44 , 2, 2.50 , 1.50 );

        PowerS[Difficulty::Easy      ].SetData(  25, 24, 3, 1.00, 1.00);
        PowerS[Difficulty::Normal    ].SetData(  50, 24, 3, 1.30, 1.20);
        PowerS[Difficulty::Hard      ].SetData(  75, 24, 3, 1.60, 1.40);
        PowerS[Difficulty::Maniac    ].SetData( 100, 32, 4, 2.00, 1.60);
        PowerS[Difficulty::Hell      ].SetData( 300, 32, 4, 3.00, 1.80);
        PowerS[Difficulty::DeathMarch].SetData(1000, 40, 5, 5.00, 2.00);
    }
}