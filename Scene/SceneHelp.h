//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"
#include "../System/Material.h"

namespace SDX_TD
{
    using namespace SDX;

    class SceneHelp : public SDX::IScene
    {
    public:
        //@Define
		UI_Button クレジット = { 125, {233,226,196,48} , 0.000000,3};
        //@End
        bool isヘルプ表示;
        Image* 表示画像;
        std::string 文章;

        SceneHelp()
        {
            LoadGUI();
            Init();            
        }

        //初期化
        void Init() override
        {
        }

        //終了時
        void Final() override
        {
        }

        //更新
        void Update() override
        {
            if (Input::mouse.Left.on && isヘルプ表示)
            {
                isヘルプ表示 = false;
                return;
            }

            if (クレジット.isClick())
            {
                表示画像 = nullptr;
                isヘルプ表示 = true;
                文章 = "[クレジット](敬称略、詳細はreadme.txt)\n"
                    "[制作･著作･その他色々]\n"
                    "(`･@･)\n"
                    "[ライブラリ]\n"
                    "SDL 2.0\n"
                    "SDXFramework 013\n"
                    "[グラフィック素材]\n"
                    "ドットワールド\n"
                    "エトリエ\n"
                    "臼井の会\n"
                    "white cat\n"
                    "ぴぽや\n"
                    "[音声素材]\n"
                    "FREEDOM HOUSE 2nd\n"
                    "ザ・マッチメイカァズ 2nd\n"
                    "[フォント素材]\n"
                    "IPAフォント\n";
            }

            //@Update
			if(クレジット.isClick()){}
            //@End
        }

        //描画
        void Draw() override
        {
#ifdef _DEBUG			
            if (Input::key.Return.on){ LoadGUI(); }
#endif
            //@Draw
			MSystem::frameS[クレジット.frameNo].Draw(クレジット.rect);
            //@End
            MFont::fontS[1].DrawRotate(クレジット.rect.GetCenter(),2,0, Color::Black, "Credit");

            if (isヘルプ表示)
            {
                //枠
                MSystem::frameS[5].Draw({ 80, 20, 540, 440 });
                MFont::fontS[1].Draw({ 100, 40 }, Color::White, 文章);
            }
        }

        void LoadGUI() override
        {
#ifndef _DEBUG
            return;
#endif
            //@Load
			SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneHelp", GUI_Factory);

			クレジット = *dynamic_cast<UI_Button*>(guiData.dataS[0].get());
            //@End
        }
    };
}
