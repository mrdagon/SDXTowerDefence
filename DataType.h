#pragma once//☀Unicode
#include "EnumType.h"
#include "Material.h"

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
        EnemyType 種族;
        Belong 移動タイプ = Belong::陸;
        Elements 魔法属性;

        int スコア = 50;
        int 最大HP = 100;
        double 防御力 = 0;
        double 移動速度 = 1;

        //無効 or 有効
        bool 異状耐性[4];//各属性効果への耐性
    };

    /**ウィッチの基礎性能.*/
    struct WitchData
    {
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

        //ステージ開始時しか参照しないパラメータ
        int    初期HP = 20;
        int    初期MP = 50;

        //レベルで変化しないパラメータ
        int    大魔法時間 = 3000;
        double 必要SP = 100;
        double MP消費 = 1.0;

        MagicType 魔法タイプ[10];
        double 詠唱回数補正;

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
        ChipType  地形情報[28][28];
    };

    namespace
    {
        DataPack<EnemyData, EnemyType> EnemyDataS;
        DataPack<MagicData, MagicType> MagicDataS;
        DataPack<WitchData, WitchType> WitchDataS;
        DataPack<StageData, StageType> StageDataS;
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

    void LoadMagicData()
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

            LoatIntToDouble(magicFile, MagicDataS[i].弾速 );

            LoatIntToDouble(magicFile, MagicDataS[i].連射支援 );
            LoatIntToDouble(magicFile, MagicDataS[i].射程支援 );
            LoatIntToDouble(magicFile, MagicDataS[i].炸裂威力 );
            magicFile.Read(MagicDataS[i].炸裂範囲,6);

            magicFile.Read(MagicDataS[i].デバフ効果,6);
            LoatIntToDouble(magicFile, MagicDataS[i].デバフ率 );
            magicFile.Read(MagicDataS[i].Hit数, 6);
        }

    }

    void LoadEnemyData()
    {

    }

    void LoadWitchData()
    {

    }
}