//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX_TD
{
	using namespace SDX;

	class SceneWitch : public SDX::IScene
	{
	public:
		//@Define
		UI_Frame 全体枠 = { 210, {170,60,360,360} , 0.000000,5};
		UI_Button ライナ = { 211, {195,83,140,40} , 0.000000,1};
		UI_Button 決定 = { 212, {270,363,160,40} , 0.000000,3};
		UI_Button ルコウ = { 213, {195,127,140,40} , 0.000000,1};
		UI_Button ロチエ = { 216, {195,215,140,40} , 0.000000,1};
		UI_Button ミナエ = { 217, {195,171,140,40} , 0.000000,1};
		UI_Button 委員長 = { 218, {195,303,140,40} , 0.000000,1};
		UI_Button フィオナ = { 219, {195,259,140,40} , 0.000000,1};
		UI_Button ディアネラ = { 220, {366,127,140,40} , 0.000000,1};
		UI_Button トレニア = { 221, {366,171,140,40} , 0.000000,1};
		UI_Button ミルラ = { 222, {366,303,140,40} , 0.000000,1};
		UI_Button バロゥ = { 223, {366,215,140,40} , 0.000000,1};
		UI_Button ナズナ = { 224, {366,259,140,40} , 0.000000,1};
		UI_Button ナツメ = { 225, {367,83,140,40} , 0.000000,1};
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
			if(ライナ.isClick()){}
			if(決定.isClick()){}
			if(ルコウ.isClick()){}
			if(ロチエ.isClick()){}
			if(ミナエ.isClick()){}
			if(委員長.isClick()){}
			if(フィオナ.isClick()){}
			if(ディアネラ.isClick()){}
			if(トレニア.isClick()){}
			if(ミルラ.isClick()){}
			if(バロゥ.isClick()){}
			if(ナズナ.isClick()){}
			if(ナツメ.isClick()){}
			//@End
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			//@Draw
			MSystem::frameS[全体枠.frameNo].Draw(全体枠.rect);
			MSystem::frameS[ライナ.frameNo].Draw(ライナ.rect);
			MSystem::frameS[決定.frameNo].Draw(決定.rect);
			MSystem::frameS[ルコウ.frameNo].Draw(ルコウ.rect);
			MSystem::frameS[ロチエ.frameNo].Draw(ロチエ.rect);
			MSystem::frameS[ミナエ.frameNo].Draw(ミナエ.rect);
			MSystem::frameS[委員長.frameNo].Draw(委員長.rect);
			MSystem::frameS[フィオナ.frameNo].Draw(フィオナ.rect);
			MSystem::frameS[ディアネラ.frameNo].Draw(ディアネラ.rect);
			MSystem::frameS[トレニア.frameNo].Draw(トレニア.rect);
			MSystem::frameS[ミルラ.frameNo].Draw(ミルラ.rect);
			MSystem::frameS[バロゥ.frameNo].Draw(バロゥ.rect);
			MSystem::frameS[ナズナ.frameNo].Draw(ナズナ.rect);
			MSystem::frameS[ナツメ.frameNo].Draw(ナツメ.rect);
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneWitch", GUI_Factory);

			全体枠 = *dynamic_cast<UI_Frame*>(guiData.dataS[0].get());
			ライナ = *dynamic_cast<UI_Button*>(guiData.dataS[1].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[2].get());
			ルコウ = *dynamic_cast<UI_Button*>(guiData.dataS[3].get());
			ロチエ = *dynamic_cast<UI_Button*>(guiData.dataS[4].get());
			ミナエ = *dynamic_cast<UI_Button*>(guiData.dataS[5].get());
			委員長 = *dynamic_cast<UI_Button*>(guiData.dataS[6].get());
			フィオナ = *dynamic_cast<UI_Button*>(guiData.dataS[7].get());
			ディアネラ = *dynamic_cast<UI_Button*>(guiData.dataS[8].get());
			トレニア = *dynamic_cast<UI_Button*>(guiData.dataS[9].get());
			ミルラ = *dynamic_cast<UI_Button*>(guiData.dataS[10].get());
			バロゥ = *dynamic_cast<UI_Button*>(guiData.dataS[11].get());
			ナズナ = *dynamic_cast<UI_Button*>(guiData.dataS[12].get());
			ナツメ = *dynamic_cast<UI_Button*>(guiData.dataS[13].get());
			//@End
		}
	};
}
