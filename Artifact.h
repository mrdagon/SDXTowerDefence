//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "EnumType.h"
#include <tuple>

namespace SDX_TD
{
	class Recipe
	{
	public:
		Element 主属性;
		int レア度;
		double 基礎確率;
		double 確率;
	};

	//神 1
	//レア 4
	//アンコ 12
	//コモン 48
	//ぐらいの出現率
	//サブ効果、基本発生率
	//素材投入量が増えると増加する
	//神     100%
	//レア   50%
	//アンコ 25%
	//コモン 12.5%
	class Artifact
	{
	public:
		//レシピはわりと単純
		//主属性率が50%以上だと確率が上がる
		//反属性率が25%以上だと確率が下がる
		static EnumArray<Recipe, ArtifactType> レシピ;

		ArtifactType 種類;
		int	コスト;
		double 攻撃;
		double 連射;
		double 射程;
		double 範囲;
		double 支援;
		double 麻痺;
		double 鈍足;
		double 吹飛;
		double 防壊;
		double 経験;
		double 素材;
		double 回収;//回収速度と回収率+
		double 強化;//強化回数と強化速度+
		double 逆境;
		double 消費;
		int Hp;
		int Mp;
		double Sp;

		//作成結果の予測を出す
		//初期の100×4だとLv3
		//10000×4だとLv201
		int 予測(int 火, int 氷, int 空, int 樹, CraftType オプション素材)
		{
			return int(火 + 氷 + 空 + 樹) / 200 + 1;
		}

		/**.*/
		bool 種類判定( int 火, int 氷, int 空, int 樹, CraftType オプション素材)
		{
			double 合計 = (火 + 氷 + 空 + 樹);
			EnumArray<double, Element> 占有率;
			占有率[Element::炎] = 火 / 合計;
			占有率[Element::氷] = 氷 / 合計;
			占有率[Element::空] = 空 / 合計;
			占有率[Element::樹] = 樹 / 合計;
			占有率[Element::無] = 0;

			for (int a = 0; a < (int)ArtifactType::COUNT; ++a)
			{
				ArtifactType type = ArtifactType(a);

				if (占有率[レシピ[type].主属性] >= 0.5  ) レシピ[type].確率 = 3;
				else if (占有率[レシピ[type].主属性] > 0) レシピ[type].確率 = 1;
				else レシピ[type].確率 = 0;

				if (占有率[レシピ[type].反属性] >= 0.25) レシピ[type].確率 /= 3;
			}
		}

		/**副効果.*/
		bool 能力判定(int 火, int 氷, int 空, int 樹, CraftType オプション素材)
		{

		}

		/**乱数で初期化.*/
		/**OSやVer違いで結果が変わるのは微妙っぽい？*/
		static void 出現率計算()
		{
			//SetRecipe(ArtifactType::カランコエ, Element::炎, Element::空);
		}

		static void SetRecipe(ArtifactType 種類, Element 主属性, Element 反属性)
		{

		}

	};

	EnumArray<Recipe, ArtifactType> Artifact::レシピ;
}