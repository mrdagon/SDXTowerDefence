//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "IStage.h"
#include "Enemy.h"
#include "Wave.h"
#include "Struct/DataS.h"
#include "Design.h"
#include "Shot.h"
#include "ShotMotion.h"

namespace SDX_TD
{
    using namespace SDX;
    class Unit : public IObject
    {
    protected:
        virtual void Dead(){}

        double Get射程()
        {
            if (Witch::Main->is射程支援 && 支援補正 > 1.0)
            {
                return (double)st->射程[Lv] * 支援補正;
            }

            return (double)st->射程[Lv];
        }

    public:
        static const int Size = 2;//2x2角
        static const int WAIT_TIME = 6000;//回収、強化時間の基準値

		Rect shape;

        const UnitData *st;//ステータス
        int    Lv = 0;
        double 支援補正 = 1.0;//StageのSupportで再計算

        int    待機時間 = -1;//攻撃の待機
        int    残り売却時間 = -1;
        int    残り強化時間 = -1;
        int    強化or売却長さ = 1;
        bool   isジョブリスト = false;//画面左のジョブリスト用

        Unit(int X座標, int Y座標, UnitType 職種 , bool isリスト , int Lv) :
			shape(X座標, Y座標, Size * CHIP_SIZE / 2, Size * CHIP_SIZE / 2, Size * CHIP_SIZE / 2, Size * CHIP_SIZE / 2),
            st(&UnitDataS[職種]),
            isジョブリスト(isリスト),
            Lv(Lv)
        {
			Witch::Main->Mp -= st->コスト[Lv];

			--Witch::配置回数[職種];
			Witch::強化回数[職種] -= Lv;

			待機時間 = WAIT_TIME;

			MSound::設置.Play();
		}

		const IShape& GetShape() const { return shape; }

        /**配置時の描画処理.*/
        void Draw() const override
        {
            //選択中
            if (SStage->selectUnit == this)
            {
                MSystem::フレーム[1].Draw({ GetX() - CHIP_SIZE, GetY() - CHIP_SIZE, CHIP_SIZE * 2, CHIP_SIZE * 2 }, {255,128,128});
            }
            else
            {
                MSystem::フレーム[1].Draw({ GetX() - CHIP_SIZE, GetY() - CHIP_SIZE, CHIP_SIZE * 2, CHIP_SIZE * 2 });
            }

            //強化中or売却中
            if (残り強化時間 > 0)
            {
                //数値が増えていく
                int Num = 99 - 残り強化時間 * 99 / 強化or売却長さ;
                MFont::fontS[FontType::BMP黒].DrawExtend({ GetX() - 12, GetY() - 10 }, 2, 2, { 255, 120, 120 }, { std::setw(2), Num });
            }
            else if (残り売却時間 > 0)
            {
                //数値が減っていく
                int Num = 残り売却時間 * 99 / 強化or売却長さ;
                MFont::fontS[FontType::BMP黒].DrawExtend({ GetX() - 12, GetY() - 10 }, 2, 2, { 120, 120, 255 }, { std::setw(2), Num });
            }
            else
            {
                MUnit::魔女[st->職種][1]->DrawRotate({ GetX(), GetY() }, 1, 0);
            }

            //レベル表示
            for (int a = 0; a < Lv; ++a)
            {
                MSystem::マーク[3]->DrawRotate({ GetX() + 6 * a - 12, GetY() + 12 }, 1, 0);
            }
        }

