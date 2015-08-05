//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX_TD
{
	using namespace SDX;

	class SceneShop : public SDX::IScene
	{
	public:
		//@Define
		UI_Frame 合計取得数枠 = { 264, {452,6,180,380} , 0.000000,5};
		UI_Frame Frame = { 311, {66,6,380,380} , 0.000000,5};
		UI_Frame 費用表示枠 = { 312, {66,392,565,80} , 0.000000,5};
		UI_Text 取得スキル欄 = { 313, {456,10,80,31} , 0.000000,1,"std::string"};
		UI_Text 消費魔石 = { 317, {487,397,24,24} , 0.000000,1,"std::string"};
		UI_Text スキル名 = { 318, {72,399,24,24} , 0.000000,1,"std::string"};
		UI_Text Text = { 319, {72,429,24,24} , 0.000000,1,"std::string"};
		UI_Text 所持魔石 = { 321, {356,399,24,24} , 0.000000,1,"std::string"};
		//@End

		SceneShop()
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
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			//@Draw
			MSystem::frameS[合計取得数枠.frameNo].Draw(合計取得数枠.rect);
			MSystem::frameS[Frame.frameNo].Draw(Frame.rect);
			MSystem::frameS[費用表示枠.frameNo].Draw(費用表示枠.rect);
			MFont::fontS[取得スキル欄.fontNo].DrawRotate(取得スキル欄.rect.GetCenter(),1,0,Color::White,取得スキル欄.text);
			MFont::fontS[消費魔石.fontNo].DrawRotate(消費魔石.rect.GetCenter(),1,0,Color::White,消費魔石.text);
			MFont::fontS[スキル名.fontNo].DrawRotate(スキル名.rect.GetCenter(),1,0,Color::White,スキル名.text);
			MFont::fontS[Text.fontNo].DrawRotate(Text.rect.GetCenter(),1,0,Color::White,Text.text);
			MFont::fontS[所持魔石.fontNo].DrawRotate(所持魔石.rect.GetCenter(),1,0,Color::White,所持魔石.text);
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneShop", GUI_Factory);

			合計取得数枠 = *dynamic_cast<UI_Frame*>(guiData.dataS[0].get());
			Frame = *dynamic_cast<UI_Frame*>(guiData.dataS[1].get());
			費用表示枠 = *dynamic_cast<UI_Frame*>(guiData.dataS[2].get());
			取得スキル欄 = *dynamic_cast<UI_Text*>(guiData.dataS[3].get());
			消費魔石 = *dynamic_cast<UI_Text*>(guiData.dataS[4].get());
			スキル名 = *dynamic_cast<UI_Text*>(guiData.dataS[5].get());
			Text = *dynamic_cast<UI_Text*>(guiData.dataS[6].get());
			所持魔石 = *dynamic_cast<UI_Text*>(guiData.dataS[7].get());
			//@End
		}
	};
}
