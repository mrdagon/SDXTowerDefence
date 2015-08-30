//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "../System/EnumType.h"
#include "../System/Material.h"
#include "../System/TDSystem.h"
#include "../Struct/WitchData.h"

namespace SDX_TD
{
    using namespace SDX;

    void LoadRecordS()
    {

		for (auto it : TDSystem::実績)
		{
			it.目標値[2] = 1;
		}

        //CSVファイルを読み込む
        File fileR("file/data/record_data.csv", FileMode::Read);
        auto strR = fileR.GetCsvToString2();

        TDSystem::プレイ秒数.Set(strR[0]);
        TDSystem::合計スキルLv.Set(strR[1]);
        TDSystem::合計Wave.Set(strR[2]);
        TDSystem::合計獲得資金.Set(strR[3]);
        TDSystem::合計消費資金.Set(strR[4]);
        
        TDSystem::合計回収回数.Set(strR[5]);
        TDSystem::合計仕事回数.Set(strR[6]);
        TDSystem::合計獲得EXP.Set(strR[7]);
        TDSystem::ザコ撃破数.Set(strR[8]);
        TDSystem::ボス撃破数.Set(strR[9]);

        TDSystem::シングル総スコア.Set(strR[10]);
        TDSystem::タッグ総スコア.Set(strR[11]);
        TDSystem::クエスト銀星数.Set(strR[12]);
        TDSystem::クエスト金星数.Set(strR[13]);

        //ウィッチ個別の実績 12,12,78,12
		std::string アイコン文字[42] =
		{
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","⑩",
			"⑪","⑫","⑬","⑭","⑮","⑯","⑰","⑱","⑲","⑳",
			"㉑","㉒","㉓","㉔","㉕","㉖","㉗","㉘","㉙","㉚",
			"㉛","㉜","㉝","㉞","㉟","㊱","㊲","㊳","㊴","㊵",
			"㊶","㊷"
		};

        for (int a = 0;a<int(WitchType::COUNT);++a)
        {
            TDSystem::クリア回数[WitchType(a)].Set(strR[14], アイコン文字[a].c_str());
            TDSystem::パーフェクト回数[WitchType(a)].Set(strR[15], アイコン文字[a].c_str());
            TDSystem::大魔法回数[WitchType(a)].Set(strR[16], アイコン文字[a].c_str());
            for (int b = 0;b<int(WitchType::COUNT);++b)
            {
                TDSystem::タッグ回数[WitchType(b)][WitchType(a)].Set(strR[17] , (アイコン文字[b]+ アイコン文字[a]).c_str());
            }
        }

        //ユニット種別の実績,42種類 = 14✕3 
        for (int a = 0;a<int(UnitType::COUNT);++a)
        {
            TDSystem::配置回数[UnitType(a)].Set(strR[18] , アイコン文字[a].c_str() );
            TDSystem::強化回数[UnitType(a)].Set(strR[19] , アイコン文字[a].c_str() );
        }

		//数が少ないので直接代入
		TDSystem::実績[ArchiveType::チュートリアルクリア].名前 = "チュートリアルクリア";
		TDSystem::実績[ArchiveType::全てのウィッチでクリア].名前 = "全てのウィッチでクリア";
		TDSystem::実績[ArchiveType::全てのユニットを使う].名前 = "全てのユニットを使う";
		TDSystem::実績[ArchiveType::全てのクエストクリア].名前 = "全てのクエストクリア";
		TDSystem::実績[ArchiveType::フリーステージクリア].名前 = "フリーステージクリア";
		TDSystem::実績[ArchiveType::ユニットを最大LVに強化].名前 = "ユニットを最大LVに強化";
		TDSystem::実績[ArchiveType::全種類の敵を撃破].名前 = "全種類の敵を撃破";
		TDSystem::実績[ArchiveType::全種類のボスを撃破].名前 = "全種類のボスを撃破";
		TDSystem::実績[ArchiveType::強化無しで最高難易度をクリア].名前 = "強化無しで最高難易度をクリア";
		TDSystem::実績[ArchiveType::強化有りで最高難易度をクリア].名前 = "強化有りで最高難易度をクリア";
		TDSystem::実績[ArchiveType::Wave100に到達].名前 = "Wave100に到達";
		TDSystem::実績[ArchiveType::全ての強化LVが100超え].名前 = "全ての強化LVが100超え";
		TDSystem::実績[ArchiveType::全ての強化LVを限界まで上げた].名前 = "全ての強化LVを限界まで上げた";
		TDSystem::実績[ArchiveType::全ての金勲章を取得した].名前 = "全ての金勲章を取得した";

		for (auto& it : TDSystem::実績)
		{
			it.目標値[0] = 1;
			it.目標値[1] = 1;
			it.目標値[2] = 1;
		}

    }

