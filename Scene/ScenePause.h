//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX_TD
{
	using namespace SDX;

	/**サブウィンドウ的に呼び出す.*/
	class ScenePause : public SDX::IScene
	{
	public:
		//@Define
		UI_Button あきらめる = { 79, {210,300,220,50} , 0.000000,3};
		UI_Button やり直す = { 80, {210,220,220,50} , 0.000000,3};
		UI_Button 続ける = { 81, {210,140,220,50} , 0.000000,3};
		//@End

		int buttonNo;//0,1,2,あきらめ、やり直す、続ける

		static int Call()
		{
			static ScenePause single;
			single.isEnd = false;

			do
			{
				single.Update();
				single.Draw();
			} while (System::Update(true) && !single.isEnd);

			return single.buttonNo;
		}

		ScenePause()
		{
			LoadGUI();
			Init();
		}

		//更新
		void Update() override
		{
			if(あきらめる.isClick())			
			{
				buttonNo = 0;
				isEnd = true;
			}
			if(やり直す.isClick())
			{
				buttonNo = 1;
				isEnd = true;
			}
			if(続ける.isClick())
			{
				buttonNo = 2;
				isEnd = true;
			}
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			Screen::SetBright(Color::Gray);
			SStage->Draw();
			Screen::SetBright(Color::White);

			あきらめる.DrawText(MFont::fontS[1], "あきらめる", 2 , Color::Black);
			やり直す.DrawText(MFont::fontS[1], "やり直す", 2, Color::Black);
			続ける.DrawText(MFont::fontS[1], "続ける", 2, Color::Black);

		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "ScenePause", GUI_Factory);

			あきらめる = *dynamic_cast<UI_Button*>(guiData.dataS[0].get());
			やり直す = *dynamic_cast<UI_Button*>(guiData.dataS[1].get());
			続ける = *dynamic_cast<UI_Button*>(guiData.dataS[2].get());
			//@End
		}
	};
}
