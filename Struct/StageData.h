//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "../System/EnumType.h"
#include "PlaceData.h"
#include "../System/TDSystem.h"

namespace SDX_TD
{
    using namespace SDX;

    /**ステージの情報.*/
    struct StageData
    {
        //作者名は読み込まない
        std::string 名前;
        std::string 説明;
        int Wave間隔;

        struct Score
        {
            EnumArray<int, WitchType> スコア;
            EnumArray<int, WitchType> 勝利;
            EnumArray<int, WitchType> 完勝;
        };

        //全体の最高スコア
        //[isトライアル][isカップル]
        Score ハイスコア[2][2];//レベル制限あり

        EnemyType 敵種類[MAX_WAVE];
        bool	  isBoss[MAX_WAVE];
        ChipType  地形[MAP_SIZE][MAP_SIZE];

        Score& Getスコア()
        {
            return ハイスコア[TDSystem::isトライアル][TDSystem::isカップル];
        }

        //メインウィッチ種、トライアルorパワー
        std::vector<Place> 初期配置[(int)WitchType::COUNT][2];

        void DrawMinimap()
        {

        }

    };

    std::array<StageData,StageType::COUNT> StageDataS;//標準ステージ
    std::map< std::string, StageData > FreeStageS;//全部文字列で管理

    void LoadStageS()
    {
        //ソフト起動時のみ行う
        bool isMap = false;
        bool isEnemy = false;
        int line = 0;

        for (StageData &it : StageDataS)
        {
            File file("file/map/map000.tmx", FileMode::Read, true);
            auto strS = file.GetLineS();
            
            for (auto &str : strS)
            {
                if (isMap || isEnemy )
                {
                    std::istringstream iss(str);
                    std::string buf;
                    int count = 0;

                    while (std::getline(iss, buf, ','))
                    {
                        if (line == -1){ break; }//data encoding="csv"を無視

                        if (isEnemy)
                        {
                            //@todo ここタイルチップ情報確認しておきたい
                            int num = (std::atoi(buf.c_str()) - 11);

                            StageDataS[0].敵種類[count + line * 10] = (EnemyType)(num % 20);
                            StageDataS[0].isBoss[count + line * 10] = (num >= 20);

                            if (count == 9){ break; }
                        }
                        else
                        {
                            StageDataS[0].地形[count][line] = (ChipType)(std::atoi(buf.c_str())-1);
                        }
                        ++count;
                    }
                    ++line;
                    if (isEnemy && line == 10){ isEnemy = false; }
                    if (isMap && line == 32){ isMap = false; }
                }
                else if (str.find("Info") != std::string::npos)
                {
                    StageDataS[0].説明 = GetTag(str, "value=");
                }
                else if (str.find("Name") != std::string::npos)
                {
                    StageDataS[0].名前 = GetTag(str, "value=");
                }
                else if (str.find("WaveSpeed") != std::string::npos)
                {
                    StageDataS[0].Wave間隔 = std::atoi(GetTag(str, "value=").c_str());
                }
                else if (str.find("layer name=\"map\"") != std::string::npos)
                {
                    isMap = true;
                    line = -1;
                }
                else if (str.find("layer name=\"enemy\"") != std::string::npos)
                {
                    isEnemy = true;
                    line = -1;
                }
            }
        }
    }

}