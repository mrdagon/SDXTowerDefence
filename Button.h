//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "IStage.h"
#include <functional>

namespace SDX_TD
{
	using namespace SDX;

	/*
	class Button : public Object
	{
	private:
	std::function<void()> 押下時の処理 = nullptr;
	public:
	void PushCheck()
	{
	if ( Hit(&Point(Input::mouse.x, Input::mouse.y)) )
	{
	SStage->selected = this;
	if (押下時の処理 != nullptr) 押下時の処理();
	Pushed();
	}
	}

	virtual void Pushed(){}
	};
	*/
}