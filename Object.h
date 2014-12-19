//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include <SDXFramework.h>
#include "RouteMap.h"
#include "EnumType.h"

namespace SDX_TD
{
	using namespace SDX;
	/**.*/
	class IObject : public IModel
	{
	protected:
		int timer = 0;///発生してから経過したフレーム数
		int lifeTime = -1;///生存期間
		Belong belong;///所属するレイヤー
	public:
		bool isSelect = false;

		/**.*/
		IObject(IShape &図形, ISprite &描画方法, Belong 所属 = Belong::その他) :
			IModel(図形, 描画方法),
			belong(所属)
		{
		}

		/**.*/
		virtual ~IObject(){}

		/**消滅判定を行い、消滅している場合消滅処理を行う.*/
		virtual bool RemoveCheck()
		{
			if (timer == lifeTime)
			{
				isRemove = true;
			}

			if (isRemove) Remove();

			return isRemove;
		}

		/**経過フレームを取得.*/
		int GetTimer()
		{
			return timer;
		}

		/**経過フレームをセット.*/
		void SetTimer(int フレーム数)
		{
			timer = フレーム数;
		}

		/**毎フレームの更新処理.*/
		virtual void Update()
		{
			timer++;
			iSprite.Update();
			Act();
		}

		/**.*/
		Belong GetBelong()
		{
			return belong;
		}

		/**Stage右枠のの説明を表示.*/
		virtual void DrawInfo(){}

		/**Update時の追加処理.*/
		virtual void Act(){}

		/**消滅時の追加処理.*/
		virtual void Remove(){}

		/**ダメージ処理.*/
		virtual void Damaged(IObject* 衝突相手){}
	};

	template <class TShape, class TSprite>
	class Object : public IObject
	{
	public:
		TShape shape;
		TSprite sprite;

		Object(TShape &&図形と位置, TSprite &&描画方法, Belong 所属) :
			IObject(shape, sprite, 所属),
			shape(図形と位置),
			sprite(描画方法)
		{}
	};
}
