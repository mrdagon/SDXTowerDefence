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
	static const double 自動床速度 = 0.5;
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
		橋,//配置不可、通行可//水
		↑,//ベルトコンベア四種
		↓,
		←,
		→,
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
		ロボット,//青ゴーレム
		グリフィン,
		ドラゴン,
		COUNT,
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
	enum class StageType
	{
		一面,
		COUNT
	};

	enum class RangeType
	{
		円,
		十字
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