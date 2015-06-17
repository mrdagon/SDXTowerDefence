//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include <SDXFramework.h>
#include "Struct/DataS.h"
#include "System/Material.h"
#include "System/TDSystem.h"

namespace SDX_TD
{
	using namespace SDX;

	/**地形データ.*/
	class Land
	{
	public:
		/**各移動タイプ毎の最短経路.*/
		class Route
		{
		public:
			int  距離[MAP_SIZE][MAP_SIZE];
			int  経路[MAP_SIZE][MAP_SIZE];
			bool is通行[MAP_SIZE][MAP_SIZE];
			MoveType 移動種;
			std::vector<int> 計算リスト;

			Route(MoveType 移動種) :
				移動種(移動種)
			{}

			bool Check通行(ChipType 地形種)
			{
				switch (移動種)
				{
				case MoveType::空:
					return 地形種 != ChipType::高山;
					break;
				case MoveType::陸:
					return ChipDataS[地形種].is陸移動;
					break;
				case MoveType::水:
					return ChipDataS[地形種].is水移動;
				default:
					return false;
				}
			}

			/**.*/
			void Init(const Land& 土地)
			{
				for (int a = 0; a < MAP_SIZE; ++a){
					for (int b = 0; b < MAP_SIZE; ++b)
					{
						//魔法が配置されていて、飛行していない場合、通行不可能
						if (移動種 != MoveType::空 && 土地.is魔法[a][b] == true)
						{
							is通行[a][b] = false;
							continue;
						}

						is通行[a][b] = Check通行(土地.地形[a][b]);
					}
				}
				経路再計算(土地);
			}

			/**.*/
			int 方向計算(int 現在の方向, int X座標, int Y座標)
			{
				//012
				//345
				//678

				int direct = 経路[X座標 / CHIP_SIZE][Y座標 / CHIP_SIZE];//現在のマスの向き

				const int def = 6;

				switch (direct)
				{
				case 1://上
					if (現在の方向 == 0 && X座標 % CHIP_SIZE > def ) break;
					if (現在の方向 == 2 && X座標 % CHIP_SIZE < def) break;
					if (is通行[(X座標 - def) / CHIP_SIZE][Y座標 / CHIP_SIZE - 1] && is通行[(X座標 + def) / CHIP_SIZE][Y座標 / CHIP_SIZE - 1]) return direct;
					break;
				case 3://左
					if (現在の方向 == 0 && Y座標 % CHIP_SIZE > def) break;
					if (現在の方向 == def && Y座標 % CHIP_SIZE < def ) break;
					if (is通行[X座標 / CHIP_SIZE - 1][(Y座標 - def ) / CHIP_SIZE] && is通行[X座標 / CHIP_SIZE - 1][(Y座標 + def) / CHIP_SIZE]) return direct;
					break;
				case 5://右
					if (現在の方向 == 2 && Y座標 % CHIP_SIZE > def ) break;
					if (現在の方向 == 8 && Y座標 % CHIP_SIZE < def ) break;
					if (is通行[X座標 / CHIP_SIZE + 1][(Y座標 - def ) / CHIP_SIZE] && is通行[X座標 / CHIP_SIZE + 1][(Y座標 + def) / CHIP_SIZE]) return direct;
					break;
				case 7://下
					if (現在の方向 == 6 && X座標 % CHIP_SIZE > def ) break;
					if (現在の方向 == 8 && X座標 % CHIP_SIZE < def ) break;
					if (is通行[(X座標 - def) / CHIP_SIZE][Y座標 / CHIP_SIZE + 1] && is通行[(X座標 + def ) / CHIP_SIZE][Y座標 / CHIP_SIZE + 1]) return direct;
					break;
				default:
					return direct;
					break;
				}

				return 現在の方向;
			}

