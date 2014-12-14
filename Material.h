//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include <SDXFramework.h>
#include "EnumType.h"

namespace SDX_TD
{
	using namespace SDX;

	/**敵＆ウィッチの画像.*/
	namespace MUnit
	{
		EnumArray<ImagePack, UnitType> 魔女;
		EnumArray<ImagePack, EnemyType> 敵;

		static void Load()
		{
			魔女[UnitType::ライナ].Load("File/Unit/Witch/Lina.png", 9, 3, 3);
			魔女[UnitType::ナツメ].Load("File/Unit/Witch/Natsume.png", 9, 3, 3);
			魔女[UnitType::ルコウ].Load("File/Unit/Witch/Rukou.png", 9, 3, 3);
			魔女[UnitType::ディアネラ].Load("File/Unit/Witch/Dianella.png", 9, 3, 3);
			魔女[UnitType::ミナエ].Load("File/Unit/Witch/Minae.png", 9, 3, 3);
			魔女[UnitType::トレニア].Load("File/Unit/Witch/Torenia.png", 9, 3, 3);
			魔女[UnitType::ロチエ].Load("File/Unit/Witch/Rochie.png", 9, 3, 3);
			魔女[UnitType::バロゥ].Load("File/Unit/Witch/Barrow.png", 9, 3, 3);
			魔女[UnitType::フィオナ].Load("File/Unit/Witch/Fiona.png", 9, 3, 3);
			魔女[UnitType::ナズナ].Load("File/Unit/Witch/Nazuna.png", 9, 3, 3);
			魔女[UnitType::委員長].Load("File/Unit/Witch/Chairwoman.png", 9, 3, 3);
			魔女[UnitType::ミルラ].Load("File/Unit/Witch/Myrra.png", 9, 3, 3);

			魔女[UnitType::兵士].Load("File/Unit/Common/000.png", 9, 3, 3);
			魔女[UnitType::踊り子].Load("File/Unit/Common/001.png", 9, 3, 3);
			魔女[UnitType::狩人].Load("File/Unit/Common/002.png", 9, 3, 3);
			魔女[UnitType::執事].Load("File/Unit/Common/003.png", 9, 3, 3);
			魔女[UnitType::技師].Load("File/Unit/Common/004.png", 9, 3, 3);
			魔女[UnitType::くノ一].Load("File/Unit/Common/005.png", 9, 3, 3);
			魔女[UnitType::師範].Load("File/Unit/Common/006.png", 9, 3, 3);
			魔女[UnitType::術士].Load("File/Unit/Common/007.png", 9, 3, 3);
			魔女[UnitType::賢者].Load("File/Unit/Common/008.png", 9, 3, 3);
			魔女[UnitType::武闘家].Load("File/Unit/Common/009.png", 9, 3, 3);
			魔女[UnitType::忍者].Load("File/Unit/Common/010.png", 9, 3, 3);
			魔女[UnitType::剣豪].Load("File/Unit/Common/011.png", 9, 3, 3);
			魔女[UnitType::料理人].Load("File/Unit/Common/012.png", 9, 3, 3);
			魔女[UnitType::勇者].Load("File/Unit/Common/013.png", 9, 3, 3);
			魔女[UnitType::射手].Load("File/Unit/Common/014.png", 9, 3, 3);
			魔女[UnitType::盗賊].Load("File/Unit/Common/015.png", 9, 3, 3);
			魔女[UnitType::騎士].Load("File/Unit/Common/016.png", 9, 3, 3);
			魔女[UnitType::司祭].Load("File/Unit/Common/017.png", 9, 3, 3);
			魔女[UnitType::僧侶].Load("File/Unit/Common/018.png", 9, 3, 3);
			魔女[UnitType::闘士].Load("File/Unit/Common/019.png", 9, 3, 3);
			魔女[UnitType::斧士].Load("File/Unit/Common/020.png", 9, 3, 3);
			魔女[UnitType::傭兵].Load("File/Unit/Common/021.png", 9, 3, 3);
			魔女[UnitType::プリンス].Load("File/Unit/Common/022.png", 9, 3, 3);
			魔女[UnitType::プリンセス].Load("File/Unit/Common/023.png", 9, 3, 3);
			魔女[UnitType::剣士].Load("File/Unit/Common/024.png", 9, 3, 3);
			魔女[UnitType::槍士].Load("File/Unit/Common/025.png", 9, 3, 3);
			魔女[UnitType::給仕].Load("File/Unit/Common/026.png", 9, 3, 3);
			魔女[UnitType::足軽].Load("File/Unit/Common/027.png", 9, 3, 3);
			魔女[UnitType::将軍].Load("File/Unit/Common/028.png", 9, 3, 3);
			魔女[UnitType::軍師].Load("File/Unit/Common/029.png", 9, 3, 3);

			敵[EnemyType::ゼリー].Load("File/Enemy/000.png", 9, 3, 3);
			敵[EnemyType::ゴブリン].Load("File/Enemy/001.png", 9, 3, 3);
			敵[EnemyType::ケットシー].Load("File/Enemy/002.png", 9, 3, 3);
			敵[EnemyType::オーガ].Load("File/Enemy/003.png", 9, 3, 3);
			敵[EnemyType::マーマン].Load("File/Enemy/004.png", 9, 3, 3);
			敵[EnemyType::ゴーレム].Load("File/Enemy/005.png", 9, 3, 3);
			敵[EnemyType::ケルベロス].Load("File/Enemy/006.png", 9, 3, 3);
			敵[EnemyType::スケルトン].Load("File/Enemy/007.png", 9, 3, 3);
			敵[EnemyType::シャーマン].Load("File/Enemy/008.png", 9, 3, 3);
			敵[EnemyType::コボルド].Load("File/Enemy/009.png", 9, 3, 3);
			敵[EnemyType::ゼリー王].Load("File/Enemy/010.png", 9, 3, 3);
			敵[EnemyType::ドラゴン].Load("File/Enemy/011.png", 9, 3, 3);
			敵[EnemyType::インプ].Load("File/Enemy/012.png", 9, 3, 3);
			敵[EnemyType::ロボット].Load("File/Enemy/013.png", 9, 3, 3);
			敵[EnemyType::グリフィン].Load("File/Enemy/014.png", 9, 3, 3);
		}
	}