        /**画面右の情報.*/
        void DrawInfo() override
        {
            namespace UI = UI_Unit;

            //画像&名前
            MSystem::フレーム[5].Draw(UI::R名前);
            MUnit::魔女[st->職種][1]->DrawRotate(UI::P画像, 2, 0);
            MFont::fontS[FontType::ゴシック中].DrawShadow(UI::P名前, Color::White, Color::Gray, st->名前);

            //レベル
            if (isジョブリスト)
            {
                //説明文
                MSystem::フレーム[5].Draw(UI::R説明);
                MFont::fontS[FontType::ゴシック小].DrawShadow(UI::P説明, Color::White, Color::Gray, st->説明文);
            }
            else
            {
                int 強化費 = 0;
                int 回収費 = int( st->コスト[Lv] * Witch::Main->回収率 );

                if (Lv != 5)
                {
                    強化費 = st->コスト[Lv + 1] - st->コスト[Lv];
                }

                //強化
                MSystem::フレーム[3].Draw(UI::R強化);
                MFont::fontS[FontType::ゴシック中].DrawShadow(UI::P強化, { 255, 0, 0 }, Color::Gray, "強化");
                MFont::fontS[FontType::ゴシック中].DrawExtend({ UI::P強化.x - 12, UI::P強化.y + 22 }, 1, 1, { 255, 128, 128 }, "－");
                MFont::fontS[FontType::BMP黒].DrawExtend({ UI::P強化.x - 4, UI::P強化.y + 22 }, 2, 2, Color::White, { std::setw(4), 強化費 });

                //売却or発動
                MSystem::フレーム[3].Draw(UI::R回収);
                if (st->is使い捨て)
                {
                    //発動
                    MFont::fontS[FontType::ゴシック中].DrawShadow(UI::P回収, Color::Blue, Color::Gray, "発動");
                }
                else
                {
                    //売却
                    MFont::fontS[FontType::ゴシック中].DrawShadow(UI::P回収, Color::Blue, Color::Gray, "回収");
                    MFont::fontS[FontType::ゴシック中].DrawExtend({ UI::P回収.x - 12, UI::P回収.y + 22 }, 1, 1, { 128, 128, 255 }, "+");
                    MFont::fontS[FontType::BMP黒].DrawExtend({ UI::P回収.x - 4, UI::P回収.y + 22 }, 2, 2, Color::White, { std::setw(4), 回収費 });
                }
            }

            //強化前後の性能
            DrawInfoState();
        }

        /**画面右の情報その2.*/
        void DrawInfoState()
        {
            namespace UI = UI_Unit;

            const bool 変化量表示 = (Lv != 5);

            IconType アイコン[5] =
            {
                IconType::レベル,
                IconType::攻撃,
                IconType::連射,
                IconType::支援,
                IconType::麻痺
            };
            int 性能[5] =
            {
                st->コスト[Lv],//上3つは確定、最大5つ
                (int)(st->攻撃力[Lv] * 支援補正),
                st->連射[Lv],
                (int)(st->支援効果[Lv] * 100),
                st->デバフ効果[Lv]
            };

            const int NextLv = (Lv + 1) % 5;

            int 次性能[5] =
            {
                st->コスト[NextLv],//上3つは確定、最大5つ
                (int)(st->攻撃力[NextLv] * 支援補正),
                st->連射[NextLv],
                (int)(st->支援効果[NextLv] * 100),
                st->デバフ効果[NextLv]
            };

            switch (st->デバフ種)
            {
            case DebuffType::鈍足:アイコン[4] = IconType::鈍足; break;
            case DebuffType::麻痺:アイコン[4] = IconType::麻痺; break;
            case DebuffType::吹飛:アイコン[4] = IconType::吹飛; break;
            case DebuffType::防壊:アイコン[4] = IconType::防壊; break;
            }

            int num = 0;

            //性能、現在値&次レベル値
            for (int a = 0; a < 5; ++a)
            {
                if (a >= 3 && 性能[a] <= 0) continue;

                MSystem::フレーム[5].Draw(UI::R性能[num], { 128, 128, 255 });

                //変化前
                MIcon::UI[アイコン[a]].Draw(UI::P性能アイコン[num]);
                int 桁数 = 5;
                if (!変化量表示) 桁数 = 10;

                MFont::fontS[FontType::BMP白].DrawExtend(UI::P性能[num], 2, 2, Color::White, { std::setw(桁数), 性能[a] });

                if (変化量表示)
                {
                    MFont::fontS[FontType::ゴシック中].Draw({ 565, UI::P性能アイコン[num].y + 8 }, Color::Yellow, "+");
                    MFont::fontS[FontType::BMP白].DrawExtend(UI::P性能[num], 2, 2, Color::Yellow, { std::setw(10), 次性能[a] - 性能[a] });
                }

                ++num;
            }
        }

