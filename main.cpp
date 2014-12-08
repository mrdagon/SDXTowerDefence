//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3

#include "stdafx.h"

#include "Object.h"
#include "Shot.h"
#include "Unit.h"
#include "Enemy.h"

#include "Stage.h"
#include "Menu.h"

#include "TitleMenu.h"
#include "Sample/Sample.h"

int main(int argc, char* argv[])
{
	using namespace SDX;
	using namespace SDX_TD;

	StageDraw::Reset();
	UnitDraw::Reset();

	WITCH::Main.reset(new WITCH::バロゥ());
	WITCH::Sub.reset(new WITCH::ディアネラ());

	System::Initialise("sample", 640, 480);//ライブラリの初期化

	LoadUnitS();
	LoadEnemyS();
	LoadStageS();
	LoadDifficultyS();
	LoadChipS();

	LoadMaterial();

	while (1)
	{
		if (Loading::GetLoadingCount() == Loading::GetSuccesCount()) break;

	}



	Director::AddScene(new Stage());
	Director::Run();

	System::End();//ライブラリの終了処理

	return 0;
}