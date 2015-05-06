//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"
#include "SceneWitch.h"

namespace SDX_TD
{
	using namespace SDX;

	class SceneQuest : public SDX::IScene
	{
	public:
		//@Define
		UI_Frame 難易度情報 = { 65, {362,302,276,110} , 0.000000,5};
		UI_Frame ステージ一覧 = { 29, {62,302,300,172} , 0.000000,5};
		UI_Button 開始 = { 30, {365,414,272,60} , 0.000000,3};
		UI_Button 難易度－ = { 60, {372,310,40,40} , 0.000000,3};
		UI_Button 難易度＋ = { 61, {591,310,40,40} , 0.000000,3};
		UI_Frame ウィッチ一覧 = { 63, {62,2,300,300} , 0.000000,5};
		UI_Frame マップ情報 = { 64, {362,2,276,300} , 0.000000,5};
		UI_Button 面数Minus = { 107, {68,308,40,160} , 0.000000,3};
		UI_Button ステージA = { 109, {115,308,195,40} , 0.000000,1};
		UI_Button ステージB = { 110, {115,348,195,40} , 0.000000,1};
		UI_Button ステージC = { 111, {115,388,195,40} , 0.000000,1};
		UI_Button ステージD = { 112, {115,428,195,40} , 0.000000,1};
		UI_Button 面数Plus = { 113, {317,308,40,160} , 0.000000,3};
		UI_Frame 難易度 = { 114, {417,310,167,40} , 0.000000,5};
		UI_Text Wave数 = { 115, {371,356,125,25} , 0.000000,1,"25 Wave"};
		UI_Text 出現数 = { 116, {503,356,125,25} , 0.000000,1,"敵数 1.2倍"};
		UI_Text HP補正 = { 117, {371,385,126,24} , 0.000000,1,"HP　1.2倍"};
		UI_Text Lv補正 = { 118, {503,385,126,24} , 0.000000,1,"LV 1.5倍"};
		UI_Frame ウィッチアイコン = { 119, {68,32,20,20} , 0.000000,0};
		UI_Button シングル_カップル = { 31, {69,258,140,40} , 0.000000,3};
		UI_Button トライアル = { 59, {216,258,140,40} , 0.000000,3};
		UI_Text ウィッチ名 = { 121, {96,32,56,20} , 0.000000,0,"std::string"};
		UI_Text 星 = { 122, {160,32,56,21} , 0.000000,0,"std::string"};
		UI_Text スコア = { 123, {226,32,126,22} , 0.000000,0,"std::string"};
		UI_Text ハイスコア = { 240, {64,4,126,22} , 0.000000,3,"Hi Score"};
		//@End
		bool isウィッチ選択中 = false;		
		int ページ数 = 0;

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
			int 難易度 = (int)TDSystem::難易度;

			//Update
			if(開始.isClick())
			{
				if (SceneWitch::SelectWitch().isOK)
				{

					Director::AddScene(std::make_shared<Stage>());
				}
				
				return;
			}
			if(難易度－.isClick())
			{
				難易度--;
			}
			if(難易度＋.isClick())
			{
				難易度++;
			}
			if (難易度 < 0){ TDSystem::難易度 = TDSystem::限界難易度; }
			else if (難易度 > (int)TDSystem::限界難易度){ TDSystem::難易度 = Difficulty::Easy; }
			else { TDSystem::難易度 = Difficulty(難易度); }

			if (面数Plus.isClick()){ ページ数++; }
			if (面数Minus.isClick()){ ページ数--; }
			if (ページ数 < 0){ ページ数 = 5; }
			if (ページ数 > 5){ ページ数 = 0; }

			if (ステージA.isClick()){ TDSystem::選択ステージ = ページ数 * 4; }
			if (ステージB.isClick()){ TDSystem::選択ステージ = ページ数 * 4+1; }
			if (ステージC.isClick()){ TDSystem::選択ステージ = ページ数 * 4+2; }
			if (ステージD.isClick()){ TDSystem::選択ステージ = ページ数 * 4+3; }
			if(シングル_カップル.isClick())
			{
				TDSystem::isカップル = !TDSystem::isカップル;
			}
			if(トライアル.isClick())
			{
				TDSystem::isトライアル = !TDSystem::isトライアル;
			}
			//End
		}

