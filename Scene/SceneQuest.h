//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX
{
	using namespace SDX;

	class SceneQuest : public SDX::IScene
	{
	public:
		//@Define
		UI_Frame 難易度情報 = { 65, {365,305,272,107} , 0.000000,1};
		UI_Frame ステージ一覧 = { 29, {62,305,300,172} , 0.000000,1};
		UI_Button 開始 = { 30, {365,418,272,60} , 0.000000,0};
		UI_Button 難易度－ = { 60, {372,310,40,40} , 0.000000,0};
		UI_Button 難易度＋ = { 61, {591,310,40,40} , 0.000000,0};
		UI_Frame ウィッチ一覧 = { 63, {364,2,276,300} , 0.000000,1};
		UI_Frame マップ情報 = { 64, {62,2,300,300} , 0.000000,1};
		UI_Button 面数Minus = { 107, {67,309,40,160} , 0.000000,0};
		UI_Button ステージA = { 109, {113,308,195,39} , 0.000000,0};
		UI_Button ステージB = { 110, {113,349,195,39} , 0.000000,0};
		UI_Button ステージC = { 111, {112,391,195,38} , 0.000000,0};
		UI_Button ステージD = { 112, {113,430,192,41} , 0.000000,0};
		UI_Button 面数Plus = { 113, {314,313,40,160} , 0.000000,0};
		UI_Text 難易度 = { 114, {417,310,167,40} , 0.000000,0,"難易度"};
		UI_Text Wave数 = { 115, {371,356,125,25} , 0.000000,0,"25 Wave"};
		UI_Text 出現数 = { 116, {503,356,125,25} , 0.000000,0,"敵数 1.2倍"};
		UI_Text HP補正 = { 117, {371,385,126,24} , 0.000000,0,"HP 1.2倍"};
		UI_Text Lv補正 = { 118, {503,385,126,24} , 0.000000,0,"LV 1.5倍"};
		UI_Frame ウィッチアイコン = { 119, {366,4,20,20} , 0.000000,0};
		UI_Button シングル_カップル = { 31, {375,258,120,40} , 0.000000,0};
		UI_Button トライアル = { 59, {507,258,120,40} , 0.000000,0};
		UI_Text ウィッチ名 = { 121, {380,4,56,20} , 0.000000,0,"std::string"};
		UI_Text 星 = { 122, {443,4,56,21} , 0.000000,0,"std::string"};
		UI_Text スコア = { 123, {505,4,126,22} , 0.000000,0,"std::string"};
		//@End

		SceneQuest()
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
			if(難易度－.isClick()){}
			if(難易度＋.isClick()){}
			if(面数Minus.isClick()){}
			if(ステージA.isClick()){}
			if(ステージB.isClick()){}
			if(ステージC.isClick()){}
			if(ステージD.isClick()){}
			if(面数Plus.isClick()){}
			if(シングル_カップル.isClick()){}
			if(トライアル.isClick()){}
			//@End
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			//@Draw
			MSystem::frameS[難易度情報.frameNo].Draw(難易度情報.rect);
			MSystem::frameS[ステージ一覧.frameNo].Draw(ステージ一覧.rect);
			MSystem::frameS[開始.frameNo].Draw(開始.rect);
			MSystem::frameS[難易度－.frameNo].Draw(難易度－.rect);
			MSystem::frameS[難易度＋.frameNo].Draw(難易度＋.rect);
			MSystem::frameS[ウィッチ一覧.frameNo].Draw(ウィッチ一覧.rect);
			MSystem::frameS[マップ情報.frameNo].Draw(マップ情報.rect);
			MSystem::frameS[面数Minus.frameNo].Draw(面数Minus.rect);
			MSystem::frameS[ステージA.frameNo].Draw(ステージA.rect);
			MSystem::frameS[ステージB.frameNo].Draw(ステージB.rect);
			MSystem::frameS[ステージC.frameNo].Draw(ステージC.rect);
			MSystem::frameS[ステージD.frameNo].Draw(ステージD.rect);
			MSystem::frameS[面数Plus.frameNo].Draw(面数Plus.rect);
			MFont::fontS[難易度.fontNo].Draw(難易度.rect.GetPoint(),Color::White,難易度.text);
			MFont::fontS[Wave数.fontNo].Draw(Wave数.rect.GetPoint(),Color::White,Wave数.text);
			MFont::fontS[出現数.fontNo].Draw(出現数.rect.GetPoint(),Color::White,出現数.text);
			MFont::fontS[HP補正.fontNo].Draw(HP補正.rect.GetPoint(),Color::White,HP補正.text);
			MFont::fontS[Lv補正.fontNo].Draw(Lv補正.rect.GetPoint(),Color::White,Lv補正.text);
			MSystem::frameS[ウィッチアイコン.frameNo].Draw(ウィッチアイコン.rect);
			MSystem::frameS[シングル_カップル.frameNo].Draw(シングル_カップル.rect);
			MSystem::frameS[トライアル.frameNo].Draw(トライアル.rect);
			MFont::fontS[ウィッチ名.fontNo].Draw(ウィッチ名.rect.GetPoint(),Color::White,ウィッチ名.text);
			MFont::fontS[星.fontNo].Draw(星.rect.GetPoint(),Color::White,星.text);
			MFont::fontS[スコア.fontNo].Draw(スコア.rect.GetPoint(),Color::White,スコア.text);
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneQuest", GUI_Factory);

			難易度情報 = *dynamic_cast<UI_Frame*>(guiData.dataS[0].get());
			ステージ一覧 = *dynamic_cast<UI_Frame*>(guiData.dataS[1].get());
			開始 = *dynamic_cast<UI_Button*>(guiData.dataS[2].get());
			難易度－ = *dynamic_cast<UI_Button*>(guiData.dataS[3].get());
			難易度＋ = *dynamic_cast<UI_Button*>(guiData.dataS[4].get());
			ウィッチ一覧 = *dynamic_cast<UI_Frame*>(guiData.dataS[5].get());
			マップ情報 = *dynamic_cast<UI_Frame*>(guiData.dataS[6].get());
			面数Minus = *dynamic_cast<UI_Button*>(guiData.dataS[7].get());
			ステージA = *dynamic_cast<UI_Button*>(guiData.dataS[8].get());
			ステージB = *dynamic_cast<UI_Button*>(guiData.dataS[9].get());
			ステージC = *dynamic_cast<UI_Button*>(guiData.dataS[10].get());
			ステージD = *dynamic_cast<UI_Button*>(guiData.dataS[11].get());
			面数Plus = *dynamic_cast<UI_Button*>(guiData.dataS[12].get());
			難易度 = *dynamic_cast<UI_Text*>(guiData.dataS[13].get());
			Wave数 = *dynamic_cast<UI_Text*>(guiData.dataS[14].get());
			出現数 = *dynamic_cast<UI_Text*>(guiData.dataS[15].get());
			HP補正 = *dynamic_cast<UI_Text*>(guiData.dataS[16].get());
			Lv補正 = *dynamic_cast<UI_Text*>(guiData.dataS[17].get());
			ウィッチアイコン = *dynamic_cast<UI_Frame*>(guiData.dataS[18].get());
			シングル_カップル = *dynamic_cast<UI_Button*>(guiData.dataS[19].get());
			トライアル = *dynamic_cast<UI_Button*>(guiData.dataS[20].get());
			ウィッチ名 = *dynamic_cast<UI_Text*>(guiData.dataS[21].get());
			星 = *dynamic_cast<UI_Text*>(guiData.dataS[22].get());
			スコア = *dynamic_cast<UI_Text*>(guiData.dataS[23].get());
			//@End
		}
	};
}
