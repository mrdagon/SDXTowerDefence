//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3
#pragma once
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
        COUNT
    };

    /**UnitとShotの魔法属性.*/
    enum class Element
    {
        炎,
        氷,
        樹,
        空,
        無,
        COUNT
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
        COUNT
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
        COUNT
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
    	COUNT,
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

        兵士,//通路用A
        傭兵,//通路用A
        足軽,//通路用A

        技師,//必中追尾A
        勇者,//必中追尾B

        剣士,//連射A
        剣豪,//連射B

        槍士,//反射A
        騎士,//反射B

        斧士,//吹き飛びA
        闘士,//吹き飛びB

        武闘家,//防御破壊A
        師範,//防御破壊B

        狩人,//対空特攻A
        射手,//対空専用B

        僧侶,//対地範囲A
        司祭,//対地ビームB

        プリンス,//十字対地範囲B
        プリンセス,//十字対空ビームB

        魔術師,//範囲A
        賢者,//範囲B

        踊り子,//支援A
        軍師,//支援B
        将軍,//支援B

	    執事,//使い捨てA
        給仕,//使い捨てB
        料理人,//使い捨てB

        盗賊,//鈍足A
        忍者,//鈍足A
        くノ一,//鈍足B
        
        COUNT,
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
        COUNT
    };

    /**ステージの種類.*/
    enum class StageType
    {
        一面,
        COUNT
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
        COUNT
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
        COUNT       
    };
}