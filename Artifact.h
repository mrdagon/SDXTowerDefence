//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "EnumType.h"

namespace SDX_TD
{
	class Artifact
	{
	public:
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
		double 回収;
		double 強化;
		double Sp;
		double 逆境;
		double 消費;
		double Hp;
		double Mp;

		//素材数に応じて能力を決定する関数
		//素材数に応じた結果予測を出す関数
		//とりあえず完全ランダムとかで仮実装

	};

}