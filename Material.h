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
        DataPack<ImagePack,EnemyType> 敵;

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

            敵[EnemyType::ゼリー].Load("File/Enemy/000.png",9,3,3);
            敵[EnemyType::ゴブリン].Load("File/Enemy/001.png",9,3,3);
            敵[EnemyType::ケットシー].Load("File/Enemy/002.png",9,3,3);
            敵[EnemyType::オーガ].Load("File/Enemy/003.png",9,3,3);
            敵[EnemyType::マーマン].Load("File/Enemy/004.png",9,3,3);
            敵[EnemyType::ゴーレム].Load("File/Enemy/005.png",9,3,3);
            敵[EnemyType::ケルベロス].Load("File/Enemy/006.png",9,3,3);
            敵[EnemyType::スケルトン].Load("File/Enemy/007.png",9,3,3);
            敵[EnemyType::シャーマン].Load("File/Enemy/008.png",9,3,3);
            敵[EnemyType::コボルド].Load("File/Enemy/009.png",9,3,3);
            敵[EnemyType::ゼリー王].Load("File/Enemy/010.png",9,3,3);
            敵[EnemyType::ドラゴン].Load("File/Enemy/011.png",9,3,3);
            敵[EnemyType::インプ].Load("File/Enemy/012.png",9,3,3);
            敵[EnemyType::ゴースト].Load("File/Enemy/013.png",9,3,3);
            敵[EnemyType::グリフィン].Load("File/Enemy/014.png",9,3,3);

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
        ImagePack 枠画像[5];
        BmpFrame  フレーム[5];

        ImagePack マーク;
        

        static void Load()
        {
            マップチップ.Load("File/System/base.png", 8 * 292 , 8 , 292);
            枠画像[0].Load("File/System/frame000.png",9,3,3);
            枠画像[1].Load("File/System/frame001.png",9,3,3);
            枠画像[2].Load("File/System/frame002.png",9,3,3);
            枠画像[3].Load("File/System/frame003.png",9,3,3);
            枠画像[4].Load("File/System/frame004.png",9,3,3);
            フレーム[0].Make( &枠画像[0] );
            フレーム[1].Make( &枠画像[1] );
            フレーム[2].Make( &枠画像[2] );
            フレーム[3].Make( &枠画像[3] );
            フレーム[4].Make( &枠画像[4] );


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