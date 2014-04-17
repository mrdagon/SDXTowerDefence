#pragma  once//☀Unicode
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
        その他
    };

    /**MagicとShotの魔法属性.*/
    enum class Elements
    {
        炎,
        氷,
        樹,
        空,
        無
    };

    enum class Difficulty
    {
        Normal,
        Hard,
        Maniac,
        Lunatic,
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
        畑//防衛拠点
    };


    /**敵の種族.*/
    enum class EnemyType
    {
        スライム,
        MAX,
    };

    /**魔法の種類.*/
    enum class MagicType
    {
        火炎,
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
        ミルラ
    };

}