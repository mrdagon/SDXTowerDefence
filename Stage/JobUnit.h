//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "IUnit.h"
#include "Design.h"

namespace SDX_TD
{
	using namespace SDX;

	/**ユニット一覧用 .*/
	class JobUnit : public IUnit
	{
	public:
		Rect shape;
		SpNull sprite;

		//配置位置
		JobUnit() :
			IUnit(shape, sprite, UnitType::ライナ , true , 0),
			shape({0,0,0,0})
		{}

		void Draw() const override
		{
			using namespace UI_Stage;

			Color color = Color::White;
			
			//選択中や残り0の時は表示色を変更
			if (SStage->selected == this){ color.SetColor(255, 120, 120); }
			if (Witch::配置回数[st->職種] <= 0){ color = Color::Gray; }
			MSystem::フレーム[3].Draw(shape , color);

			//ユニットアイコンと残り数の表示
			MUnit::魔女[st->職種][1]->DrawRotate(shape.GetPoint() + P差分[3], 1, 0);
			MFont::fontS[FontType::BMP黒].DrawExtend(shape.GetPoint() + P差分[4], 2, 2, Color::White, { std::setw(2), Witch::強化回数[st->職種] });
			MFont::fontS[FontType::BMP黒].Draw(shape.GetPoint() + P差分[5], Color::White, "×");
		}

		void SetType(UnitType 職種)
		{
			st = &UnitDataS[職種];
		}

	};

}