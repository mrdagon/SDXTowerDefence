//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "EnumType.h"
#include "TDSystem.h"//設定等色々
#include "../Struct/WitchData.h"//経験値、レベル、スキルポイント
#include "../Struct/StageData.h"//ハイスコア等

namespace SDX_TD
{
    using namespace SDX;

    bool SaveAndLoad(FileMode 保存or読み込み)
    {
        //バイナリ形式で保存
        File file("file/save/save.dat", 保存or読み込み, false);

        //ファイルが無いのに読み込もうとしたら初期データにする
        if (file.GetFileMode() == FileMode::None)
		{
			return false;
		}

        //古いバージョンのセーブデータを読み込む時のなんちゃら用
		int version = TDSystem::バージョン;
        file.ReadWrite( version );

		//version 103以下は無効
		if (version <= 103)
		{
			return false;
		}

        file.ReadWrite(WitchData::スキルLv);

		file.ReadWrite(TDSystem::レベル);
        file.ReadWrite(TDSystem::限界難易度);

		for (int a = 0; a < StageType::COUNT; ++a)
		{
			file.ReadWrite(TDSystem::isクエスト開放[a]);
		}

        file.ReadWrite(TDSystem::最大スキルポイント);
        file.ReadWrite(TDSystem::残りスキルポイント);
        file.ReadWrite(TDSystem::経験値);

		//設定関連
        file.ReadWrite(TDSystem::効果音の音量);
        file.ReadWrite(TDSystem::BGMの音量);

        file.ReadWrite(TDSystem::isグリッド);
        file.ReadWrite(TDSystem::isHPゲージ);
        file.ReadWrite(TDSystem::is高速);
		file.ReadWrite(TDSystem::isエフェクト省略);

        file.ReadWrite(TDSystem::isタッチ);
        file.ReadWrite(TDSystem::isフルスクリーン);
        file.ReadWrite(TDSystem::is配置記録);

        file.ReadWrite(TDSystem::isリプレイ保存);

		//記録と実績関連
		file.ReadWrite(TDSystem::プレイ秒数);
		file.ReadWrite(TDSystem::合計スキルLv);
		file.ReadWrite(TDSystem::合計Wave);
		file.ReadWrite(TDSystem::合計獲得資金);
		file.ReadWrite(TDSystem::合計消費資金);

		file.ReadWrite(TDSystem::合計回収回数);
		file.ReadWrite(TDSystem::合計仕事回数);
		file.ReadWrite(TDSystem::合計獲得EXP);
		file.ReadWrite(TDSystem::ザコ撃破数);
		file.ReadWrite(TDSystem::ボス撃破数);

		file.ReadWrite(TDSystem::シングル総スコア);
		file.ReadWrite(TDSystem::タッグ総スコア);
		file.ReadWrite(TDSystem::クエスト銀星数);
		file.ReadWrite(TDSystem::クエスト金星数);

		file.ReadWrite(TDSystem::クリア回数);
		file.ReadWrite(TDSystem::パーフェクト回数);
		file.ReadWrite(TDSystem::大魔法回数);
		file.ReadWrite(TDSystem::タッグ回数);

		file.ReadWrite(TDSystem::配置回数);
		file.ReadWrite(TDSystem::強化回数);

		file.ReadWrite(TDSystem::種族撃破数);
		file.ReadWrite(TDSystem::種族ボス撃破数);


        if (保存or読み込み == FileMode::Write)
        {
			TDSystem::プレイ秒数.現在値 += Time::GetNowCount() / 1000;
			Time::ResetCount();
			file.ReadWrite( TDSystem::プレイ秒数.現在値);

            int num = StageDataS.size();
            file.Write( num );

            for (auto &it : StageDataS)
            {
                //ファイル名を入れる
				//if (it.first == ""){ continue; }
                file.Write(it.first);
				
                file.Write(it.second.成績[0][0]);
				file.Write(it.second.成績[1][0]);
				file.Write(it.second.成績[0][1]);
				file.Write(it.second.成績[1][1]);

                for (int a = 0; a < 24; ++a)
                {
                    file.Write(it.second.初期配置[a % 12][a / 12]);
                }
            }
        }
        else
        {
			file.ReadWrite(TDSystem::プレイ秒数.現在値);

            int num = 0;
            file.Read( num );

            for (int a = 0; a < num;++a)
            {
                std::string fileName;
                file.Read(fileName);

				file.Read(StageDataS[fileName].成績[0][0]);
				file.Read(StageDataS[fileName].成績[1][0]);
				file.Read(StageDataS[fileName].成績[0][1]);
				file.Read(StageDataS[fileName].成績[1][1]);

                for (int a = 0; a < 24; ++a)
                {
                    file.Read(StageDataS[fileName].初期配置[a % 12][a / 12]);
                }
            }
        }

        return true;
    }
}