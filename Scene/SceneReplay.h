//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"
#include "../Struct/ReplayData.h"

namespace SDX_TD
{
    using namespace SDX;

    class SceneReplay : public SDX::IScene
    {
    public:
        //@Define
		UI_Frame リプレイ情報 = { 127, {362,302,276,110} , 0.000000,5};
		UI_Button 開始 = { 128, {365,414,272,60} , 0.000000,3};
		UI_Text スコア = { 129, {510,390,100,15} , 0.000000,0,"score"};
		UI_ScrollBar スクロールバー = { 132, {320,52,36,374} , 0.000000,4};
		UI_Frame マップ情報 = { 133, {362,2,276,300} , 0.000000,5};
		UI_Button リプレイ選択 = { 135, {67,9,248,40} , 0.000000,1};
		UI_Text ウィッチ = { 139, {535,330,50,15} , 0.000000,0,"std::string"};
		UI_Text トライアル = { 142, {510,310,50,15} , 0.000000,0,"Difficulty"};
		UI_Text 結果 = { 144, {510,370,100,15} , 0.000000,0,"Perfect"};
		UI_Frame ステージ一覧 = { 145, {62,2,300,476} , 0.000000,5};
		UI_Button 下スクロール = { 146, {318,434,40,40} , 0.000000,3};
		UI_Button 上スクロール = { 148, {318,6,40,40} , 0.000000,3};
		UI_Text 難易度 = { 246, {510,350,100,15} , 0.000000,0,"Difficulty"};
		UI_Text カップル = { 248, {560,310,50,15} , 0.000000,0,"Difficulty"};
        //@End
        unsigned int replayNo = 0;
        std::vector<ReplayData> replayS;

        const static std::string 項目名[5];

        /**リプレイデータ一覧の再読み込み.*/
        void LoadReplay()
        {
            replayS.clear();

			auto strS = Directory::GetFileName( "replay" );

			//リプレイ一覧の読み込み
			for ( auto &it : strS )
			{
				if (it.find(".rep") == std::string::npos) { continue; }

				ReplayData buf;
				buf.SaveOrLoad( it.c_str(), true, FileMode::Read);
				replayS.push_back( buf );
			}

            スクロールバー.SetSize(replayS.size(), 11);
            
            //y座標の差 0～スクロールバーの高さ
            if (replayNo >= replayS.size())
            {
                replayNo = 0;
            }
        }

        SceneReplay()
        {
            LoadGUI();
            Init();
        }

        //更新
        void Update() override
        {
            //Update
			if ( replayNo < replayS.size() && 開始.isClick() && StageDataS.count(replayS[replayNo].ステージ名))
            {
                auto buf = Witch::スキルLv;
				if (replayS[replayNo].SaveOrLoad(replayS[replayNo].ファイル名.c_str(), false, FileMode::Read))
				{
					Stage::Call(true, &replayS[replayNo]);
					Witch::スキルLv = buf;
				}
            }
            if (replayS.size() )
            {
                スクロールバー.Update();
            }
            
            if(下スクロール.isClick())
            {
                スクロールバー.AddIndex(1);
            }
            if(上スクロール.isClick())
            {
                スクロールバー.AddIndex(-1);
            }

            if ( !Input::mouse.Left.on){ return; }

            Rect buf = リプレイ選択.rect;

            for (int a = 0; a < std::min((int)replayS.size(), 11); ++a)
            {
                if (buf.Hit( &Input::mouse.GetPoint()))
                {
                    replayNo = a + スクロールバー.scrIndex;
                }
                buf.y += 42;
            }
            //End
        }

