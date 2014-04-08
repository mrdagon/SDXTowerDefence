#pragma once//☀Unicode
#include <SDXFrameWork.h>
#include "EnumType.h"

namespace SDX
{
    namespace Land
    {
        static const int 到達不可 = 99999999;
        static const int MapSize = 28;
        static const int ChipSize = 16;

        /**各移動タイプ毎の最短経路.*/
        class Route
        {
        public:
            bool isUse;//falseなら計算しない
            int  距離[MapSize][MapSize];
            int  経路[MapSize][MapSize];
            bool is通行[MapSize][MapSize];
            Belong 種類;

            /**.*/
            void SetState(Belong 陸空水, bool 使用フラグ)
            {
                種類 = 陸空水;
                isUse = 使用フラグ;
            }

            /**.*/
            void Init(const ChipType 地形[MapSize][MapSize], const bool 配置リスト[MapSize][MapSize])
            {
                if (!isUse) return;

                for (int i = 0; i < MapSize; ++i)
                {
                    for (int j = 0; j < MapSize; ++j)
                    {
                        if (種類 != Belong::空 && 配置リスト[i][j] == true)
                        {
                            is通行[i][j] = false;
                            continue;
                        }

                        switch (地形[i][j])
                        {
                            case ChipType::草://常に通行可
                            case ChipType::氷:
                            case ChipType::沼:
                            case ChipType::穴:
                            case ChipType::畑:
                                is通行[i][j] = true;
                                break;
                            case ChipType::山://空以外障害物扱い
                            case ChipType::森:
                                is通行[i][j] = (種類 == Belong::空);
                                break;
                            case ChipType::水://陸のみ障害物扱い
                                is通行[i][j] = (種類 != Belong::陸);
                                break;
                            case ChipType::高山://常に通行不可
                                is通行[i][j] = false;
                                break;
                        }
                    }
                }

                経路再計算(地形);
            }

            /**.*/
            int CulculateDistance(int 現在の方向, int X座標, int Y座標)
            {
                int distance = 経路[X座標 / ChipSize][Y座標 / ChipSize];

                switch (distance)
                {
                case 1://↑
                    if (現在の方向 == 0 && X座標 % ChipSize > 12) break;
                    if (現在の方向 == 2 && X座標 % ChipSize <  4) break;
                    if (is通行[(X座標 - 4) / ChipSize][Y座標 / ChipSize - 1] && is通行[(X座標 + 4) / ChipSize][Y座標 / ChipSize - 1]) return distance;
                    break;
                case 3://←
                    if (現在の方向 == 0 && Y座標 % ChipSize > 12) break;
                    if (現在の方向 == 4 && Y座標 % ChipSize <  4) break;
                    if (is通行[X座標 / ChipSize - 1][(Y座標 - 4) / ChipSize] && is通行[X座標 / ChipSize - 1][(Y座標 + 4) / ChipSize]) return distance;
                    break;
                case 5://→
                    if (現在の方向 == 2 && Y座標 % ChipSize > 12) break;
                    if (現在の方向 == 8 && Y座標 % ChipSize <  4) break;
                    if (is通行[X座標 / ChipSize + 1][(Y座標 - 4) / ChipSize] && is通行[X座標 / ChipSize + 1][(Y座標 + 4) / ChipSize]) return distance;
                    break;
                case 7://↓
                    if (現在の方向 == 6 && X座標 % ChipSize > 12) break;
                    if (現在の方向 == 8 && X座標 % ChipSize <  4) break;
                    if (is通行[(X座標 - 4) / ChipSize][Y座標 / ChipSize + 1] && is通行[(X座標 + 4) / ChipSize][Y座標 / ChipSize + 1]) return distance;
                    break;
                default:
                    return distance;
                    break;
                }
                return 現在の方向;
            }

            std::vector<int> 計算リスト;

            /**.*/
            void 経路再計算(const ChipType 地形[MapSize][MapSize])
            {
                計算リスト.clear();

                for (int i = 0; i < MapSize; ++i)
                {
                    for (int j = 0; j < MapSize; ++j)
                    {
                        if (地形[i][j] == ChipType::畑)
                        {
                            距離[i][j] = 0;
                            計算リスト.push_back(i + j*MapSize);
                        }
                        else{
                            距離[i][j] = 到達不可;
                        }
                    }
                }

                for (unsigned int i = 0; i < 計算リスト.size(); ++i)
                {
                    経路探索(計算リスト[i] % MapSize, 計算リスト[i] / MapSize);
                }
            }

