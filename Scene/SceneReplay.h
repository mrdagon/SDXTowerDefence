﻿//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX_TD
{
	using namespace SDX;

	class SceneReplay : public SDX::IScene
	{
	public:
		//@Define
		UI_Frame リプレイ情報 = { 127, {364,305,275,110} , 0.000000,5};
		UI_Button 開始 = { 128, {364,418,274,60} , 0.000000,3};
		UI_Text スコア = { 129, {484,382,146,24} , 0.000000,0,"score"};
		UI_Button スクロールバー = { 132, {318,50,40,381} , 0.000000,3};
		UI_Frame マップ情報 = { 133, {364,2,275,300} , 0.000000,5};
		UI_Button リプレイ選択 = { 135, {65,6,248,40} , 0.000000,1};
		UI_Text ウィッチ = { 139, {509,343,118,25} , 0.000000,0,"std::string"};
		UI_Text 難易度 = { 142, {375,343,118,25} , 0.000000,0,"Difficulty"};
		UI_Text 結果 = { 144, {375,383,97,22} , 0.000000,0,"Perfect"};
		UI_Frame ステージ一覧 = { 145, {62,2,300,476} , 0.000000,5};
		UI_Button 下スクロール = { 146, {318,434,40,40} , 0.000000,3};
		UI_Button 上スクロール = { 148, {318,6,40,40} , 0.000000,3};
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
			if(開始.isClick()){}
			if(スクロールバー.isClick()){}
			if(リプレイ選択.isClick()){}
			if(下スクロール.isClick()){}
			if(上スクロール.isClick()){}
			//@End
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			//@Draw
			MSystem::frameS[リプレイ情報.frameNo].Draw(リプレイ情報.rect);
			MSystem::frameS[開始.frameNo].Draw(開始.rect);
			MFont::fontS[スコア.fontNo].DrawRotate(スコア.rect.GetCenter(),1,0,Color::White,スコア.text);
			MSystem::frameS[スクロールバー.frameNo].Draw(スクロールバー.rect);
			MSystem::frameS[マップ情報.frameNo].Draw(マップ情報.rect);
			MSystem::frameS[リプレイ選択.frameNo].Draw(リプレイ選択.rect);
			MFont::fontS[ウィッチ.fontNo].DrawRotate(ウィッチ.rect.GetCenter(),1,0,Color::White,ウィッチ.text);
			MFont::fontS[難易度.fontNo].DrawRotate(難易度.rect.GetCenter(),1,0,Color::White,難易度.text);
			MFont::fontS[結果.fontNo].DrawRotate(結果.rect.GetCenter(),1,0,Color::White,結果.text);
			MSystem::frameS[ステージ一覧.frameNo].Draw(ステージ一覧.rect);
			MSystem::frameS[下スクロール.frameNo].Draw(下スクロール.rect);
			MSystem::frameS[上スクロール.frameNo].Draw(上スクロール.rect);
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
			スクロールバー = *dynamic_cast<UI_Button*>(guiData.dataS[3].get());
			マップ情報 = *dynamic_cast<UI_Frame*>(guiData.dataS[4].get());
			リプレイ選択 = *dynamic_cast<UI_Button*>(guiData.dataS[5].get());
			ウィッチ = *dynamic_cast<UI_Text*>(guiData.dataS[6].get());
			難易度 = *dynamic_cast<UI_Text*>(guiData.dataS[7].get());
			結果 = *dynamic_cast<UI_Text*>(guiData.dataS[8].get());
			ステージ一覧 = *dynamic_cast<UI_Frame*>(guiData.dataS[9].get());
			下スクロール = *dynamic_cast<UI_Button*>(guiData.dataS[10].get());
			上スクロール = *dynamic_cast<UI_Button*>(guiData.dataS[11].get());
			//@End
		}
	};
}
