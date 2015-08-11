//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"
#include "../System/TDSystem.h"

namespace SDX_TD
{
	using namespace SDX;

	class SceneArchive : public SDX::IScene
	{
	public:
		//Define
		UI_Frame 項目枠1 = { 285, {64,64,280,409} , 0.000000,5};
		UI_Frame 項目枠2 = { 293,{ 350,64,280,409 } , 0.000000,5 };
		UI_Button タブ0 = { 291, {64,3,55,55} , 0.000000,3};
		UI_Button タブ1 = { 295, {121,3,55,55} , 0.000000,3};
		UI_Button タブ2 = { 296, {178,3,55,55} , 0.000000,3};
		UI_Button タブ3 = { 297, {235,3,55,55} , 0.000000,3};
		UI_Button タブ5 = { 299, {349,3,55,55} , 0.000000,3};
		UI_Button タブ6 = { 300, {406,3,55,55} , 0.000000,3};
		UI_Button タブ4 = { 301, {292,3,55,55} , 0.000000,3};
		UI_Button タブ7 = { 302, {463,3,55,55} , 0.000000,3};
		UI_Button タブ8 = { 305, {520,3,55,55} , 0.000000,3};
		UI_Button タブ9 = { 306, {577,3,55,55} , 0.000000,3};
		UI_Text ランクアイコン = { 307, {68,75,31,23} , 0.000000,1,"std::string"};
		UI_Text 項目名 = { 332, {109,75,114,23} , 0.000000,1,"std::string"};
		UI_Text 記録 = { 333, {234,75,100,23} , 0.000000,1,"std::string"};
		//End
		int tabNo = 0;

		SceneArchive()
		{
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
			//ページ切り替えのみ？
			//カーソル合わせたらヘルプとか、条件表示とか？
			//Update
			if (タブ0.isClick()) { tabNo = 0; }
			if(タブ1.isClick()){ tabNo = 1; }
			if(タブ2.isClick()){ tabNo = 2; }
			if(タブ3.isClick()){ tabNo = 3; }
			if(タブ5.isClick()){ tabNo = 4; }
			if(タブ6.isClick()){ tabNo = 5; }
			if(タブ4.isClick()){ tabNo = 6; }
			if(タブ7.isClick()){ tabNo = 7; }
			if(タブ8.isClick()){ tabNo = 8; }
			if(タブ9.isClick()){ tabNo = 9; }
			//End
		}

		//描画
		void Draw() override
		{
			DrawScore(tabNo * 2 , false);
			DrawScore(tabNo * 2 + 1, true);

			//タブ部分の描画、選択中のタブは表示を変える
			for (int a = 0;a < 10;++a)
			{

			}

			//Draw
			MSystem::frameS[項目枠1.frameNo].Draw(項目枠1.rect);
			MSystem::frameS[項目枠2.frameNo].Draw(項目枠2.rect);
			MSystem::frameS[タブ0.frameNo].Draw(タブ0.rect);
			MSystem::frameS[タブ1.frameNo].Draw(タブ1.rect);
			MSystem::frameS[タブ2.frameNo].Draw(タブ2.rect);
			MSystem::frameS[タブ3.frameNo].Draw(タブ3.rect);
			MSystem::frameS[タブ5.frameNo].Draw(タブ5.rect);
			MSystem::frameS[タブ6.frameNo].Draw(タブ6.rect);
			MSystem::frameS[タブ4.frameNo].Draw(タブ4.rect);
			MSystem::frameS[タブ7.frameNo].Draw(タブ7.rect);
			MSystem::frameS[タブ8.frameNo].Draw(タブ8.rect);
			MSystem::frameS[タブ9.frameNo].Draw(タブ9.rect);
			//End
		}

