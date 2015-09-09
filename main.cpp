//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3

#include "stdafx.h"

#ifndef __WINDOWS__
#include "PreCompile.cpp"
#endif

#include <cassert>

//配布時は相対パス(というかコード埋め込み)、デバッグ時は絶対パス
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

std::vector<int> SDX_TD::Land::Route::未計算リスト;

int main(int argc, char* argv[])
{
    using namespace SDX;
    using namespace SDX_TD;
	Time::ResetCount();

	UI_Reset();
	LoadDataS();
    SaveAndLoad(FileMode::Read);

    System::Initialise("GTD ver0.05β", 640, 480);//ライブラリの初期化
    Window::SetLogicalSize(640, 480);

    Music::SetMainVolume( (TDSystem::BGMの音量*TDSystem::BGMの音量 ) / 100.0 + 0.01);
	Sound::SetMainVolume((TDSystem::BGMの音量*TDSystem::BGMの音量) / 100.0 + 0.01);

    LoadMaterial();

    while (1)
    {
        if (Loading::GetLoadingCount() == Loading::GetSuccesCount()) break;
    }
	MFont::SetIcon();

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