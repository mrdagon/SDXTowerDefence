//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <Tiled/IGUI.h>

namespace SDX_TD
{
    /** クラスの説明.*/
    class UI_ScrollBar : public SDX::IGUI
    {
    public:
        //@メンバー宣言
        int frameNo;
        //@End
        int scrIndex;//スクロール位置 0～size - barSize
        int size;//全体、分割数
        int pageSize;//1ページの項目表示数
        double scrSize;//1スクロールの長さ
        Rect scrBox;//0～rect.X
        bool isGrip = false;

        //@コンストラクタ
        UI_ScrollBar( int id , const Rect& rect, double angle,int frameNo):
            frameNo(frameNo),
            IGUI(id,rect,angle)
        {}
        //@End

        //初期化
        void Init() override
        {
            //@Init
            
            //@End
        }

        //終了時
        void Final() override
        {
            //@Final
            
            //@End
        }

        //更新
        void Update() override
        {
            if (isGrip)
            {
                if (Input::mouse.Left.hold)
                {
                    scrBox.Move(0, Input::mouse.moveY);
                    if (scrBox.y < rect.y)
                    {
                        scrBox.y = rect.y;
                    }
                    else if (scrBox.y > rect.GetBottom() - scrBox.GetH())
                    {
                        scrBox.y = rect.GetBottom() - scrBox.GetH();
                    }

                    scrIndex = int((scrBox.y - rect.y) / scrSize);
                }
                else
                {
                    isGrip = false;
                }

            }
            else if(isClick())
            {
                if ( !scrBox.Hit( &Input::mouse.GetPoint()))
                {
                    scrBox.y = Input::mouse.y - scrBox.GetH() / 2;
                    if (scrBox.y < rect.y)
                    {
                        scrBox.y = rect.y;
                    }
                    else if (scrBox.y > rect.GetBottom() - scrBox.GetH())
                    {
                        scrBox.y = rect.GetBottom() - scrBox.GetH();
                    }

                    scrIndex = int((scrBox.y - rect.y) / scrSize);
                }
                isGrip = true;
            }
        }

        //描画
        void Draw() override
        {
            MSystem::frameS[8].Draw(rect);
            MSystem::frameS[8].Draw(scrBox);
        }
 
        void SetSize(int 要素数 , int ページ表示数)
        {
            size = 要素数;
            pageSize = ページ表示数;
            scrIndex = 0;
            isGrip = false;

            scrBox = rect;
            if (pageSize < size)
            {
                scrBox.heightDown = rect.heightDown * pageSize / size;
            }

            scrSize = rect.heightDown / size;
        }

        void AddIndex(int 値)
        {
            scrIndex += 値;
            scrIndex = std::max(std::min(scrIndex, size - pageSize), 0);
            //位置計算
            scrBox.y = rect.y + scrSize * scrIndex;
        }
    
    };
}
