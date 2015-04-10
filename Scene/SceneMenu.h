//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX
{
	using namespace SDX;

	class SceneMenu : public SDX::IScene
	{
	public:
		//@Define
		UI_Frame 全体枠 = { 99, {60,0,580,480} , 0.000000,int};
		UI_Button Story = { 67, {0,0,60,60} , 0.000000,int};
		UI_Button Quest = { 72, {0,60,60,60} , 0.000000,int};
		UI_Button Free = { 73, {0,120,60,60} , 0.000000,int};
		UI_Button Replay = { 74, {0,300,60,60} , 0.000000,int};
		UI_Button Archive = { 75, {0,240,60,60} , 0.000000,int};
		UI_Button Skill = { 76, {0,180,60,60} , 0.000000,int};
		UI_Button Help = { 77, {0,360,60,60} , 0.000000,int};
		UI_Button Config = { 78, {0,420,60,60} , 0.000000,int};
		//@End

		SceneMenu()
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
			frameS[全体枠.frameNo]->Draw(全体枠.rect);
			frameS[Story.frameNo]->Draw(Story.rect);
			frameS[Quest.frameNo]->Draw(Quest.rect);
			frameS[Free.frameNo]->Draw(Free.rect);
			frameS[Replay.frameNo]->Draw(Replay.rect);
			frameS[Archive.frameNo]->Draw(Archive.rect);
			frameS[Skill.frameNo]->Draw(Skill.rect);
			frameS[Help.frameNo]->Draw(Help.rect);
			frameS[Config.frameNo]->Draw(Config.rect);
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneMenu", GUI_Factory);

			全体枠 = *dynamic_cast<UI_Frame*>(guiData.dataS[0].get());
			Story = *dynamic_cast<UI_Button*>(guiData.dataS[1].get());
			Quest = *dynamic_cast<UI_Button*>(guiData.dataS[2].get());
			Free = *dynamic_cast<UI_Button*>(guiData.dataS[3].get());
			Replay = *dynamic_cast<UI_Button*>(guiData.dataS[4].get());
			Archive = *dynamic_cast<UI_Button*>(guiData.dataS[5].get());
			Skill = *dynamic_cast<UI_Button*>(guiData.dataS[6].get());
			Help = *dynamic_cast<UI_Button*>(guiData.dataS[7].get());
			Config = *dynamic_cast<UI_Button*>(guiData.dataS[8].get());
			//@End
		}
	};
}
