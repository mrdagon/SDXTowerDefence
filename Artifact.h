//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "EnumType.h"
#include <tuple>
#include "TDSystem.h"

//このソースコードは使用していない
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

	class Artifact
	{
	public:
		static Artifact 所持S[200];
		static Artifact レシピS[100];
		static EnumArray<double, ArtifactType> 基本出現率;

		ArtifactType 種類;
		RecipeState 状態;
		int Lv;
		bool is祝福;//副効果の有無
		double 攻撃;
		double 連射;
		double 射程;
		double 範囲;
		double 支援;
		double 麻痺;
		double 鈍足;
		double 吹飛;
		double 防壊;
		double 回収;
		double 強化;
		double 逆境;
		double 消費;
		int Hp;
		int Mp;
		double Sp;

		static void MakeRecipe(DevelopType 開発種)
		{
			//性能の決定
			for (int a = 0; a < 100; ++a)
			{
				double 補正 = std::abs(a / 10 - 4.5) + std::abs(a%10 - 4.5);
				//補正値は0～8
				//中央から離れる程レベルに補正が入る？
				レシピS[a].性能決定(開発種 , (int)補正 - 1);
				レシピS[a].状態 = RecipeState::不明;
			}

			レシピS[44].状態 = RecipeState::識別;
			レシピS[45].状態 = RecipeState::識別;
			レシピS[54].状態 = RecipeState::識別;
			レシピS[55].状態 = RecipeState::識別;
		}

		/**レシピの更新処理から呼び出す.*/
		/** レア率等は暫定*/
		void 性能決定(DevelopType 開発種, int レベル補正)
		{
			//レベルの決定
			Lv = std::min( TDSystem::工房レベル + Rand::Get(レベル補正) , 9999 );
			int レア度 = レア度決定(開発種);
			種類決定(レア度);
			//性能はレベル+9に比例
			double pt = (Lv + 9) / 2;

			switch (種類)
			{
				//神レア、コモンの3倍の性能
				case ArtifactType::トルネルージュ:
					break;
				case ArtifactType::ジャガーノート:
					break;
				case ArtifactType::雪風＆空魂:
					break;
				case ArtifactType::皇剣シルヴァウス:
					break;
				case ArtifactType::カランコエ:
					break;
				case ArtifactType::フォトンルーメン:
					break;
				case ArtifactType::紅蜂:
					break;
				case ArtifactType::クレメンス:
					break;
				case ArtifactType::スヴァーズ:
					break;
				case ArtifactType::プリティワンド:
					break;
				case ArtifactType::チューベローズ:
					break;
				case ArtifactType::フィソステギア:
					break;
				case ArtifactType::炎の宝珠:
					break;
				case ArtifactType::氷の宝珠:
					break;
				case ArtifactType::風の宝珠:
					break;
				case ArtifactType::樹の宝珠:
					break;
				case ArtifactType::炎の結晶:
					break;
				case ArtifactType::氷の結晶:
					break;
				case ArtifactType::風の結晶:
					break;
				case ArtifactType::樹の結晶:
					break;
				case ArtifactType::炎の欠片:
					break;
				case ArtifactType::氷の欠片:
					break;
				case ArtifactType::風の欠片:
					break;
				case ArtifactType::樹の欠片:
					break;
			}
		}

		int レア度決定(DevelopType 開発種)
		{
			double ram = Rand::Get(1.0);
			//種類の決定
			switch (開発種)
			{
			case DevelopType::啓示の書:
				is祝福 = Rand::Coin(0.3);
				if (ram < 1.0 / 50) return 3;
				else if (ram < 1.0 / 5) return 2;
				else if (ram < 1.0 / 2) return 1;
				else return 0;
				break;
			case DevelopType::悟りの書:
				is祝福 = Rand::Coin(0.1);
				if (ram < 1.0 / 200) return 3;
				else if (ram < 1.0 / 20) return 2;
				else if (ram < 1.0 / 5) return 1;
				else return 0;
				break;
			case DevelopType::閃きの書:
				is祝福 = Rand::Coin(0.05);
				if (ram < 1.0 / 1000) return 3;
				else if (ram < 1.0 / 100) return 2;
				else if (ram < 1.0 / 10) return 1;
				else return 0;
			default:
				break;
			}
			return 0;
		}

		void 種類決定(int レア度)
		{
			int no;

			switch (レア度)
			{
			case 0:
				no = Rand::Get(11);
				種類 = ArtifactType(no);
				break;
			case 1:
				no = Rand::Get(3);
				種類 = ArtifactType((int)ArtifactType::炎の宝珠 + no);
				break;
			case 2:
				no = Rand::Get(3);
				種類 = ArtifactType((int)ArtifactType::炎の結晶 + no);
				break;
			case 3:
				no = Rand::Get(3);
				種類 = ArtifactType((int)ArtifactType::炎の欠片 + no);
				break;
			}
		}
	};

	Artifact Artifact::所持S[200];
	Artifact Artifact::レシピS[100];
}