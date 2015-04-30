//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX
{
	using namespace SDX;

	class SceneStory : public SDX::IScene
	{
	public:
		//@Define
		UI_Text 実装中～ = { 106, {300,200,100,100} , 0.000000,1,"実装中"};
		//@End

		SceneStory()
		{
			LoadGUI();
			Init();
		}

		//初期化
		void Init() override
		{
			//@Init
			//@End
		}

		//終了時
		void Final() override
		{
			//@Final
			//@End
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
			//Draw
			MFont::fontS[実装中～.fontNo].DrawRotate(実装中～.rect.GetCenter(),1,0,Color::Black,実装中～.text);
			//End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneStory", GUI_Factory);

			実装中～ = *dynamic_cast<UI_Text*>(guiData.dataS[0].get());
			//@End
		}
	};
}
