//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX
{
	using namespace SDX;

	class SceneSkill : public SDX::IScene
	{
	public:
		//@Define
		UI_Button Button = { 162, {85,6,80,100} , 0.000000,int};
		UI_Button リセット = { 175, {445,442,170,32} , 0.000000,int};
		UI_Frame レベル = { 177, {85,442,170,32} , 0.000000,int};
		UI_Frame 残りポイント = { 178, {265,442,170,32} , 0.000000,int};
		UI_Button Button = { 179, {175,6,80,100} , 0.000000,int};
		UI_Button Button = { 180, {265,6,80,100} , 0.000000,int};
		UI_Button Button = { 181, {355,6,80,100} , 0.000000,int};
		UI_Button Button = { 182, {445,6,80,100} , 0.000000,int};
		UI_Button Button = { 183, {535,6,80,100} , 0.000000,int};
		UI_Button Button = { 190, {445,116,80,100} , 0.000000,int};
		UI_Button Button = { 191, {535,116,80,100} , 0.000000,int};
		UI_Button Button = { 192, {85,116,80,100} , 0.000000,int};
		UI_Button Button = { 193, {355,116,80,100} , 0.000000,int};
		UI_Button Button = { 194, {175,116,80,100} , 0.000000,int};
		UI_Button Button = { 195, {265,116,80,100} , 0.000000,int};
		UI_Button Button = { 196, {535,225,80,100} , 0.000000,int};
		UI_Button Button = { 197, {85,226,80,100} , 0.000000,int};
		UI_Button Button = { 198, {445,226,80,100} , 0.000000,int};
		UI_Button Button = { 199, {175,226,80,100} , 0.000000,int};
		UI_Button Button = { 200, {355,226,80,100} , 0.000000,int};
		UI_Button Button = { 201, {265,226,80,100} , 0.000000,int};
		UI_Button Button = { 202, {175,336,80,100} , 0.000000,int};
		UI_Button Button = { 203, {355,336,80,100} , 0.000000,int};
		UI_Button Button = { 204, {535,335,80,100} , 0.000000,int};
		UI_Button Button = { 205, {445,336,80,100} , 0.000000,int};
		UI_Button Button = { 206, {85,336,80,100} , 0.000000,int};
		UI_Button Button = { 207, {265,336,80,100} , 0.000000,int};
		//@End

		SceneSkill()
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
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[リセット.frameNo]->Draw(リセット.rect);
			frameS[レベル.frameNo]->Draw(レベル.rect);
			frameS[残りポイント.frameNo]->Draw(残りポイント.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneSkill", GUI_Factory);

			Button = *dynamic_cast<UI_Button*>(guiData.dataS[0].get());
			リセット = *dynamic_cast<UI_Button*>(guiData.dataS[1].get());
			レベル = *dynamic_cast<UI_Frame*>(guiData.dataS[2].get());
			残りポイント = *dynamic_cast<UI_Frame*>(guiData.dataS[3].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[4].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[5].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[6].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[7].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[8].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[9].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[10].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[11].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[12].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[13].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[14].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[15].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[16].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[17].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[18].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[19].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[20].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[21].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[22].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[23].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[24].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[25].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[26].get());
			//@End
		}
	};
}
