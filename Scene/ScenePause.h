//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX
{
	using namespace SDX;

	class ScenePause : public SDX::IScene
	{
	public:
		//@Define
		UI_Button あきらめる = { 79, {211,301,221,50} , 0.000000,int};
		UI_Button やり直す = { 80, {209,218,221,50} , 0.000000,int};
		UI_Button 続ける = { 81, {209,140,221,50} , 0.000000,int};
		//@End

		ScenePause()
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
			//@Draw
			frameS[あきらめる.frameNo]->Draw(あきらめる.rect);
			frameS[やり直す.frameNo]->Draw(やり直す.rect);
			frameS[続ける.frameNo]->Draw(続ける.rect);
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "ScenePause", GUI_Factory);

			あきらめる = *dynamic_cast<UI_Button*>(guiData.dataS[0].get());
			やり直す = *dynamic_cast<UI_Button*>(guiData.dataS[1].get());
			続ける = *dynamic_cast<UI_Button*>(guiData.dataS[2].get());
			//@End
		}
	};
}
