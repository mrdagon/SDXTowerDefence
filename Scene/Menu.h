//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Stage/Layer.h"
#include "Stage/Object.h"
#include "IMenu.h"

namespace SDX_TD
{
	using namespace SDX;

	/**動的な要素のあるメニュー用.*/
	class Menu : public IMenu
	{
	private:
		Layer<IObject> backEffectS;
		Layer<IObject> midEffectS;
		Layer<IObject> frontEffectS;
	public:
		/**毎フレーム実行される更新処理.*/
		void Update() final
		{
			SMenu = this;

			//レイヤー処理
			backEffectS.Update();
			midEffectS.Update();
			frontEffectS.Update();

			//消滅処理
			backEffectS.ExeRemove();
			midEffectS.ExeRemove();
			frontEffectS.ExeRemove();

			//サブ処理
			SubUpdate();
		}

		/**画面の描画.*/
		void Draw() final
		{
			SMenu = this;

			backEffectS.Draw();

			midEffectS.Draw();

			frontEffectS.Draw();

			//サブ描画
			SubDraw();
		}

		virtual void SubUpdate(){}
		virtual void SubDraw(){}

		/**エフェクト等を追加.*/
		void Add(IObject* 追加するオブジェクト, int 待機時間 = 0) override
		{
			midEffectS.Add(追加するオブジェクト, 待機時間);
		}
		/**前景オブジェクトを追加.*/
		void AddFront(IObject* 追加するオブジェクト, int 待機時間 = 0) override
		{
			frontEffectS.Add(追加するオブジェクト, 待機時間);
		}
		/**背景オブジェクトを追加.*/
		void AddBack(IObject* 追加するオブジェクト, int 待機時間 = 0) override
		{
			backEffectS.Add(追加するオブジェクト, 待機時間);
		}
	};
}