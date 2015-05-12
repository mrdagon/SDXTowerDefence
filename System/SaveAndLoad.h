﻿//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "System/EnumType.h"
#include "Struct/WitchData.h"//経験値、レベル、スキルポイント
#include "System/TDSystem.h"//設定等色々
#include "Struct/StageData.h"//ハイスコア等

namespace SDX_TD
{
    using namespace SDX;

    bool SaveAndLoad(FileMode 保存or読み込み)
    {
        //バイナリ形式で保存
        File file("file/save/save.dat", 保存or読み込み, false);

        //ファイルが無いのに読み込もうとしたら失敗
        if (file.GetFileMode() == FileMode::None){return false;}

        //古いバージョンのセーブデータを読み込む時のなんちゃら用
        file.ReadWrite(TDSystem::バージョン);

        file.ReadWrite(WitchData::スキルLv);

        file.ReadWrite(TDSystem::限界難易度);

        file.ReadWrite(TDSystem::最大スキルポイント);
        file.ReadWrite(TDSystem::残りスキルポイント);
        file.ReadWrite(TDSystem::経験値);

        file.ReadWrite(TDSystem::効果音の音量);
        file.ReadWrite(TDSystem::BGMの音量);

        file.ReadWrite(TDSystem::isグリッド);
        file.ReadWrite(TDSystem::isHPゲージ);
        file.ReadWrite(TDSystem::is高速);
        file.ReadWrite(TDSystem::isエフェクト);

        file.ReadWrite(TDSystem::isタッチ);
        file.ReadWrite(TDSystem::isフルスクリーン);
        file.ReadWrite(TDSystem::is配置記録);

        file.ReadWrite(TDSystem::isリプレイ保存);

        if (保存or読み込み == FileMode::Write)
        {
            int num = StageDataS.size();
            file.Write( num );

            for (auto &it : StageDataS)
            {
                //ファイル名を入れる
                file.Write(it.first);

                file.ReadWrite(it.second.成績, 4);

                for (int a = 0; a < 24; ++a)
                {
                    file.Write(it.second.初期配置[a % 12][a / 12]);
                }
            }
        }
        else
        {
            int num;
            file.Read( num);

            for (int a = 0; a < num;++a)
            {
                std::string fileName;
                file.Read(fileName);

                file.ReadWrite(StageDataS[fileName].成績, 4);

                for (int a = 0; a < 24; ++a)
                {
                    file.Read(StageDataS[fileName].初期配置[a % 12][a / 12]);
                }
            }
        }


        return true;
    }
}