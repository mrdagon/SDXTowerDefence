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
        コボルド,
        マーマン,
        ゴーレム,
        ケルベロス,
        スケルトン,
        シャーマン,
        ゼリー王,
        インプ,
        ゴースト,
        グリフィン,
        ドラゴン,
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

        兵士,//通路用
        傭兵,
        足軽,

        勇者,
        プリンス,

        剣士,
        剣豪,
        師範,

        槍士,
        騎士,

        斧士,
        闘士,
        武闘家,

        弓使い,
        射手,
        技師,

        僧侶,
        司祭,
        プリンセス,

        魔法使い,
        賢者,
        風水師,

        踊り子,//支援系
        軍師,
        将軍,

	執事,//使い捨て
        給仕,

        忍者,	//鈍足
        くノ一,
        呪術師,
        
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