//☀Unicode
#include "stdafx.h"
#include "Stage.h"
#include "Enemy.h"
#include "Shot.h"
#include "Unit.h"

int main(int argc, char* argv[])
{
    using namespace SDX;
    using namespace SDX_TD;

    System::Initialise("sample", 640, 480);//ライブラリの初期化

    while (System::Update())
    {
        Time::StartWatch();

        Object* n;

        for (int i = 0; i < 100000; ++i)
        {
            n = new Object(nullptr, nullptr);
            delete n;
        }


        Time::DrawWatch(10, 10, "処理時間(ミリ秒)");
    }

    //Director::AddScene( new Stage() );
    //Director::Run();

    System::End();//ライブラリの終了処理

    return 0;
}