        /**射程を表示する.*/
        void DrawRange()
        {
            const double 射程 = Get射程();
            const double 幅 = st->射程幅[Lv]/2;
            double x, y;
            const Color color = {255,255,255,128};

            if (isジョブリスト)
            {
                x = ( Input::mouse.x - CHIP_SIZE / 2) / CHIP_SIZE * CHIP_SIZE + CHIP_SIZE;
                y = ( Input::mouse.y - CHIP_SIZE / 2) / CHIP_SIZE * CHIP_SIZE + CHIP_SIZE;
            }
            else
            {
                x = GetX();
                y = GetY();
            }

            switch (st->射程種)
            {
            case RangeType::円:
                Drawing::Circle({ x, y, 射程 }, color, 0);
                Drawing::Circle({ x, y, 射程 }, Color::Red, 2);
                break;
            case RangeType::十字:				
                Drawing::Rect({ x -射程 , y -幅, 射程*2 , 幅*2 }, color);
                Drawing::Rect({ x - 幅, y - 射程, 幅*2, 射程-幅 }, color);
                Drawing::Rect({ x - 幅, y + 幅, 幅*2, 射程-幅 }, color);
                Drawing::Polygon
                    ({
                        {x-幅,y-幅},
                        {x-幅,y-射程},
                        {x+幅,y-射程},
                        {x+幅,y-幅},
                        {x+射程,y-幅},
                        {x+射程, y+幅 },
                        {x+幅, y+幅 },
                        {x+幅, y+射程 },
                        {x-幅, y+射程 },
                        {x-幅, y+幅 },
                        {x-射程, y+幅 },
                        {x-射程, y-幅 },
                        {x-幅, y-幅 }
                    },Color::Red, 2);
                break;
            default:
                break;
            }


        }

        /**.*/
        bool RemoveCheck() override
        {
            if (isRemove)
            {
                const int x = int(GetX() - Size * CHIP_SIZE) / CHIP_SIZE + 1;
                const int y = int(GetY() - Size * CHIP_SIZE) / CHIP_SIZE + 1;
                SStage->land.RemoveUnit(x, y, Size);
                SStage->ResetSelect(this);
                Remove();
            }

            return this->isRemove;
        }

        bool 強化開始()
        {
            if (	
                isジョブリスト ||
                Lv >= 5 ||
                残り強化時間 > 0 ||
                残り売却時間 > 0 ||
                !Witch::強化回数[st->職種]
                )
            { 
                return false; 
            }

            const int 必要MP = st->コスト[Lv + 1] - st->コスト[Lv];

            if (Witch::Main->Mp < 必要MP){ return false; }

            --Witch::強化回数[st->職種];

            Witch::Main->Mp -= 必要MP;

            残り強化時間 = int((Lv + 1) * (Lv + 1) * 60 * Witch::Main->強化速度);
            強化or売却長さ = 残り強化時間;

            //開始前、or強化速度=0の時は即LVアップ
            if (SStage->GetWave() == 0 || Witch::Main->強化速度 <= 0)
            {
                ++Lv;
                残り強化時間 = -1;
            }

            return true;
        }

        /** 売却処理or発動処理.*/
        bool 売却開始()
        {
            if (isジョブリスト) return false;
            if (残り強化時間 > 0 || 残り売却時間 > 0) return false;

            //開始前or回収速度=0の時は即回収
            if (SStage->GetWave() == 0 || Witch::Main->回収速度 <= 0)
            {
                isRemove = true;
                Witch::配置回数[st->職種]++;
                Witch::強化回数[st->職種] += Lv;
                Witch::Main->Mp += st->コスト[Lv];
                残り売却時間 = -1;
            }
            else
            {
                if (st->is使い捨て)
                {
                    //使い捨て
                    Shoot(nullptr);
                    isRemove = true;
                }
                else
                {
                    //売却
                    残り売却時間 = int((SStage->GetWave() + 1) * 60 * Witch::Main->回収速度);
                    強化or売却長さ = 残り売却時間;
                }
            }

            return true;
        }

