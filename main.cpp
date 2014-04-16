//☀Unicode
#include "stdafx.h"
#include "Stage.h"
#include "Enemy.h"
#include "Shot.h"
#include "Magic.h"
#include "Menu.h"

#include "TitleMenu.h"

int main(int argc, char* argv[])
{
    using namespace SDX;
    using namespace SDX_TD;

    System::Initialise("sample", 640, 480);//ライブラリの初期化

    Director::AddScene( new Stage() );
    Director::Run();

    System::End();//ライブラリの終了処理

    return 0;
}
