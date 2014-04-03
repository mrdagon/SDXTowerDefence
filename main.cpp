//☀Unicode
#include "stdafx.h"
#include "Scene.h"
using namespace SDX;
#include "Enemy.h"
#include "Shot.h"
#include "Unit.h"

#include "Sample/Sample.h"

int main(int argc, char* argv[])
{
    System::Initialise("sample", 640, 480);//ライブラリの初期化

    Scene scene;
    
    scene.Init();

    int time = 0;

    while (System::Update())
    {
        ++time;
        scene.Update();
        scene.Draw();

        Scene::LandUpdate();

        if (Input::mouse.Left.on)
        {
            if (Land::now->SetCheck(Input::mouse.x / 20, Input::mouse.y / 20, 2))
            {
                Scene::Now()->Add(new Unit(Input::mouse.x / 20, Input::mouse.y / 20, 2, nullptr));
            }
        }

        if (time % 30 == 0)
        {
            Scene::Add(new Enemy(30, 30, nullptr));
            Scene::Add(new Enemy(30, 30, nullptr, Belong::Sea));
        }
    }

    System::End();//ライブラリの終了処理

    return 0;
}
