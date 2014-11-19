//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
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
            int no = 現在Wave % 100;
            int x = -2;
            int y = 待ち時間 * 80 / Wave間隔 - 80;
            while(true)
            {
                敵種類[no] = EnemyType::マーマン; 

                isBoss[no] = (no% 2 == 0);

                if(isBoss[no] )
                {
                    MSystem::フレーム[0].Draw({ x, y, 40, 80 });
                    MUnit::敵[敵種類[no]][1]->DrawRotate({ x + 20, y + 50 }, 2, 0);
                }else{
                    MSystem::フレーム[0].Draw({ x, y, 40, 80 });

                    MUnit::敵[敵種類[no]][1]->Draw({ x + 4, y + 36 });
                    MUnit::敵[敵種類[no]][1]->Draw({ x + 4 + 16, y + 36 });
                    MUnit::敵[敵種類[no]][1]->Draw({ x + 4 + 8, y + 36 + 8 });
                }
                //Wave数
                MFont::BMP黒.DrawExtend({ x + 6, y + 4 }, 2 - (no / 99), 2 - (no / 99), Color::White, no + 1);

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