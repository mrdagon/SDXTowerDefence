#pragma once//☀Unicode
#include "EnumType.h"

namespace SDX_TD
{
    using namespace SDX;
    //パラメータ用のデータ型

    /**魔法の基礎性能.*/
    struct MagicData
    {
        static const int 最大レベル = 6;

        MagicType 魔法種;
        Elements 魔法属性;

        int コスト[最大レベル];
        int 攻撃力[最大レベル];
        int 速度[最大レベル];
        int 射程[最大レベル];
        double 支援範囲[最大レベル];
        double 支援効果[最大レベル];

        double 炸裂範囲[最大レベル];
        double 炸裂威力[最大レベル];

        int 属性効果[最大レベル];
        double 発動率[最大レベル];

        double 半径 = 10;//当たり判定の大きさ

        bool is対空 = true;//空の敵に当たるかどうか
        bool is対地 = true;//地上の敵に当たるかどうか

        bool is貫通 = true;//命中時に消滅するかどうか

        bool is防御低下 = false;//防御低下効果の有無

        bool is使い捨て = false;

        bool isウィッチ = false;//指揮官魔法、詠唱回数の管理が違う

        int  錬魔回数 = 1;//素材による強化回数
    };

    /**敵の基礎性能.*/
    struct EnemyData
    {
        //基礎ステータス
        EnemyType 種族;
        Belong 移動タイプ = Belong::陸;
        Elements 魔法属性;

        int スコア = 50;
        int 体力 = 100;
        double 防御力 = 0;
        double 移動速度 = 1;

        //高い程ききやすい 0_無効 1_通常 2_倍
        double 突風耐性;//吹き飛び量
        double 麻痺耐性;//移動速度低下率増加
        double 冷凍耐性;//移動不可能時間
        double 火傷耐性;//炎上時間
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
        
        int    大魔法時間 = 3000;
        double 必要SP = 100;

        int    初期HP = 20;
        int    初期MP = 50;
        double MP消費 = 1.0;
        double 弱点補正 = 1.1;
        double 状態強化[4];
        double 属性強化[4];

        MagicType 魔法タイプ[10];
        int    初期詠唱回数[10];

        int    スキルレベル[10];
        int    レベル;
        int    経験値;
    };

    struct StageData
    {
        std::string 名前;
        std::string 説明;

        int シングルのハイスコア[(int)WitchType::MAX];

        int タッグのハイスコア[3];        
        std::tuple<WitchType,WitchType> タッグの組み合わせ[3];

        Difficulty シングルの難易度[(int)WitchType::MAX];
        Difficulty タッグの難易度[3];

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

    void LoadMagicData()
    {

    }

    void LoadEnemyData()
    {

    }

    void LoadWitchData()
    {

    }
}