			/**.*/
			void 経路再計算(const Land& 土地)
			{
				計算リスト.clear();

				for (int a = 0; a < MAP_SIZE; ++a){
					for (int b = 0; b < MAP_SIZE; ++b)
					{
						if (土地.地形[a][b] == ChipType::畑)
						{
							距離[a][b] = 0;
							計算リスト.push_back(a + b*MAP_SIZE);
						}
						else
						{
							距離[a][b] = 到達不可;
						}
					}
				}

				for (unsigned int a = 0; a < 計算リスト.size(); ++a)
				{
					経路探索(計算リスト[a] % MAP_SIZE, 計算リスト[a] / MAP_SIZE);
				}
			}

			/**.*/
			void 経路探索(int X座標, int Y座標)
			{
				//斜め方向は距離7、上下左右は5で近似
				const int distance[2] = { 距離[X座標][Y座標] + 7, 距離[X座標][Y座標] + 5 };

				for (int a = 0; a < 9; ++a)
				{
					//現在のマスは無視
					if (a == 4) continue;

					const int X = X座標 - 1 + a % 3;
					const int Y = Y座標 - 1 + a / 3;
					//移動不可能なマスは無視
					if (!is通行[X][Y]) continue;
					//画面外になる場合は無視
					if (X < 0 || X >= MAP_SIZE || Y < 0 || Y >= MAP_SIZE) continue;
					//斜め移動が制限される場合は無視
					if (a == 0 && (!is通行[X座標 - 1][Y座標] || !is通行[X座標][Y座標 - 1])) continue;
					if (a == 2 && (!is通行[X座標 + 1][Y座標] || !is通行[X座標][Y座標 - 1])) continue;
					if (a == 6 && (!is通行[X座標 - 1][Y座標] || !is通行[X座標][Y座標 + 1])) continue;
					if (a == 8 && (!is通行[X座標 + 1][Y座標] || !is通行[X座標][Y座標 + 1])) continue;

					//斜め移動優先
					if (a % 2 == 0 && 距離[X][Y] == distance[0] && 経路[X][Y] % 2 == 0)
					{
						経路[X][Y] = 8 - a;
					}

					//最短経路更新
					if (距離[X][Y] > distance[a % 2])
					{
						距離[X][Y] = distance[a % 2];
						経路[X][Y] = 8 - a;
						計算リスト.push_back(X + Y * MAP_SIZE);
					}
				}
			}
		};

		ChipType 地形[MAP_SIZE][MAP_SIZE];

		bool is魔法[MAP_SIZE][MAP_SIZE];//魔法が配置済みかどうか

		//敵がいるかどうか、
		bool is陸敵[MAP_SIZE][MAP_SIZE];//地上の敵がいるかどうか
		bool is水敵[MAP_SIZE][MAP_SIZE];//水陸の敵がいるかどうか
		double 支援効果[MAP_SIZE][MAP_SIZE];

		std::vector<int> 穴の位置;//発生位置の場所

		Route 陸路;
		Route 空路;
		Route 水路;

		Land():
			陸路(MoveType::陸),
			空路(MoveType::空),
			水路(MoveType::水)
		{}

		/**初期化を行う.*/
		void Init()
		{
			穴の位置.clear();
			//暫定地形
			for (int a = 0; a < MAP_SIZE; ++a){
				for (int b = 0; b < MAP_SIZE; ++b)
				{
					is魔法[a][b] = false;
					地形[a][b] = StageDataS[TDSystem::選択ステージ].地形[a][b];
					if (地形[a][b] == ChipType::穴)
					{
						穴の位置.push_back(a + b * MAP_SIZE);
					}
				}
			}

			陸路.Init(*this);
			空路.Init(*this);
			水路.Init(*this);
		}

