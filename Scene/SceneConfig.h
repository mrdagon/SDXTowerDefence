//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX
{
	using namespace SDX;

	class SceneConfig : public SDX::IScene
	{
	public:
		//@Define
		UI_Button 効果音＋ = { 90, {520,65,60,60} , 0.000000,0};
		UI_Button 効果音－ = { 91, {120,65,60,60} , 0.000000,0};
		UI_Button BGM－ = { 92, {120,165,60,60} , 0.000000,0};
		UI_Button BGM＋ = { 93, {520,166,60,60} , 0.000000,0};
		UI_Button グリッド = { 94, {95,250,240,60} , 0.000000,0};
		UI_Button 敵HP = { 95, {365,250,240,60} , 0.000000,0};
		UI_Button エフェクト表示 = { 96, {365,325,240,60} , 0.000000,0};
		UI_Button タッチ操作 = { 97, {95,325,240,60} , 0.000000,0};
		UI_Button リプレイ保存 = { 98, {365,400,240,60} , 0.000000,0};
		UI_Text 効果音 = { 100, {274,25,155,31} , 0.000000,0,"効果音"};
		UI_Text BGM = { 101, {271,132,161,25} , 0.000000,0,"BGM"};
		UI_Frame BGMゲージ = { 102, {200,166,300,60} , 0.000000,0};
		UI_Frame 効果音ゲージ = { 103, {200,64,300,60} , 0.000000,0};
		UI_Button ゲーム速度 = { 124, {95,400,240,60} , 0.000000,0};
		//@End

		SceneConfig()
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
			if(効果音＋.isClick()){}
			if(効果音－.isClick()){}
			if(BGM－.isClick()){}
			if(BGM＋.isClick()){}
			if(グリッド.isClick()){}
			if(敵HP.isClick()){}
			if(エフェクト表示.isClick()){}
			if(タッチ操作.isClick()){}
			if(リプレイ保存.isClick()){}
			if(ゲーム速度.isClick()){}
			//@End
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			//@Draw
			MSystem::frameS[効果音＋.frameNo].Draw(効果音＋.rect);
			MSystem::frameS[効果音－.frameNo].Draw(効果音－.rect);
			MSystem::frameS[BGM－.frameNo].Draw(BGM－.rect);
			MSystem::frameS[BGM＋.frameNo].Draw(BGM＋.rect);
			MSystem::frameS[グリッド.frameNo].Draw(グリッド.rect);
			MSystem::frameS[敵HP.frameNo].Draw(敵HP.rect);
			MSystem::frameS[エフェクト表示.frameNo].Draw(エフェクト表示.rect);
			MSystem::frameS[タッチ操作.frameNo].Draw(タッチ操作.rect);
			MSystem::frameS[リプレイ保存.frameNo].Draw(リプレイ保存.rect);
			MFont::fontS[効果音.fontNo].Draw(効果音.rect.GetPoint(),Color::White,効果音.text);
			MFont::fontS[BGM.fontNo].Draw(BGM.rect.GetPoint(),Color::White,BGM.text);
			MSystem::frameS[BGMゲージ.frameNo].Draw(BGMゲージ.rect);
			MSystem::frameS[効果音ゲージ.frameNo].Draw(効果音ゲージ.rect);
			MSystem::frameS[ゲーム速度.frameNo].Draw(ゲーム速度.rect);
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneConfig", GUI_Factory);

			効果音＋ = *dynamic_cast<UI_Button*>(guiData.dataS[0].get());
			効果音－ = *dynamic_cast<UI_Button*>(guiData.dataS[1].get());
			BGM－ = *dynamic_cast<UI_Button*>(guiData.dataS[2].get());
			BGM＋ = *dynamic_cast<UI_Button*>(guiData.dataS[3].get());
			グリッド = *dynamic_cast<UI_Button*>(guiData.dataS[4].get());
			敵HP = *dynamic_cast<UI_Button*>(guiData.dataS[5].get());
			エフェクト表示 = *dynamic_cast<UI_Button*>(guiData.dataS[6].get());
			タッチ操作 = *dynamic_cast<UI_Button*>(guiData.dataS[7].get());
			リプレイ保存 = *dynamic_cast<UI_Button*>(guiData.dataS[8].get());
			効果音 = *dynamic_cast<UI_Text*>(guiData.dataS[9].get());
			BGM = *dynamic_cast<UI_Text*>(guiData.dataS[10].get());
			BGMゲージ = *dynamic_cast<UI_Frame*>(guiData.dataS[11].get());
			効果音ゲージ = *dynamic_cast<UI_Frame*>(guiData.dataS[12].get());
			ゲーム速度 = *dynamic_cast<UI_Button*>(guiData.dataS[13].get());
			//@End
		}
	};
}
