//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"
#include "../System/TDSystem.h"
#include "../System/Material.h"

namespace SDX_TD
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
		UI_Text 効果音 = { 100, {114,80,120,30} , 0.000000,3,"Sound Volume"};
		UI_Frame BGMゲージ = { 102, {340,166,200,61} , 0.000000,1};
		UI_Frame 効果音ゲージ = { 103, {340,64,200,60} , 0.000000,1};
		UI_Frame 初期配置 = { 124, {95,400,240,60} , 0.000000,5};
		UI_Button グリッドChk = { 227, {100,255,50,50} , 0.000000,3};
		UI_Button 敵HPChk = { 229, {370,255,50,50} , 0.000000,3};
		UI_Button エフェクト表示Chk = { 230, {370,330,50,50} , 0.000000,3};
		UI_Button リプレイ保存Chk = { 231, {370,405,50,50} , 0.000000,3};
		UI_Button タッチ操作Chk = { 232, {100,330,50,50} , 0.000000,3};
		UI_Button 初期配置Chk = { 233, {100,405,50,50} , 0.000000,3};
		UI_Text BGM = { 234, {126,180,100,30} , 0.000000,3,"BGM Volume"};
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
			//Update
			if (効果音＋.isClick()){ TDSystem::効果音の音量++; }
			if (効果音－.isClick()){ TDSystem::効果音の音量--; }
			if (BGM－.isClick()){ TDSystem::BGMの音量--; }
			if (BGM＋.isClick()){ TDSystem::BGMの音量++; }
			if (グリッドChk.isClick()){ TDSystem::isグリッド = !TDSystem::isグリッド; }
			if (敵HPChk.isClick()){ TDSystem::isHPゲージ = !TDSystem::isHPゲージ; }
			if (エフェクト表示Chk.isClick()){ TDSystem::isエフェクト = !TDSystem::isエフェクト; }
			if (リプレイ保存Chk.isClick()){ TDSystem::isリプレイ保存 = !TDSystem::isリプレイ保存; }
			if (タッチ操作Chk.isClick()){ TDSystem::isタッチ = !TDSystem::isタッチ; }
			if (初期配置Chk.isClick()){ TDSystem::is配置記録 = !TDSystem::is配置記録; }
			//End

			TDSystem::効果音の音量 = std::min(std::max(0, TDSystem::効果音の音量), 10);
			TDSystem::BGMの音量 = std::min(std::max(0, TDSystem::BGMの音量), 10);
		}

		void DrawCheck(UI_Frame &外枠 , UI_Button &チェックボックス , const char* 文字列 , bool &チェックフラグ)
		{
			if (チェックフラグ)
			{
				MIcon::UI[IconType::麻痺].DrawRotate(チェックボックス.rect.GetCenter(), 1, 0);
			}
			MFont::fontS[FontType::ゴシック中].DrawRotate(外枠.rect.GetCenter() + Point(25,0), 1, 0, Color::White, 文字列);

		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			//Draw
			MSystem::frameS[効果音＋.frameNo].Draw(効果音＋.rect);
			MSystem::frameS[効果音－.frameNo].Draw(効果音－.rect);
			MSystem::frameS[BGM－.frameNo].Draw(BGM－.rect);
			MSystem::frameS[BGM＋.frameNo].Draw(BGM＋.rect);
			MSystem::frameS[グリッド.frameNo].Draw(グリッド.rect);
			MSystem::frameS[敵HP.frameNo].Draw(敵HP.rect);
			MSystem::frameS[エフェクト表示.frameNo].Draw(エフェクト表示.rect);
			MSystem::frameS[タッチ操作.frameNo].Draw(タッチ操作.rect);
			MSystem::frameS[リプレイ保存.frameNo].Draw(リプレイ保存.rect);
			MFont::fontS[効果音.fontNo].DrawRotate(効果音.rect.GetCenter(),2,0,Color::White,効果音.text);
			MSystem::frameS[BGMゲージ.frameNo].Draw(BGMゲージ.rect);
			MSystem::frameS[効果音ゲージ.frameNo].Draw(効果音ゲージ.rect);
			MSystem::frameS[初期配置.frameNo].Draw(初期配置.rect);
			MSystem::frameS[グリッドChk.frameNo].Draw(グリッドChk.rect);
			MSystem::frameS[敵HPChk.frameNo].Draw(敵HPChk.rect);
			MSystem::frameS[エフェクト表示Chk.frameNo].Draw(エフェクト表示Chk.rect);
			MSystem::frameS[リプレイ保存Chk.frameNo].Draw(リプレイ保存Chk.rect);
			MSystem::frameS[タッチ操作Chk.frameNo].Draw(タッチ操作Chk.rect);
			MSystem::frameS[初期配置Chk.frameNo].Draw(初期配置Chk.rect);
			MFont::fontS[BGM.fontNo].DrawRotate(BGM.rect.GetCenter(),2,0,Color::White,BGM.text);
			//End
			//音量ゲージ
			Rect rect = { 効果音ゲージ.rect.GetX()+5, 効果音ゲージ.rect.GetY()+50, 18,5};
			for (int a = 0; a < TDSystem::効果音の音量; ++a )
			{
				rect.Draw(Color::Red);
				rect.heightUp += 5;
				rect.x += 19;
			}
			rect = { BGMゲージ.rect.GetX() + 5, BGMゲージ.rect.GetY() + 50, 18, 5 };
			for (int a = 0; a < TDSystem::BGMの音量; ++a )
			{
				rect.Draw(Color::Red);
				rect.heightUp += 5;
				rect.x += 19;
			}
			//チェックボックス＆項目名
			DrawCheck(グリッド, グリッドChk, "グリッド表示", TDSystem::isグリッド);
			DrawCheck(敵HP, 敵HPChk, "体力ゲージ表示", TDSystem::isHPゲージ);
			DrawCheck(初期配置, 初期配置Chk, "初期配置記録", TDSystem::is配置記録);
			DrawCheck(タッチ操作, タッチ操作Chk, "タッチ操作モード", TDSystem::isタッチ);
			DrawCheck(エフェクト表示, エフェクト表示Chk, "エフェクト簡略化", TDSystem::isエフェクト);
			DrawCheck(リプレイ保存, リプレイ保存Chk, "更新時リプレイ保存", TDSystem::isリプレイ保存);


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
			初期配置 = *dynamic_cast<UI_Frame*>(guiData.dataS[12].get());
			グリッドChk = *dynamic_cast<UI_Button*>(guiData.dataS[13].get());
			敵HPChk = *dynamic_cast<UI_Button*>(guiData.dataS[14].get());
			エフェクト表示Chk = *dynamic_cast<UI_Button*>(guiData.dataS[15].get());
			リプレイ保存Chk = *dynamic_cast<UI_Button*>(guiData.dataS[16].get());
			タッチ操作Chk = *dynamic_cast<UI_Button*>(guiData.dataS[17].get());
			初期配置Chk = *dynamic_cast<UI_Button*>(guiData.dataS[18].get());
			BGM = *dynamic_cast<UI_Text*>(guiData.dataS[19].get());
			//@End
		}
	};
}