        /**.*/
        void Act()
        {
            --残り売却時間;
            --残り強化時間;
            待機時間 -= st->連射[Lv];

            if (残り強化時間 == 0 )
            {
                MSound::強化.Play();
                Lv++;
                待機時間 = WAIT_TIME;
                return;
            }

            if (残り売却時間 == 0 )
            {
                MSound::売却.Play();
                Witch::Main->Mp += st->コスト[Lv] * Witch::Main->回収率;
                isRemove = true;

                //ウィッチは配置数が回復する
                if ((int)st->職種 < (int)WitchType::COUNT)
                {
                    Witch::配置回数[st->職種]++;
                }

                return;
            }

            if (待機時間 <= 0 && 残り売却時間 < 0 && 残り強化時間 < 0 && !st->is使い捨て )
            {
                Enemy* 対象 = CheckRange();
                
                if ( 対象 )
                {
                    //射程内に敵がいるなら攻撃					
                    Shoot(対象);
                    待機時間 = WAIT_TIME;
                }
            }
        }

        /**敵が射程内か判定.*/
        Enemy* CheckRange()
        {
            Enemy* 対象 = nullptr;
            double 射程 = Get射程();
            int 幅 = st->射程幅[Lv];

            switch (st->射程種)
            {
            case RangeType::円:
                //敵を選択中
                if (SStage->selectEnemy)
                {
                    const bool 地形対応 = (SStage->selectEnemy->st->移動種 == MoveType::空 && st->is対空) || (SStage->selectEnemy->st->移動種 != MoveType::空 && st->is対地);

                    if (地形対応 && GetDistance(SStage->selectEnemy) <= 射程)
                    {
                        対象 = SStage->selectEnemy;
                    }
                }

                //選択した敵が範囲外 or 敵未選択
                if (対象 == nullptr)
                {
                    対象 = SStage->GetNearEnemy(this, st->is対地, st->is対空);
                    if (!対象 || GetDistance(対象) > 射程)
                    {
                        対象 = nullptr;
                    }
                }
                break;
            case RangeType::十字:
                //敵を選択中
                if (SStage->selectEnemy)
                {
                    const bool 地形対応 = (SStage->selectEnemy->st->移動種 == MoveType::空 && st->is対空) || (SStage->selectEnemy->st->移動種 != MoveType::空 && st->is対地);

                    if (地形対応 && SStage->GetClossDistance(this,SStage->selectEnemy, 幅 ,射程) >= 0)
                    {
                        対象 = SStage->selectEnemy;
                    }
                }

                //選択した敵が範囲外 or 敵未選択
                if (対象 == nullptr)
                {
                    対象 = SStage->GetNearEnemyCloss(this, st->is対地, st->is対空,幅,射程);
                }

                break;
            }

            return 対象;
        }

        /**攻撃処理.*/
		using S勇者 = Shot < Circle, SpImage, MOTION::勇者 >;
		using S追尾 = Shot < Circle, SpImage, MOTION::追尾<SPEED::Liner> >;

		using S直進 = Shot < Circle, SpImage, MOTION::ToFront<SPEED::Liner> >;
		using S加速 = Shot < Circle, SpImage, MOTION::ToFront<SPEED::AccelLimit> >;
		using S回転 = Shot < Circle, SpImage, MOTION::回転 >;
		using S追跡 = Shot < Circle, SpImage, MOTION::追跡 >;