		void DrawScore(int no)
		{
			WitchType 種類 = (WitchType)no;
			Point buf = { 0, no * 18 };

			MUnit::魔女[(UnitType)no][1]->DrawRotate(ウィッチアイコン.rect.GetCenter() + buf, 1, 0);
			MFont::fontS[ウィッチ名.fontNo].DrawRotate(ウィッチ名.rect.GetCenter() + buf, 1, 0, Color::White, WitchDataS[種類].名前);
			for (int a = 0; a < 6; ++a)
			{
				StageDataS[0].Getスコア().完勝[種類] = no / 2;
				StageDataS[0].Getスコア().勝利[種類] = no;

				if (StageDataS[0].Getスコア().完勝[種類] > a)
				{
					//金星
					MFont::fontS[2].DrawRotate(星.rect.GetCenter() + buf + Point(10*a,0), 1, 0, Color::Yellow, "☆");
				}
				else if (StageDataS[0].Getスコア().勝利[種類] > a)
				{
					//銀星
					MFont::fontS[2].DrawRotate(星.rect.GetCenter() + buf + Point(10 * a, 0), 1, 0, Color::Silver, "☆");
				}
				else
				{
					//黒星
					MFont::fontS[2].DrawRotate(星.rect.GetCenter() + buf + Point(10 * a, 0), 1, 0, Color::Black, "☆");
				}

				StageDataS[0].Getスコア().スコア[種類] = no * no * no;
			}
			//MSystem::frameS[ウィッチアイコン.frameNo].Draw(ウィッチアイコン.rect);
			//MFont::fontS[ウィッチ名.fontNo].DrawRotate(ウィッチ名.rect.GetCenter(), 1, 0, Color::White, ウィッチ名.text);
			//MFont::fontS[星.fontNo].DrawRotate(星.rect.GetCenter(), 1, 0, Color::White, 星.text);
			MFont::fontS[スコア.fontNo].DrawRotate(スコア.rect.GetCenter() + buf, 2, 0, Color::White, { std::setw(8) ,StageDataS[0].Getスコア().スコア[種類]});
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			//Draw
			MSystem::frameS[難易度情報.frameNo].Draw(難易度情報.rect);
			MSystem::frameS[ステージ一覧.frameNo].Draw(ステージ一覧.rect);
			開始.DrawText(MFont::fontS[2], "Start", 2);
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
			//難易度情報
			DifficultyData &data = DifficultyDataS[TDSystem::難易度];

			難易度.DrawText(MFont::fontS[2], data.名前.c_str() , 2);
			MFont::fontS[Wave数.fontNo].DrawRotate(Wave数.rect.GetCenter(), 1, 0, Color::White, { "Wave" , std::setw(4) , data.Wave数[TDSystem::isトライアル] });
			MFont::fontS[出現数.fontNo].DrawRotate(出現数.rect.GetCenter(), 1, 0, Color::White, { "Enemy ", data.雑魚召喚数[TDSystem::isトライアル] });
			MFont::fontS[HP補正.fontNo].DrawRotate(HP補正.rect.GetCenter(), 1, 0, Color::White, { "Hp ", data.HP補正[TDSystem::isトライアル] * 100, "%" });
			MFont::fontS[Lv補正.fontNo].DrawRotate(Lv補正.rect.GetCenter(), 1, 0, Color::White, { "Lv ", data.レベル補正[TDSystem::isトライアル] * 100, "%" });
			MSystem::frameS[シングル_カップル.frameNo].Draw(シングル_カップル.rect);
			MSystem::frameS[トライアル.frameNo].Draw(トライアル.rect);
			//モードスイッチ
			シングル_カップル.DrawText(MFont::fontS[2], (TDSystem::isカップル)?"Couple":"Single", 2);
			トライアル.DrawText(MFont::fontS[2], (TDSystem::isトライアル)?"Trial":"Power", 2);
			//スコア一覧
			MFont::fontS[ハイスコア.fontNo].DrawRotate(ハイスコア.rect.GetCenter(), 2, 0, Color::White, ハイスコア.text);
			for (int a = 0; a < (int)WitchType::COUNT; ++a)
			{
				DrawScore(a);
			}
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
			難易度 = *dynamic_cast<UI_Frame*>(guiData.dataS[13].get());
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
			ハイスコア = *dynamic_cast<UI_Text*>(guiData.dataS[24].get());
			//@End
		}
	};
}
