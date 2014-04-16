#pragma once//☀Unicode
#include "Utility/File.h"

namespace SDX_TD
{
    using namespace SDX;

    namespace TDSystem
    {
        int 難易度;
        int ステージ番号;
        bool isトライアル;
        bool isシングル;

        int Hp;
        int 素材数[4];

        //各ステージのハイスコア

        //実績関連

        //ウィッチの強化

        //設定関連
        double 効果音の音量;
        double BGMの音量;
        bool isグリッド;
        bool isHPゲージ;
        bool isエフェクト;

        static void SaveAndLoad( FileMode 読み込みor書込)
        {

        }

    }
}