		void Shoot(Enemy *対象)
		{
			const double 速度 = st->弾速[Lv];
			const double 射程 = Get射程();
			double 角度 = 0;

			if (対象)
			{
				角度 = this->GetDirect(対象);
			}
			double 敵方向 = 角度;

			//入力省略,描画方法,移動方法
#define DEF { GetX(), GetY(), st->半径 },st,Lv,角度,支援補正

			for (int a = 0; a < st->Hit数[Lv]; ++a)
			{
				switch (st->職種)
				{
				case UnitType::ライナ://勇者強化					
					角度 = PAI * 2 * a / st->Hit数[Lv];
					SStage->Add(new S勇者(&MEffect::弾, { { GetX(), GetY() }, (int)Rand::Get(射程 / 2, 射程), 角度, 速度 / 10 }, DEF));
					break;
				case UnitType::ナツメ://僧侶強化
					SStage->Add(new Bomm({ GetX(), GetY(), 射程 }, st, Lv, 支援補正));
					break;
				case UnitType::ルコウ://騎士強化
					SStage->Add(new S加速(&MEffect::弾, { { -速度, 速度 / 30, 9999 } }, DEF), a * 3);
					break;
				case UnitType::ディアネラ://槍兵強化//八方向攻撃
					if (a == 0)
					{
						角度 -= DEG * 10 * (st->Hit数[Lv] / 2 + 1);
					}
					角度 += DEG * 10;
					SStage->Add(new S加速(&MEffect::弾, { { 速度 / 10, 速度 / 60, 速度 } }, DEF));
					break;
				case UnitType::ミナエ://剣豪強化
					角度 = 敵方向 + Rand::Get(-a * DEG * 5, a * DEG * 5);
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, { GetX(), GetY(), st->半径 }, st, Lv, 角度 + Rand::Get(-30 * DEG, 30 * DEG), 支援補正), a * 2);
					break;
				case UnitType::トレニア://斧兵強化/範囲吹き飛び
					SStage->Add(new S加速(&MEffect::弾, { { -速度, 0.1, 9999 } }, DEF));
					break;
				case UnitType::ロチエ://周囲鈍足
					SStage->Add(new Bomm({ GetX(), GetY(), 射程 }, st, Lv, 支援補正));
					break;
				case UnitType::バロゥ://全方向、防御低下
					角度 = PAI * 2 * a / st->Hit数[Lv];
					SStage->Add(new S追尾(&MEffect::弾, { 速度 , DEG * 2 }, DEF), a * 5);
					break;
				case UnitType::フィオナ://司祭強化
					if (a != 0) break;
					SStage->Add(new Beam({ GetX(), GetY(),角度, 1000 , 0 , 10 }, st, Lv, 支援補正, st->Hit数[Lv]));
					break;
				case UnitType::ナズナ://吹き飛び、直進弾
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, DEF));
					break;
				case UnitType::委員長://麻痺範囲、追尾
					SStage->Add(new S追跡(&MEffect::弾, { 速度 }, DEF), a * 10);
					break;
				case UnitType::ミルラ://防御低下、追尾
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, DEF));
					break;
				case UnitType::兵士://通路用A-単発直進
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, DEF));
					break;
				case UnitType::傭兵://通路用A-単発直進
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, DEF));
					break;
				case UnitType::足軽://通路用A-単発直進
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, DEF));
					break;
				case UnitType::技師://必中追尾A-単発型
					SStage->Add(new S追尾(&MEffect::弾, { 速度, DEG * 2 }, DEF));
					break;
				case UnitType::勇者://必中追尾B-周囲展開型
					角度 = PAI * 2 * a / st->Hit数[Lv];
					SStage->Add(new S勇者(&MEffect::弾, { { GetX(), GetY() }, (int)射程, 角度, 速度 / 10 }, DEF));
					break;
				case UnitType::剣士://連射A-単発直進
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, DEF));
					break;
				case UnitType::剣豪://連射B-乱射直進
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, { GetX(), GetY(), st->半径 }, st, Lv, 角度 + Rand::Get(-30 * DEG, 30 * DEG), 支援補正));
					break;
				case UnitType::槍士://3WAY直進
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, { GetX(),GetY(),st->半径 }, st, Lv, 角度 - (st->Hit数[Lv] * 5 - 5 + a * 10) * DEG, 支援補正));
					break;
				case UnitType::騎士://反射B-連射加速直進
					SStage->Add(new S加速(&MEffect::弾, { { -速度, 速度 / 20, 速度 * 2 } }, DEF), a * 10);
					break;
				case UnitType::斧士://吹き飛びA-後ろ射出加速
					SStage->Add(new S加速(&MEffect::弾, { { -速度, 0.1, 速度 * 10 } }, DEF));
					break;
				case UnitType::闘士://吹き飛びB-後ろ射出複数
					角度 = 敵方向 + Rand::Get(-PAI / 8, +PAI / 8);
					SStage->Add(new S加速(&MEffect::弾, { { -速度, 0.1, 速度 * 10 } }, DEF), a * 10);
					break;
				case UnitType::武闘家://防御破壊A-加速弾-8WAY					
					SStage->Add(new S加速(&MEffect::弾, { { 速度 , -速度 / 10, 速度 / 2 } }, { GetX(), GetY(), st->半径 }, st, Lv, a * PAI / 4, 支援補正));
					break;
				case UnitType::師範://防御破壊B-炸裂弾、周りぐるぐる
					SStage->Add(new S回転(&MEffect::弾, { { GetX(), GetY() }, a*PAI / 2, 速度, 射程 }, DEF));
					break;
				case UnitType::狩人://対空専用A-長射程、3連射
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, DEF), a * 10);
					break;
				case UnitType::射手://対空専用B-中射程、高連射
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, DEF));
					break;
				case UnitType::僧侶://対地範囲A-麻痺付与
					SStage->Add(new Bomm({ GetX(), GetY(), 射程 }, st, Lv, 支援補正));
					break;
				case UnitType::司祭://対地ビームB
					if (a != 0) break;
					SStage->Add(new Beam({ GetX(), GetY(), 角度, 1000, 0, 10 }, st, Lv, 支援補正, st->Hit数[Lv]));
					break;
				case UnitType::プリンス://短ビーム
					SStage->Add(new Beam({ GetX(), GetY(), 角度, 射程 , 0, 10 }, st, Lv, 支援補正, 1));
					break;
				case UnitType::プリンセス://連続ビーム
					SStage->Add(new Beam({ GetX() + 32, GetY(), 0		  , 射程 - 32, 0, (double)st->射程幅[Lv] }, st, Lv, 支援補正, 1));
					SStage->Add(new Beam({ GetX(), GetY() + 32, PAI / 2, 射程 - 32, 0, (double)st->射程幅[Lv] }, st, Lv, 支援補正, 1));
					SStage->Add(new Beam({ GetX() - 32, GetY(), PAI, 射程 - 32, 0, (double)st->射程幅[Lv] }, st, Lv, 支援補正, 1));
					SStage->Add(new Beam({ GetX(), GetY() - 32, PAI * 3 / 2, 射程 - 32, 0, (double)st->射程幅[Lv] }, st, Lv, 支援補正, 1));
					break;
				case UnitType::術士://範囲A-加速弾、命中時範囲攻撃
					SStage->Add(new S加速(&MEffect::弾, { { 0, 速度 / 10, 速度 } }, DEF));
					break;
				case UnitType::賢者://範囲B-ホーミング弾、命中時範囲攻撃
					SStage->Add(new S追跡(&MEffect::弾, { 速度 }, DEF), a * 10);
					break;
				case UnitType::踊り子://支援A-弱麻痺
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, DEF));
					break;
				case UnitType::軍師://支援B-弱吹飛
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, DEF));
					break;
				case UnitType::将軍://支援B-弱防御低下
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, DEF));
					break;
				case UnitType::執事://使い捨てA-円形使い捨て
					SStage->Add(new Bomm({ GetX(), GetY(), 射程 }, st, Lv, 支援補正));
					break;
				case UnitType::給仕://使い捨てB-十字使い捨て
					SStage->Add(new Beam({ GetX(), GetY(), 0, 1000, (double)st->射程幅[Lv] }, st, Lv, 支援補正, 1));
					SStage->Add(new Beam({ GetX(), GetY(), PAI / 2, 1000, (double)st->射程幅[Lv] }, st, Lv, 支援補正, 1));
					break;
				case UnitType::料理人://使い捨てB-円形使い捨て
					SStage->Add(new Bomm({ GetX(), GetY(), 射程 }, st, Lv, 支援補正));
					break;
				case UnitType::盗賊://鈍足A-高連射、直進弾
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, DEF));
					break;
				case UnitType::忍者://鈍足A-3-8方向、直進弾
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, DEF));
					break;
				case UnitType::くノ一://鈍足B-低連射、炸裂効果
					SStage->Add(new S直進(&MEffect::弾, { 速度 }, DEF));
					break;
				}
			}
#undef DEF
		}

    };
}