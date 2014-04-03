#pragma    once//☀Unicode
#include    <SDXFrameWork.h>

namespace    SDX
{
                enum    class    ChipType
                {
                                草,//通常地形
                                氷,//移動速度2倍
                                沼,//移動速度半減
                                森,//配置可能、通行不可
                                //ここより↓は配置不可能
                                山,//配置＆通行不可
                                高山,//空中も通行不可
                                水,//一部敵のみ通行可
                                井戸,//敵が湧く
                                塔//防衛拠点
                };

                namespace    Land
                {
                                static    const    int    到達不可    =    99999999;

                                template    <int    横幅,    int    縦幅>
                                class    Root
                                {
                                public:
                                                bool    isUse;//falseなら計算しない
                                                int    距離[横幅][縦幅];
                                                int    経路[横幅][縦幅];
                                                bool    is通行[横幅][縦幅];
                                                int    種類;//0    陸,1空,2水陸,3水限定

                                                void    SetState(int    陸空水,    bool    使用フラグ)
                                                {
                                                                種類    =    陸空水;
                                                                isUse    =    使用フラグ;
                                                }

                                                void    Init(    const    ChipType    地形[横幅][縦幅],    const    bool    配置リスト[横幅][縦幅])
                                                {
                                                                if    (!isUse)    return;

                                                                for    (int    i    =    0;    i    <    横幅;    ++i)
                                                                {
                                                                                for    (int    j    =    0;    j    <    縦幅;    ++j)
                                                                                {
                                                                                                if    (種類    !=    1    &&    配置リスト[i][j]    ==    true)
                                                                                                {
                                                                                                                is通行[i][j]    =    false;
                                                                                                                continue;
                                                                                                }

                                                                                                switch    (地形[i][j])
                                                                                                {
                                                                                                case    ChipType::草://常に通れる
                                                                                                case    ChipType::氷:
                                                                                                case    ChipType::沼:
                                                                                                case    ChipType::井戸:
                                                                                                case    ChipType::塔:
                                                                                                                is通行[i][j]    =    true;
                                                                                                                break;
                                                                                                case    ChipType::山://空以外障害物
                                                                                                case    ChipType::森:
                                                                                                                is通行[i][j]    =    (種類    ==    1);
                                                                                                                break;
                                                                                                case    ChipType::水://陸のみ障害物
                                                                                                                is通行[i][j]    =    (種類    !=    0);
                                                                                                                break;
                                                                                                case    ChipType::高山:
                                                                                                                is通行[i][j]    =    false;
                                                                                                                break;
                                                                                                }
                                                                                }
                                                                }

                                                                経路再計算(地形);
                                                }

                                                int    CulculateDistance(int    現在の方向,    int    X座標,    int    Y座標)
                                                {
                                                                int    distance    =    経路[X座標    /    20][Y座標    /    20];

                                                                switch    (distance)
                                                                {
                                                                case    1://↑
                                                                                if    (現在の方向    ==    0    &&    X座標    %    20    >    14)    break;
                                                                                if    (現在の方向    ==    2    &&    X座標    %    20    <    6)    break;
                                                                                if    (is通行[(X座標    -    6)    /    20][Y座標    /    20    -    1]    &&    is通行[(X座標    +    6)    /    20][Y座標    /    20    -    1])    return    distance;
                                                                                break;
                                                                case    3://←
                                                                                if    (現在の方向    ==    0    &&    Y座標    %    20    >    14)    break;
                                                                                if    (現在の方向    ==    6    &&    Y座標    %    20    <    6)    break;
                                                                                if    (is通行[X座標    /    20    -    1][(Y座標    -    6)    /    20]    &&    is通行[X座標    /    20    -    1][(Y座標    +    6)    /    20])    return    distance;
                                                                                break;
                                                                case    5://→
                                                                                if    (現在の方向    ==    2    &&    Y座標    %    20    >    14)    break;
                                                                                if    (現在の方向    ==    8    &&    Y座標    %    20    <    6)    break;
                                                                                if    (is通行[X座標    /    20    +    1][(Y座標    -    6)    /    20]    &&    is通行[X座標    /    20    +    1][(Y座標    +    6)    /    20])    return    distance;
                                                                                break;
                                                                case    7://↓
                                                                                if    (現在の方向    ==    6    &&    X座標    %    20    >    14)    break;
                                                                                if    (現在の方向    ==    8    &&    X座標    %    20    <    6)    break;
                                                                                if    (is通行[(X座標    -    6)    /    20][Y座標    /    20    +    1]    &&    is通行[(X座標    +    6)    /    20][Y座標    /    20    +    1])    return    distance;
                                                                                break;
                                                                default:
                                                                                return    distance;
                                                                                break;
                                                                }
                                                                return    現在の方向;
                                                }

