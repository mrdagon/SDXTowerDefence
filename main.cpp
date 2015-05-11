//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3
#include "stdafx.h"

static const int version = 102;

#ifndef __WINDOWS__

#include "PreCompile.cpp"
#include "Design.cpp"

#endif

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

//#include "Scene/SceneStage.h"
//#include "Scene/ScenePause.h"
//#include "Scene/SceneResult.h"

#include "System/SaveAndLoad.h"

int main(int argc, char* argv[])
{
    using namespace SDX;
    using namespace SDX_TD;

    //UIの位置をリセット
    UI_Reset();

    System::Initialise("GTD ver0.02α", 640, 480);//ライブラリの初期化

    Window::SetLogicalSize(640, 480);

    Music::SetMainVolume(0.0);
    Sound::SetMainVolume(0.0);
    //Window::SetSize(960, 720);
    //Window::SetFullscreen(true);
    //Window::SetLogicalSize(640, 480);

    TDSystem::限界難易度 = Difficulty::DeathMarch;

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

    //★Witch::SetMain(WitchType::ライナ);
    //★Witch::SetMain(WitchType::ナツメ);
    //★Witch::SetMain(WitchType::ルコウ);
    //★Witch::SetMain(WitchType::ディアネラ);
    //★Witch::SetMain(WitchType::ミナエ);
    //★Witch::SetMain(WitchType::トレニア);
    //★Witch::SetMain(WitchType::ロチエ);
    //★Witch::SetMain(WitchType::バロゥ);
    //★Witch::SetMain(WitchType::フィオナ);
    //★Witch::SetMain(WitchType::ナズナ);
    //★Witch::SetMain(WitchType::委員長);
    Witch::SetMain(WitchType::ミルラ);

    //Director::AddScene(std::make_shared<Stage>());
    Director::AddScene(std::make_shared<SceneMenu>());
    Director::Run();

    System::End();//ライブラリの終了処理

    return 0;
}