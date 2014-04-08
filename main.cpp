//☀Unicode
#include "stdafx.h"
#include "Stage.h"
using namespace SDX;
#include "Enemy.h"
#include "Shot.h"
#include "Unit.h"

int main(int argc, char* argv[])
{
    System::Initialise("sample", 640, 480);//ライブラリの初期化

    Director::AddScene( new Stage() );
    Director::Run();

    System::End();//ライブラリの終了処理

    return 0;
}
