//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"
#include "../Stage/IStage.h"
#include "../Struct/ReplayData.h"

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

        bool isRetry;//どのボタンでResult画面を抜けたか
        int baseScore;
        double bonusRate;
        double diffRate;
        double lifeBonus;
        int totalScore;
        int getEXP;
		int Lv上昇量;
        ResultType 結果;

        static bool Call()
        {
            static SceneResult single;
            single.Init();

            do
            {
                single.Update();
                single.Draw();
            } while (System::Update(true) && !single.isEnd);

            return single.isRetry;
        }

        SceneResult()
        {
            LoadGUI();
        }

        //初期化
        void Init() override
        {
            isEnd = false;
            isリプレイ保存済み = false;

            diffRate = 1 + DifficultyDataS[TDSystem::難易度].スコア補正;
            bonusRate = std::min( Witch::Hp / Witch::最大Hp + 1.0 , 2.0);

			if (Witch::Hp >= Witch::最大Hp)
			{
				結果 = ResultType::Perfect;
				is勝利 = true;
			}
			else if (Witch::Hp > 0)
			{
				結果 = ResultType::Win;
				is勝利 = true;
			}
			else
			{
				結果 = ResultType::Lose;
				is勝利 = false;
			}

            if (Witch::Hp == Witch::最大Hp)
            {
                bonusRate = 3.0;
            }
            else if ( Witch::Hp <= 0)
            {
                //敗北時はボーナス半減
                bonusRate = 0.5;
            }

            baseScore = SStage->score;
            totalScore = int(SStage->score * diffRate * bonusRate);
			Lv上昇量 = 0;
			getEXP = 0;

			//以降の処理は非リプレイ時のみ
			if (SStage->isReplay){ return; }
			//スコアの更新と経験値の獲得
			//5% + 更新分
	        getEXP = totalScore / 20;//5%
			getEXP += StageDataS[TDSystem::選択ステージ].Update(Witch::Main->種類 , totalScore , 結果);
			if (TDSystem::isカップル)
			{
				getEXP += StageDataS[TDSystem::選択ステージ].Update(Witch::Sub->種類, totalScore, 結果);
			}

			TDSystem::経験値 += getEXP;

			Lv上昇量 = TDSystem::CheckLVUp();

			//クリア時にリプレイAutoSave
			if (TDSystem::isリプレイ保存 && is勝利 == true)
			{
				SStage->SaveReplay(結果, totalScore);
				isリプレイ保存済み = true;
			}
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
                if ( !isリプレイ保存済み )
                {
                    SStage->SaveReplay(結果, totalScore);
					isリプレイ保存済み = true;
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
            SStage->Draw();
            Screen::SetBright(Color::White);

            //@todo とりあえず一気に表示、演出は修正するかも

            //Draw
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

            Result.DrawText(MFont::fontS[2], ReplayData::結果名[(int)結果], 2);

			MFont::fontS[最終スコア.fontNo].DrawRotate(最終スコア.rect.GetCenter(), 1, 0, Color::White, { 最終スコア.text ,std::setw(10), totalScore});
			MFont::fontS[撃破スコア.fontNo].DrawRotate(撃破スコア.rect.GetCenter(), 1, 0, Color::White, { 撃破スコア.text, std::setw(10) , baseScore});
			MFont::fontS[難易度補正.fontNo].DrawRotate(難易度補正.rect.GetCenter(), 1, 0, Color::White, { 難易度補正.text , " x " , diffRate });
			MFont::fontS[体力補正.fontNo].DrawRotate(体力補正.rect.GetCenter(), 1, 0, Color::White, { 体力補正.text , " x " , bonusRate });
			MFont::fontS[獲得経験値.fontNo].DrawRotate(獲得経験値.rect.GetCenter(), 1, 0, Color::White, { 獲得経験値.text  , std::setw(10) , getEXP});

			if (Lv上昇量 > 0)
			{
				MFont::fontS[獲得経験値.fontNo].DrawRotate(獲得経験値.rect.GetCenter() + Point(0,20), 1, 0, Color::White, "Lv Up");
			}

            //End
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