		/**is陸の敵を追加更新.*/
		void UpdateEnemy(int X座標, int Y座標, MoveType 移動種)
		{
			const int xa = (X座標 - 6) / CHIP_SIZE;
			const int xb = (X座標 + 6) / CHIP_SIZE;
			const int ya = (Y座標 - 6) / CHIP_SIZE;
			const int yb = (Y座標 + 6) / CHIP_SIZE;

			if ( ChipDataS[地形[xa][ya]].is陸移動) is陸敵[xa][ya] = true;
			if ( ChipDataS[地形[xa][yb]].is陸移動) is陸敵[xa][yb] = true;
			if ( ChipDataS[地形[xb][ya]].is陸移動) is陸敵[xb][ya] = true;
			if ( ChipDataS[地形[xb][yb]].is陸移動) is陸敵[xb][yb] = true;

			if (移動種 == MoveType::水)
			{
				if (ChipDataS[地形[xa][ya]].is水移動) is水敵[xa][ya] = true;
				if (ChipDataS[地形[xa][yb]].is水移動) is陸敵[xa][yb] = true;
				if (ChipDataS[地形[xb][ya]].is水移動) is陸敵[xb][ya] = true;
				if (ChipDataS[地形[xb][yb]].is水移動) is陸敵[xb][yb] = true;
			}
		}

		/**敵の有無を初期化.*/
		void InitEnemyPos()
		{
			for (int a = 0; a < MAP_SIZE; ++a){
				for (int b = 0; b < MAP_SIZE; ++b)
				{
					is陸敵[a][b] = false;
					is水敵[a][b] = false;
				}
			}
		}

		/**基本的なチェック.*/
		bool SetCheck(int X座標, int Y座標, int 大きさ) const
		{
			if (X座標 < 3 || X座標 > MAP_SIZE - 3 || Y座標 < 3 || Y座標 > MAP_SIZE - 3) return false;

			//配置が可能かチェック
			for (int a = 0; a < 大きさ; ++a){
				for (int b = 0; b < 大きさ; ++b)
				{
					if (
						is魔法[X座標 + a][Y座標 + b] ||
						!ChipDataS[地形[X座標 + a][Y座標 + b]].is配置可能 ||
						is陸敵[X座標 + a][Y座標 + b] ||
						is水敵[X座標 + a][Y座標 + b]
						) return false;
				}
			}

			return true;
		}

		/**配置が可能か確認、可能なら配置.*/
		bool SetUnit(int X座標, int Y座標, int 大きさ)
		{
			if (!SetCheck(X座標, Y座標, 大きさ)) { return false; }

			//仮配置
			for (int a = 0; a < 大きさ; ++a){
				for (int b = 0; b < 大きさ; ++b)
				{
					is魔法[X座標 + a][Y座標 + b] = true;
				}
			}

			//ルートを塞がないかチェック、空はルート固定なので確認しない
			陸路.Init(*this);

			//到達不可の位置に囲われた敵がいるかチェック
			for (int a = 0; a < MAP_SIZE; ++a){
				for (int b = 0; b < MAP_SIZE; ++b)
				{
					if (陸路.距離[a][b] == 到達不可 && (is陸敵[a][b] == true || 地形[a][b] == ChipType::穴))
					{
						for (int a = 0; a < 大きさ; ++a){
							for (int b = 0; b < 大きさ; ++b)
							{
								is魔法[X座標 + a][Y座標 + b] = false;
							}
						}
						陸路.Init(*this);
						return false;
					}
				}
			}

			水路.Init(*this);
			for (int a = 0; a < MAP_SIZE; ++a){
				for (int b = 0; b < MAP_SIZE; ++b)
				{
					if (水路.距離[a][b] == 到達不可 && is水敵[a][b] == true)
					{
						for (int a = 0; a < 大きさ; ++a){
							for (int b = 0; b < 大きさ; ++b)
							{
								is魔法[X座標 + a][Y座標 + b] = false;
							}
						}
						水路.Init(*this);
						return false;
					}
				}
			}

			return true;
		}

		/**ユニットをどかして経路を再計算する.*/
		void RemoveUnit(int X座標, int Y座標, int 大きさ)
		{
			for (int a = 0; a < 大きさ; ++a){
				for (int b = 0; b < 大きさ; ++b)
				{
					is魔法[X座標 + a][Y座標 + b] = false;
				}
			}

			陸路.Init(*this);
			水路.Init(*this);
		}

