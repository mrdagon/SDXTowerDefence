#pragma once//☀SDL
#include "EnumType.h"

namespace SDX_TD
{
    using namespace SDX;
    struct Wave
    {
        int 現在Wave = -1;
        int 次Waveまでの時間 = 240;
        int 最終Wave = 25;
        int Wave間隔 = 600;

        EnemyType 敵種類[100];
        bool isBoss[100];

        int GetPosition()
        {
            return 次Waveまでの時間 * 60 / Wave間隔 - 60;
        }

        bool Check()
        {
            次Waveまでの時間--;

            if (次Waveまでの時間 == 0 && 最終Wave != 現在Wave)
            {
                ++現在Wave;
                次Waveまでの時間 = Wave間隔;
                return true;
            }

            return false;
        }
    };
}