	/**その他のアイコン.*/
	namespace MIcon
	{
		ImagePack ターゲット;
		EnumArray<Image, IconType> UI;
		EnumArray<Image, WitchType> 魔導具;
		EnumArray<Image, Element> 属性;

		static void Load()
		{
			ターゲット.Load("File/System/target.png", 3, 3, 1);

			UI[IconType::ライフ].Load("File/System/icon/000.png");
			UI[IconType::マナ].Load("File/System/icon/001.png");
			UI[IconType::レベル].Load("File/System/icon/002.png");
			UI[IconType::攻撃].Load("File/System/icon/003.png");
			UI[IconType::連射].Load("File/System/icon/004.png");
			UI[IconType::支援].Load("File/System/icon/005.png");
			UI[IconType::鈍足].Load("File/System/icon/006.png");
			UI[IconType::麻痺].Load("File/System/icon/007.png");
			UI[IconType::強化].Load("File/System/icon/008.png");
			UI[IconType::吹飛].Load("File/System/icon/009.png");
			UI[IconType::防壊].Load("File/System/icon/010.png");
			UI[IconType::速度].Load("File/System/icon/011.png");
			UI[IconType::回避].Load("File/System/icon/012.png");
			UI[IconType::防御].Load("File/System/icon/013.png");
			UI[IconType::回復].Load("File/System/icon/014.png");

			魔導具[WitchType::ライナ].Load("File/Unit/artifact/000.png");
			魔導具[WitchType::ナツメ].Load("File/Unit/artifact/001.png");
			魔導具[WitchType::ルコウ].Load("File/Unit/artifact/002.png");
			魔導具[WitchType::ディアネラ].Load("File/Unit/artifact/003.png");
			魔導具[WitchType::ミナエ].Load("File/Unit/artifact/004.png");
			魔導具[WitchType::トレニア].Load("File/Unit/artifact/005.png");
			魔導具[WitchType::ロチエ].Load("File/Unit/artifact/006.png");
			魔導具[WitchType::バロゥ].Load("File/Unit/artifact/007.png");
			魔導具[WitchType::フィオナ].Load("File/Unit/artifact/008.png");
			魔導具[WitchType::ナズナ].Load("File/Unit/artifact/009.png");
			魔導具[WitchType::委員長].Load("File/Unit/artifact/010.png");
			魔導具[WitchType::ミルラ].Load("File/Unit/artifact/011.png");

			属性[Element::炎].Load("File/Unit/element/000.png");
			属性[Element::氷].Load("File/Unit/element/001.png");
			属性[Element::空].Load("File/Unit/element/002.png");
			属性[Element::樹].Load("File/Unit/element/003.png");
			属性[Element::無].Load("File/Unit/element/004.png");
		}
	}

	/**エフェクトや弾.*/
	namespace MEffect
	{
		Image 弾;

		static void Load()
		{
			弾.Load("File/Effect/shot000.png");
		}
	}

	/**UI等のシステム.*/
	namespace MSystem
	{
		ImagePack マップチップ;
		ImagePack 枠画像[14];
		BmpFrame  フレーム[14];

		ImagePack マーク;

		Image 背景;

