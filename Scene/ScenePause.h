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
		UI_Button あきらめる = { 79, {210,300,220,50} , 0.000000,3};
		UI_Button やり直す = { 80, {210,220,220,50} , 0.000000,3};
		UI_Button 続ける = { 81, {210,140,220,50} , 0.000000,3};
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
			if(あきらめる.isClick()){}
			if(やり直す.isClick()){}
			if(続ける.isClick()){}
			//@End
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			//@Draw
			MSystem::frameS[あきらめる.frameNo].Draw(あきらめる.rect);
			MSystem::frameS[やり直す.frameNo].Draw(やり直す.rect);
			MSystem::frameS[続ける.frameNo].Draw(続ける.rect);
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
