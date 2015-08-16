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
	class SceneWitch : public SDX::IScene
	{
	public:
		WitchType first = WitchType::COUNT;
		WitchType second = WitchType::COUNT;

		bool isOK;//

		static SceneWitch& SelectWitch()
		{
			static SceneWitch single;
			single.isEnd = false;
			single.isOK = false;

			do
			{
				single.Update();
				single.Draw();
			} while (System::Update(true) && !single.isEnd);

			if(single.first != WitchType::COUNT )Witch::SetMain(single.first);
			if (single.second != WitchType::COUNT)Witch::SetSub(single.second);

			return single;
		}

	private:
		//@Define
		UI_Frame 全体枠 = { 210, {170,60,360,360} , 0.000000,5};
		UI_Button ライナ = { 211, {195,83,140,40} , 0.000000,1};
		UI_Button 決定 = { 212, {185,363,160,40} , 0.000000,3};
		UI_Button ルコウ = { 213, {195,127,140,40} , 0.000000,1};
		UI_Button ロチエ = { 216, {195,215,140,40} , 0.000000,1};
		UI_Button ミナエ = { 217, {195,171,140,40} , 0.000000,1};
		UI_Button 委員長 = { 218, {195,303,140,40} , 0.000000,1};
		UI_Button フィオナ = { 219, {195,259,140,40} , 0.000000,1};
		UI_Button ディアネラ = { 220, {366,127,140,40} , 0.000000,1};
		UI_Button トレニア = { 221, {366,171,140,40} , 0.000000,1};
		UI_Button ミルラ = { 222, {366,303,140,40} , 0.000000,1};
		UI_Button バロゥ = { 223, {366,215,140,40} , 0.000000,1};
		UI_Button ナズナ = { 224, {366,259,140,40} , 0.000000,1};
		UI_Button ナツメ = { 225, {367,83,140,40} , 0.000000,1};
		UI_Button キャンセル = { 244, {356,363,160,40} , 0.000000,3};
		//@End

		SceneWitch()
		{
			LoadGUI();
			Init();
		}

		void ChangeWitch(WitchType 種類)
		{
			if ( !TDSystem::isカップル)
			{
				first = 種類;
				return;
			}

			if (first == 種類)
			{
				first = second;
				second = WitchType::COUNT;
			}
			else if (second == 種類)
			{
				second = WitchType::COUNT;
			}
			else if (first == WitchType::COUNT)
			{
				first = 種類;
			}
			else
			{
				second = 種類;
			}
		}

		//更新
		void Update() override
		{
			//Update
			if (ライナ.isClick()){ ChangeWitch(WitchType::ライナ); }
			if (ルコウ.isClick()){ ChangeWitch(WitchType::ルコウ); }
			if (ロチエ.isClick()){ ChangeWitch(WitchType::ロチエ); }
			if (ミナエ.isClick()){ ChangeWitch(WitchType::ミナエ); }
			if (委員長.isClick()){ ChangeWitch(WitchType::委員長); }
			if (フィオナ.isClick()){ ChangeWitch(WitchType::フィオナ); }
			if (ディアネラ.isClick()){ ChangeWitch(WitchType::ディアネラ); }
			if (トレニア.isClick()){ ChangeWitch(WitchType::トレニア); }
			if (ミルラ.isClick()){ ChangeWitch(WitchType::ミルラ); }
			if (バロゥ.isClick()){ ChangeWitch(WitchType::バロゥ); }
			if (ナズナ.isClick()){ ChangeWitch(WitchType::ナズナ); }
			if (ナツメ.isClick()){ ChangeWitch(WitchType::ナツメ); }

			if( 決定.isClick() )
			{
				if (first != WitchType::COUNT && (!TDSystem::isカップル || second != WitchType::COUNT))
				{
					isOK = true;
					isEnd = true;
				}
			}
			if( キャンセル.isClick() )
			{
				isOK = false;
				isEnd = true;
			}
			//End
		}

		void DrawWB(UI_Button &ボタン , WitchType 種類)
		{
			Point pt = ボタン.rect.GetCenter();

			if (種類 == first)
			{
				Screen::SetBright(Color::Red);
				ボタン.Draw();
				Screen::SetBright(Color::White);
				if (TDSystem::isカップル){ MFont::fontS[2].Draw(ボタン.rect.GetPoint(), Color::White, "First"); }
			}
			else if (種類 == second && TDSystem::isカップル)
			{
				Screen::SetBright(Color::Red);
				ボタン.Draw();
				Screen::SetBright(Color::White);
				MFont::fontS[2].Draw(ボタン.rect.GetPoint(), Color::White, "Second");
			}
			else
			{
				ボタン.Draw();
			}

			//アイコン
			MUnit::味方[(UnitType)種類][2]->DrawRotate( pt - Point(50,0) ,2,0 );
			//名前
			MFont::fontS[1].DrawRotate( pt + Point(20,0) , 1, 0, Color::White, WitchDataS[種類].名前);

		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			Screen::SetBright(Color::Gray);
			Director::GetScene(0)->Draw();
			Screen::SetBright(Color::White);

			//Draw
			MSystem::frameS[全体枠.frameNo].Draw(全体枠.rect);
			キャンセル.DrawText(MFont::fontS[2], "Cancel" , 2);
			if ( first == WitchType::COUNT || (TDSystem::isカップル && second == WitchType::COUNT)){ Screen::SetBright(Color::Gray); }
			決定.DrawText(MFont::fontS[2], "OK" , 2);
			Screen::SetBright();
			//End

			DrawWB(ライナ,WitchType::ライナ);
			DrawWB(ルコウ,WitchType::ルコウ);
			DrawWB(ロチエ,WitchType::ロチエ);
			DrawWB(ミナエ,WitchType::ミナエ);
			DrawWB(委員長,WitchType::委員長);
			DrawWB(フィオナ,WitchType::フィオナ);
			DrawWB(ディアネラ,WitchType::ディアネラ);
			DrawWB(トレニア,WitchType::トレニア);
			DrawWB(ミルラ,WitchType::ミルラ);
			DrawWB(バロゥ,WitchType::バロゥ);
			DrawWB(ナズナ,WitchType::ナズナ);
			DrawWB(ナツメ,WitchType::ナツメ);
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneWitch", GUI_Factory);

			全体枠 = *dynamic_cast<UI_Frame*>(guiData.dataS[0].get());
			ライナ = *dynamic_cast<UI_Button*>(guiData.dataS[1].get());
			決定 = *dynamic_cast<UI_Button*>(guiData.dataS[2].get());
			ルコウ = *dynamic_cast<UI_Button*>(guiData.dataS[3].get());
			ロチエ = *dynamic_cast<UI_Button*>(guiData.dataS[4].get());
			ミナエ = *dynamic_cast<UI_Button*>(guiData.dataS[5].get());
			委員長 = *dynamic_cast<UI_Button*>(guiData.dataS[6].get());
			フィオナ = *dynamic_cast<UI_Button*>(guiData.dataS[7].get());
			ディアネラ = *dynamic_cast<UI_Button*>(guiData.dataS[8].get());
			トレニア = *dynamic_cast<UI_Button*>(guiData.dataS[9].get());
			ミルラ = *dynamic_cast<UI_Button*>(guiData.dataS[10].get());
			バロゥ = *dynamic_cast<UI_Button*>(guiData.dataS[11].get());
			ナズナ = *dynamic_cast<UI_Button*>(guiData.dataS[12].get());
			ナツメ = *dynamic_cast<UI_Button*>(guiData.dataS[13].get());
			キャンセル = *dynamic_cast<UI_Button*>(guiData.dataS[14].get());
			//@End
		}
	};
}