                                                bool    SetCheck(int    X座標,    int    Y座標)
                                                {

                                                }

                                                bool    RemoveUnit(int    X座標,    int    Y座標)
                                                {

                                                }

                                                std::vector<int>    計算リスト;

                                                void    経路再計算(const    ChipType    地形[横幅][縦幅])
                                                {
                                                                計算リスト.clear();

                                                                for    (int    i    =    0;    i    <    横幅;    ++i)
                                                                {
                                                                                for    (int    j    =    0;    j    <    縦幅;    ++j)
                                                                                {
                                                                                                if    (地形[i][j]    ==    ChipType::塔)
                                                                                                {
                                                                                                                距離[i][j]    =    0;
                                                                                                                計算リスト.push_back(i+j*横幅);
                                                                                                }else{
                                                                                                                距離[i][j]    =    到達不可;
                                                                                                }
                                                                                }
                                                                }

                                                                for    (unsigned    int    i    =    0;    i    <    計算リスト.size();    ++i)
                                                                {
                                                                                経路探索(計算リスト[i]    %    横幅,    計算リスト[i]    /    横幅);
                                                                }
                                                }

                                                void    経路探索(int    X座標,    int    Y座標)
                                                {
                                                                //斜め方向は距離7、上下左右は5で近似
                                                                const    int    distance[2]    =    {    距離[X座標][Y座標]    +    7,    距離[X座標][Y座標]    +    5    };

                                                                for    (int    i    =    0;    i    <    9;    ++i)
                                                                {
                                                                                if    (i    ==    4)    continue;
                                                                                const    int    X    =    X座標    -    1    +    i    %    3;
                                                                                const    int    Y    =    Y座標    -    1    +    i    /    3;
                                                                                if    (X    <    0    ||    X    >23    ||    Y    <    0    ||    Y    >    23)    continue;
                                                                                if    (i    ==    0    &&    (!is通行[X座標    -    1][Y座標]    ||    !is通行[X座標][Y座標    -    1]))    continue;
                                                                                if    (i    ==    2    &&    (!is通行[X座標    +    1][Y座標]    ||    !is通行[X座標][Y座標    -    1]))    continue;
                                                                                if    (i    ==    6    &&    (!is通行[X座標    -    1][Y座標]    ||    !is通行[X座標][Y座標    +    1]))    continue;
                                                                                if    (i    ==    8    &&    (!is通行[X座標    +    1][Y座標]    ||    !is通行[X座標][Y座標    +    1]))    continue;
                                                                                if    (!is通行[X][Y])    continue;

                                                                                if    (距離[X][Y]    >    distance[i    %    2])
                                                                                {
                                                                                                距離[X][Y]    =    distance[i    %    2];
                                                                                                経路[X][Y]    =    8    -    i;
                                                                                                計算リスト.push_back(X    +    Y    *横幅);
                                                                                }
                                                                }
                                                }
                                };

                                template    <int    横幅,int    縦幅>
                                class    Land
                                {
                                public:
                                                ChipType    地形[横幅][縦幅];
                                                bool    砲台配置[横幅][縦幅];
                                                Root<横幅,    縦幅>    陸路;
                                                Root<横幅,    縦幅>    空路;
                                                Root<横幅,    縦幅>    水路;
                                                Root<横幅,    縦幅>    海路;

                                                bool    地上配置[横幅][縦幅];
                                                bool    水上配置[横幅][縦幅];

