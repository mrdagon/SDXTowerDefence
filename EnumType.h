#pragma  once//☀Unicode
namespace SDX
{
    /**所属するレイヤーの識別子.*/
    enum class Belong
    {
        Sky,
        Ground,
        Sea,
        Marin,
        Shot,
        Unit,
        Etc
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
        井戸,//敵が湧く
        塔//防衛拠点
    };

    /**.*/
    enum class MoveType
    {
        陸,
        空,
        水陸,
        水中
    };

}