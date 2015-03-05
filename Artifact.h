//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "EnumType.h"
#include <tuple>
#include "TDSystem.h"

namespace SDX_TD
{
	//レシピの状態
	enum class RecipeState
	{
		不明,
		レア度識別,
		識別,
		開発済
	};

	enum class RecipeType
	{
		//強化
		攻撃,
		連射,
		射程,
		支援,
		麻痺,//準固有特性
		鈍足,//準固有特性
		吹飛,//準固有特性
		防壊,//準固有特性
		範囲,//レア特性
		回収,//レア特性
		強化,//レア特性
		特攻,//固有特性
		逆境,//固有特性
		消費,//固有特性
		Hp,//レア特性
		Mp,//レア特性
		Sp,//レア特性
		COUNT
	};

	class Recipe
	{


	};

	/**魔導具.*/
	class Artifact
	{
		EnumArray<int, RecipeType> 強化Lv;
	};
}