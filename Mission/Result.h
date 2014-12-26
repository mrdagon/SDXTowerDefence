//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "Design.h"

namespace SDX_TD
{
	using namespace SDX;

	/** サブメニュー用オブジェクト、ミッション中にメニュー開いて一時停止.*/
	/** @todo 仮実装*/
	/** 位置情報はほぼ無駄*/
	class Result : public IScene
	{
	public:
		Result()
		{}

		void Update()
		{
			if (!Input::mouse.Left.on) { return; }

			const Point pt = Input::mouse.GetPoint();

		}

		void Draw()
		{
		}
	};
}