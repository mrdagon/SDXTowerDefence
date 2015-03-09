//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "EnumType.h"
#include "WitchData.h"//経験値、レベル、スキルポイント
#include "TDSystem.h"//設定等色々
#include "StageData.h"//ハイスコア等

namespace SDX_TD
{
	using namespace SDX;

	bool SaveAndLoad(FileMode 保存or読み込み)
	{
		//バイナリ形式で保存
		File file("file/save/save.dat", 保存or読み込み, false);

		if (file.GetFileMode() == FileMode::None){return false;}

		//古いバージョンのセーブデータを読み込む時のなんちゃら用
		file.ReadWrite(TDSystem::バージョン);

		for (auto &it : WitchDataS)
		{
			file.ReadWrite(it.レベル);
			file.ReadWrite(it.経験値);
		}

		file.ReadWrite(WitchData::最大スキルLv);
		file.ReadWrite(WitchData::スキルLv);

		for (auto &it : StageDataS)
		{
			file.ReadWrite(it.トライアル);
			file.ReadWrite(it.アンリミテッド);
			
			for (int a = 0; a < 24; ++a)
			{
				file.ReadWrite(it.初期配置[a/2][a%12]);
			}			
		}

		file.ReadWrite(TDSystem::資金);
		file.ReadWrite(TDSystem::素材数,4);

		file.ReadWrite(TDSystem::効果音の音量);
		file.ReadWrite(TDSystem::BGMの音量);

		file.ReadWrite(TDSystem::isグリッド);
		file.ReadWrite(TDSystem::isHPゲージ);
		file.ReadWrite(TDSystem::is高速);
		file.ReadWrite(TDSystem::isエフェクト);

		file.ReadWrite(TDSystem::isタッチ);

		file.ReadWrite(TDSystem::is常時リプレイ保存);
		file.ReadWrite(TDSystem::is更新リプレイ保存);
		file.ReadWrite(TDSystem::is勝利リプレイ保存);

		return true;
	}
}