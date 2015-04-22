//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX
{
	using namespace SDX;

	class SceneResult : public SDX::IScene
	{
	public:
		//@Define
		UI_Button リプレイ保存 = { 83, {121,382,120,60} , 0.000000,0};
		UI_Button リトライ = { 84, {258,384,120,60} , 0.000000,0};
		UI_Button 終了 = { 85, {398,383,120,60} , 0.000000,0};
		UI_Frame 全体枠 = { 86, {80,10,480,460} , 0.000000,int};
		UI_Frame Result = { 87, {100,30,440,40} , 0.000000,0};
		UI_Text 最終スコア = { 151, {225,242,196,54} , 0.000000,0,"Score"};
		UI_Text 撃破スコア = { 153, {253,83,146,32} , 0.000000,0,"撃破スコア"};
		UI_Text 難易度補正 = { 154, {250,130,146,31} , 0.000000,0,"Difficulty Bonus"};
		UI_Text 体力補正 = { 155, {249,175,146,31} , 0.000000,0,"Life Bonus"};
		UI_Text 獲得経験値 = { 156, {223,313,196,54} , 0.000000,0,"EXP"};
		//@End

		SceneResult()
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
			frameS[リプレイ保存.frameNo]->Draw(リプレイ保存.rect);
			frameS[リトライ.frameNo]->Draw(リトライ.rect);
			frameS[終了.frameNo]->Draw(終了.rect);
			frameS[全体枠.frameNo]->Draw(全体枠.rect);
			frameS[Result.frameNo]->Draw(Result.rect);
			fontS[最終スコア.fontNo]->Draw(最終スコア.rect.GetPoint(),Color::White,最終スコア.text);
			fontS[撃破スコア.fontNo]->Draw(撃破スコア.rect.GetPoint(),Color::White,撃破スコア.text);
			fontS[難易度補正.fontNo]->Draw(難易度補正.rect.GetPoint(),Color::White,難易度補正.text);
			fontS[体力補正.fontNo]->Draw(体力補正.rect.GetPoint(),Color::White,体力補正.text);
			fontS[獲得経験値.fontNo]->Draw(獲得経験値.rect.GetPoint(),Color::White,獲得経験値.text);
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneResult", GUI_Factory);

			リプレイ保存 = *dynamic_cast<UI_Button*>(guiData.dataS[0].get());
			リトライ = *dynamic_cast<UI_Button*>(guiData.dataS[1].get());
			終了 = *dynamic_cast<UI_Button*>(guiData.dataS[2].get());
			全体枠 = *dynamic_cast<UI_Frame*>(guiData.dataS[3].get());
			Result = *dynamic_cast<UI_Frame*>(guiData.dataS[4].get());
			最終スコア = *dynamic_cast<UI_Text*>(guiData.dataS[5].get());
			撃破スコア = *dynamic_cast<UI_Text*>(guiData.dataS[6].get());
			難易度補正 = *dynamic_cast<UI_Text*>(guiData.dataS[7].get());
			体力補正 = *dynamic_cast<UI_Text*>(guiData.dataS[8].get());
			獲得経験値 = *dynamic_cast<UI_Text*>(guiData.dataS[9].get());
			//@End
		}
	};
}
