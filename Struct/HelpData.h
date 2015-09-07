//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
namespace SDX_TD
{
	using namespace SDX;
	/**ユニット初期配置の情報.*/
	struct HelpData
	{
		std::string 題名;
		Image* 説明画像;
		std::string 説明文;
	};

	std::array<HelpData, 20> HelpDataS;

	void LoadHelpS()
	{
		for (int a = 0;a < 20;++a)
		{
			std::string fileName = "file/help/help";
			fileName += a;
			fileName += ".txt";
			File file( fileName.c_str() , FileMode::Read);
			auto strS = file.GetLineS();
			//一行目はタイトル兼ボタン名
			HelpDataS[a].題名 = strS[0];
			//二行目はインデックス画像ファイル名
			if (strS[1].length() > 3)
			{
				HelpDataS[a].説明画像->Load( strS[1].c_str() );
			}
			//三行目以降は説明文
			for (unsigned int b = 2; b < strS.size(); ++b)
			{
				HelpDataS[a].説明文 += strS[b];
			}
		}
	}
}