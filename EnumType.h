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

    /**UnitとShotの魔法属性.*/
    enum class Elements
    {
        炎,
        氷,
        樹,
        空,
        無
    };

    /**.*/
    enum class ChipType
    {
        草,//通常地形
        氷,//移動速度2倍
        沼,//移動速度半減
        森,//配置可能、通行不可
        //ここより↓は配置不可能
        山,//配置＆通行不可
        高山,//空中も通行不可
        水,//一部敵のみ通行可
        穴,//敵が湧く
        畑//防衛拠点
    };

    /**.*/
    enum class EnemyType
    {
        スライム,
        None,
    };

    /**.*/
    enum class UnitType
    {
        火炎,
    };

    /**.*/
    enum class WitchType
    {
        スライム,
        None,
    };

}