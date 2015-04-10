//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX
{
	using namespace SDX;

	class SceneReplay : public SDX::IScene
	{
	public:
		//@Define
		UI_Frame リプレイ情報 = { 127, {366,304,272,109} , 0.000000,1};
		UI_Button 開始 = { 128, {364,418,272,60} , 0.000000,0};
		UI_Text スコア = { 129, {371,385,255,23} , 0.000000,int,"std::string"};
		UI_Button Button = { 132, {318,50,40,381} , 0.000000,int};
		UI_Frame マップ情報 = { 133, {364,2,274,300} , 0.000000,1};
		UI_Button Button = { 135, {65,6,248,40} , 0.000000,int};
		UI_Text ウィッチ = { 139, {504,352,125,25} , 0.000000,int,"std::string"};
		UI_Text 難易度 = { 142, {370,318,125,25} , 0.000000,int,"std::string"};
		UI_Text クリア = { 144, {505,321,56,21} , 0.000000,int,"std::string"};
		UI_Frame ステージ一覧 = { 145, {62,2,300,476} , 0.000000,1};
		UI_Button Button = { 146, {318,434,40,40} , 0.000000,int};
		UI_Text タッグ = { 147, {371,351,125,25} , 0.000000,int,"std::string"};
		UI_Button Button = { 148, {318,6,40,40} , 0.000000,int};
		//@End

		SceneReplay()
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
			frameS[リプレイ情報.frameNo]->Draw(リプレイ情報.rect);
			frameS[開始.frameNo]->Draw(開始.rect);
			fontS[スコア.fontNo]->Draw(スコア.rect.GetPoint(),Color::White,スコア.text);
			frameS[Button.frameNo]->Draw(Button.rect);
			frameS[マップ情報.frameNo]->Draw(マップ情報.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			fontS[ウィッチ.fontNo]->Draw(ウィッチ.rect.GetPoint(),Color::White,ウィッチ.text);
			fontS[難易度.fontNo]->Draw(難易度.rect.GetPoint(),Color::White,難易度.text);
			fontS[クリア.fontNo]->Draw(クリア.rect.GetPoint(),Color::White,クリア.text);
			frameS[ステージ一覧.frameNo]->Draw(ステージ一覧.rect);
			frameS[Button.frameNo]->Draw(Button.rect);
			fontS[タッグ.fontNo]->Draw(タッグ.rect.GetPoint(),Color::White,タッグ.text);
			frameS[Button.frameNo]->Draw(Button.rect);
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneReplay", GUI_Factory);

			リプレイ情報 = *dynamic_cast<UI_Frame*>(guiData.dataS[0].get());
			開始 = *dynamic_cast<UI_Button*>(guiData.dataS[1].get());
			スコア = *dynamic_cast<UI_Text*>(guiData.dataS[2].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[3].get());
			マップ情報 = *dynamic_cast<UI_Frame*>(guiData.dataS[4].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[5].get());
			ウィッチ = *dynamic_cast<UI_Text*>(guiData.dataS[6].get());
			難易度 = *dynamic_cast<UI_Text*>(guiData.dataS[7].get());
			クリア = *dynamic_cast<UI_Text*>(guiData.dataS[8].get());
			ステージ一覧 = *dynamic_cast<UI_Frame*>(guiData.dataS[9].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[10].get());
			タッグ = *dynamic_cast<UI_Text*>(guiData.dataS[11].get());
			Button = *dynamic_cast<UI_Button*>(guiData.dataS[12].get());
			//@End
		}
	};
}
