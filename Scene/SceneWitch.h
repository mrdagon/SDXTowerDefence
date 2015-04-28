//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX
{
	using namespace SDX;

	class SceneWitch : public SDX::IScene
	{
	public:
		//@Define
		UI_Frame Frame = { 210, {170,60,360,360} , 0.000000,int};
		UI_Button 決定 = { 211, {195,80,140,40} , 0.000000,1};
		UI_Button 決定 = { 212, {270,360,160,40} , 0.000000,3};
		UI_Button 決定 = { 213, {195,124,140,40} , 0.000000,int};
		UI_Button 決定 = { 216, {195,212,140,40} , 0.000000,int};
		UI_Button 決定 = { 217, {195,168,140,40} , 0.000000,1};
		UI_Button 決定 = { 218, {195,300,140,40} , 0.000000,int};
		UI_Button 決定 = { 219, {195,256,140,40} , 0.000000,1};
		UI_Button 決定 = { 220, {366,124,140,40} , 0.000000,int};
		UI_Button 決定 = { 221, {366,168,140,40} , 0.000000,1};
		UI_Button 決定 = { 222, {366,300,140,40} , 0.000000,int};
		UI_Button 決定 = { 223, {366,212,140,40} , 0.000000,int};
		UI_Button 決定 = { 224, {366,256,140,40} , 0.000000,1};
		UI_Button 決定 = { 225, {367,80,140,40} , 0.000000,1};
		//@End

		SceneWitch()
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
			if(決定.isClick()){}
			if(決定.isClick()){}
			if(決定.isClick()){}
			if(決定.isClick()){}
			if(決定.isClick()){}
			if(決定.isClick()){}
			if(決定.isClick()){}
			if(決定.isClick()){}
			if(決定.isClick()){}
			if(決定.isClick()){}
			if(決定.isClick()){}
			if(決定.isClick()){}
			if(決定.isClick()){}
			//@End
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			//@Draw
			MSystem::frameS[Frame.frameNo].Draw(Frame.rect);
			MSystem::frameS[決定.frameNo].Draw(決定.rect);
			MSystem::frameS[決定.frameNo].Draw(決定.rect);
			MSystem::frameS[決定.frameNo].Draw(決定.rect);
			MSystem::frameS[決定.frameNo].Draw(決定.rect);
			MSystem::frameS[決定.frameNo].Draw(決定.rect);
			MSystem::frameS[決定.frameNo].Draw(決定.rect);
			MSystem::frameS[決定.frameNo].Draw(決定.rect);
			MSystem::frameS[決定.frameNo].Draw(決定.rect);
			MSystem::frameS[決定.frameNo].Draw(決定.rect);
			MSystem::frameS[決定.frameNo].Draw(決定.rect);
			MSystem::frameS[決定.frameNo].Draw(決定.rect);
			MSystem::frameS[決定.frameNo].Draw(決定.rect);
			MSystem::frameS[決定.frameNo].Draw(決定.rect);
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneWitch", GUI_Factory);

			Frame = *dynamic_cast<UI_Frame*>(guiData.dataS[0].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[1].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[2].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[3].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[4].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[5].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[6].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[7].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[8].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[9].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[10].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[11].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[12].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[13].get());
			//@End
		}
	};
}
