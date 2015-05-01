//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "PlaceData.h"

namespace SDX_TD
{
    using namespace SDX;
    //ステージ中でのリプレイに残る操作一覧
    //ゲーム速度の変更やオプション等は
    enum class Command
    {
        選択解除,
        ユニット選択,
        地上敵選択,
        空中敵選択,
        大魔法発動,
        Wave送り,
        強化,
        売却,
        発動,
        種別選択,
        新規配置,
        null,
    };

    struct CommandData
    {
        Command 種類;
        Point マウス座標;
        int 操作情報;//種類別のパラメータ
        int 操作した時間;

        CommandData(Command 種類,const Point &マウス座標,int 操作情報,int 操作した時間) :
            種類(種類),
            マウス座標(マウス座標),
            操作情報(操作情報),
            操作した時間(操作した時間)
        {}

    };

    class ReplayData
    {
    public:
        //■見出し情報
        int バージョン;

        //使用ウィッチ、サブウィッチ
        std::string ステージ名;//自作マップにも対応
        WitchType メイン;
        WitchType サブ;
        bool isトライアル;
        bool isカップル;
        EnumArray<int, SkillType> スキルLv;

        //自作マップリプレイはとりあえず非実装
        int StageNo;//初期マップ用		

        Difficulty 難易度;
        int 残りHP;
        int スコア;

        //■内部情報
        //初期配置データ
        std::vector<Place> 初期配置;

        int 乱数初期化子;
        //操作データ一覧
        std::vector<CommandData> commandS;

        void AddCommand(Command 種類 , const Point& 座標 , int 操作情報 , int timer)
        {

        }

    };

}