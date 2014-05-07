#pragma once//☀Unicode
#include <SDXFrameWork.h>
#include "EnumType.h"

namespace SDX_TD
{
    using namespace SDX;

    /**敵＆ウィッチの画像.*/
    namespace MUnit
    {
        DataPack<ImagePack,WitchType> 魔女;

        //ImagePack 魔女[(int)WitchType::MAX];

        static void Load()
        {
            魔女[WitchType::ライナ].Load("File/Unit/Lina.png",9,3,3);
            魔女[WitchType::ナツメ].Load("File/Unit/Natsume.png",9,3,3);
            魔女[WitchType::ルコウ].Load("File/Unit/Rukou.png",9,3,3);
            魔女[WitchType::ディアネラ].Load("File/Unit/Dianella.png",9,3,3);
            魔女[WitchType::ミナエ].Load("File/Unit/Minae.png",9,3,3);
            魔女[WitchType::トレニア].Load("File/Unit/Torenia.png",9,3,3);
            魔女[WitchType::ロチエ].Load("File/Unit/Rochie.png",9,3,3);
            魔女[WitchType::バロゥ].Load("File/Unit/Barrow.png",9,3,3);
            魔女[WitchType::フィオナ].Load("File/Unit/Fiona.png",9,3,3);
            魔女[WitchType::ナズナ].Load("File/Unit/Nazuna.png",9,3,3);
            魔女[WitchType::委員長].Load("File/Unit/Chairwoman.png",9,3,3);
            魔女[WitchType::ミルラ].Load("File/Unit/Myrra.png",9,3,3);
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

        ImagePack マーク;
        

        static void Load()
        {
            マップチップ.Load("File/System/base.png", 8 * 292 , 8 , 292);
            枠画像[0].Load("File/System/magic_frame000.png",9,3,3);
            枠画像[1].Load("File/System/magic_frame001.png",9,3,3);
            枠画像[2].Load("File/System/magic_frame002.png",9,3,3);
            魔法枠[0].Make( &枠画像[0] );
            魔法枠[1].Make( &枠画像[1] );
            魔法枠[2].Make( &枠画像[2] );
            
            マーク.Load("File/System/mark.png",4,4,1);         
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
        Font ゴシック小;
        Font ゴシック中;
        BmpFont BMP黒;
        BmpFont BMP白;

        ImagePack 英語;
        ImagePack 黒数字;
        ImagePack 白数字;

        static void Load()
        {
            英語.Load("File/System/font.png",26,10,3);
            黒数字.Load("File/System/font_num_black.png",10,10,1);
            白数字.Load("File/System/font_num_white.png",10,10,1);

            BMP黒.SetAlphabetCapital(&英語);
            BMP黒.SetAlphabetLow(&英語);
            BMP黒.SetNumber(&黒数字);

            BMP白.SetNumber(&白数字);
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