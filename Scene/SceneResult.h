//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"
#include "../Stage/IStage.h"

namespace SDX_TD
{
    using namespace SDX;

    class SceneResult : public SDX::IScene
    {
    private:
        bool is勝利;
        bool isリプレイ保存済み = false;
    public:
        //@Define
        UI_Button リプレイ保存 = { 83, {121,384,120,60} , 0.000000,3};
        UI_Button リトライ = { 84, {258,384,120,60} , 0.000000,3};
        UI_Button 終了 = { 85, {398,384,120,60} , 0.000000,3};
        UI_Frame 全体枠 = { 86, {80,10,480,460} , 0.000000,5};
        UI_Frame Result = { 87, {100,30,440,40} , 0.000000,5};
        UI_Text 最終スコア = { 151, {225,242,196,54} , 0.000000,0,"Score"};
        UI_Text 撃破スコア = { 153, {253,83,146,32} , 0.000000,0,"Score"};
        UI_Text 難易度補正 = { 154, {250,130,146,31} , 0.000000,0,"Difficulty Bonus"};
        UI_Text 体力補正 = { 155, {249,175,146,31} , 0.000000,0,"Life Bonus"};
        UI_Text 獲得経験値 = { 156, {223,313,196,54} , 0.000000,0,"EXP"};
        //@End

        bool isRetry;

        static bool CallResult(bool is勝利)
        {
            static SceneResult single(is勝利);
            single.Init();
            //スコア更新時にリプレイAutoSaveするかどうか
            if (TDSystem::isリプレイ保存)
            {

            }

            do
            {
                single.Update();
                single.Draw();
            } while (System::Update(true) && !single.isEnd);

            return single.isRetry;
        }

        SceneResult(bool is勝利):
            is勝利(is勝利)
        {
            LoadGUI();
        }

        //初期化
        void Init() override
        {
            isEnd = false;
            isリプレイ保存済み = false;
        }

        //終了時
        void Final() override
        {
        }

        //更新
        void Update() override
        {
            if(リプレイ保存.isClick())
            {
                if ( !isリプレイ保存済み)
                {
                    SStage->SaveReplay();
                }
            }

            if(リトライ.isClick())
            {
                isRetry = true;
                isEnd = true;
            }
            if(終了.isClick())
            {
                isRetry = false;
                isEnd = true;
            }
        }

        //描画
        void Draw() override
        {
#ifdef _DEBUG			
            if (Input::key.Return.on){ LoadGUI(); }
#endif
            Director::IsDraw() = true;
            Screen::SetBright(Color::Gray);
            Director::GetScene(0)->Draw();
            Screen::SetBright(Color::White);

            //@Draw
            MSystem::frameS[全体枠.frameNo].Draw(全体枠.rect);
            
            if (isリプレイ保存済み)
            {
                Screen::SetBright(Color::Gray);
                リプレイ保存.DrawText(MFont::fontS[1], "保存済み", 1, Color::Red);
                Screen::SetBright();
            }
            else
            {
                リプレイ保存.DrawText(MFont::fontS[1], "リプレイ保存", 1, Color::Black);
            }
            リトライ.DrawText(MFont::fontS[1], "リトライ", 1, Color::Black);
            終了.DrawText(MFont::fontS[1], "終了", 1, Color::Black);

            Result.DrawText(MFont::fontS[2], (is勝利) ? "Win" : "Lose", 2);

            MFont::fontS[最終スコア.fontNo].DrawRotate(最終スコア.rect.GetCenter(),1,0,Color::White,最終スコア.text);
            MFont::fontS[撃破スコア.fontNo].DrawRotate(撃破スコア.rect.GetCenter(),1,0,Color::White,撃破スコア.text);
            MFont::fontS[難易度補正.fontNo].DrawRotate(難易度補正.rect.GetCenter(),1,0,Color::White,難易度補正.text);
            MFont::fontS[体力補正.fontNo].DrawRotate(体力補正.rect.GetCenter(),1,0,Color::White,体力補正.text);
            MFont::fontS[獲得経験値.fontNo].DrawRotate(獲得経験値.rect.GetCenter(),1,0,Color::White,獲得経験値.text);
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
