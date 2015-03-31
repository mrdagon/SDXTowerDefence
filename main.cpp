//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3

#include "stdafx.h"

#ifndef __WINDOWS__

#include "PreCompile.cpp"
#include "Design.cpp"

#endif

#include "Stage.h"
#include "MenuTitle.h"
#include "SaveAndLoad.h"

SDX::IFont* fontS[10];
SDX::ImagePack imageS;
SDX::IFrame* frameS[10];

#include <Tiled/TmxToGUI.h>
#include "QuestScene.h"

#include <Tiled/TmxToCode.h>

int main(int argc, char* argv[])
{
	using namespace SDX;
	using namespace SDX_TD;

	//TMXtoCode("template.tmx", "GUIClass_Template.h", "GUICode_Template.h");

	System::Initialise("GTD ver0.02α", 640, 480);//ライブラリの初期化

	imageS.LoadTmx("template.tmx");
	fontS[0] = new Font(SystemFont::Gothic, 10);
	auto frame0 = ImagePack("data/pipo-WindowBase001.png", 9, 3, 3);
	auto frame1 = ImagePack("data/pipo-WindowBase004.png", 9, 3, 3);
	frameS[0] = new BmpFrame( &frame0 );
	frameS[1] = new BmpFrame(&frame1);

	QuestScene scene;

	while (System::Update())
	{
		scene.Draw();
	}

	return 0;

	//UIの位置をリセット
	UI_Reset();

	System::Initialise("GTD ver0.02α", 640 , 480 );//ライブラリの初期化

	//Window::SetLogicalSize(640, 480);

	Music::SetMainVolume(0.0);
	Sound::SetMainVolume(0.0);
	//Window::SetSize(960, 720);

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
	Director::AddScene(std::make_shared<MenuMain>());
	Director::Run();

	System::End();//ライブラリの終了処理

	return 0;
}