    void CheckArchiveS()
    {		
        //実績等の判定処理
        //TDSystem::実績[ArchiveType::チュートリアルクリア];//未実装
        for (auto it : TDSystem::クリア回数)
        {
            if (it.現在値 <= 0)
            {
                TDSystem::実績[ArchiveType::全てのウィッチでクリア].現在値 = false;
                break;
            }
            TDSystem::実績[ArchiveType::全てのウィッチでクリア].現在値 = true;
        }

        for (auto it : TDSystem::配置回数)
        {
            if (it.現在値 <= 0)
            {
                TDSystem::実績[ArchiveType::全てのユニットを使う].現在値 = false;
                break;
            }
            TDSystem::実績[ArchiveType::全てのユニットを使う].現在値 = true;
        }
    
        //TDSystem::実績[ArchiveType::フリーステージクリア];SceneResult::Init()で判定
        //TDSystem::実績[ArchiveType::ユニットを最大LVに強化];Unit::Actで処理、開始前に最大レベルにしても実績解除されない仕様

        for (auto it : TDSystem::種族撃破数)
        {
            if (it <= 0)
            {
                TDSystem::実績[ArchiveType::全種類の敵を撃破].現在値 = false;
                break;
            }
            TDSystem::実績[ArchiveType::全種類の敵を撃破].現在値 = true;
        }

        for (auto it : TDSystem::種族ボス撃破数)
        {
            if (it <= 0)
            {
                TDSystem::実績[ArchiveType::全種類のボスを撃破].現在値 = false;
                break;
            }
            TDSystem::実績[ArchiveType::全種類のボスを撃破].現在値 = true;
        }

        //TDSystem::実績[ArchiveType::強化無しで最高難易度をクリア];SceneResult::Init()で処理
        //TDSystem::実績[ArchiveType::強化有りで最高難易度をクリア];SceneResult::Init()で処理
        //TDSystem::実績[ArchiveType::Wave100に到達]; Stage::NextWave()で処理

        TDSystem::実績[ArchiveType::全ての強化LVが100超え].現在値 = true;
        TDSystem::実績[ArchiveType::全ての強化LVを限界まで上げた].現在値 = true;

        for (auto it : WitchData::スキルLv)
        {
            if (it < 9999)
            {
                TDSystem::実績[ArchiveType::全ての強化LVを限界まで上げた].現在値 = false;
            }
            if (it < 100)
            {
                TDSystem::実績[ArchiveType::全ての強化LVが100超え].現在値 = false;
                break;
            }
        }

        //ここから全記録Goldかの判定
        if( TDSystem::プレイ秒数.CheckRank() != 3 ) return;
        if (TDSystem::合計スキルLv.CheckRank() != 3 ) return;
        if (TDSystem::合計Wave.CheckRank() != 3 ) return;
        if (TDSystem::合計獲得資金.CheckRank() != 3 ) return;
        if (TDSystem::合計消費資金.CheckRank() != 3 ) return;

        if (TDSystem::合計回収回数.CheckRank() != 3 ) return;
        if (TDSystem::合計仕事回数.CheckRank() != 3 ) return;
        if (TDSystem::ザコ撃破数.CheckRank() != 3 ) return;
        if (TDSystem::ボス撃破数.CheckRank() != 3 ) return;
        if (TDSystem::合計Wave.CheckRank() != 3 ) return;

        if (TDSystem::シングル総スコア.CheckRank() != 3) return;
        if (TDSystem::タッグ総スコア.CheckRank() != 3) return;
        if (TDSystem::クエスト銀星数.CheckRank() != 3) return;
        if (TDSystem::クエスト金星数.CheckRank() != 3) return;

        //ウィッチ個別の実績 12,12,78,12
        for (auto it : TDSystem::クリア回数){if(it.CheckRank() != 3) return;}
        for (auto it : TDSystem::パーフェクト回数) { if (it.CheckRank() != 3) return; }
        for (auto it : TDSystem::大魔法回数) { if (it.CheckRank() != 3) return; }
        for (auto it : TDSystem::タッグ回数){for (auto itt : it){if (itt.CheckRank() != 3) return;}}

        //ユニット種別の実績,42種類 = 14✕3 
        for (auto it : TDSystem::配置回数) { if (it.CheckRank() != 3) return; }
        for (auto it : TDSystem::強化回数) { if (it.CheckRank() != 3) return; }

        //全条件達成してたらtrue
        TDSystem::実績[ArchiveType::全ての金勲章を取得した].現在値 = true;
    }
}