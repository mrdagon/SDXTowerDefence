//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <SDXFrameWork.h>

namespace SDX
{
	class QuestScene : public IScene
	{
	public:
		//@Define
		GUI_Text 題字 = { {26,27,575,39},10,"こんにちは"};
		GUI_Frame 外枠 = { {11,12,611,301},1};
		GUI_Button キャンセルボタン = { {194,231,108,53},1};
		GUI_Button OKボタン = { {351,229,111,56},0};
		GUI_Image ねずみ = { {22,220,0,0},11};
		GUI_Image 剣 = { {480,174,0,0},3};
		GUI_Image ひよこ = { {185,193,0,0},12};
		GUI_Image くま = { {525,228,0,0},14};
		GUI_Image にわとり = { {330,178,0,0},13};
		GUI_Image 短剣 = { {149,165,0,0},2};
		//@End

		QuestScene()
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
			//@End
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (!Input::key.Return.on){ LoadGUI(); }
#endif
			//@Draw
			//fontS[題字.fontNo].Draw(題字.rect,題字.text);
			//frameS[外枠.frameNo].Draw(外枠.rect);
			//frameS[キャンセルボタン.frameNo].Draw(キャンセルボタン.rect);
			//frameS[OKボタン.frameNo].Draw(OKボタン.rect);
			//imageS[ねずみ.gID].Draw(ねずみ.rect.GetCenter());
			//imageS[剣.gID].Draw(剣.rect.GetCenter());
			//imageS[ひよこ.gID].Draw(ひよこ.rect.GetCenter());
			//imageS[くま.gID].Draw(くま.rect.GetCenter());
			//imageS[にわとり.gID].Draw(にわとり.rect.GetCenter());
			//imageS[短剣.gID].Draw(短剣.rect.GetCenter());
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG			
			return;
#endif
			//@Load
			GUIData guiData = TMXtoGUI("template.tmx", "QuestScene", GUI_Factory);

			題字 = *dynamic_cast<GUI_Text*>(guiData.dataS[0].get());
			外枠 = *dynamic_cast<GUI_Frame*>(guiData.dataS[1].get());
			キャンセルボタン = *dynamic_cast<GUI_Button*>(guiData.dataS[2].get());
			OKボタン = *dynamic_cast<GUI_Button*>(guiData.dataS[3].get());
			ねずみ = *dynamic_cast<GUI_Image*>(guiData.dataS[4].get());
			剣 = *dynamic_cast<GUI_Image*>(guiData.dataS[5].get());
			ひよこ = *dynamic_cast<GUI_Image*>(guiData.dataS[6].get());
			くま = *dynamic_cast<GUI_Image*>(guiData.dataS[7].get());
			にわとり = *dynamic_cast<GUI_Image*>(guiData.dataS[8].get());
			短剣 = *dynamic_cast<GUI_Image*>(guiData.dataS[9].get());
			//@End
		}
	};
}
