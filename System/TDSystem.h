//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "../Struct/DataS.h"
#include "../System/EnumType.h"

namespace SDX_TD
{
    using namespace SDX;
    class IUnit;

    /**グローバル変数用.*/
    namespace TDSystem
    {
        //この4つはStageSelectとStageで共通なのでグローバル変数
        Difficulty 難易度 = Difficulty::Easy;
        std::string 選択ステージ = StageType::Quest[0];

        bool isスキル = true;//notならスキル効果無し
        bool isカップル = true;//notならシングル
		bool isクエスト = true;//クエストモードならture
		GameType ゲームモード = GameType::クエスト;

        int バージョン = 104;//

        //アイテム関連
		int レベル = 1;
        int 最大スキルポイント = 5;
        int 残りスキルポイント = 5;
		bool isクエスト開放[StageType::COUNT] = { true , true , false};
		double 経験値 = 0;
        //ランダムステージの状況
		Difficulty 限界難易度 = Difficulty::Easy;

        //実績関連-各ウィッチ毎に保存するのと全体のと
		EnumArray<bool,ArchiveType> 実績;

		//個別実績は達成度合いに応じてマークを付ける
		//実績14個 
		//全体記録 1P
		//ウィッチ記録 1×12P
		//ユニット記録 6P
		//20P

		struct RecordData
		{
			std::string 名前;
			std::string 説明;
			double 現在値 = 0;
			double 目標値[3];

			void Set(const char* 名前, const char* 説明, std::array<double, 3> 目標値)
			{
				this->名前 = 名前;
				this->説明 = 説明;
				this->目標値[0] = 目標値[0];
				this->目標値[1] = 目標値[1];
				this->目標値[2] = 目標値[2];
			}

			void Set(std::vector<std::string>& csvデータ)
			{
				this->名前 = csvデータ[0];
				this->説明 = csvデータ[1];
				this->目標値[0] = std::stod(csvデータ[2]);
				this->目標値[1] = std::stod(csvデータ[3]);
				this->目標値[2] = std::stod(csvデータ[4]);
			}

			//目標を達成しているか判定
			int CheckRank()
			{
				if (現在値 >= 目標値[2]) return 3;
				if (現在値 >= 目標値[1]) return 2;
				if (現在値 >= 目標値[0]) return 1;
				return 0;
			}
		};

		//1P14個で丁度良さそう？あるいは14x3で7P

		RecordData プレイ秒数;//Save時に処理
		RecordData 合計スキルLv;//仕様変更も検討
		RecordData 合計Wave;//Stageで処理
		RecordData 合計獲得資金;//Enemyで処理
		RecordData 合計消費資金;//Unitで処理

		RecordData 合計回収回数;//Unitで処理
		RecordData 合計仕事回数;//Unitで処理
		RecordData 合計獲得EXP;//SceneResultで処理
		RecordData ザコ撃破数;//Enemyで処理
		RecordData ボス撃破数;//Enemyで処理

		RecordData シングル総スコア;//StageDataで計算
		RecordData タッグ総スコア;//StageDataで計算
		RecordData クエスト銀星数;//StageDataで計算
		RecordData クエスト金星数;//StageDataで計算

		//ウィッチ個別の実績 12,12,78,12
		EnumArray<RecordData, WitchType> クリア回数;//SceneResultで処理
		EnumArray<RecordData, WitchType> パーフェクト回数;//SceneResultで処理
		EnumArray<RecordData, WitchType> 大魔法回数;//Witchで処理
		EnumArray<EnumArray<RecordData,WitchType>, WitchType> タッグ回数;//SceneResultで処理

		//ユニット種別の実績,42種類 = 14✕3 
		EnumArray<RecordData, UnitType> 配置回数;//Unitで処理
		EnumArray<RecordData, UnitType> 強化回数;//Unitで処理

		//ザコ&ボス撃破数
		EnumArray<int, EnemyType> 種族撃破数;//Enemyで処理
		EnumArray<int, EnemyType> 種族ボス撃破数;//Enemyで処理

        //設定関連
        int 効果音の音量 = 3;//0～10
        int BGMの音量 = 3;//0～10

		bool isグリッド = false;//マスのグリッドと中央の薄い十字の表示
        bool isHPゲージ = true;//敵Hpゲージの表示ON/OFF
		bool is高速 = false;//ゲーム速度を1,4,16,64倍速モードにする
		bool isエフェクト省略 = false;//死亡時エフェクト,大魔法カットインのON/OFF
        bool is配置記録 = true;//初期配置の記録を行なうかどうか
		bool isリプレイ保存 = false;//常にリプレイの自動保存フラグ

        bool isタッチ = false;//タブレット用の操作スタイルフラグ
		bool isフルスクリーン = false;//フルスクリーンフラグ

		//Lvアップ判定処理
		int CheckLVUp()
		{
			int num = 0;

			while ( 経験値 >= std::min(レベル * 10000,1000000))
			{
				経験値 -= std::min(レベル * 10000, 1000000);
				++レベル;
				++最大スキルポイント;
				++残りスキルポイント;
				++num;
			}

			return num;
		}

    }
}