﻿#pragma  once//☀Unicode
namespace SDX_TD
{
    using namespace SDX;

    /**所属するレイヤーの識別子.*/
    enum class Belong
    {
        空,
        陸,
        水陸,
        水中,
        弾,
        砲台,
        その他,
        MAX
    };

    /**MagicとShotの魔法属性.*/
    enum class Elements
    {
        炎,
        氷,
        樹,
        空,
        無,
        MAX
    };

    /**難易度の種類.*/
    enum class Difficulty
    {
        Easy,
        Normal,
        Hard,
        Maniac,
        Hell,
        DeathMarch,
        MAX
    };

    /**地形の種類.*/
    enum class ChipType
    {
        草,//通常地形
        沼,//移動速度半減
        森,//配置可能、通行不可
        道,//配置不可、通行可
        橋,//配置不可、通行可//水
        ↑,//ベルトコンベア四種
        ↓,
        ←,
        →,
        山,//配置＆通行不可
        高山,//飛行も通行不可能
        水,//一部敵のみ通行可
        穴,//敵が湧く
        畑,//防衛拠点
        MAX
    };

    /**敵の種族.*/
    enum class EnemyType
    {
        ゼリー,
        ゴブリン,
        ケットシー,
        オーガ,
        マーマン,
        ゴーレム,
        ケルベロス,
        スケルトン,
        シャーマン,
        コボルド,
        ゼリーキング,
        ドラゴン,
        インプ,
        ゴースト,
        グリフィン,
        MAX,
    };

    /**魔法の種類.*/
    enum class MagicType
    {
        炎基礎1,
        炎基礎2,
        炎基礎3,
        炎基礎4,
        炎基礎5,
        氷基礎1,
        氷基礎2,
        氷基礎3,
        氷基礎4,
        氷基礎5,
        樹基礎1,
        樹基礎2,
        樹基礎3,
        樹基礎4,
        樹基礎5,
        空基礎1,
        空基礎2,
        空基礎3,
        空基礎4,
        空基礎5,
        ライナ1,
        ライナ2,
        ライナ3,
        ライナ4,
        ライナ5,
        ナツメ1,
        ナツメ2,
        ナツメ3,
        ナツメ4,
        ナツメ5,
        ルコウ1,
        ルコウ2,
        ルコウ3,
        ルコウ4,
        ルコウ5,
        ディアネラ1,
        ディアネラ2,
        ディアネラ3,
        ディアネラ4,
        ディアネラ5,
        ミナエ1,
        ミナエ2,
        ミナエ3,
        ミナエ4,
        ミナエ5,
        トレニア1,
        トレニア2,
        トレニア3,
        トレニア4,
        トレニア5,
        ロチエ1,
        ロチエ2,
        ロチエ3,
        ロチエ4,
        ロチエ5,
        バロゥ1,
        バロゥ2,
        バロゥ3,
        バロゥ4,
        バロゥ5,
        フィオナ1,
        フィオナ2,
        フィオナ3,
        フィオナ4,
        フィオナ5,
        ナズナ1,
        ナズナ2,
        ナズナ3,
        ナズナ4,
        ナズナ5,
        委員長1,
        委員長2,
        委員長3,
        委員長4,
        委員長5,
        ミルラ1,
        ミルラ2,
        ミルラ3,
        ミルラ4,
        ミルラ5,
        MAX,
    };

    /**ウィッチの種類.*/
    enum class WitchType
    {
        ライナ,
        ナツメ,
        ルコウ,
        ディアネラ,
        ミナエ,
        トレニア,
        ロチエ,
        バロゥ,
        フィオナ,
        ナズナ,
        委員長,
        ミルラ,
        MAX
    };

    /**ステージの種類.*/
    enum class StageType
    {
        一面,
        MAX
    };

    enum class RangeType
    {
        円,
        四角,
        十字細,
        十字太
    };

    enum class DebuffType
    {
        痺れ,
        眠り,
        吹飛,
        防壊,
        無
    };

}