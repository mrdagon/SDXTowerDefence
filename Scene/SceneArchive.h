//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX
{
	using namespace SDX;

	class SceneArchive : public SDX::IScene
	{
	public:
		//@Define
		UI_Text 実装中～ = { 104, {204,181,295,105} , 0.000000,0,"実装中"};
		//@End

		SceneArchive()
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
			fontS[実装中～.fontNo]->Draw(実装中～.rect.GetPoint(),Color::White,実装中～.text);
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneArchive", GUI_Factory);

			実装中～ = *dynamic_cast<UI_Text*>(guiData.dataS[0].get());
			//@End
		}
	};
}
