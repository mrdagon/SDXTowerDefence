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
        ImagePack ターゲット;
        DataPack<Image,IconType> UI; 
        DataPack<Image,WitchType> 魔導具;
        DataPack<Image,Element> 属性;

        static void Load()
        {
            ターゲット.Load("File/System/target.png",3,3,1);

            //UI.Load("File/System/icon.png", 20 , 10 , 2);
            UI[IconType::ライフ].Load("File/System/icon/000.png");
            UI[IconType::マナ].Load("File/System/icon/001.png");
            UI[IconType::レベル].Load("File/System/icon/002.png");
            UI[IconType::攻撃].Load("File/System/icon/003.png");
            UI[IconType::連射].Load("File/System/icon/004.png");
            UI[IconType::支援].Load("File/System/icon/005.png");
            UI[IconType::鈍足].Load("File/System/icon/006.png");
            UI[IconType::麻痺].Load("File/System/icon/007.png");
            UI[IconType::強化].Load("File/System/icon/008.png");
            UI[IconType::吹飛].Load("File/System/icon/009.png");
            UI[IconType::防壊].Load("File/System/icon/010.png");
            UI[IconType::速度].Load("File/System/icon/011.png");
            UI[IconType::回避].Load("File/System/icon/012.png");
            UI[IconType::防御].Load("File/System/icon/013.png");
            UI[IconType::回復].Load("File/System/icon/014.png");

            魔導具[WitchType::ライナ].Load("File/Magic/artifact/000.png");
            魔導具[WitchType::ナツメ].Load("File/Magic/artifact/001.png");
            魔導具[WitchType::ルコウ].Load("File/Magic/artifact/002.png");
            魔導具[WitchType::ディアネラ].Load("File/Magic/artifact/003.png");
            魔導具[WitchType::ミナエ].Load("File/Magic/artifact/004.png");
            魔導具[WitchType::トレニア].Load("File/Magic/artifact/005.png");
            魔導具[WitchType::ロチエ].Load("File/Magic/artifact/006.png");
            魔導具[WitchType::バロゥ].Load("File/Magic/artifact/007.png");
            魔導具[WitchType::フィオナ].Load("File/Magic/artifact/008.png");
            魔導具[WitchType::ナズナ].Load("File/Magic/artifact/009.png");
            魔導具[WitchType::委員長].Load("File/Magic/artifact/010.png");
            魔導具[WitchType::ミルラ].Load("File/Magic/artifact/011.png");

            属性[Element::炎].Load("File/Magic/element/000.png");
            属性[Element::氷].Load("File/Magic/element/001.png");
            属性[Element::空].Load("File/Magic/element/002.png");
            属性[Element::樹].Load("File/Magic/element/003.png");
            属性[Element::無].Load("File/Magic/element/004.png");


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
        ImagePack 枠画像[14];
        BmpFrame  フレーム[14];

        ImagePack マーク;
        
        Image 背景;


        static void Load()
        {
            マップチップ.Load("File/System/mapchip.png", 10 , 10 , 1);
            枠画像[0].Load("File/System/frame000.png",9,3,3);
            枠画像[1].Load("File/System/frame001.png",9,3,3);
            枠画像[2].Load("File/System/frame002.png",9,3,3);
            枠画像[3].Load("File/System/frame003.png",9,3,3);
            枠画像[4].Load("File/System/frame004.png",9,3,3);
            枠画像[5].Load("File/System/frame005.png",9,3,3);
            枠画像[6].Load("File/System/frame006.png",9,3,3);
            枠画像[7].Load("File/System/frame007.png",9,3,3);
            枠画像[8].Load("File/System/frame008.png",9,3,3);
            枠画像[9].Load("File/System/frame009.png",9,3,3);
            枠画像[10].Load("File/System/frame010.png",9,3,3);
            枠画像[11].Load("File/System/frame011.png",9,3,3);
            枠画像[12].Load("File/System/frame012.png",9,3,3);
            枠画像[13].Load("File/System/frame013.png",9,3,3);

            for(int a = 0;a<14;++a)
            {
                フレーム[a].Make( &枠画像[a] );
            }


            フレーム[1].Make( &枠画像[1] );
            フレーム[2].Make( &枠画像[2] );
            フレーム[3].Make( &枠画像[3] );
            フレーム[4].Make( &枠画像[4] );
            フレーム[5].Make( &枠画像[5] );
            フレーム[6].Make( &枠画像[6] );
            フレーム[7].Make( &枠画像[7] );
            フレーム[8].Make( &枠画像[8] );
            フレーム[9].Make( &枠画像[9] );

            背景.Load("File/System/back000.jpg");

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
            ゴシック小.Load(SystemFont::Gothic,12);
            ゴシック中.Load(SystemFont::Gothic,16);

            英語.Load("File/System/font.png",30,10,3);
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