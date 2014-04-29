#pragma once//☀Unicode
#include <SDXFrameWork.h>
#include "EnumType.h"

namespace SDX_TD
{
    using namespace SDX;

    /**敵＆ウィッチの画像.*/
    namespace MUnit
    {
        static void Load()
        {
        
        }
    }

    /**魔法のアイコン.*/
    namespace MMagic
    {
        ImagePack 魔法;

        static void Load()
        {
            魔法.Load("File/Magic/magic","png",(int)MagicType::MAX);

            
        }
    }

    /**その他のアイコン.*/
    namespace MIcon
    {
        static void Load()
        {
        
        }
    }

    /**エフェクトや弾.*/
    namespace MEffect
    {
        static void Load()
        {
        
        }
    }

    /**UI等のシステム.*/
    namespace MSystem
    {
        ImagePack マップチップ;
        ImagePack 枠画像[3];
        BmpFrame  魔法枠[3];

        static void Load()
        {
            マップチップ.Load("File/System/base.png", 8 * 292 , 8 , 292);
            枠画像[0].Load("File/System/magic_frame000.png",9,3,3);
            枠画像[1].Load("File/System/magic_frame001.png",9,3,3);
            枠画像[2].Load("File/System/magic_frame002.png",9,3,3);
            魔法枠[0].Make( &枠画像[0] );
            魔法枠[1].Make( &枠画像[1] );
            魔法枠[2].Make( &枠画像[2] );
        }
    }

    /**BGM.*/
    namespace MMusic
    {
        static void Load()
        {
        
        }
    }

    /**効果音.*/
    namespace MSound
    {
        static void Load()
        {
        
        }
    }

    /**フォント.*/
    namespace MFont
    {
        static Font ゴシック小;
        static Font ゴシック中;
        static BmpFont 白フォント;

        static void Load()
        {
        
        }
    }

    static void LoadMaterial()
    {
        MUnit::Load();
        MMagic::Load();
        MIcon::Load();
        MEffect::Load();
        MSystem::Load();

        MMusic::Load();
        MSound::Load();
        MFont::Load();
    }

}