		static void Load()
		{
			マップチップ.Load("File/System/mapchip.png", 10, 10, 1);
			枠画像[0].Load("File/System/frame000.png", 9, 3, 3);
			枠画像[1].Load("File/System/frame001.png", 9, 3, 3);
			枠画像[2].Load("File/System/frame002.png", 9, 3, 3);
			枠画像[3].Load("File/System/frame003.png", 9, 3, 3);
			枠画像[4].Load("File/System/frame004.png", 9, 3, 3);
			枠画像[5].Load("File/System/frame005.png", 9, 3, 3);
			枠画像[6].Load("File/System/frame006.png", 9, 3, 3);
			枠画像[7].Load("File/System/frame007.png", 9, 3, 3);
			枠画像[8].Load("File/System/frame008.png", 9, 3, 3);
			枠画像[9].Load("File/System/frame009.png", 9, 3, 3);
			枠画像[10].Load("File/System/frame010.png", 9, 3, 3);
			枠画像[11].Load("File/System/frame011.png", 9, 3, 3);
			枠画像[12].Load("File/System/frame012.png", 9, 3, 3);
			枠画像[13].Load("File/System/frame013.png", 9, 3, 3);

			for (int a = 0; a < 14; ++a)
			{
				フレーム[a].Make(&枠画像[a]);
			}

			フレーム[1].Make(&枠画像[1]);
			フレーム[2].Make(&枠画像[2]);
			フレーム[3].Make(&枠画像[3]);
			フレーム[4].Make(&枠画像[4]);
			フレーム[5].Make(&枠画像[5]);
			フレーム[6].Make(&枠画像[6]);
			フレーム[7].Make(&枠画像[7]);
			フレーム[8].Make(&枠画像[8]);
			フレーム[9].Make(&枠画像[9]);

			背景.Load("File/System/back000.jpg");

			マーク.Load("File/System/mark.png", 4, 4, 1);
		}
	}

	/**BGM.*/
	namespace MMusic
	{
		static void Load()
		{
		}
	}

	/**効果音.*/
	namespace MSound
	{
		static void Load()
		{
		}
	}

	/**フォント.*/
	namespace MFont
	{
		Font ゴシック小;
		Font ゴシック中;
		Font BMP黒;
		Font BMP黒影;
		Font BMP白;

		ImagePack 英語;
		ImagePack 英影;
		ImagePack 黒数字;
		ImagePack 黒影;
		ImagePack 白数字;

		static void Load()
		{
			ゴシック小.Load(SystemFont::Gothic, 12,0);
			ゴシック中.Load(SystemFont::Gothic, 16,0);
			BMP黒.Load("", 6,0);
			BMP黒影.Load("", 7, 0);
			BMP白.Load("", 6, 0);

			英語.Load("File/Font/font2.png", 30, 10, 3);
			英影.Load("File/Font/font.png", 30, 10, 3);
			黒影.Load("File/Font/font_num_black.png", 10, 10, 1);
			黒数字.Load("File/Font/font_num_black2.png", 10, 10, 1);
			白数字.Load("File/Font/font_num_white.png", 10, 10, 1);

			//フォント調整_____a__b__c__d__e__f__g__h__i__j__k__l__m__n__o__p__q__r__s__t__u__v__w__x__y__z
			英語.AdjustWidth({ 1, 3, 2, 2, 3, 3, 1, 2, 4, 2, 3, 2, 0, 1, 1, 2, 1, 2, 2, 2, 1, 1, 0, 1, 2, 2 });
			英影.AdjustWidth({ 1, 3, 2, 2, 3, 3, 1, 2, 4, 2, 3, 2, 0, 1, 1, 2, 1, 2, 2, 2, 1, 1, 0, 1, 2, 2 });

			BMP黒.SetImageS("a", &英語, 26);
			BMP黒.SetImageS("A", &英語, 26);
			BMP黒.SetImageS("0", &黒数字, 10);
			BMP黒.SetImage("×", 英語[26]);
			BMP黒.SetImage("□", 英語[27]);
			BMP黒.SetImage("○", 英語[28]);
			BMP黒.SetImage("☆", 英語[29]);

			BMP黒影.SetImageS("a", &英影, 26);
			BMP黒影.SetImageS("A", &英影, 26);
			BMP黒影.SetImageS("0", &黒影, 10);
			BMP黒影.SetImage("×", 英影[26]);
			BMP黒影.SetImage("□", 英影[27]);
			BMP黒影.SetImage("○", 英影[28]);
			BMP黒影.SetImage("☆", 英影[29]);


			BMP白.SetImageS("0", &白数字, 10);
		}
	}

	static void LoadMaterial()
	{
		//Loading::Start();
		MUnit::Load();
		MUnit::Load();
		MIcon::Load();
		MEffect::Load();
		MSystem::Load();

		MMusic::Load();
		MSound::Load();
		MFont::Load();

		//Loading::End();
	}
}