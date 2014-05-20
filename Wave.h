#pragma once//☀SDL
#include "Material.h"

namespace SDX_TD
{
    using namespace SDX;
    class Wave
    {
    public:
        bool isStop = false;//Wave進行停止
        int 現在Wave = 0;
        int 待ち時間 = 600;
        int 最終Wave = 9999;
        int Wave間隔 = 600;

        EnemyType 敵種類[100];
        bool isBoss[100];

        bool Check()
        {
            if( isStop ) return false;

            待ち時間--;

            if (待ち時間 <= 0 && 最終Wave != 現在Wave)
            {
                ++現在Wave;
                待ち時間 = Wave間隔;
                return true;
            }

            return false;
        }

        void Draw()
        {
            int no = 現在Wave;
            int x = -2;
            int y = 待ち時間 * 80 / Wave間隔 - 80;
            while(true)
            {
                敵種類[no] = EnemyType::マーマン; 

                MSystem::フレーム[4].Draw(x,y,40,80);
                MUnit::敵[敵種類[no]][1]->Draw( x + 6, y + 6 );
                MFont::BMP黒.Draw( x+6 , y+6 , Color::White , no+1 );

                y += 80;
                no++;
                if( y > 480 || no >= 最終Wave) break;
            }

            //Drawing::Rect( x , Window::GetHeight() - 40, 60, 40, Color::Red, false);
        }

        void DrawInfo()
        {
            
            
        }
        
    };
}