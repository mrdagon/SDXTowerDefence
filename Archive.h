//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Menu.h"

namespace SDX_TD
{
	using namespace SDX;

	//実績一覧
	class ArchiveMenu : public IScene
	{
	public:
		ArchiveMenu()
		{
		}

		void Update() override
		{
			namespace UI = UI_Archive;

		}

		void Draw() override
		{
			namespace UI = UI_Archive;
		}

	};
}