//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "EnumType.h"
#include <tuple>

namespace SDX_TD
{
	class Artifact
	{
	public:
		static Artifact recipeS[10][10];
		static int		openS[10][10];//レシピの状態,-1 不明, 0見える,1 解放済

		ArtifactType 種類;
		double 攻撃;
		double 連射;
		double 射程;
		double 範囲;
		double 支援;
		double 麻痺;
		double 鈍足;
		double 吹飛;
		double 防壊;
		double 回収;//回収速度と回収率+
		double 強化;//強化回数と強化速度+
		double 逆境;
		double 消費;
		int Hp;
		int Mp;
		double Sp;

		static void MakeRecipe(RecipeType レシピ種)
		{


		}
	};

	Artifact Artifact::recipeS[10][10];

}