        //描画
        void Draw() override
        {
#ifdef _DEBUG			
            if (Input::key.Return.on){ LoadGUI(); }
#endif
            //右側
            MSystem::frameS[マップ情報.frameNo].Draw(マップ情報.rect);
            MSystem::frameS[リプレイ情報.frameNo].Draw(リプレイ情報.rect);
            開始.DrawText(MFont::fontS[2], "Start", 2);

            if ( replayS.size() > 0)
            {
                ReplayData &buf = replayS[replayNo];

                for (int a = 0; a < 5; ++a)
                {
                    MFont::fontS[2].DrawRotate(トライアル.rect.GetCenter() + Point(-100, a * 20), 1, 0, Color::White, 項目名[a]);
                }

                MFont::fontS[2].DrawRotate(スコア.rect.GetCenter(), 1, 0, Color::White, { std::setw(8) , buf.スコア });

                if (buf.isカップル)
                {                    
                    MUnit::魔女[(UnitType)buf.メイン][1]->DrawRotate(ウィッチ.rect.GetCenter() - Point(10,0), 1, 0);
                    MUnit::魔女[(UnitType)buf.サブ][1]->DrawRotate(ウィッチ.rect.GetCenter() + Point(10, 0), 1, 0);
                }
                else
                {
                    MUnit::魔女[(UnitType)buf.メイン][1]->DrawRotate(ウィッチ.rect.GetCenter(), 1, 0);
                }

                MFont::fontS[2].DrawRotate(難易度.rect.GetCenter(), 1, 0, Color::White, DifficultyDataS[buf.難易度].名前);

                MFont::fontS[2].DrawRotate(結果.rect.GetCenter(), 1, 0, Color::White, ReplayData::結果名[(int)buf.結果]);
                MFont::fontS[2].DrawRotate(カップル.rect.GetCenter(), 1, 0, Color::White, (buf.isカップル)?"○Couple":"×Couple");
                MFont::fontS[2].DrawRotate(トライアル.rect.GetCenter(), 1, 0, Color::White, (buf.isトライアル) ? "○Trial" : "×Trial");
                
                if (StageDataS.count( buf.ステージ名))
                {
                    StageDataS[buf.ステージ名].DrawMinimap(マップ情報.rect.GetCenter() - Point(0,15) );
                }
            }
            //左側
            MSystem::frameS[ステージ一覧.frameNo].Draw(ステージ一覧.rect);
            MSystem::frameS[下スクロール.frameNo].Draw(下スクロール.rect);
            MSystem::frameS[上スクロール.frameNo].Draw(上スクロール.rect);
            スクロールバー.Draw();

            MSystem::矢印[2].DrawRotate(上スクロール.rect.GetCenter(), 2, 0);
            MSystem::矢印[3].DrawRotate(下スクロール.rect.GetCenter(), 2, 0);

            //End

            Rect buf = リプレイ選択.rect;

            for (int a = 0; a < std::min( (int)replayS.size(),11); ++a)
            {
                if (a + スクロールバー.scrIndex == replayNo){ Screen::SetBright(Color::Red); }
                MSystem::frameS[リプレイ選択.frameNo].Draw( buf );
                MFont::fontS[1].DrawRotate(buf.GetCenter(), 1, 0, Color::White, replayS[a + スクロールバー.scrIndex].ファイル名);
                Screen::SetBright();
                buf.y += 42;
            }
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
			スクロールバー = *dynamic_cast<UI_ScrollBar*>(guiData.dataS[3].get());
			マップ情報 = *dynamic_cast<UI_Frame*>(guiData.dataS[4].get());
			リプレイ選択 = *dynamic_cast<UI_Button*>(guiData.dataS[5].get());
			ウィッチ = *dynamic_cast<UI_Text*>(guiData.dataS[6].get());
			トライアル = *dynamic_cast<UI_Text*>(guiData.dataS[7].get());
			結果 = *dynamic_cast<UI_Text*>(guiData.dataS[8].get());
			ステージ一覧 = *dynamic_cast<UI_Frame*>(guiData.dataS[9].get());
			下スクロール = *dynamic_cast<UI_Button*>(guiData.dataS[10].get());
			上スクロール = *dynamic_cast<UI_Button*>(guiData.dataS[11].get());
			難易度 = *dynamic_cast<UI_Text*>(guiData.dataS[12].get());
			カップル = *dynamic_cast<UI_Text*>(guiData.dataS[13].get());
            //@End

            スクロールバー.SetSize(replayS.size(), 11);
        }
    };

    const std::string SceneReplay::項目名[5] =
    {
        "Mode",
        "Witch",
        "Difficulty",
        "Result",
        "Score"
    };

}
