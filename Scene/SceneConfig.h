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
		UI_Button 効果音＋ = { 90, {545,65,60,60} , 0.000000,3};
		UI_Button 効果音－ = { 91, {276,65,60,60} , 0.000000,3};
		UI_Button BGM－ = { 92, {276,165,60,60} , 0.000000,3};
		UI_Button BGM＋ = { 93, {545,166,60,60} , 0.000000,3};
		UI_Frame グリッド = { 94, {95,250,240,60} , 0.000000,5};
		UI_Frame 敵HP = { 95, {365,250,240,60} , 0.000000,5};
		UI_Frame エフェクト表示 = { 96, {365,325,240,60} , 0.000000,5};
		UI_Frame タッチ操作 = { 97, {95,325,240,60} , 0.000000,5};
		UI_Frame リプレイ保存 = { 98, {365,400,240,60} , 0.000000,5};
		UI_Text 効果音 = { 100, {105,80,155,31} , 0.000000,0,"Sound Volume"};
		UI_Frame BGMゲージ = { 102, {340,166,200,61} , 0.000000,1};
		UI_Frame 効果音ゲージ = { 103, {340,64,200,60} , 0.000000,1};
		UI_Frame ゲーム速度 = { 124, {95,400,240,60} , 0.000000,5};
		UI_Button グリッドChk = { 227, {100,255,50,50} , 0.000000,3};
		UI_Button 敵HPChk = { 229, {370,255,50,50} , 0.000000,3};
		UI_Button エフェクトChk = { 230, {370,330,50,50} , 0.000000,3};
		UI_Button リプレイChk = { 231, {370,405,50,50} , 0.000000,3};
		UI_Button タッチChk = { 232, {100,330,50,50} , 0.000000,3};
		UI_Button 速度Chk = { 233, {100,405,50,50} , 0.000000,3};
		UI_Text BGM = { 234, {105,180,161,25} , 0.000000,0,"BGM Volume"};
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
			if(グリッドChk.isClick()){}
			if(敵HPChk.isClick()){}
			if(エフェクトChk.isClick()){}
			if(リプレイChk.isClick()){}
			if(タッチChk.isClick()){}
			if(速度Chk.isClick()){}
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
			MFont::fontS[効果音.fontNo].DrawRotate(効果音.rect.GetCenter(),1,0,Color::White,効果音.text);
			MSystem::frameS[BGMゲージ.frameNo].Draw(BGMゲージ.rect);
			MSystem::frameS[効果音ゲージ.frameNo].Draw(効果音ゲージ.rect);
			MSystem::frameS[ゲーム速度.frameNo].Draw(ゲーム速度.rect);
			MSystem::frameS[グリッドChk.frameNo].Draw(グリッドChk.rect);
			MSystem::frameS[敵HPChk.frameNo].Draw(敵HPChk.rect);
			MSystem::frameS[エフェクトChk.frameNo].Draw(エフェクトChk.rect);
			MSystem::frameS[リプレイChk.frameNo].Draw(リプレイChk.rect);
			MSystem::frameS[タッチChk.frameNo].Draw(タッチChk.rect);
			MSystem::frameS[速度Chk.frameNo].Draw(速度Chk.rect);
			MFont::fontS[BGM.fontNo].DrawRotate(BGM.rect.GetCenter(),1,0,Color::White,BGM.text);
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
			グリッド = *dynamic_cast<UI_Frame*>(guiData.dataS[4].get());
			敵HP = *dynamic_cast<UI_Frame*>(guiData.dataS[5].get());
			エフェクト表示 = *dynamic_cast<UI_Frame*>(guiData.dataS[6].get());
			タッチ操作 = *dynamic_cast<UI_Frame*>(guiData.dataS[7].get());
			リプレイ保存 = *dynamic_cast<UI_Frame*>(guiData.dataS[8].get());
			効果音 = *dynamic_cast<UI_Text*>(guiData.dataS[9].get());
			BGMゲージ = *dynamic_cast<UI_Frame*>(guiData.dataS[10].get());
			効果音ゲージ = *dynamic_cast<UI_Frame*>(guiData.dataS[11].get());
			ゲーム速度 = *dynamic_cast<UI_Frame*>(guiData.dataS[12].get());
			グリッドChk = *dynamic_cast<UI_Button*>(guiData.dataS[13].get());
			敵HPChk = *dynamic_cast<UI_Button*>(guiData.dataS[14].get());
			エフェクトChk = *dynamic_cast<UI_Button*>(guiData.dataS[15].get());
			リプレイChk = *dynamic_cast<UI_Button*>(guiData.dataS[16].get());
			タッチChk = *dynamic_cast<UI_Button*>(guiData.dataS[17].get());
			速度Chk = *dynamic_cast<UI_Button*>(guiData.dataS[18].get());
			BGM = *dynamic_cast<UI_Text*>(guiData.dataS[19].get());
			//@End
		}
	};
}
