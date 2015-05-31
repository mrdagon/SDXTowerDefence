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
		UI_Frame 難易度情報 = { 65, {62,258,300,216} , 0.000000,5};
		UI_Frame ステージ一覧 = { 29, {362,258,276,154} , 0.000000,5};
		UI_Button 開始 = { 30, {365,414,272,60} , 0.000000,3};
		UI_Button 難易度－ = { 60, {83,266,40,40} , 0.000000,3};
		UI_Button 難易度＋ = { 61, {302,266,40,40} , 0.000000,3};
		UI_Frame ウィッチ一覧 = { 63, {62,2,300,256} , 0.000000,5};
		UI_Frame マップ情報 = { 64, {362,2,276,256} , 0.000000,5};
		UI_Button 面数Minus = { 107, {368,263,40,144} , 0.000000,3};
		UI_Button ステージA = { 109, {415,264,170,36} , 0.000000,1};
		UI_Button ステージB = { 110, {415,300,170,36} , 0.000000,1};
		UI_Button ステージC = { 111, {415,336,170,36} , 0.000000,1};
		UI_Button ステージD = { 112, {415,372,170,36} , 0.000000,1};
		UI_Button 面数Plus = { 113, {592,263,40,144} , 0.000000,3};
		UI_Frame 難易度 = { 114, {128,266,167,40} , 0.000000,5};
		UI_Text Wave数 = { 115, {250,349,60,25} , 0.000000,1,"25 Wave"};
		UI_Text 出現数 = { 116, {251,379,60,25} , 0.000000,1,"敵数 1.2倍"};
		UI_Text HP補正 = { 117, {251,409,60,24} , 0.000000,1,"HP　1.2倍"};
		UI_Text Lv補正 = { 118, {252,439,60,24} , 0.000000,1,"LV 1.5倍"};
		UI_Frame ウィッチアイコン = { 119, {68,32,20,20} , 0.000000,0};
		UI_Button シングル_カップル = { 31, {213,311,130,30} , 0.000000,3};
		UI_Button トライアル = { 59, {83,311,130,30} , 0.000000,3};
		UI_Text ウィッチ名 = { 121, {96,32,56,20} , 0.000000,0,"std::string"};
		UI_Text 星 = { 122, {155,31,21,21} , 0.000000,0,"std::string"};
		UI_Text スコア = { 123, {278,32,30,22} , 0.000000,2,"std::string"};
		UI_Text ハイスコア = { 240, {64,9,126,22} , 0.000000,2,"Hi Score"};
        //@End
        bool isQuest = true;//クエスト用 or フリー用
        int ページ数 = 0;
        int 現在ステージ = 0;

        SceneQuest()
        {
            LoadGUI();
            Init();
        }

        //更新
        void Update() override
        {
            int 難易度 = (int)TDSystem::難易度;

            //Update
			if (開始.isClick() && TDSystem::選択ステージ != "" && (isQuest || 現在ステージ < (int)StageType::Free.size() ))
            {
                if (SceneWitch::SelectWitch().isOK )
                {
                    Stage::Call(false);
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

            int maxPage = (isQuest) ? 5 : (StageType::Free.size() - 1) / 4;

            if (ページ数 < 0){ ページ数 = maxPage; }
            if (ページ数 > maxPage){ ページ数 = 0; }

            if (ステージA.isClick()){ 現在ステージ = ページ数 * 4; }
            if (ステージB.isClick()){ 現在ステージ = ページ数 * 4 + 1; }
            if (ステージC.isClick()){ 現在ステージ = ページ数 * 4 + 2; }
            if (ステージD.isClick()){ 現在ステージ = ページ数 * 4 + 3; }

            if (isQuest)
            {
                TDSystem::選択ステージ = StageType::Quest[現在ステージ];
            }
            else
            {
                if (現在ステージ < (int)StageType::Free.size())
                {
                    TDSystem::選択ステージ = StageType::Free[現在ステージ];
                }
                else
                {
                    TDSystem::選択ステージ = "";
                }
            }

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
            if (TDSystem::選択ステージ == ""){ return; }

            WitchType 種類 = (WitchType)no;
            Point buf = { 0, no * 18 };

            MUnit::魔女[(UnitType)no][1]->DrawRotate(ウィッチアイコン.rect.GetCenter() + buf, 1, 0);
            MFont::fontS[ウィッチ名.fontNo].DrawRotate(ウィッチ名.rect.GetCenter() + buf, 1, 0, Color::White, WitchDataS[種類].名前);
            for (int a = 0; a < (int)TDSystem::限界難易度+1; ++a)
            {
                if (StageDataS[TDSystem::選択ステージ].Getスコア().完勝[種類] >= a)
                {
                    //金星
                    MFont::fontS[2].DrawRotate(星.rect.GetCenter() + buf + Point(10*a,0), 1, 0, Color::Yellow, "☆");
                }
                else if (StageDataS[TDSystem::選択ステージ].Getスコア().勝利[種類] >= a)
                {
                    //銀星
                    MFont::fontS[2].DrawRotate(星.rect.GetCenter() + buf + Point(10 * a, 0), 1, 0, Color::Silver, "☆");
                }
                else
                {
                    //黒星
                    MFont::fontS[2].DrawRotate(星.rect.GetCenter() + buf + Point(10 * a, 0), 1, 0, Color::Black, "☆");
                }
            }
            MFont::fontS[スコア.fontNo].DrawRotate(スコア.rect.GetCenter() + buf, 2, 0, Color::White, { std::setw(10), StageDataS[TDSystem::選択ステージ].Getスコア().スコア[種類] });
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

            MSystem::矢印[0].DrawRotate(難易度－.rect.GetCenter(), 2, 0);
            MSystem::矢印[1].DrawRotate(難易度＋.rect.GetCenter(), 2, 0);
            //
            MSystem::frameS[マップ情報.frameNo].Draw(マップ情報.rect);
            if (TDSystem::選択ステージ != "")
            {
                StageDataS[TDSystem::選択ステージ].DrawMinimap(マップ情報.rect.GetCenter() , false);
            }

            //難易度情報
            DifficultyData &data = DifficultyDataS[TDSystem::難易度];

            難易度.DrawText(MFont::fontS[2], data.名前.c_str() , 2);
            for (int a = 0; a < (int)TDSystem::難易度 + 1; ++a)
            {
                MFont::fontS[2].DrawRotate( 難易度.rect.GetCenter() + Point(10 * a - 5 * (int)TDSystem::難易度, 10), 1, 0, Color::Yellow, "☆");
            }

			int waveCount = data.Wave数[TDSystem::isトライアル] + !TDSystem::isトライアル * Witch::スキルLv[SkillType::試練];

			MFont::fontS[2].DrawRotate(Wave数.rect.GetCenter() - Point(100, 0), 2, 0, Color::White, { "Wave" });
			MFont::fontS[2].DrawRotate(出現数.rect.GetCenter() - Point(100, 0), 2, 0, Color::White, { "Enemy " });
			MFont::fontS[2].DrawRotate(HP補正.rect.GetCenter() - Point(100, 0), 2, 0, Color::White, { "Hp " });
			MFont::fontS[2].DrawRotate(Lv補正.rect.GetCenter() - Point(100, 0), 2, 0, Color::White, { "Lv " });

			MFont::fontS[FontType::ゴシック中].DrawRotate(Wave数.rect.GetCenter() , 1, 0, Color::White, { waveCount });
			MFont::fontS[FontType::ゴシック中].DrawRotate(出現数.rect.GetCenter() , 1, 0, Color::White, { data.雑魚召喚数[TDSystem::isトライアル] });
			MFont::fontS[FontType::ゴシック中].DrawRotate(HP補正.rect.GetCenter() , 1, 0, Color::White, { data.HP補正[TDSystem::isトライアル] * 100, "%" });
			MFont::fontS[FontType::ゴシック中].DrawRotate(Lv補正.rect.GetCenter() , 1, 0, Color::White, { data.レベル補正[TDSystem::isトライアル] * 100, "%" });


            MSystem::frameS[シングル_カップル.frameNo].Draw(シングル_カップル.rect);
            MSystem::frameS[トライアル.frameNo].Draw(トライアル.rect);
            //モードスイッチ
            シングル_カップル.DrawText(MFont::fontS[2], (TDSystem::isカップル)?"○ Couple":"× Couple", 2);
            トライアル.DrawText(MFont::fontS[2], (TDSystem::isトライアル)?"○ Trial":"× Trial", 2);
            //スコア一覧
            MFont::fontS[ハイスコア.fontNo].DrawRotate(ハイスコア.rect.GetCenter(), 2, 0, Color::White, ハイスコア.text);
            for (int a = 0; a < (int)WitchType::COUNT; ++a)
            {
                DrawScore(a);
            }
            //ステージ名一覧
            MSystem::frameS[面数Minus.frameNo].Draw(面数Minus.rect);
            MSystem::frameS[面数Plus.frameNo].Draw(面数Plus.rect);
            MSystem::矢印[0].DrawRotate(面数Minus.rect.GetCenter(), 2, 0);
            MSystem::矢印[1].DrawRotate(面数Plus.rect.GetCenter(), 2, 0);

            for (int a = 0; a < 4; ++a)
            {
                UI_Button* buf = &ステージA;
                switch (a)
                {
                    case 0: buf = &ステージA; break;
                    case 1: buf = &ステージB; break;
                    case 2: buf = &ステージC; break;
                    case 3: buf = &ステージD; break;
                }

                if (現在ステージ == ページ数 * 4 + a)
                {
                    Screen::SetBright(Color::Red);
                }
                if (isQuest)
                {
                    buf->DrawText(MFont::fontS[1], StageDataS[StageType::Quest[ページ数 * 4 + a]].名前.c_str(), 1);
                }else{
                    if (ページ数 * 4 + a < (int)StageType::Free.size())
                    {
                        buf->DrawText(MFont::fontS[1], StageDataS[StageType::Free[ページ数 * 4 + a]].名前.c_str(), 1);
                    }
                    else
                    {
                        buf->DrawText(MFont::fontS[1], "No Data", 1);
                    }
                }
                Screen::SetBright(Color::White);

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