		/**地形の描画.*/
		void Draw() const
		{

			//地形の表示
			for (int a = 0; a < MAP_SIZE; ++a){
				for (int b = 0; b < MAP_SIZE; ++b)
				{
					Rect 位置(a * CHIP_SIZE + CHIP_SIZE / 2, b * CHIP_SIZE + CHIP_SIZE / 2, CHIP_SIZE, CHIP_SIZE);
					MSystem::マップチップ[(int)地形[a][b]]->DrawExtend({ a * CHIP_SIZE, b * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE });
					//デバッグ用
					//if (地形[a][b] != ChipType::草)  Drawing::Rect(位置, Color::Blue, true);
					//if (地形[a][b] == ChipType::畑)  Drawing::Rect(位置, Color::Red, true);
					//if (is魔法[a][b])                Drawing::Rect(位置, Color::Yellow, true);
					//if (is陸敵[a][b])              Drawing::Rect(位置, Color::Gray, true);
					//if (is水敵[a][b])              Drawing::Rect(位置, Color::Purple, true);
				}
			}

			if ( !TDSystem::isグリッド ){ return; }

			//罫線の表示
			for (int a = 0; a <= MAP_SIZE*CHIP_SIZE; a += CHIP_SIZE)
			{
				Drawing::Line({ (double)a, 0 }, { (double)a, MAP_SIZE * CHIP_SIZE }, Color::White, 1);
				Drawing::Line({ 0, (double)a }, { MAP_SIZE*CHIP_SIZE, (double)a }, Color::White, 1);
			}
			//真ん中の十字
			Drawing::Line({ (double)MAP_SIZE*CHIP_SIZE / 2 - CHIP_SIZE * 2, (double)MAP_SIZE*CHIP_SIZE / 2 }, { (double)MAP_SIZE*CHIP_SIZE / 2 + CHIP_SIZE * 2, (double)MAP_SIZE*CHIP_SIZE / 2 }, Color::White, 4);
			Drawing::Line({ (double)MAP_SIZE*CHIP_SIZE / 2, (double)MAP_SIZE*CHIP_SIZE / 2 - CHIP_SIZE * 2 }, { (double)MAP_SIZE*CHIP_SIZE / 2, (double)MAP_SIZE*CHIP_SIZE / 2 + CHIP_SIZE * 2 }, Color::White, 4);

		}

		/**配置先の表示.*/
		void DrawSetPos()
		{
			const int x = int((Input::mouse.x - CHIP_SIZE / 2) / CHIP_SIZE);
			const int y = int((Input::mouse.y - CHIP_SIZE / 2) / CHIP_SIZE);

			if (SetCheck((int)x, (int)y, 2))
			{
				Color color = {0,255,0,200};
				Drawing::Rect({ x * CHIP_SIZE, y *CHIP_SIZE, CHIP_SIZE * 2, CHIP_SIZE * 2 }, color, true);
			}
			else
			{
				Color color = { 255, 0, 0, 200 };
				Drawing::Rect({ x * CHIP_SIZE, y *CHIP_SIZE, CHIP_SIZE * 2, CHIP_SIZE * 2 }, color, true);
			}
		}

		/**現在の地形が通行可能かどうか.*/
		bool Check移動不可(double X座標, double Y座標, MoveType 移動種)
		{
			int x = (int)X座標 / CHIP_SIZE;
			int y = (int)Y座標 / CHIP_SIZE;

			if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE) return false;

			//falseなら通行不可
			switch (移動種)
			{
			case SDX_TD::MoveType::空:
				return !空路.is通行[x][y];
				break;
			case SDX_TD::MoveType::陸:
				return !陸路.is通行[x][y] || is魔法[x][y];
				break;
			case SDX_TD::MoveType::水:
				return !水路.is通行[x][y] || is魔法[x][y];
				break;
			default:
				return false;
				break;
			}
		}
	};
}