//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "PlaceData.h"
#include "../Stage/Witch.h"

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

        CommandData() = default;

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
        std::string ファイル名;//リプレイファイル名
        std::string ステージ名;//自作マップにも対応、ステージファイル名
        WitchType メイン;
        WitchType サブ;
        bool isトライアル;
        bool isカップル;
        Difficulty 難易度;
		double スコア;
        ResultType 結果;

        static std::string 結果名[3];

        //初期配置データ
        static int 乱数初期化子;
        //操作データ一覧
        static std::vector<CommandData> commandS;
		
		static std::vector<Place> 初期配置;

        bool SaveOrLoad(const char* リプレイファイル名 , bool isTag , FileMode 保存or読み込み , ResultType result = ResultType::Lose , double score = 0)
        {
			std::string folderName = "replay/";
			ファイル名 = リプレイファイル名;

            File file( (folderName + リプレイファイル名).c_str() , 保存or読み込み, true);

			if (file.GetFileMode() == FileMode::None)
			{
				return false;
			}

            if (isTag)
            {
                file.ReadWrite(バージョン);
                file.ReadWrite(ステージ名);
                file.ReadWrite(メイン);
                file.ReadWrite(サブ);
                file.ReadWrite(isトライアル);
                file.ReadWrite(isカップル);
                file.ReadWrite(難易度);
                file.ReadWrite(スコア);
                file.ReadWrite(結果);
                return true;
            }

            バージョン = TDSystem::バージョン;
            file.ReadWrite( バージョン );
			file.ReadWrite(TDSystem::選択ステージ);
			if (保存or読み込み == FileMode::Read)
			{
				file.ReadWrite(メイン);
				file.ReadWrite(サブ);
				Witch::SetMain(メイン);
				Witch::SetSub(サブ);
			}
			else
			{
				file.ReadWrite( Witch::witchS[0].種類 );
				file.ReadWrite( Witch::witchS[1].種類);
			}
            file.ReadWrite( TDSystem::isトライアル);
            file.ReadWrite( TDSystem::isカップル);
            file.ReadWrite( TDSystem::難易度);
            file.ReadWrite( score );
            file.ReadWrite( result );

            file.ReadWrite( 乱数初期化子 );
            file.ReadWrite( commandS );
            file.ReadWrite( Witch::スキルLv );
			file.ReadWrite( 初期配置 );

			return true;
        }
    };

    std::string ReplayData::結果名[3] = {"Lose", "Win", "Perfect"};

    int ReplayData::乱数初期化子 = 0;
    //操作データ一覧
    std::vector<CommandData> ReplayData::commandS;

	std::vector<Place> ReplayData::初期配置;
}