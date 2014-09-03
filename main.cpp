//☀Unicode
#include "stdafx.h"

#include "Object.h"
#include "Shot.h"
#include "Unit.h"
#include "Enemy.h"

#include "Stage.h"
#include "Menu.h"

#include "TitleMenu.h"

int main(int argc, char* argv[])
{
    using namespace SDX;
    using namespace SDX_TD;
    
    WITCH::Main.reset(new WITCH::バロゥ());
    WITCH::Sub.reset(new WITCH::ディアネラ());

    System::Initialise("sample", 640, 480);//ライブラリの初期化

    LoadUnitS();
    LoadChipS();

    LoadMaterial();

    Director::AddScene( new Stage() );
    Director::Run();

    System::End();//ライブラリの終了処理

    return 0;
}