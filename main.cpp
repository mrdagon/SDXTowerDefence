﻿//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3

#include "stdafx.h"

#ifndef __WINDOWS__

#include "PreCompile.cpp"
#include "Design.cpp"

#endif

#include "Stage.h"
#include "Title.h"

int main(int argc, char* argv[])
{
	using namespace SDX;
	using namespace SDX_TD;

	//UIの位置をリセット
	UI_Reset();

	System::Initialise("GTD ver0.02α", int(640 * TDSystem::カメラ.zoom), int(480 * TDSystem::カメラ.zoom));//ライブラリの初期化

	LoadUnitS();
	LoadEnemyS();
	LoadStageS();
	LoadWitchS();
	LoadDifficultyS();
	LoadChipS();

	LoadMaterial();

	while (1)
	{
		if (Loading::GetLoadingCount() == Loading::GetSuccesCount()) break;
	}

	//ゲームモード設定等
	TDSystem::isカップル = false;
	TDSystem::isトライアル = true;

	Witch::SetMain(WitchType::ライナ);

	Director::AddScene(std::make_shared<Stage>());
	Director::AddScene(std::make_shared<StageSelect>());
	Director::Run();

	System::End();//ライブラリの終了処理

	return 0;
}