//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX_TD
{
	using namespace SDX;

	class SceneHelpSub : public SDX::IScene
	{
	public:
		//@Define
		UI_Frame 全体枠 = { 356, {50,20,540,440} , 0.000000,5};
		UI_Text ヘルプ題名 = { 374, {55,25,527,20} , 0.000000,1,"std::string"};
		//@End
		IScene* 親画面;
		HelpData* 情報;

		SceneHelpSub()
		{
			LoadGUI();
			Init();
		}

		static bool Call(IScene* 元画面 , int ヘルプ番号)
		{
			static SceneHelpSub single;
			single.Init();
			single.親画面 = 元画面;
			single.情報 = &HelpDataS[ヘルプ番号];

			do
			{
				single.Update();
				single.Draw();
			} while (System::Update(true) && !single.isEnd);

			return true;
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
			//クリックで元の画面に戻る
			if (Input::mouse.Left.on )
			{
				this->isEnd = true;
				return;
			}
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			//元画面を薄暗く表示
            Director::IsDraw() = true;
			親画面->Draw();
			Drawing::Rect(Window::GetSize(), { 0,0,0,64 });

			//Draw
			MSystem::frameS[全体枠.frameNo].Draw(全体枠.rect);
			MFont::fontS[ヘルプ題名.fontNo].DrawRotate(ヘルプ題名.rect.GetCenter(),1,0,Color::White,ヘルプ題名.text);
			//End
			//あればヘルプ画像を表示
			if (情報->説明画像)
			{
				情報->説明画像->Draw({ 40,40 });
				MFont::fontS[FontType::ゴシック小].Draw({ 40 + 情報->説明画像->GetHeight(),40 }, Color::White, 情報->説明文);
			}
			else
			{
				MFont::fontS[FontType::ゴシック小].Draw({ 40,40 }, Color::White, 情報->説明文);
			}
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneHelpSub", GUI_Factory);

			全体枠 = *dynamic_cast<UI_Frame*>(guiData.dataS[0].get());
			ヘルプ題名 = *dynamic_cast<UI_Text*>(guiData.dataS[1].get());
			//@End
		}
	};
}
