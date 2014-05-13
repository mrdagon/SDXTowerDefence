#pragma once//☀Unicode
#include <SDXFrameWork.h>
#include "DataType.h"
#include "Material.h"

namespace SDX_TD
{
    using namespace SDX;
    namespace Land
    {


        /**各移動タイプ毎の最短経路.*/
        class Route
        {
        public:
            bool isUse;//falseなら計算しない

            int  距離[MapSize][MapSize];
            int  経路[MapSize][MapSize];
            bool is通行[MapSize][MapSize];
            Belong 種類;

            std::vector<int> 計算リスト;

            bool Check通行(ChipType 地形種, Belong 移動種)
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
                    return ChipDataS[地形種].is水上移動;
                default:
                    return false;
                }
            }

            /**.*/
            void SetState(Belong 陸空水, bool 使用フラグ)
            {
                種類 = 陸空水;
                isUse = 使用フラグ;
            }

            /**.*/
            void Init(const ChipType 地形[MapSize][MapSize], const bool 配置リスト[MapSize][MapSize])
            {
                if ( !isUse ) return;

                for (int i = 0; i < MapSize; ++i)
                for (int j = 0; j < MapSize; ++j)
                {
                    //魔法が配置されると通行不可能
                    if (種類 != Belong::空 && 配置リスト[i][j] == true)
                    {
                        is通行[i][j] = false;
                        continue;
                    }

                    is通行[i][j] = Check通行( 地形[i][j] , 種類);
                }

                経路再計算(地形);
            }

            /**.*/
            int 方向計算(int 現在の方向, int X座標, int Y座標)
            {
                int mx = (現在の方向 % 3 - 1) * 7;
                int my = (現在の方向 / 3 - 1) * 7;

                return 経路[(X座標-mx) / ChipSize][(Y座標-my) / ChipSize];

                int direct = 経路[X座標 / ChipSize][Y座標 / ChipSize];

                switch (direct)
                {
                case 1://↑
                    if (現在の方向 == 0 && X座標 % ChipSize > 11) break;
                    if (現在の方向 == 2 && X座標 % ChipSize <  4) break;
                    if (is通行[(X座標 - 4) / ChipSize][Y座標 / ChipSize - 1] && is通行[(X座標 + 4) / ChipSize][Y座標 / ChipSize - 1]) return direct;
                    break;
                case 3://←
                    if (現在の方向 == 0 && Y座標 % ChipSize > 11) break;
                    if (現在の方向 == 4 && Y座標 % ChipSize <  4) break;
                    if (is通行[X座標 / ChipSize - 1][(Y座標 - 4) / ChipSize] && is通行[X座標 / ChipSize - 1][(Y座標 + 4) / ChipSize]) return direct;
                    break;
                case 5://→
                    if (現在の方向 == 2 && Y座標 % ChipSize > 11) break;
                    if (現在の方向 == 8 && Y座標 % ChipSize <  4) break;
                    if (is通行[X座標 / ChipSize + 1][(Y座標 - 4) / ChipSize] && is通行[X座標 / ChipSize + 1][(Y座標 + 4) / ChipSize]) return direct;
                    break;
                case 7://↓
                    if (現在の方向 == 6 && X座標 % ChipSize > 11) break;
                    if (現在の方向 == 8 && X座標 % ChipSize <  4) break;
                    if (is通行[(X座標 - 4) / ChipSize][Y座標 / ChipSize + 1] && is通行[(X座標 + 4) / ChipSize][Y座標 / ChipSize + 1]) return direct;
                    break;
                default:
                    return direct;
                    break;
                }
                return 現在の方向;
            }

