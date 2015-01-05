﻿//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "IUnit.h"
#include "Design.h"
#include "Shot.h"
#include "ShotMotion.h"

namespace SDX_TD
{
	using namespace SDX;

	//弾の種類
	//発射方式
	class Unit : public IUnit
	{
	public:
		Rect shape;
		SpNull sprite;

		//配置位置
		Unit(UnitType 職種 , int X座標,int Y座標) :
			IUnit(shape, sprite, 職種, false),
			shape(X座標, Y座標, Size * CHIP_SIZE / 2, Size * CHIP_SIZE / 2, Size * CHIP_SIZE / 2, Size * CHIP_SIZE / 2)
		{
			Witch::Main->Mp -= st->コスト[0];
			--Witch::詠唱回数[職種];

			待機時間 = WAIT_TIME;

			MSound::設置.Play();
		}

		using S勇者 = Shot < Circle, SpImage, MOTION::勇者 >;
		using S追尾 = Shot < Circle, SpImage, MOTION::追尾<SPEED::Liner> >;

		template <class TSpeed = SPEED::Liner>
		using S直進 = Shot < Circle, SpImage, MOTION::ToFront<TSpeed> >;

		void Shoot(IEnemy *対象)
		{
			double 速度 = st->弾速[Lv];
			double 角度;
						
			if (対象)
			{
				角度 = this->GetDirect(対象);
			}

			MSound::攻撃.Play();

//入力省略,描画方法,移動方法
#define DEF { GetX(), GetY(), st->半径 },st,Lv,角度,支援補正
			switch (st->職種)
			{
			case UnitType::ライナ://勇者強化
				for (int a = 0; a < st->Hit数[Lv]; ++a)
				{
					角度 = PAI * 2 * a / st->Hit数[Lv];
					SStage->Add	( new S勇者(&MEffect::弾, { { GetX(), GetY() }, Rand::Get( st->射程[Lv]/2 , st->射程[Lv]), 角度 , 速度 / 10 }, DEF) );
				}
				break;
			case UnitType::ナツメ://武闘家強化
				break;
			case UnitType::ルコウ://騎士強化
				break;
			case UnitType::ディアネラ://プリンセス強化
				break;
			case UnitType::ミナエ://賢者強化
				break;
			case UnitType::トレニア://闘士強化
				break;
			case UnitType::ロチエ://くの一強化
				break;
			case UnitType::バロゥ://狩人強化
				break;
			case UnitType::フィオナ://司祭強化
				break;
			case UnitType::ナズナ://軍師強化
				break;
			case UnitType::委員長://僧侶強化
				break;
			case UnitType::ミルラ://将軍強化
				break;
			case UnitType::兵士://通路用A-単発直進
				//実装する
				SStage->Add(new S直進<>(&MEffect::弾, { 速度 }, DEF));
				break;
			case UnitType::傭兵://通路用A-単発直進
				break;
			case UnitType::足軽://通路用A-単発直進
				break;
			case UnitType::技師://必中追尾A-単発型
				//実装する
				SStage->Add(new S追尾(&MEffect::弾, { 速度, DEG }, DEF));
				break;
			case UnitType::勇者://必中追尾B-周囲展開型
				break;
			case UnitType::剣士://連射A-単発直進
				//実装する
				SStage->Add(new S直進<>(&MEffect::弾, { 速度 }, DEF));
				break;
			case UnitType::剣豪://連射B-乱射直進
				break;
			case UnitType::槍士://反射A-3WAY直進
				//実装する
				角度 -= (st->Hit数[Lv] - 1) * 5 * DEG;
				for (int a = 0; a < st->Hit数[Lv]; ++a)
				{
					角度 += 10*DEG;//10℃刻み
					SStage->Add(new S直進<>(&MEffect::弾, { 速度 }, DEF));
				}
				break;
			case UnitType::騎士://反射B-連射加速直進
				break;
			case UnitType::斧士://吹き飛びA-後ろ射出加速
				//実装する
				SStage->Add(new S直進<SPEED::Accel>(&MEffect::弾, { { -速度 , 0.1 } }, DEF));
				break;
			case UnitType::闘士://吹き飛びB-周囲回転
				break;
			case UnitType::武闘家://防御破壊A-加速弾-8WAY
				//実装する
				for (int a = 0; a < st->Hit数[Lv]; ++a)
				{
					角度 += PAI / 4;
					IShot* shot = new S直進<SPEED::AccelLimit>(&MEffect::弾, { { 速度 * 2, -0.1, 速度 } }, DEF);
					shot->lifeTime = 120;
					SStage->Add(shot);
				}
				break;
			case UnitType::師範://防御破壊B-炸裂弾、周りぐるぐる
				break;
			case UnitType::狩人://対空専用A-長射程、3連射
				//実装する
				SStage->Add(new S直進<>(&MEffect::弾, { 速度 }, DEF));
				break;
			case UnitType::射手://対空専用B-中射程、高連射
				break;
			case UnitType::僧侶://対地範囲A-麻痺付与
				break;
			case UnitType::司祭://対地ビームB
				break;
			case UnitType::プリンス://3-8方向攻撃
				break;
			case UnitType::プリンセス://3-8方向攻撃
				break;
			case UnitType::術士://範囲A-加速弾、命中時範囲攻撃
				//実装する
				SStage->Add(new S直進<SPEED::Accel>(&MEffect::弾, { { 0, 速度/10 } }, DEF));
				break;
			case UnitType::賢者://範囲B-ホーミング弾、命中時範囲攻撃
				break;
			case UnitType::踊り子://支援A-弱麻痺
				SStage->Add(new S直進<>(&MEffect::弾, { 速度 }, DEF));
				//実装する
				break;
			case UnitType::軍師://支援B-弱吹飛
				break;
			case UnitType::将軍://支援B-弱防御低下
				break;
			case UnitType::執事://使い捨てA-円形使い捨て
				//実装する
				SStage->Add(new Bomm({ GetX(), GetY(), (double)st->射程[Lv] }, st, Lv, 支援補正));
				break;
			case UnitType::給仕://使い捨てB-十字使い捨て
				break;
			case UnitType::料理人://使い捨てB-円形使い捨て
				break;
			case UnitType::盗賊://鈍足A-高連射、直進弾
				//実装する
				SStage->Add(new S直進<>(&MEffect::弾, { 速度 }, DEF));
				break;
			case UnitType::忍者://鈍足A-3-8方向、直進弾
				break;
			case UnitType::くノ一://鈍足B-低連射、炸裂効果
				break;
			}
#undef DEF
		}
	};
}