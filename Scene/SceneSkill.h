//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX
{
	using namespace SDX;

	class SceneSkill : public SDX::IScene
	{
	public:
		//@Define
		UI_Button 攻撃 = { 162, {85,6,80,70} , 0.000000,3};
		UI_Button リセット = { 175, {445,442,170,32} , 0.000000,3};
		UI_Frame レベル = { 177, {85,442,170,32} , 0.000000,5};
		UI_Frame 残りポイント = { 178, {265,442,170,32} , 0.000000,5};
		UI_Button 拡散 = { 179, {175,6,80,70} , 0.000000,3};
		UI_Button 防壊 = { 180, {265,6,80,70} , 0.000000,3};
		UI_Button 節約 = { 181, {355,6,80,70} , 0.000000,3};
		UI_Button 対獣 = { 182, {445,6,80,70} , 0.000000,3};
		UI_Button 対闇 = { 183, {535,6,80,70} , 0.000000,3};
		UI_Button 対人 = { 190, {445,86,80,70} , 0.000000,3};
		UI_Button 対竜 = { 191, {535,86,80,70} , 0.000000,3};
		UI_Button 連射 = { 192, {85,86,80,70} , 0.000000,3};
		UI_Button 体力 = { 193, {355,86,80,70} , 0.000000,3};
		UI_Button 麻痺 = { 194, {175,86,80,70} , 0.000000,3};
		UI_Button 回収 = { 195, {265,86,80,70} , 0.000000,3};
		UI_Button 幸運 = { 196, {535,166,80,70} , 0.000000,3};
		UI_Button 射程 = { 197, {85,166,80,70} , 0.000000,3};
		UI_Button 対水 = { 198, {445,166,80,70} , 0.000000,3};
		UI_Button 鈍足 = { 199, {175,166,80,70} , 0.000000,3};
		UI_Button 魔力 = { 200, {355,166,80,70} , 0.000000,3};
		UI_Button 強化 = { 201, {265,166,80,70} , 0.000000,3};
		UI_Button 吹飛 = { 202, {175,246,80,70} , 0.000000,3};
		UI_Button 必殺 = { 203, {355,246,80,70} , 0.000000,3};
		UI_Button 試練 = { 204, {535,246,80,70} , 0.000000,3};
		UI_Button 対樹 = { 205, {445,246,80,70} , 0.000000,3};
		UI_Button 支援 = { 206, {85,246,80,70} , 0.000000,3};
		UI_Button 逆境 = { 207, {265,246,80,70} , 0.000000,3};
		UI_Frame スキル説明 = { 209, {85,324,528,108} , 0.000000,5};
		//@End

		SceneSkill()
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
			if(攻撃.isClick()){}
			if(リセット.isClick()){}
			if(拡散.isClick()){}
			if(防壊.isClick()){}
			if(節約.isClick()){}
			if(対獣.isClick()){}
			if(対闇.isClick()){}
			if(対人.isClick()){}
			if(対竜.isClick()){}
			if(連射.isClick()){}
			if(体力.isClick()){}
			if(麻痺.isClick()){}
			if(回収.isClick()){}
			if(幸運.isClick()){}
			if(射程.isClick()){}
			if(対水.isClick()){}
			if(鈍足.isClick()){}
			if(魔力.isClick()){}
			if(強化.isClick()){}
			if(吹飛.isClick()){}
			if(必殺.isClick()){}
			if(試練.isClick()){}
			if(対樹.isClick()){}
			if(支援.isClick()){}
			if(逆境.isClick()){}
			//@End
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			//@Draw
			MSystem::frameS[攻撃.frameNo].Draw(攻撃.rect);
			MSystem::frameS[リセット.frameNo].Draw(リセット.rect);
			MSystem::frameS[レベル.frameNo].Draw(レベル.rect);
			MSystem::frameS[残りポイント.frameNo].Draw(残りポイント.rect);
			MSystem::frameS[拡散.frameNo].Draw(拡散.rect);
			MSystem::frameS[防壊.frameNo].Draw(防壊.rect);
			MSystem::frameS[節約.frameNo].Draw(節約.rect);
			MSystem::frameS[対獣.frameNo].Draw(対獣.rect);
			MSystem::frameS[対闇.frameNo].Draw(対闇.rect);
			MSystem::frameS[対人.frameNo].Draw(対人.rect);
			MSystem::frameS[対竜.frameNo].Draw(対竜.rect);
			MSystem::frameS[連射.frameNo].Draw(連射.rect);
			MSystem::frameS[体力.frameNo].Draw(体力.rect);
			MSystem::frameS[麻痺.frameNo].Draw(麻痺.rect);
			MSystem::frameS[回収.frameNo].Draw(回収.rect);
			MSystem::frameS[幸運.frameNo].Draw(幸運.rect);
			MSystem::frameS[射程.frameNo].Draw(射程.rect);
			MSystem::frameS[対水.frameNo].Draw(対水.rect);
			MSystem::frameS[鈍足.frameNo].Draw(鈍足.rect);
			MSystem::frameS[魔力.frameNo].Draw(魔力.rect);
			MSystem::frameS[強化.frameNo].Draw(強化.rect);
			MSystem::frameS[吹飛.frameNo].Draw(吹飛.rect);
			MSystem::frameS[必殺.frameNo].Draw(必殺.rect);
			MSystem::frameS[試練.frameNo].Draw(試練.rect);
			MSystem::frameS[対樹.frameNo].Draw(対樹.rect);
			MSystem::frameS[支援.frameNo].Draw(支援.rect);
			MSystem::frameS[逆境.frameNo].Draw(逆境.rect);
			MSystem::frameS[スキル説明.frameNo].Draw(スキル説明.rect);
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG
			return;
#endif
			//@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneSkill", GUI_Factory);

			攻撃 = *dynamic_cast<UI_Button*>(guiData.dataS[0].get());
			リセット = *dynamic_cast<UI_Button*>(guiData.dataS[1].get());
			レベル = *dynamic_cast<UI_Frame*>(guiData.dataS[2].get());
			残りポイント = *dynamic_cast<UI_Frame*>(guiData.dataS[3].get());
			拡散 = *dynamic_cast<UI_Button*>(guiData.dataS[4].get());
			防壊 = *dynamic_cast<UI_Button*>(guiData.dataS[5].get());
			節約 = *dynamic_cast<UI_Button*>(guiData.dataS[6].get());
			対獣 = *dynamic_cast<UI_Button*>(guiData.dataS[7].get());
			対闇 = *dynamic_cast<UI_Button*>(guiData.dataS[8].get());
			対人 = *dynamic_cast<UI_Button*>(guiData.dataS[9].get());
			対竜 = *dynamic_cast<UI_Button*>(guiData.dataS[10].get());
			連射 = *dynamic_cast<UI_Button*>(guiData.dataS[11].get());
			体力 = *dynamic_cast<UI_Button*>(guiData.dataS[12].get());
			麻痺 = *dynamic_cast<UI_Button*>(guiData.dataS[13].get());
			回収 = *dynamic_cast<UI_Button*>(guiData.dataS[14].get());
			幸運 = *dynamic_cast<UI_Button*>(guiData.dataS[15].get());
			射程 = *dynamic_cast<UI_Button*>(guiData.dataS[16].get());
			対水 = *dynamic_cast<UI_Button*>(guiData.dataS[17].get());
			鈍足 = *dynamic_cast<UI_Button*>(guiData.dataS[18].get());
			魔力 = *dynamic_cast<UI_Button*>(guiData.dataS[19].get());
			強化 = *dynamic_cast<UI_Button*>(guiData.dataS[20].get());
			吹飛 = *dynamic_cast<UI_Button*>(guiData.dataS[21].get());
			必殺 = *dynamic_cast<UI_Button*>(guiData.dataS[22].get());
			試練 = *dynamic_cast<UI_Button*>(guiData.dataS[23].get());
			対樹 = *dynamic_cast<UI_Button*>(guiData.dataS[24].get());
			支援 = *dynamic_cast<UI_Button*>(guiData.dataS[25].get());
			逆境 = *dynamic_cast<UI_Button*>(guiData.dataS[26].get());
			スキル説明 = *dynamic_cast<UI_Frame*>(guiData.dataS[27].get());
			//@End
		}
	};
}