            /**.*/
            void 経路探索(int X座標, int Y座標)
            {
                //斜め方向は距離7、上下左右は5で近似
                const int distance[2] = { 距離[X座標][Y座標] + 7, 距離[X座標][Y座標] + 5 };

                for (int i = 0; i < 9; ++i)
                {
                    if (i == 4) continue;
                    const int X = X座標 - 1 + i % 3;
                    const int Y = Y座標 - 1 + i / 3;
                    if (X < 0 || X >= MapSize || Y < 0 || Y >= MapSize ) continue;
                    if (i == 0 && (!is通行[X座標 - 1][Y座標] || !is通行[X座標][Y座標 - 1])) continue;
                    if (i == 2 && (!is通行[X座標 + 1][Y座標] || !is通行[X座標][Y座標 - 1])) continue;
                    if (i == 6 && (!is通行[X座標 - 1][Y座標] || !is通行[X座標][Y座標 + 1])) continue;
                    if (i == 8 && (!is通行[X座標 + 1][Y座標] || !is通行[X座標][Y座標 + 1])) continue;
                    if (!is通行[X][Y]) continue;

                    if (距離[X][Y] > distance[i % 2])
                    {
                        距離[X][Y] = distance[i % 2];
                        経路[X][Y] = 8 - i;
                        計算リスト.push_back( X + Y * MapSize);
                    }
                }
            }
        };

        /**地形データ.*/
        class Land
        {
        public:
            ChipType 地形[MapSize][MapSize];
            bool     砲台配置[MapSize][MapSize];
            Route 陸路;
            Route 空路;
            Route 水路;
            Route 海路;

            bool 地上配置[MapSize][MapSize];
            bool 水上配置[MapSize][MapSize];

            std::vector<int> 塔の位置;

            /**初期化を行う.*/
            void Init()
            {
                for (int i = 0; i < MapSize; ++i)
                {
                    for (int j = 0; j < MapSize; ++j)
                    {
                        地形[i][j] = ChipType::草;

                        if (i == 0 || j == 0 || i == MapSize-1 || j == MapSize-1) 地形[i][j] = ChipType::高山;
                    }
                }
                地形[1][1] = ChipType::穴;
                地形[7][1] = ChipType::穴;
                地形[14][1] = ChipType::穴;
                地形[22][1] = ChipType::穴;
                地形[26][26] = ChipType::畑;

                塔の位置.clear();
                塔の位置.push_back( 1 + 1 * MapSize);
                塔の位置.push_back( 7 + 1 * MapSize);
                塔の位置.push_back(14 + 1 * MapSize);
                塔の位置.push_back(22 + 1 * MapSize);

                陸路.SetState( Belong::陸, true);
                空路.SetState( Belong::空, true);
                水路.SetState( Belong::水陸, true);
                海路.SetState( Belong::水中, true);

                陸路.Init(地形, 砲台配置);
                空路.Init(地形, 砲台配置);
                水路.Init(地形, 砲台配置);
                海路.Init(地形, 砲台配置);
            }

            /**地上配置を更新.*/
            void SetGroungPost(int X座標, int Y座標)
            {
                const int xa = (X座標 - 4) / ChipSize;
                const int xb = (X座標 + 4) / ChipSize;
                const int ya = (Y座標 - 4) / ChipSize;
                const int yb = (Y座標 + 4) / ChipSize;

                地上配置[xa][ya] = true;
                if (xa != xb)
                {
                    地上配置[xb][ya] = true;
                    if (ya != yb)
                    {
                        地上配置[xa][yb] = true;
                        地上配置[xb][yb] = true;
                    }
                }
                else if (ya != yb)
                {
                    地上配置[xa][yb] = true;
                }
            }

            /**水上配置を更新.*/
            void SetSeaPost(int X座標, int Y座標)
            {
                const int xa = (X座標 - 4) / ChipSize;
                const int xb = (X座標 + 4) / ChipSize;
                const int ya = (Y座標 - 4) / ChipSize;
                const int yb = (Y座標 + 4) / ChipSize;

                水上配置[xa][ya] = true;
                if (xa != xb)
                {
                    水上配置[xb][ya] = true;
                    if (ya != yb)
                    {
                        水上配置[xa][yb] = true;
                        水上配置[xb][yb] = true;
                    }
                }
                else if (ya != yb){
                    水上配置[xb][yb] = true;
                }
            }

            /**地上配置と水上配置を初期化.*/
            void InitEnemyPost()
            {
                for (int i = 0; i < MapSize; ++i)
                {
                    for (int j = 0; j < MapSize; ++j)
                    {
                        地上配置[i][j] = false;
                        水上配置[i][j] = false;
                    }
                }
            }

