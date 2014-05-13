#pragma once//☀SDL
#include "EnumType.h"

namespace SDX_TD
{
    using namespace SDX;
    class Wave
    {
    public:
        int 現在Wave = -1;
        int 待ち時間 = 240;
        int 最終Wave = 25;
        int Wave間隔 = 600;

        EnemyType 敵種類[100];
        bool isBoss[100];

        bool Check()
        {
            待ち時間--;

            if (待ち時間 == 0 && 最終Wave != 現在Wave)
            {
                ++現在Wave;
                待ち時間 = Wave間隔;
                return true;
            }

            return false;
        }

        void Draw()
        {
            int x = 待ち時間 * 60 / Wave間隔 - 60;
            Drawing::Rect( x , Window::GetHeight() - 40, 60, 40, Color::Red, false);
        }
    };
}