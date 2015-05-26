//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3

#include "stdafx.h"

#ifndef __WINDOWS__

#include "PreCompile.cpp"
#include "Design.cpp"

#endif

#include <cassert>
//#include <Utility/Pool.h>

//配布時は相対パス、デバッグ時は絶対パス
#ifdef _DEBUG
static const char* TMX_FILE_NAME = "C:/Users/Uemura/Documents/GitHub/SDXTowerDefence/Scene/Layout.tmx";
#else
static const char* TMX_FILE_NAME = "Layout.tmx";
#endif

#include <Tiled/TmxToGUI.h>
#include "Stage/Stage.h"
#include "System/Material.h"
#include "Scene/SceneMenu.h"

#include "System/SaveAndLoad.h"
#include <Sample/Sample.h>

int main(int argc, char* argv[])
{
    using namespace SDX;
    using namespace SDX_TD;

	SampleTime();
	return 0;
	UI_Reset();
    LoadUnitS();
    LoadEnemyS();
    LoadStageS();
    LoadWitchS();
    LoadDifficultyS();
    LoadChipS();
    SaveAndLoad(FileMode::Read);

    System::Initialise("GTD ver0.02α", 640, 480);//ライブラリの初期化
    Window::SetLogicalSize(640, 480);

    Music::SetMainVolume( (TDSystem::BGMの音量*TDSystem::BGMの音量 ) / 100.0);
    Sound::SetMainVolume( (TDSystem::BGMの音量*TDSystem::BGMの音量) / 100.0);

    LoadMaterial();

    while (1)
    {
        if (Loading::GetLoadingCount() == Loading::GetSuccesCount()) break;
    }

    if (TDSystem::isフルスクリーン)
    {
        Window::SetFullscreen(true);
    }

    Director::AddScene(std::make_shared<SceneMenu>());
    Director::Run();

    SaveAndLoad(FileMode::Write);

    System::End();//ライブラリの終了処理

    return 0;
}