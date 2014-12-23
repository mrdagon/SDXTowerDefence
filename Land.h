//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include <SDXFramework.h>
#include "DataS.h"
#include "Material.h"

namespace SDX_TD
{
	using namespace SDX;

	static const int MapSize = 32;//マップの縦横タイル数
	static const int ChipSize = 16;//マップチップのドット数
	static const int 到達不可 = 99999999;
	static const double 自動床速度 = 0.5;

	/**地形データ.*/
	class Land
	{
	public:
		/**各移動タイプ毎の最短経路.*/
		class Route
		{
		public:
			int  距離[MapSize][MapSize];
			int  経路[MapSize][MapSize];
			bool is通行[MapSize][MapSize];
			Belong 移動種;
			std::vector<int> 計算リスト;

			Route(Belong 移動種) :
				移動種(移動種)
			{}

			bool Check通行(ChipType 地形種)
			{
				switch (移動種)
				{
				case Belong::空:
					return 地形種 != ChipType::高山;
					break;
				case Belong::陸:
					return ChipDataS[地形種].is陸移動;
					break;
				case Belong::水:
					return ChipDataS[地形種].is水移動;
				default:
					return false;
				}
			}

			/**.*/
			void Init(const Land& 土地)
			{
				for (int a = 0; a < MapSize; ++a){
					for (int b = 0; b < MapSize; ++b)
					{
						//魔法が配置されていて、飛行していない場合、通行不可能
						if (移動種 != Belong::空 && 土地.is魔法[a][b] == true)
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
				int mx = (現在の方向 % 3 - 1) * 7;
				int my = (現在の方向 / 3 - 1) * 7;

				return 経路[(X座標 - mx) / ChipSize][(Y座標 - my) / ChipSize];

				int direct = 経路[X座標 / ChipSize][Y座標 / ChipSize];

				switch (direct)
				{
				case 1://↑
					if (現在の方向 == 0 && X座標 % ChipSize > 11) break;
					if (現在の方向 == 2 && X座標 % ChipSize < 4) break;
					if (is通行[(X座標 - 4) / ChipSize][Y座標 / ChipSize - 1] && is通行[(X座標 + 4) / ChipSize][Y座標 / ChipSize - 1]) return direct;
					break;
				case 3://←
					if (現在の方向 == 0 && Y座標 % ChipSize > 11) break;
					if (現在の方向 == 4 && Y座標 % ChipSize < 4) break;
					if (is通行[X座標 / ChipSize - 1][(Y座標 - 4) / ChipSize] && is通行[X座標 / ChipSize - 1][(Y座標 + 4) / ChipSize]) return direct;
					break;
				case 5://→
					if (現在の方向 == 2 && Y座標 % ChipSize > 11) break;
					if (現在の方向 == 8 && Y座標 % ChipSize < 4) break;
					if (is通行[X座標 / ChipSize + 1][(Y座標 - 4) / ChipSize] && is通行[X座標 / ChipSize + 1][(Y座標 + 4) / ChipSize]) return direct;
					break;
				case 7://↓
					if (現在の方向 == 6 && X座標 % ChipSize > 11) break;
					if (現在の方向 == 8 && X座標 % ChipSize < 4) break;
					if (is通行[(X座標 - 4) / ChipSize][Y座標 / ChipSize + 1] && is通行[(X座標 + 4) / ChipSize][Y座標 / ChipSize + 1]) return direct;
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

				for (int a = 0; a < MapSize; ++a){
					for (int b = 0; b < MapSize; ++b)
					{
						if (土地.地形[a][b] == ChipType::畑)
						{
							距離[a][b] = 0;
							計算リスト.push_back(a + b*MapSize);
						}
						else{
							距離[a][b] = 到達不可;
						}
					}
				}

				for (unsigned int a = 0; a < 計算リスト.size(); ++a)
				{
					経路探索(計算リスト[a] % MapSize, 計算リスト[a] / MapSize);
				}
			}

			/**.*/
			void 経路探索(int X座標, int Y座標)
			{
				//斜め方向は距離7、上下左右は5で近似
				const int distance[2] = { 距離[X座標][Y座標] + 7, 距離[X座標][Y座標] + 5 };

				for (int a = 0; a < 9; ++a)
				{
					if (a == 4) continue;
					const int X = X座標 - 1 + a % 3;
					const int Y = Y座標 - 1 + a / 3;
					if (X < 0 || X >= MapSize || Y < 0 || Y >= MapSize) continue;
					if (a == 0 && (!is通行[X座標 - 1][Y座標] || !is通行[X座標][Y座標 - 1])) continue;
					if (a == 2 && (!is通行[X座標 + 1][Y座標] || !is通行[X座標][Y座標 - 1])) continue;
					if (a == 6 && (!is通行[X座標 - 1][Y座標] || !is通行[X座標][Y座標 + 1])) continue;
					if (a == 8 && (!is通行[X座標 + 1][Y座標] || !is通行[X座標][Y座標 + 1])) continue;
					if (!is通行[X][Y]) continue;

					if (距離[X][Y] > distance[a % 2])
					{
						距離[X][Y] = distance[a % 2];
						経路[X][Y] = 8 - a;
						計算リスト.push_back(X + Y * MapSize);
					}
				}
			}
		};

		ChipType 地形[MapSize][MapSize];

		bool is魔法[MapSize][MapSize];//魔法が配置済みかどうか

		//敵がいるかどうか、
		bool is陸敵[MapSize][MapSize];//地上の敵がいるかどうか
		bool is水敵[MapSize][MapSize];//水陸の敵がいるかどうか
		double 支援効果[MapSize][MapSize];

		std::vector<int> 穴の位置;//発生位置の場所

		Route 陸路;
		Route 空路;
		Route 水路;

		Land():
			陸路(Belong::陸),
			空路(Belong::空),
			水路(Belong::水)
		{}

		/**初期化を行う.*/
		void Init()
		{
			for (int a = 0; a < MapSize; ++a){
				for (int b = 0; b < MapSize; ++b)
				{
					地形[a][b] = ChipType::草;

					if (a <= 2 || b <= 2 || a >= MapSize - 3 || b >= MapSize - 3) 地形[a][b] = ChipType::山;
				}
			}

			地形[3][3] = ChipType::穴;
			地形[25][25] = ChipType::畑;

			穴の位置.clear();
			穴の位置.push_back(3 + 3 * MapSize);

			陸路.Init(*this);
			空路.Init(*this);
			水路.Init(*this);
		}

		/**is陸の敵を追加更新.*/
		void UpdateEnemy(int X座標, int Y座標, Belong 移動種)
		{
			const int xa = (X座標 - 6) / ChipSize;
			const int xb = (X座標 + 6) / ChipSize;
			const int ya = (Y座標 - 6) / ChipSize;
			const int yb = (Y座標 + 6) / ChipSize;

			if (ChipDataS[地形[xa][ya]].is陸移動) is陸敵[xa][ya] = true;
			if (ChipDataS[地形[xa][yb]].is陸移動) is陸敵[xa][yb] = true;
			if (ChipDataS[地形[xb][ya]].is陸移動) is陸敵[xb][ya] = true;
			if (ChipDataS[地形[xb][yb]].is陸移動) is陸敵[xb][yb] = true;

			if (移動種 == Belong::水)
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
			for (int a = 0; a < MapSize; ++a){
				for (int b = 0; b < MapSize; ++b)
				{
					is陸敵[a][b] = false;
					is水敵[a][b] = false;
				}
			}
		}

		//基本的なチェック
		bool SetCheck(int X座標, int Y座標, int 大きさ) const
		{
			if (X座標 < 3 || X座標 > MapSize - 3 || Y座標 < 3 || Y座標 > MapSize - 3) return false;

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
			for (int a = 0; a < MapSize; ++a){
				for (int b = 0; b < MapSize; ++b)
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
			for (int a = 0; a < MapSize; ++a){
				for (int b = 0; b < MapSize; ++b)
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

		//地形の描画
		void Draw() const
		{
			//罫線の表示
			for (int a = 0; a <= MapSize*ChipSize; a += ChipSize)
			{
				Drawing::Line({ (double)a, 0 }, { (double)a, MapSize * ChipSize }, Color::White, 1);
				Drawing::Line({ 0, (double)a }, { MapSize*ChipSize, (double)a }, Color::White, 1);
			}

			//地形の表示
			for (int a = 0; a < MapSize; ++a){
				for (int b = 0; b < MapSize; ++b)
				{
					Image* チップ = MSystem::マップチップ[2];
					Rect 位置(a * ChipSize + ChipSize / 2, b * ChipSize + ChipSize / 2, ChipSize, ChipSize);

					if (地形[a][b] == ChipType::草)  チップ = MSystem::マップチップ[0];

					//デバッグ用
					//if (地形[a][b] != ChipType::草)  Drawing::Rect(位置, Color::Blue, true);
					//if (地形[a][b] == ChipType::畑)  Drawing::Rect(位置, Color::Red, true);
					//if (is魔法[a][b])                Drawing::Rect(位置, Color::Yellow, true);
					//if (is陸敵[a][b])              Drawing::Rect(位置, Color::Gray, true);
					//if (is水敵[a][b])              Drawing::Rect(位置, Color::Purple, true);

					チップ->DrawExtend({ a * ChipSize, b * ChipSize, ChipSize, ChipSize });
				}
			}
		}

		//配置先の表示
		void DrawSetPos()
		{
			const double x = (Input::mouse.x - ChipSize / 2) / ChipSize;
			const double y = (Input::mouse.y - ChipSize / 2) / ChipSize;

			Screen::SetBlendMode(BlendMode::Alpha, 200);
			if (SetCheck((int)x, (int)y, 2))
			{
				Drawing::Rect({ x * ChipSize, y *ChipSize, ChipSize * 2, ChipSize * 2 }, Color::Green, true);
			}
			else{
				Drawing::Rect({ x * ChipSize, y *ChipSize, ChipSize * 2, ChipSize * 2 }, Color::Red, true);
			}
			Screen::SetBlendMode(BlendMode::NoBlend, 0);
		}

		/**敵が地形と衝突しているかチェック.*/
		bool Check地形(double X座標, double Y座標, Belong 移動種)
		{
			int x = (int)X座標 / ChipSize;
			int y = (int)Y座標 / ChipSize;

			if (x < 0 || x >= MapSize || y < 0 || y >= MapSize) return false;

			//trueなら通行不可
			switch (移動種)
			{
			case SDX_TD::Belong::空:
				return !空路.is通行[x][y];
				break;
			case SDX_TD::Belong::陸:
				return !陸路.is通行[x][y];
				break;
			case SDX_TD::Belong::水:
				return !水路.is通行[x][y];
				break;
			default:
				return false;
				break;
			}
		}
	};
}