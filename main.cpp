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

    MainWitch = new Witch(WitchType::ライナ);
    MainWitch->特殊補正[DebuffType::吹飛] = 1;

    System::Initialise("sample", 640, 480);//ライブラリの初期化

    //16:9
    //40:

    LoadMagicS();
    LoadChipS();

    LoadMaterial();

    Director::AddScene( new Stage() );
    Director::Run();

    System::End();//ライブラリの終了処理

    return 0;
}