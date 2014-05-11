//☀Unicode
#include "stdafx.h"
#include "Stage.h"
#include "Enemy.h"
#include "Shot.h"
#include "Magic.h"
#include "Menu.h"

#include "TitleMenu.h"
#include "Sample/Sample.h"

int main(int argc, char* argv[])
{
    using namespace SDX;
    using namespace SDX_TD;

    MainWitch = new Witch();
    MainWitch->状態強化[(int)Elements::空] = 1;

    System::Initialise("sample", 800, 600);//ライブラリの初期化

    LoadMagicData();
    LoadMaterial();

    Director::AddScene( new Stage() );
    Director::Run();

    System::End();//ライブラリの終了処理

    return 0;
}