		void DrawScore(int ページ番号 ,bool 右ページ)
		{
			static TDSystem::RecordData 実績[14];
			TDSystem::RecordData *dataS[14];

			switch (ページ番号)
			{
			case 0://実績関連、このページだけ特殊
				

				break;
			case 1://全体記録
				dataS[0] = &TDSystem::プレイ秒数;
				dataS[1] = &TDSystem::合計スキルLv;//仕様変更も検討
				dataS[2] = &TDSystem::合計Wave;//Stageで処理
				dataS[3] = &TDSystem::合計獲得資金;//Enemyで処理
				dataS[4] = &TDSystem::合計消費資金;//Unitで処理
				dataS[5] = &TDSystem::合計回収回数;//Unitで処理
				dataS[6] = &TDSystem::合計仕事回数;//Unitで処理
				dataS[7] = &TDSystem::合計獲得EXP;//SceneResultで処理
				dataS[8] = &TDSystem::ザコ撃破数;//Enemyで処理
				dataS[9] = &TDSystem::ボス撃破数;//Enemyで処理
				dataS[10] = &TDSystem::シングル総スコア;//StageDataで計算
				dataS[11] = &TDSystem::タッグ総スコア;//StageDataで計算
				dataS[12] = &TDSystem::クエスト銀星数;//StageDataで計算
				dataS[13] = &TDSystem::クエスト金星数;//StageDataで計算
				break;
			case 2://ウィッチ個別記録
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
				dataS[0] = &TDSystem::クリア回数[WitchType(ページ番号 - 2)];
				dataS[1] = &TDSystem::パーフェクト回数[WitchType(ページ番号 - 2)];
				dataS[2] = &TDSystem::大魔法回数[WitchType(ページ番号 - 2)];
				for (int a = 0,b=3;a < 12;++a)
				{
					if (ページ番号 - 2 == a) { continue; }
					dataS[b] = &TDSystem::タッグ回数[WitchType(ページ番号 - 2)][WitchType(a)];
					++b;
				}
				break;
			case 14://各種ユニット配置回数
			case 15:
			case 16:
				for (int a = 0;a < 14;++a)
				{
					dataS[a] = &TDSystem::配置回数[UnitType(a+(ページ番号-14)*14)];
				}
				break;
			case 17://各種ユニット強化回数
			case 18:
			case 19:
				for (int a = 0;a < 14;++a)
				{
					dataS[a] = &TDSystem::強化回数[UnitType(a + (ページ番号 - 17) * 14)];
				}
				break;
			}

			Point posI = ランクアイコン.rect.GetPoint();
			Point posN = 項目名.rect.GetPoint();
			Point posR = 記録.rect.GetPoint();

			if (右ページ)
			{
				posI.Move(300, 0);
				posN.Move(300, 0);
				posR.Move(300, 0);
			}

			for (int a = 0;a < 14;++a)
			{
				//達成度アイコン
				MFont::fontS[ランクアイコン.fontNo].DrawRotate(ランクアイコン.rect.GetCenter(), 1, 0, Color::White, ランクアイコン.text);

				//項目名
				MFont::fontS[項目名.fontNo].DrawRotate(項目名.rect.GetCenter(), 1, 0, Color::White, 項目名.text);

				//記録
				if (ページ番号 == 1 && a == 0)
				{
					//時刻だけ変換して表示
					MFont::fontS[記録.fontNo].DrawRotate(記録.rect.GetCenter(), 1, 0, Color::White, 記録.text);
				}
				else
				{
					MFont::fontS[記録.fontNo].DrawRotate(記録.rect.GetCenter(), 1, 0, Color::White, 記録.text);
				}

				posI.Move(0, 25);
				posN.Move(0, 25);
				posR.Move(0, 25);
			}
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneArchive", GUI_Factory);

			項目枠1 = *dynamic_cast<UI_Frame*>(guiData.dataS[0].get());
			タブ0 = *dynamic_cast<UI_Button*>(guiData.dataS[1].get());
			項目枠2 = *dynamic_cast<UI_Frame*>(guiData.dataS[2].get());
			タブ1 = *dynamic_cast<UI_Button*>(guiData.dataS[3].get());
			タブ2 = *dynamic_cast<UI_Button*>(guiData.dataS[4].get());
			タブ3 = *dynamic_cast<UI_Button*>(guiData.dataS[5].get());
			タブ5 = *dynamic_cast<UI_Button*>(guiData.dataS[6].get());
			タブ6 = *dynamic_cast<UI_Button*>(guiData.dataS[7].get());
			タブ4 = *dynamic_cast<UI_Button*>(guiData.dataS[8].get());
			タブ7 = *dynamic_cast<UI_Button*>(guiData.dataS[9].get());
			タブ8 = *dynamic_cast<UI_Button*>(guiData.dataS[10].get());
			タブ9 = *dynamic_cast<UI_Button*>(guiData.dataS[11].get());
			ランクアイコン = *dynamic_cast<UI_Text*>(guiData.dataS[12].get());
			項目名 = *dynamic_cast<UI_Text*>(guiData.dataS[13].get());
			記録 = *dynamic_cast<UI_Text*>(guiData.dataS[14].get());
			//@End
		}
	};
}
