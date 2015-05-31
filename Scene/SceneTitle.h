//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX_TD
{
	using namespace SDX;

	class SceneTitle : public SDX::IScene
	{
	public:
		//@Define
		UI_Text 題字 = { 88, {159,134,356,78} , 0.000000,0,"ぐらちTD(仮)"};
		UI_Text 押して下さい = { 89, {291,316,77,39} , 0.000000,0,"push any key"};
		//@End

		SceneTitle()
		{
			LoadGUI();
			Init();
		}

		//更新
		void Update() override
		{
			//@Update
			//@End
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			//@Draw
			MFont::fontS[題字.fontNo].DrawRotate(題字.rect.GetCenter(),1,0,Color::White,題字.text);
			MFont::fontS[押して下さい.fontNo].DrawRotate(押して下さい.rect.GetCenter(),1,0,Color::White,押して下さい.text);
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneTitle", GUI_Factory);

			題字 = *dynamic_cast<UI_Text*>(guiData.dataS[0].get());
			押して下さい = *dynamic_cast<UI_Text*>(guiData.dataS[1].get());
			//@End
		}
	};
}
