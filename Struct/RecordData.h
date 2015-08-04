//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "../System/EnumType.h"
#include "../System/Material.h"

namespace SDX_TD
{
    using namespace SDX;

    struct RecordData
    {
        std::string 名前;
		std::string 説明;
		double 目標値[3];

        void Set(const char* 名前, const char* 説明, std::array<double,3> 目標値)
        {
			this->名前 = 名前;
			this->説明 = 説明;
			this->目標値[0] = 目標値[0];
			this->目標値[1] = 目標値[1];
			this->目標値[2] = 目標値[2];
        }
    };


	struct ArchiveData
	{
		std::string 名前;
		std::string 説明;

		void Set(const char* 名前, const char* 説明)
		{
			this->名前 = 名前;
			this->説明 = 説明;
		}
	};

	EnumArray<ArchiveData, ArchiveType> ArchiveDataS;
    EnumArray<RecordData, RecordType> RecordDataS;

    void LoadRecordS()
    {
		//CSVファイルを読み込む
		File fileA("", FileMode::Read);
		File fileR("", FileMode::Read);

		auto strA = fileA.GetCsvToString2();
		auto strR = fileR.GetCsvToString2();


		for (int a = 0;a < int(ArchiveType::COUNT);++a)
		{
			ArchiveDataS[ArchiveType(a)].名前 = strA[a][0];
			ArchiveDataS[ArchiveType(a)].説明 = strA[a][1];
		}

		for (int a = 0;a< int(RecordType::COUNT);++a)
		{
			RecordDataS[RecordType(a)].Set(
				strR[a][0].c_str(),
				strR[a][1].c_str(),
				{
					std::stoi(strR[a][2]),
					std::stoi(strR[a][3]),
					std::stoi(strR[a][4])
				}								
			);
		}


		ArchiveDataS[ArchiveType::Wave100に到達した].Set("","");


	}
}