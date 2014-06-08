#pragma  once//☀Unicode
namespace SDX_TD
{
    using namespace SDX;

    /**所属するレイヤーの識別子.*/
    enum class Belong
    {
        空,
        陸,
        水,
        弾,
        砲台,
        その他,
        MAX
    };

    /**UnitとShotの魔法属性.*/
    enum class Element
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
        ゼリー王,
        ドラゴン,
        インプ,
        ゴースト,
        グリフィン,
        畑荒らし,
        MAX,
    };

    /**魔法の種類.*/
    enum class UnitType
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

        兵士,
        踊り子,
        弓使い,
        執事,
        技師,
        くノ一,
        師範,
        魔法使い,
        賢者,
        武闘家,
        忍者,
        剣豪,
        呪術師,
        勇者,
        詩人,
        風水師,
        騎士,
        司祭,
        僧侶,
        闘士,
        斧士,
        傭兵,
        プリンス,
        プリンセス,
        剣士,
        槍士,
        給仕,
        槍使い,
        将軍,
        軍師,
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
        鈍足,
        麻痺,
        吹飛,
        防壊,
        無,
        MAX
    };

    enum class IconType
    {
        ライフ,
        マナ,
        レベル,
        攻撃,
        連射,
        支援,
        鈍足,
        麻痺,
        強化,
        吹飛,
        防壊,
        速度,
        回避,
        防御,
        回復,
        MAX       
    };
}