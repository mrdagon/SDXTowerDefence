//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3

#include "stdafx.h"

#ifndef __WINDOWS__
#include "PreCompile.cpp"
#include "Design.cpp"
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

void ChangeStdwMap()
{
	using namespace SDX;
	using namespace SDX_TD;

	for (int a = 0; a < 20; ++a)
	{
		std::string mapName = "file/stdwmap/stage";
		std::string enemyName = "file/stdwmap/enemy";
		std::string tmxName = "file/stdw";

		mapName += std::to_string(a / 10) + std::to_string(a % 10);
		mapName += ".txt";
		enemyName += std::to_string(a / 10) + std::to_string(a % 10);
		enemyName += ".txt";
		tmxName += std::to_string(a / 10) + std::to_string(a % 10);
		tmxName += ".txt";

		File map(mapName.c_str(), FileMode::Read);
		File enemy(enemyName.c_str(), FileMode::Read);
		File newMap(tmxName.c_str(), FileMode::Write);

		newMap.AddLine("3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,");

		auto csvM = map.GetCsvToInt();

		for (int b = 0; b < 30; ++b)
		{
			std::string str = "3,";
			for (int c = 0; c < 30; ++c)
			{
				str += std::to_string(csvM[c + b * 31 + 14] + 1);
				str += ",";
			}
			str += "3,";
			newMap.AddLine(str);
		}
		newMap.AddLine("3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3");
		newMap.AddLine("</data>");
		newMap.AddLine("</layer>");
		newMap.AddLine("<layer name = \"enemy\" width = \"32\" height = \"32\">");
		newMap.AddLine("<data encoding = \"csv\">");
		auto csvE = enemy.GetCsvToInt();

		for (int b = 0; b < 10; ++b)
		{
			std::string str = "";
			for (int c = 0; c < 10; ++c)
			{
				int num = 0;

				switch (csvE[c + b * 11 + 14] % 15)
				{
				case 0:num = 11; break;
				case 1:num = 12; break;
				case 2:num = 14; break;
				case 3:num = 15; break;
				case 4:num = 13; break;
				case 5:num = 19; break;
				case 6:num = 18; break;
				case 7:num = 22; break;
				case 8:num = 24; break;
				case 9:num = 17; break;
				case 10:num = 16; break;
				case 11:num = 25; break;
				case 12:num = 20; break;
				}
				if (csvE[c + b * 11 + 14] >= 15)
				{
					num += 20;
				}
				str += std::to_string(num);
				str += ",";
			}

			for (int c = 0; c < 22; ++c)
			{
				str += "0,";
			}
			newMap.AddLine(str);
		}

		for (int c = 0; c < 21; ++c)
		{
			newMap.AddLine("0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,");
		}
		newMap.AddLine("0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");
		newMap.AddLine("</data>");
		newMap.AddLine("</layer>");
		newMap.AddLine("</map>");
	}
}


int main(int argc, char* argv[])
{
	//変換コード
    using namespace SDX;
    using namespace SDX_TD;

	UI_Reset();
    LoadUnitS();
    LoadEnemyS();
    LoadStageS();
    LoadWitchS();
    LoadDifficultyS();
    LoadChipS();
    SaveAndLoad(FileMode::Read);

    System::Initialise("GTD ver0.03β", 640, 480);//ライブラリの初期化
    Window::SetLogicalSize(640, 480);

    Music::SetMainVolume( (TDSystem::BGMの音量*TDSystem::BGMの音量 ) / 100.0 + 0.01);
	Sound::SetMainVolume((TDSystem::BGMの音量*TDSystem::BGMの音量) / 100.0 + 0.01);

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