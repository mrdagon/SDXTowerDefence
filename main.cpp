//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3

#include "stdafx.h"

#include "Mission/Stage.h"
#include "Camp/Title.h"

int main(int argc, char* argv[])
{
	using namespace SDX;
	using namespace SDX_TD;

	//UIの位置をリセット
	UI_Reset();

	System::Initialise("GTD", 640, 480);//ライブラリの初期化

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