            /**配置が可能か確認、可能なら配置.*/
            bool SetCheck(int X座標, int Y座標, int 大きさ)
            {
                //通行不可地形に既に存在する敵は無視する
                for (int i = 0; i < MapSize; ++i)
                {
                    for (int j = 0; j < MapSize; ++j)
                    {
                        switch (地形[i][j])
                        {
                        case ChipType::水:
                            地上配置[i][j] = false;
                            break;
                        case ChipType::森:
                        case ChipType::山:
                        case ChipType::高山:
                            地上配置[i][j] = false;
                            水上配置[i][j] = false;
                            break;
                        default:
                            break;
                        }
                    }
                }

                for (int i = 0; i < 大きさ; ++i)
                {
                    for (int j = 0; j < 大きさ; ++j)
                    {
                        if (砲台配置[X座標 + i][Y座標 + j] )                                  return false;
                        if ((int)地形[X座標 + i][Y座標 + j] > (int)ChipType::森)              return false;
                        if (地上配置[X座標 + i][Y座標 + j] || 水上配置[X座標 + i][Y座標 + j]) return false;
                        if (地形[X座標 + i][Y座標 + j] == ChipType::穴)                     return false;
                    }
                }

                for (int i = 0; i < 大きさ; ++i)
                {
                    for (int j = 0; j < 大きさ; ++j)
                    {
                        砲台配置[X座標 + i][Y座標 + j] = true;
                    }
                }

                陸路.Init(地形, 砲台配置);

                bool isOK = true;
                //空中でない敵がいるマスと始点が到達不可ならfalse
                for (int i = 0; i < MapSize*MapSize; ++i)
                {
                    if (
                        陸路.距離[i % MapSize][i / MapSize] == 到達不可 &&
                        (地上配置[i % MapSize][i / MapSize] == true || 地形[i % MapSize][i / MapSize] == ChipType::穴)
                       )
                    {
                        isOK = false;
                        break;
                    }
                }

                if (isOK && 水路.isUse)
                {
                    水路.Init(地形, 砲台配置);
                    for (int i = 0; i < MapSize*MapSize; ++i)
                    {
                        if (水路.距離[i % MapSize][i / MapSize] == 到達不可 && 水上配置[i % MapSize][i / MapSize] == true)
                        {
                            isOK = false;
                            break;
                        }
                    }
                }

                if (!isOK)
                {
                    //配置を戻す
                    for (int i = 0; i < 大きさ; ++i)
                    {
                        for (int j = 0; j < 大きさ; ++j)
                        {
                            砲台配置[X座標 + i][Y座標 + j] = false;
                        }
                    }

                    陸路.Init(地形, 砲台配置);
                    if (水路.isUse)    水路.Init(地形, 砲台配置);
                }

                return isOK;
            }

            /**ユニットをどかして経路を再計算する.*/
            void RemoveUnit(int X座標, int Y座標, int 大きさ)
            {
                for (int i = 0; i < 大きさ; ++i)
                {
                    for (int j = 0; j < 大きさ; ++j)
                    {
                        砲台配置[X座標 + i][Y座標 + j] = false;
                    }
                }
                陸路.Init(地形, 砲台配置);
                水路.Init(地形, 砲台配置);
            }

            void Draw() const
            {
                //罫線の表示
                for (int i = 0; i <= MapSize*ChipSize; i += ChipSize)
                {
                    Drawing::Line(i, 0, i, MapSize * ChipSize, Color::White, 1);
                    Drawing::Line(0, i, MapSize*ChipSize, i, Color::White, 1);
                }

                //地形の表示
                for (int i = 0; i < MapSize; ++i)
                {
                    for (int j = 0; j < MapSize; ++j)
                    {
                        if ( 地形[i][j] != ChipType::草)  Drawing::Rect(i * ChipSize, j * ChipSize, ChipSize, ChipSize, Color::Blue, true);
                        if ( 地形[i][j] == ChipType::畑)  Drawing::Rect(i * ChipSize, j * ChipSize, ChipSize, ChipSize, Color::Red, true);
                        if ( 砲台配置[i][j])              Drawing::Rect(i * ChipSize, j * ChipSize, ChipSize, ChipSize, Color::Yellow, true);
                        if ( 地上配置[i][j])              Drawing::Rect(i * ChipSize, j * ChipSize, ChipSize, ChipSize, Color::Gray, true);
                        if ( 水上配置[i][j])              Drawing::Rect(i * ChipSize, j * ChipSize, ChipSize, ChipSize, Color::Purple, true);
                    }
                }
            }
        };

        static Land *now;
    }
}