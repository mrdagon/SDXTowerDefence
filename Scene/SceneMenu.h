//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"
#include "SceneArchive.h"
#include "SceneConfig.h"
#include "SceneHelp.h"
#include "SceneQuest.h"
#include "SceneSkill.h"
#include "SceneReplay.h"
#include "SceneStory.h"
#include "SceneTitle.h"
#include "SceneWitch.h"

namespace SDX_TD
{
    using namespace SDX;

    class SceneMenu : public SDX::IScene
    {
    public:
        IScene* activeScene = nullptr;
        //子Scene
        SceneStory sceneStory;
        SceneQuest sceneQuest;
        SceneQuest sceneFree;
        SceneArchive sceneArchive;
        SceneConfig sceneConfig;
        SceneHelp sceneHelp;
        SceneSkill sceneSkill;
        SceneReplay sceneReplay;

        //@Define
		UI_Frame 全体枠 = { 99, {0,0,640,480} , 0.000000,0};
		UI_Button Storyタグ = { 67, {0,0,60,60} , 0.000000,0};
		UI_Button Questタグ = { 72, {0,60,60,60} , 0.000000,0};
		UI_Button Freeタグ = { 73, {0,120,60,60} , 0.000000,0};
		UI_Button Replayタグ = { 74, {0,300,60,60} , 0.000000,0};
		UI_Button Archiveタグ = { 75, {0,240,60,60} , 0.000000,0};
		UI_Button Skillタグ = { 76, {0,180,60,60} , 0.000000,0};
		UI_Button Helpタグ = { 77, {0,360,60,60} , 0.000000,0};
		UI_Button Configタグ = { 78, {0,420,60,60} , 0.000000,0};
        //@End

        SceneMenu()
        {
            sceneFree.isQuest = false;

			MMusic::メニュー.Play();

            LoadGUI();
            Init();
        }

        //初期化
        void Init() override
        {
        }

        //終了時
        void Final() override
        {
        }

        //更新
        void Update() override
        {
            if (Storyタグ.isClick()){ activeScene = &sceneStory; }
            if (Questタグ.isClick()){ activeScene = &sceneQuest; }
            if (Freeタグ.isClick()){ activeScene = &sceneFree; }
            if (Replayタグ.isClick())
            { 
                sceneReplay.LoadReplay();
                activeScene = &sceneReplay;
            }
            if (Archiveタグ.isClick()){ activeScene = &sceneArchive; }
            if (Skillタグ.isClick()){ activeScene = &sceneSkill; }
            if (Helpタグ.isClick()){ activeScene = &sceneHelp; }
            if (Configタグ.isClick()){ activeScene = &sceneConfig; }

            if (activeScene)
            {
                activeScene->Update();
            }

            if (Input::key.Escape.on)
            {
                this->isEnd = true;
            }

        }

        void DrawTag(UI_Button &タグ, const char* 文字列 , bool isBig )
        {
            MIcon::UI[IconType::マナ].DrawRotate( タグ.rect.GetCenter(), 1+isBig, 0);
            MFont::fontS[FontType::BMP黒].DrawRotate( タグ.rect.GetCenter() + Point(0,15) , 1 , 0, Color::White, 文字列);
        }

        //描画
        void Draw() override
        {
#ifdef _DEBUG			
            if (Input::key.Return.on){ LoadGUI(); }
#endif
            //枠部分の表示
            //@Draw
			MSystem::frameS[全体枠.frameNo].Draw(全体枠.rect);
			MSystem::frameS[Storyタグ.frameNo].Draw(Storyタグ.rect);
			MSystem::frameS[Questタグ.frameNo].Draw(Questタグ.rect);
			MSystem::frameS[Freeタグ.frameNo].Draw(Freeタグ.rect);
			MSystem::frameS[Replayタグ.frameNo].Draw(Replayタグ.rect);
			MSystem::frameS[Archiveタグ.frameNo].Draw(Archiveタグ.rect);
			MSystem::frameS[Skillタグ.frameNo].Draw(Skillタグ.rect);
			MSystem::frameS[Helpタグ.frameNo].Draw(Helpタグ.rect);
			MSystem::frameS[Configタグ.frameNo].Draw(Configタグ.rect);
            //@End
            //アイコンと文字の表示
            DrawTag(Storyタグ, "Story", activeScene == &sceneStory);
            DrawTag(Questタグ, "Quest", activeScene == &sceneQuest);
            DrawTag(Freeタグ, "Free", activeScene == &sceneFree);
            DrawTag(Replayタグ, "Replay", activeScene == &sceneReplay);
            DrawTag(Archiveタグ, "Archive", activeScene == &sceneArchive);
            DrawTag(Skillタグ, "Skill", activeScene == &sceneSkill);
            DrawTag(Helpタグ, "Help", activeScene == &sceneHelp);
            DrawTag(Configタグ, "Config", activeScene == &sceneConfig);

            if (activeScene)
            {
                activeScene->Draw();
            }
        }

        void LoadGUI() override
        {
#ifndef _DEBUG
            return;
#endif
            //@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneMenu", GUI_Factory);

			全体枠 = *dynamic_cast<UI_Frame*>(guiData.dataS[0].get());
			Storyタグ = *dynamic_cast<UI_Button*>(guiData.dataS[1].get());
			Questタグ = *dynamic_cast<UI_Button*>(guiData.dataS[2].get());
			Freeタグ = *dynamic_cast<UI_Button*>(guiData.dataS[3].get());
			Replayタグ = *dynamic_cast<UI_Button*>(guiData.dataS[4].get());
			Archiveタグ = *dynamic_cast<UI_Button*>(guiData.dataS[5].get());
			Skillタグ = *dynamic_cast<UI_Button*>(guiData.dataS[6].get());
			Helpタグ = *dynamic_cast<UI_Button*>(guiData.dataS[7].get());
			Configタグ = *dynamic_cast<UI_Button*>(guiData.dataS[8].get());
            //@End
        }
    };
}
