//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
namespace SDX_TD
{
    using namespace SDX;

    static const int MAP_SIZE = 32;//マップの縦横タイル数
    static const int CHIP_SIZE = 16;//マップチップのドット数
    static const int 到達不可 = 99999999;
    static const int MAX_WAVE = 100;

    /**敵の移動タイプ.*/
    enum class MoveType
    {
        空,
        陸,
        水,
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
        森,//配置可能、通行不可
        山,//配置＆通行不可
        道,//配置不可、通行可
        畑,//防衛拠点
        穴,//敵が湧く
        //以下α版未実装
        高山,//飛行も通行不可能
        沼,//移動速度半減
        橋,//配置不可、通行可
        水,//一部敵のみ通行可
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
        ゴーレム,
        ケルベロス,
        スケルトン,
        シャーマン,
        ゼリー王,
        マーマン,
        インプ,
        トレント,//青ゴーレム
        グリフィン,
        ドラゴン,
        COUNT,
    };

    /**敵のサブ種族*/
    enum class SubEnemyType
    {
        竜,
        獣,
        亜人,
        闇,
        水棲,
        自然,
        COUNT
    };

    /**魔法の種類.*/
    /** ウィッチ12種 専用*/
    /** 汎用30種、一人11個選ぶので基本4回、12種余り*/
    enum class UnitType
    {
        ライナ,//勇者強化
        ナツメ,//武闘家強化
        ルコウ,//騎士強化型
        ディアネラ,//プリンセス強化
        ミナエ,//剣豪強化
        トレニア,//斧士強化
        ロチエ,//くノ一強化
        バロゥ,//賢者強化
        フィオナ,//司祭強化
        ナズナ,//支援効果 中 吹き飛ばし
        委員長,//僧侶強化 連射型範囲 麻痺100％
        ミルラ,//支援効果 大 麻痺付き

        兵士,//通路用A - 直進
        傭兵,//通路用A - 直進
        足軽,//通路用A - 直進

        技師,//必中追尾A - 完全追尾
        勇者,//必中追尾B

        剣士,//連射A - 直進
        剣豪,//連射B - 直進

        槍士,//反射A - 直進
        騎士,//反射B

        斧士,//吹き飛びA - 加速
        闘士,//吹き飛びB - 加速,長射程

        武闘家,//防御破壊A -直進
        師範,//防御破壊B 周りぐるぐる発射

        狩人,//対空特攻A - 直進
        射手,//対空専用B - 直進

        僧侶,//対地範囲A - 範囲
        司祭,//対地ビームB -範囲

        プリンス,//短ビームB -範囲
        プリンセス,//対空ビームB -範囲

        術士,//炸裂系範囲A -直進
        賢者,//炸裂系範囲B -方向転換型追尾

        踊り子,//支援A 弱麻痺 - 直進
        軍師,//支援B 弱吹飛 - 直進
        将軍,//支援B -直進

        執事,//使い捨てA -範囲円
        給仕,//使い捨てB -範囲十字
        料理人,//使い捨てB -範囲

        盗賊,//鈍足A -直進
        忍者,//鈍足A -直進
        くノ一,//鈍足B -直進

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
    namespace StageType
    {
        static std::vector<std::string> Free;
        static const std::string Quest[24] =
        {
            "map00.tmx",
            "map01.tmx",
            "map02.tmx",
            "map03.tmx",
            "map04.tmx",
            "map05.tmx",
            "map06.tmx",
            "map07.tmx",
            "map08.tmx",
            "map09.tmx",
            "map10.tmx",
            "map11.tmx",
            "map12.tmx",
            "map13.tmx",
            "map14.tmx",
            "map15.tmx",
            "map16.tmx",
            "map17.tmx",
            "map18.tmx",
            "map19.tmx",
            "map20.tmx",
            "map21.tmx",
            "map22.tmx",
            "map23.tmx"
        };
    }

    enum class RangeType
    {
        円,
        十字,
        COUNT
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

    namespace FontType
    {
        enum FontType
        {
            ゴシック小,
            ゴシック中,
            BMP黒,
            BMP黒影,
            BMP白
        };
    }

    enum class ResultType
    {
        Lose,
        Win,
        Perfect,
        COUNT
    };

    /**アーティファクトの種類.*/
    enum class ArtifactType
    {
        //神レア 1
        トルネルージュ,
        ジャガーノート,
        雪風＆空魂,
        皇剣シルヴァウス,
        カランコエ,
        フォトンルーメン,
        紅蜂,
        クレメンス,
        スヴァーズ,
        プリティワンド,
        チューベローズ,
        フィソステギア,
        //属性4つ×レア度3×ステータス14
        //神レア以外はユニークな名前が付く
        //レア 2、宝珠=レア、結晶=アンコ、欠片=コモン
        炎の宝珠,
        氷の宝珠,
        風の宝珠,
        樹の宝珠,
        炎の結晶,
        氷の結晶,
        風の結晶,
        樹の結晶,
        炎の欠片,
        氷の欠片,
        風の欠片,
        樹の欠片,
        //非装備、どこかのマスがこれになる、
        啓示の書,// 1％
        悟りの書,// 9％
        閃きの書,// 90％
        COUNT
    };

    enum class SkillType
    {
        攻撃,//合算=ナツメ/ライナ/トレニア
        連射,//合算=ディアネラ/バロゥ/ロチエ
        射程,//合算=ルコウ/ミナエ/フィオナ
        支援,//合算=ミルラ/ナズナ/委員長

        拡散,//トレニア
        麻痺,//ロチエ
        鈍足,//ロチエ
        吹飛,//ミナエ

        防壊,//ナツメ
        回収,//ディアネラ
        強化,//委員長
        逆境,//ライナ

        集中,//ディアネラ
        体力,//フィオナ
        魔力,//ナズナ
        必殺,//バロゥ

        対獣,//ナツメ
        対人,//バロゥ
        対水,//委員長
        対樹,//ミナエ

        対闇,//フィオナ
        対竜,//ルコウ
        幸運,//ナズナ
        試練,//ルコウ
        COUNT
    };

    /**工房の追加素材.*/
    /**とりあえず三種類のみ*/
    enum class DevelopType
    {
        啓示の書,//レア率上昇･大
        悟りの書,//レア率上昇･小
        閃きの書,//追加効果無し
        COUNT
    };
}