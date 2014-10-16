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
        bool isStop = true;//Wave進行停止
        int 現在Wave = 0;
        int 待ち時間 = 600;
        int 最終Wave = 1000;
        int Wave間隔 = 600;

        EnemyType 敵種類[100];
        bool isBoss[100];
        
        bool Init()
        {
            File file("File/Map/enemy_001.csv", FileMode::Read, true);
            auto data = file.GetCsvToInt();

            for(int a=0; a<100;++a)
            {
                敵種類[a] = EnemyType(data[a]%20);
                isBoss[a] = (data[a]>=20);
            }

            return true;
        }

        bool Check()
        {
            if( isStop || 最終Wave == 現在Wave) return false;

            待ち時間--;

            if (待ち時間 <= 0 )
            {
                待ち時間 = Wave間隔;
                return true;
            }

            return false;
        }

        /**次Waveに進める.*/
        bool ToNext()
        {
            isStop = false;

            if( 現在Wave == 最終Wave )
            {
                return false;
            }

            待ち時間 = Wave間隔;
            return true;
        }

        void Draw()
        {
            int no = 現在Wave;
            int x = -2;
            int y = 待ち時間 * 80 / Wave間隔 - 80;
            while(true)
            {
                if(isBoss[no%100] )
                {
                    MSystem::フレーム[0].Draw({ x, y, 40, 80 });
                    MUnit::敵[敵種類[no%100]][1]->DrawRotate({ x + 20, y + 50 }, 2, 0);
                }else{
                    MSystem::フレーム[0].Draw({ x, y, 40, 80 });

                    MUnit::敵[敵種類[no%100]][1]->Draw({ x + 4, y + 36 });
                    MUnit::敵[敵種類[no%100]][1]->Draw({ x + 4 + 16, y + 36 });
                    MUnit::敵[敵種類[no%100]][1]->Draw({ x + 4 + 8, y + 36 + 8 });
                }
                //Wave数
                int size = 2;
                if( no >= 100 ){ size = 1 ;}

                MFont::BMP黒.DrawExtend({ x + 6, y + 4 }, size, size, Color::White, no + 1);

                y += 80;
                ++no;

                if( y > 480 || no > 最終Wave) break;
            }
        }

        void DrawInfo()
        {
            
            
        }
    };
}