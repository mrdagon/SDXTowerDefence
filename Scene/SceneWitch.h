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

		WitchType pointWitch;//マウスが乗ってるウィッチ
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
		UI_Button ライナ = { 211, {195,82,40,40} , 0.000000,1};
		UI_Button 決定 = { 212, {185,363,160,40} , 0.000000,3};
		UI_Button ルコウ = { 213, {195,126,40,40} , 0.000000,1};
		UI_Button ロチエ = { 216, {250,126,40,40} , 0.000000,1};
		UI_Button ミナエ = { 217, {250,82,40,40} , 0.000000,1};
		UI_Button 委員長 = { 218, {305,126,40,40} , 0.000000,1};
		UI_Button フィオナ = { 219, {305,82,40,40} , 0.000000,1};
		UI_Button ディアネラ = { 220, {359,126,40,40} , 0.000000,1};
		UI_Button トレニア = { 221, {415,82,40,40} , 0.000000,1};
		UI_Button ミルラ = { 222, {470,126,40,40} , 0.000000,1};
		UI_Button バロゥ = { 223, {415,126,40,40} , 0.000000,1};
		UI_Button ナズナ = { 224, {470,82,40,40} , 0.000000,1};
		UI_Button ナツメ = { 225, {360,82,40,40} , 0.000000,1};
		UI_Button 説明枠 = { 244, {179,295,342,50} , 0.000000,1};
		UI_Button キャンセル = { 352, {357,363,160,40} , 0.000000,3};
		UI_Button 大魔法枠 = { 354, {179,235,342,50} , 0.000000,1};
		UI_Button ユニット枠 = { 355, {179,175,342,50} , 0.000000,1};
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
			if (ライナ.rect.Hit( &Input::mouse.GetPoint() )){ pointWitch = WitchType::ライナ; } else 
			if (ルコウ.rect.Hit( &Input::mouse.GetPoint() )){ pointWitch = WitchType::ルコウ; } else 
			if (ロチエ.rect.Hit( &Input::mouse.GetPoint() )){ pointWitch = WitchType::ロチエ; } else 
			if (ミナエ.rect.Hit( &Input::mouse.GetPoint() )){ pointWitch = WitchType::ミナエ; } else 
			if (委員長.rect.Hit( &Input::mouse.GetPoint() )){ pointWitch = WitchType::委員長; } else 
			if (フィオナ.rect.Hit( &Input::mouse.GetPoint() )){ pointWitch = WitchType::フィオナ; } else 
			if (ディアネラ.rect.Hit( &Input::mouse.GetPoint() )){ pointWitch = WitchType::ディアネラ; } else
			if (トレニア.rect.Hit( &Input::mouse.GetPoint() )){ pointWitch = WitchType::トレニア; } else 
			if (ミルラ.rect.Hit( &Input::mouse.GetPoint() )){ pointWitch = WitchType::ミルラ; } else 
			if (バロゥ.rect.Hit( &Input::mouse.GetPoint() )){ pointWitch = WitchType::バロゥ; } else 
			if (ナズナ.rect.Hit( &Input::mouse.GetPoint() )){ pointWitch = WitchType::ナズナ; } else 
			if (ナツメ.rect.Hit( &Input::mouse.GetPoint() )){ pointWitch = WitchType::ナツメ; } else 
			{ pointWitch = WitchType::COUNT; }

			if (pointWitch != WitchType::COUNT && Input::mouse.Left.on )
			{
				ChangeWitch(pointWitch);
			}

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
			MUnit::味方[(UnitType)種類][2]->DrawRotate( pt ,2,0 );
			//名前
			//MFont::fontS[1].DrawRotate( pt + Point(20,0) , 1, 0, Color::White, WitchDataS[種類].名前);

		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			//Screen::SetBright({ 64,64,64 });
			Director::GetScene(0)->Draw();
			Drawing::Rect(Window::GetSize(), { 0,0,0,64 });
			//Screen::SetBright(Color::White);

			//Draw
			MSystem::frameS[全体枠.frameNo].Draw(全体枠.rect);
			キャンセル.DrawText(MFont::fontS[2], "Cancel" , 2);
			if ( first == WitchType::COUNT || (TDSystem::isカップル && second == WitchType::COUNT)){ Screen::SetBright(Color::Gray); }
			決定.DrawText(MFont::fontS[2], "OK" , 2);
			Screen::SetBright();
			//End

			説明枠.Draw();
			大魔法枠.Draw();
			ユニット枠.Draw();
			MFont::fontS[FontType::BMP黒].Draw(ユニット枠.rect.GetPoint() + Point(4,4), Color::White, "Unit");
			MFont::fontS[FontType::BMP黒].Draw(大魔法枠.rect.GetPoint() + Point(4, 4), Color::White, "Ultimate");
			MFont::fontS[FontType::BMP黒].Draw(説明枠.rect.GetPoint() + Point(4, 4), Color::White, "Passive");

			if (pointWitch != WitchType::COUNT)
			{

				//使用可能ウィッチ
				Point pt = ユニット枠.rect.GetPoint();
				pt.Move(22, 30);

				for (int a = 1; a < 12; ++a)
				{
					MUnit::味方[WitchDataS[pointWitch].職種[a]][1]->DrawRotate(pt,2,0);
					pt.Move(30, 0);
				}

				//パッシブ効果
				MFont::fontS[FontType::ゴシック小].Draw(説明枠.rect.GetPoint(),Color::White,WitchDataS[pointWitch].パッシブ説明);

				//大魔法説明
				MFont::fontS[FontType::ゴシック小].Draw(大魔法枠.rect.GetPoint(), Color::White, WitchDataS[pointWitch].大魔法説明);

			}

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
			説明枠 = *dynamic_cast<UI_Button*>(guiData.dataS[14].get());
			キャンセル = *dynamic_cast<UI_Button*>(guiData.dataS[15].get());
			大魔法枠 = *dynamic_cast<UI_Button*>(guiData.dataS[16].get());
			ユニット枠 = *dynamic_cast<UI_Button*>(guiData.dataS[17].get());
			//@End
		}
	};
}