                                                /**初期化を行う.*/
                                                void    Init()
                                                {
                                                                for    (int    i    =    0;    i    <    横幅;    ++i)
                                                                {
                                                                                for    (int    j    =    0;    j    <    縦幅;    ++j)
                                                                                {
                                                                                                if    (Rand::Get(5)    !=    0)    地形[i][j]    =    ChipType::草;
                                                                                                else                                                                            地形[i][j]    =    ChipType::水;

                                                                                                if    (i    ==    0    ||    j    ==    0    ||    i    ==    23    ||    j    ==    23)    地形[i][j]    =    ChipType::高山;
                                                                                }
                                                                }
                                                                地形[22][22]    =    ChipType::塔;

                                                                陸路.SetState(0,    true);
                                                                空路.SetState(1,    true);
                                                                水路.SetState(2,    true);
                                                                海路.SetState(3,    true);

                                                                陸路.Init(    地形    ,    砲台配置    );
                                                                空路.Init(    地形    ,    砲台配置    );
                                                                水路.Init(    地形    ,    砲台配置    );
                                                                海路.Init(    地形    ,    砲台配置    );
                                                }

                                                /**地上配置を更新.*/
                                                void    SetGroungPost(int    X座標,    int    Y座標)
                                                {
                                                                const    int    xa    =    (X座標    -    6)    /    20;
                                                                const    int    xb    =    (X座標    +    6)    /    20;
                                                                const    int    ya    =    (Y座標    -    6)    /    20;
                                                                const    int    yb    =    (Y座標    +    6)    /    20;

                                                                地上配置[xa][ya]    =    true;
                                                                if    (xa    !=    xb)
                                                                {
                                                                                地上配置[xb][ya]    =    true;
                                                                                if    (ya    !=    yb)
                                                                                {
                                                                                                地上配置[xa][yb]    =    true;
                                                                                                地上配置[xb][yb]    =    true;
                                                                                }
                                                                }
                                                                else    if    (ya    !=    yb){
                                                                                地上配置[xa][yb]    =    true;
                                                                }
                                                }
                                                /**水上配置を更新.*/
                                                void    SetSeaPost(int    X座標,    int    Y座標)
                                                {
                                                                const    int    xa    =    (X座標    -    6)    /    20;
                                                                const    int    xb    =    (X座標    +    6)    /    20;
                                                                const    int    ya    =    (Y座標    -    6)    /    20;
                                                                const    int    yb    =    (Y座標    +    6)    /    20;

                                                                水上配置[xa][ya]    =    true;
                                                                if    (xa    !=    xb)
                                                                {
                                                                                水上配置[xb][ya]    =    true;
                                                                                if    (ya    !=    yb)
                                                                                {
                                                                                                水上配置[xa][yb]    =    true;
                                                                                                水上配置[xb][yb]    =    true;
                                                                                }
                                                                }
                                                                else    if    (ya    !=    yb){
                                                                                水上配置[xb][yb]    =    true;
                                                                }
                                                }

                                                /**地上配置と水上配置を初期化.*/
                                                void    InitEnemyPost()
                                                {
                                                                for    (int    i    =    0;    i    <    横幅;    ++i)
                                                                {
                                                                                for    (int    j    =    0;    j    <    縦幅;    ++j)
                                                                                {
                                                                                                地上配置[i][j]    =    false;
                                                                                                水上配置[i][j]    =    false;
                                                                                }
                                                                }
                                                }

