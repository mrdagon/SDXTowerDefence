//☀Unicode
#include "stdafx.h"

#include "Utility/Motion.h"

//#include "Object.h"
//#include "Shot.h"
//#include "Unit.h"
//#include "Enemy.h"
//
//#include "Stage.h"
//#include "Menu.h"
//
//#include "TitleMenu.h"


//#include "Sample/Sample.h"

int main(int argc, char* argv[])
{
    using namespace SDX;

    auto a = Motion::ToFront<Speed::Liner>(10);
    auto b = Motion::Bound<Speed::Liner>(10,{0,0,10,10},0);
    auto c = Motion::Orbit<Speed::Liner>(10);
    auto d = Motion::Vibrate(10);
    auto e = Motion::ToPoint<Speed::Liner>(10,{0,0});

    //using namespace SDX_TD;
    //
    //MainWitch = new Witch::ライナ();
    //SubWitch = new Witch::ライナ();

    //System::Initialise("sample", 640, 480);//ライブラリの初期化

    //LoadUnitS();
    //LoadChipS();

    //LoadMaterial();

    //Director::AddScene( new Stage() );
    //Director::Run();

    //System::End();//ライブラリの終了処理
    
    return 0;
}