            /**.*/
            void 経路再計算(const ChipType 地形[MapSize][MapSize])
            {
                計算リスト.clear();

                for (int i = 0; i < MapSize; ++i)
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
            int      地形画像[MapSize][MapSize];
            Route    陸路;
            Route    空路;
            Route    水路;

            bool     is魔法[MapSize][MapSize];//魔法が配置済みかどうか
            bool     is陸の敵[MapSize][MapSize];//地上の敵がいるかどうか
            bool     is水の敵[MapSize][MapSize];//水陸の敵がいるかどうか
            double   支援効果[MapSize][MapSize];

            std::vector<int> 穴の位置;

            /**初期化を行う.*/
            void Init()
            {
                for (int i = 0; i < MapSize; ++i)
                for (int j = 0; j < MapSize; ++j)
                {
                    地形[i][j] = ChipType::草;

                    if (i <= 1 || j <= 1 || i >= MapSize-2 || j >= MapSize-2 ) 地形[i][j] = ChipType::山;
                }

                地形[2][2] = ChipType::穴;
                地形[26][26] = ChipType::畑;

                穴の位置.clear();
                穴の位置.push_back(2 + 2 * MapSize);

                陸路.SetState( Belong::陸, true);
                空路.SetState( Belong::空, true);
                水路.SetState( Belong::水, true);

                陸路.Init(地形, is魔法);
                空路.Init(地形, is魔法);
                水路.Init(地形, is魔法);
            }

            /**is陸の敵を更新.*/
            void Update陸の敵(int X座標, int Y座標)
            {
                const int xa = (X座標 - 6) / ChipSize;
                const int xb = (X座標 + 6) / ChipSize;
                const int ya = (Y座標 - 6) / ChipSize;
                const int yb = (Y座標 + 6) / ChipSize;

                if (ChipDataS[地形[xa][ya]].is陸移動) is陸の敵[xa][ya] = true;
                if (ChipDataS[地形[xa][yb]].is陸移動) is陸の敵[xa][yb] = true;
                if (ChipDataS[地形[xb][ya]].is陸移動) is陸の敵[xb][ya] = true;
                if (ChipDataS[地形[xb][yb]].is陸移動) is陸の敵[xb][yb] = true;
            }

            /**is水の敵を更新.*/
            void Update水の敵(int X座標, int Y座標)
            {
                const int xa = (X座標 - 6) / ChipSize;
                const int xb = (X座標 + 6) / ChipSize;
                const int ya = (Y座標 - 6) / ChipSize;
                const int yb = (Y座標 + 6) / ChipSize;

                if (ChipDataS[地形[xa][ya]].is水上移動 ) is水の敵[xa][ya] = true;
                if (ChipDataS[地形[xa][yb]].is水上移動 ) is水の敵[xa][yb] = true;
                if (ChipDataS[地形[xb][ya]].is水上移動 ) is水の敵[xb][yb] = true;
                if (ChipDataS[地形[xb][yb]].is水上移動 ) is水の敵[xb][yb] = true;
            }

            /**is陸の敵とis水の敵を初期化.*/
            void InitEnemyPos()
            {
                for (int i = 0; i < MapSize; ++i)
                for (int j = 0; j < MapSize; ++j)
                {
                    is陸の敵[i][j] = false;
                    is水の敵[i][j] = false;
                }
            }

            bool SetMagic(int X座標 ,int Y座標 , int 大きさ)
            {
                if( !SetCheck(X座標,Y座標,大きさ) ) return false;

                //仮配置
                for (int i = 0; i < 大きさ; ++i)
                for (int j = 0; j < 大きさ; ++j)
                {
                    is魔法[X座標 + i][Y座標 + j] = true;
                }

                //ルートを塞がないかチェック
                //空と水中はルート固定なので確認しない
                bool isOK = true;

                陸路.Init(地形, is魔法);

                //空中でない敵か発生点が到達不可ならfalse
                for (int i = 0; i < MapSize; ++i)
                for (int j = 0; j < MapSize; ++j)
                {
                    if (陸路.距離[i][j] == 到達不可 && (is陸の敵[i][j] == true || 地形[i][j] == ChipType::穴))
                    {
                        isOK = false;
                        break;
                    }
                }

                if (isOK && 水路.isUse)
                {
                    水路.Init(地形, is魔法);
                    for (int i = 0; i < MapSize; ++i)
                    for (int j = 0; j < MapSize; ++j)
                    {
                        //穴が到達不可になってるかは再チェックしない
                        if (水路.距離[i][j] == 到達不可 && is水の敵[i][j] == true)
                        {
                            isOK = false;
                            break;
                        }
                    }
                }

                if (isOK) return true;

                //失敗したら仮配置を戻す
                for (int i = 0; i < 大きさ; ++i)
                for (int j = 0; j < 大きさ; ++j)
                {
                    is魔法[X座標 + i][Y座標 + j] = false;
                }

                陸路.Init(地形, is魔法);
                水路.Init(地形, is魔法);

                return false;
            }

            /**配置が可能か確認、可能なら配置.*/
            bool SetCheck(int X座標, int Y座標, int 大きさ) const
            {
                if( X座標 < 2 || X座標 >= MapSize-3 || Y座標 < 2 || Y座標 >= MapSize-3 ) return false;

                //配置が可能かチェック
                for (int i = 0; i < 大きさ; ++i)
                for (int j = 0; j < 大きさ; ++j)
                {
                    if (
                            is魔法[X座標 + i][Y座標 + j] ||
                            !ChipDataS[地形[X座標 + i][Y座標 + j]].is配置可能 ||
                            is陸の敵[X座標 + i][Y座標 + j] ||
                            is水の敵[X座標 + i][Y座標 + j]
                        ) return false;
                }

                return true;
            }

            /**ユニットをどかして経路を再計算する.*/
            void RemoveMagic(int X座標, int Y座標, int 大きさ)
            {
                for (int i = 0; i < 大きさ; ++i)
                for (int j = 0; j < 大きさ; ++j)
                {
                    is魔法[X座標 + i][Y座標 + j] = false;
                }

                陸路.Init(地形, is魔法);
                水路.Init(地形, is魔法);
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
                for (int j = 0; j < MapSize; ++j)
                {
                    Image* チップ = MSystem::マップチップ[0];

                    if ( 地形[i][j] == ChipType::草)  チップ = MSystem::マップチップ[32];
                    if ( 地形[i][j] != ChipType::草)  Drawing::Rect(i * ChipSize, j * ChipSize, ChipSize, ChipSize, Color::Blue, true);
                    if ( 地形[i][j] == ChipType::畑)  Drawing::Rect(i * ChipSize, j * ChipSize, ChipSize, ChipSize, Color::Red, true);
                    if ( is魔法[i][j])                Drawing::Rect(i * ChipSize, j * ChipSize, ChipSize, ChipSize, Color::Yellow, true);
                    if ( is陸の敵[i][j])              Drawing::Rect(i * ChipSize, j * ChipSize, ChipSize, ChipSize, Color::Gray, true);
                    if ( is水の敵[i][j])              Drawing::Rect(i * ChipSize, j * ChipSize, ChipSize, ChipSize, Color::Purple, true);

                    チップ->DrawExtend(i * ChipSize, j * ChipSize, (i+1)*ChipSize , (j+1)*ChipSize);
                }

                //配置先の表示
                const int x = (Input::mouse.x - ChipSize/2) / ChipSize;
                const int y = (Input::mouse.y - ChipSize/2) / ChipSize;

                Screen::SetBlendMode(BlendMode::Alpha,200);
                if( SetCheck(x,y,2) )
                {
                    Drawing::Rect( x * ChipSize,y *ChipSize, ChipSize*2 , ChipSize *2 , Color::Green , true );
                }else{
                    Drawing::Rect( x * ChipSize,y *ChipSize, ChipSize*2 , ChipSize *2 , Color::Red , true );
                }
                Screen::SetBlendMode(BlendMode::NoBlend,0);
            }

            ChipType Get地形(double X座標, double Y座標)
            {
                return 地形[(int)X座標 / ChipSize][(int)Y座標 / ChipSize];
            }
            
            /**地形との衝突しているか返す.*/
            bool Check地形(double X座標, double Y座標, Belong 移動種)
            {
                int x = (int)X座標 / ChipSize;
                int y = (int)Y座標 / ChipSize;

                if( x < 0 || x >= MapSize || y < 0 || y >= MapSize ) return false; 

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

    /**唯一のアクティブなLand.*/
    namespace{ Land::Land *SLand; }

}