                                                /**配置が可能か確認、可能なら配置.*/
                                                bool    SetCheck(int    X座標,    int    Y座標,    int    大きさ)
                                                {
                                                                //通行不可地形に既に存在する敵は無視する
                                                                for    (int    i    =    0;    i    <    横幅;    ++i)
                                                                {
                                                                                for    (int    j    =    0;    j    <    縦幅;    ++j)
                                                                                {
                                                                                                switch(地形[i][j])
                                                                                                {
                                                                                                                case    ChipType::水:
                                                                                                                                地上配置[i][j]    =    false;
                                                                                                                                break;
                                                                                                                case    ChipType::森:
                                                                                                                case    ChipType::山:
                                                                                                                case    ChipType::高山:
                                                                                                                                地上配置[i][j]    =    false;
                                                                                                                                水上配置[i][j]    =    false;
                                                                                                                                break;
                                                                                                                default:
                                                                                                                                break;
                                                                                                }
                                                                                }
                                                                }

                                                                for    (int    i    =    0;    i    <    大きさ;    ++i)
                                                                {
                                                                                for    (int    j    =    0;    j    <    大きさ;    ++j)
                                                                                {
                                                                                                if    (砲台配置[X座標    +    i][Y座標    +    j])    return    false;
                                                                                                if    ((int)地形[X座標    +    i][Y座標    +    j]    >(int)ChipType::森)    return    false;
                                                                                                if    (地上配置[X座標    +    i][Y座標    +    j]    ||    水上配置[X座標    +    i][Y座標    +    j])    return    false;
                                                                                                if    (地形[X座標    +    i][Y座標    +    j]    ==    ChipType::井戸)    return    false;
                                                                                }
                                                                }

                                                                for    (int    i    =    0;    i    <    大きさ;    ++i)
                                                                {
                                                                                for    (int    j    =    0;    j    <    大きさ;    ++j)
                                                                                {
                                                                                                砲台配置[X座標    +    i][Y座標    +    j]    =    true;
                                                                                }
                                                                }

                                                                陸路.Init(地形,    砲台配置);

                                                                bool    isOK    =    true;
                                                                //空中でない敵がいるマスと始点が到達不可ならfalse
                                                                for    (int    i    =    0;    i    <    横幅*縦幅;    ++i)
                                                                {
                                                                                if    (
                                                                                                陸路.距離[i    %    24][i    /    24]    ==    到達不可    &&
                                                                                                (
                                                                                                        地上配置[i    %    24][i    /    24]    ==    true    ||
                                                                                                        地形[i    %    24][i    /    24]    ==    ChipType::井戸    )//||
                                                                                                        //(水上配置[i    %    24][i    /    24]    ==    true    &&    地形[i    %    24][i    /    24]    !=    ChipType::水))
                                                                                                )
                                                                                {
                                                                                                isOK    =    false;
                                                                                                break;
                                                                                }
                                                                }

                                                                if    (isOK    &&    水路.isUse)
                                                                {
                                                                                水路.Init(地形,    砲台配置);
                                                                                for    (int    i    =    0;    i    <    横幅*縦幅;    ++i)
                                                                                {
                                                                                                if    (水路.距離[i    %    24][i    /    24]    ==    到達不可    &&    水上配置[i    %    24][i    /    24]    ==    true    )
                                                                                                {
                                                                                                                isOK    =    false;
                                                                                                                break;
                                                                                                }
                                                                                }
                                                                }
                                                                
                                                                if    (!isOK)
                                                                {
                                                                                //配置を戻す
                                                                                for    (int    i    =    0;    i    <    大きさ;    ++i)
                                                                                {
                                                                                                for    (int    j    =    0;    j    <    大きさ;    ++j)
                                                                                                {
                                                                                                                砲台配置[X座標    +    i][Y座標    +    j]    =    false;
                                                                                                }
                                                                                }

                                                                                陸路.Init(地形,    砲台配置);
                                                                                if    (水路.isUse)    水路.Init(地形,    砲台配置);
                                                                }

                                                                return    isOK;
                                                }

                                                /**ユニットをどかして経路を再計算する.*/
                                                void    RemoveUnit(int    X座標,    int    Y座標,    int    大きさ)
                                                {
                                                                for    (int    i    =    0;    i    <    大きさ;    ++i)
                                                                {
                                                                                for    (int    j    =    0;    j    <    大きさ;    ++j)
                                                                                {
                                                                                                砲台配置[X座標    +    i][Y座標    +    j]    =    false;
                                                                                }
                                                                }
                                                                陸路.Init(    地形    ,    砲台配置    );
                                                                水路.Init(    地形    ,    砲台配置    );
                                                }
                                };

                                static    Land<24,    24>    *now;
                }
}