//ライブラリ設定
#include "DxLib.h"
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#define PI 3.14159265358979323846f
//データの読込
void gazou_load();
void sound_load();
void map_load();
void unit_load();
void job_load();
void text_load();
int  text_check(char TEX[60]);
void sikikan_data();
void nando_data();
void ene_data();
void option_data();
void data_save();
void data_load();
void replay_save();
void replay_load();
//タイトルﾒﾆｭｰ
void title();
void top_menu();
//ステージセレクト
void stage_select();
void stage_select_syori();
void stage_select_byouga();
//ボーナスタイル画面
void bonus_select();
void bonus_byouga();
void bonus_open();
void tile_make();
//履歴画面
void history_select();
void history_byouga();
//ヘルプ画面
void help_select();
void help_byouga();
void help_gazou(int);
//リプレイ関連
void replay_select();
void replay_byouga();
void replay_kensaku();
//オプション
void option_select();
void option_byouga();
//戦闘メイン関数
void vs_syokika();
void bonus_hosei();
void vs_main();
void replay_syori();
void player_syori();
void wave_syori();
void unit_syori();
void shot_syori();
void ene_syori();
void ene_move(int);
void ene_kabe(int);
void gameover_syori();
//メニュー画面
void vs_menu();
//操作関連
void mouse_check();
void vs_sousa();
void vs_sousa_jikkou();
//配置関係
int set_check();
int kabe_check();
int check_sel();
void syougai_check();
void kyori_keisan(int X,int Y);
void set_unit(int T);
void sell_unit(int U);
void up_unit(int U);
void sien_check();
//当たり判定関連
void shot_hantei(int U);
void hit_hantei();
void han_hantei(int S);
void str_hantei(int S);
void hit_damege(int E,int S);
//生成関連
void shot_make(int U ,int E);
void ene_make(int E,int X,int Y,int L,int T);
void sort_ene(int i);
void sort_shot(int i);
//描画関連
void byouga_syori();
void back_byouga();
void unit_byouga();
void ene_byouga();
void shot_byouga();
void wave_byouga();
void brave_byouga();
void menu_byouga();
void gameover_byouga();
void status_byouga();
void status_unit(int U);
void status_ene(int E);
//チュートリアル用
void tuto_byouga();
void tuto_mes(int T,int E,char mes_a[100],char mes_b[100],char mes_c[100],int I);
void tuto_mou(int T,int E,int X,int Y);
//その他
void err_c();
double kakudo(int x_1,int y_1 ,int x_2,int y_2);
void award_check();
void mes(int X,int Y,char M[100],int C,int C2,int F);
void mes_bmf(int X,int Y,char M[30],int XKAN,double SIZE);
void suu_bmf(int X,int Y,double SIZE,int U,int XKAN,int T);
void waku(int X,int Y,int XS,int YS,int TYPE,int NO);
double kakudo(int,int,int,int);
void okodukai_check();
void se_ok(int S);
void fps_check();
int randam(int R);
//各弾の処理
int shot_move_n(int S);
int shot_move_s(int S);
int shot_move_r(int S);
int shot_move_hm(int S);
int shot_move03(int S);
int shot_move05(int S);
int shot_move10(int S);
int shot_move14(int S);
int shot_move21(int S);
int shot_move22(int S);
//
class UNITDATA {//ユニットステータス
public:
    int type;//ジョブタイプ
    int lv;//砲台レベル
    int atk;//攻撃力
    int ren;//射撃間隔
    int spd;//弾速
    int han;//射撃範囲
    int stn;//スタン時間
    int stn_p;//スタン時間
    int kuu;//対空補正
    int poi;//毒効果
    int bom;//炸裂範囲
    int chr;//チャージ限界
    int tame;//現在の溜め時間
    int cost;//ユニットコスト
    int x,y;//座標軸
    int wait;//待ち時間最大
    int sell;//売却フラグ
    int anti;//対属性
    int arm;//防御低下
    int sum;//吹き飛ばし
};
class SHOTDATA{//射撃データ
public:
    int type;//タイプ
    int atk;//攻撃力
    int stn;//スタン時間
    int stn_p;//スタン確率
    int poi;//毒効果
    int bom;//炸裂範囲
    int sp,sx,sy;//速度成分
    int time;//時間
    int x,y;//座標軸
    int nai_x,nai_y;//内部処理用X,Y
    int target;//対象
    int kuu;//対空対地
    int arm;//防御低下
    int ref;//反射回数
    int anti;//対属性
    int sum;//吹き飛ばし効果
    double r;//角度
};
class ENEDATA{//敵データ
public:
    int type;//敵タイプ
    int lv;//レベル
    int money;//資金
    int hp_max;//最大HP
    int hp;//HP
    int spd;//速度
    int muki;//方向
    int x,y;//X,Y座標
    int stan;//スタン残り時間
    int poi;//毒残り時間
    int def;//防御力
    int heal;//回復能力
    int fly;//飛行フラグ
    int boss;//ボスフラグ
    int nai_x,nai_y;//内部処理用X,Y
    int time;//距離判別用
    int ani;//アニメーション用
    int avoid;//回避率
    int steru;//ステルス能力
    int muteki;//無敵状態
    int mx,my;//敵が位置を取得する座標
    int m_muki;//敵向き保存
    int hx,hy;//敵吹き飛び
};
class JOBDATA{//兵種データ
public:
    char name[60];//兵種名
    char info[3][60];//説明文
    int cost[6];//アップグレードコスト
    int atk[6];//攻撃力
    int ren[6];//射撃間隔
    int spd[6];//弾速
    int han[6];//射撃範囲
    int stn[6];//スタン時間
    int stn_p[6];//スタン確率
    int kuu[6];//対空補正
    int poi[6];//毒効果
    int bom[6];//炸裂範囲
    int chr[6];//チャージ限界
    int sum[6];//スマッシュ効果
    int armer;//防御低下効果の有無
    int anti;//対属性の有無
    int set_rest;//設置残り数
    int up_rest;//強化上限
    int set_max;//設置限界　初期値
};
class SYUDATA{//敵種族データ
public:
    char name[60];//種族名
    char info[3][60];//説明文
    int hp;//HP
    int spd;//速
    int money;//資金
};
class MAPDATA{//マップデータ
public:
    int ok[30][30];//設置可能フラグ
    int muki[30][30];//最短方向
    int kyori[30][30];//ゴールまでの距離
    int kabe[30][30];//壁の有無
    int goal[30][30];//ゴールフラグ
    int g_check[30][30];
    int sien[30][30];//支援効果
};
class BOMDATA{
public:
    int x;
    int y;
    int r;//半径
    int color;//色
    int time;
};
class BEAMDATA{
public:
    int x;
    int y;
    double s;//太さ
    double r;//角度
    int time;
    int type;//色
};
class EFEDATA{
public:
    int x;//Ｘ座標
    int y;//Ｙ座標
    int t;//エフェクト残り時間
    int s;//エフェクトサイズ
};
class SIKIKANDATA{
public:
    char name[60];//名前
    char info[6][60];//説明文
    int job_set[12];//砲台の種類
    int brave_t;//必殺技基本発動時間
    int sell_sp;//売却速度
    int up_sp;//アップグレード速度
    int sell_cost;//資金回収率
};
class PLAYER{
public:
    int life;//体力
    int money;//お金
    int brave;//勇気ため量
    int brave_time;//勇気残り時間
    int brave_time_n;//勇気残り時間内部
    int brave_long;//勇気発動時間
    int brave_rate;//勇気溜まり易さ
    int brave_point;//勇気溜まり内部計算用
    int score;//スコア
    int siki_no;//使用将軍番号
    int point;//パネル用ポイント
    int sell_s;//売却速度
    int up_s;//強化速度
    int sell_rate;//回収率
    int sozai_hitu[4];//素材必要数
    int date;//最後に遊んだ日付
};
class AWARD{
public://称号､ステータス上昇フラグ
    int kunsyou[160];//勲章 160種類個
    int sikikan_ok[8];//将軍使用フラグ
    int play_mode;//各プレイモード使用フラグ
    int stage_ok[20];//ステージプレイ可能フラグ

    int maxup_cnt[30];//最大アップグレード回数
    int set_cnt[30];//配置回数
    int enemy_cnt[15];//敵撃破回数
    int boss_cnt[15];//ボス撃破回数
    int enemy_maxlv[15];//ボス最大撃破レベル

    int siki_siyou[8];//指揮官使用回数
    int siki_brave[8];//ブレイブ発動回数

    int stage_clear[20];//各ステージのクリア回数
    int stage_boss[20];//各ステージの最大ボス撃破LV

    int thi_score;//トータルハイスコア
    int tget_money;//総獲得資金
    int tget_sozai;//総獲得素材
    int tget_wave;//総WAVE数
    int tget_bonus;//総獲得ボーナス
    int sozai[4];//各素材の数
    int help_ok[40];//ヘルプを見たかどうか
    int version;//バージョン
};
class BONUS{
    //獲得したボーナス
public:
    int unit_setp[30];//ユニット配置回数＋
    int unit_upp[30];//ユニット強化回数＋
    int unit_powp[30];//ユニットステータス上限
    int unit_setp_max[30];//セット数強化限界
    int money_p;//初期資金ボーナス
    int life_p;//初期ライフボーナス
    int luck;//運
};
class STAGE{
public:
    char name[60];//ステージ名
    char info[100];//説明文
    int samon_iti[32];//召還場所
    int samon_no;//召還場所の数
    int samon_time;//召還間隔
    int wave_type[100];//そのステージのWEVEデータ
    int wave_sp;//wave進行速度
    int fly_mode;//飛行ユニットを強制直進させるか
    int map_set[30][30];//マップデータ
    int hi_score[2][8];//ハイスコア、ボーナスの有無、将軍
    int best_score[2];//ベストスコアの武将番号
    int max_nando[2];//最大クリア難易度
    int max_siki[2][8];//シキカン毎の最高クリア難易度
};
class INPUt{
//入力関連
public:
    int mou_x,mou_y,mou_LC,mou_LD,mou_RC,mou_RD,mou_h,mou_ht;//操作関連
    char p_k[256];//押し判定用
    char d_k[256];//押し続け判定用
    int sousa[6];//各種操作判定用// WAVE進行,設置,解雇,強化,仕事,ブレイブ
    int select;//選択操作//
};
class OPTION{
public:
    int sc_key[6];//各ショートカットキー M B N S U W
    int efe_on;//エフェクトの有無
    int bgm_on;//音楽の大きさ
    int se_on;//効果音の大きさ
    int grid_on;//グリッドの濃さ
    int hp_on;//敵ＨＰの表示
    int key_set[26];//対応するキー
};
class TILE{
    public://称号､ステータス上昇フラグ
    int naka[10][10];//タイルの中身
    int open[10][10];//タイルめくりフラグ
    int ok[10][10];//タイル見えるフラグ
    int chance[93];//タイル登場確率
    int hitu[93][4];//必要素材
};
class HELP{
public:
    char name[60];//ヘルプ見出し
    char info[16][60];//ヘルプ内容
    int x;//文字をずらす距離
};
class REPLAY{
public:
    //ファイルヘッダ用
    char name[100][60];
    int stage[100];
    int sikikan[100];
    int mode[100];
    int time[100];
    int score[100];
    //読み込む
    int rand;
    int sousa[100000];//操作内容//WAVE進行,設置,売却,強化,仕事,ブレイブの記録と再生用
    int select[100000];//選択//敵選択、兵種選択、ユニット選択
    int count[100000];//操作時間
    int iti[100000];//設置位置
    int no;//現在どこまで再生、記録したか
    int ok;//リ
    int kazu;//リプレイの数

    int aut;//オート保存
};
class NANDO{
public:
    int hp_hosei;
    int lv_hosei;
    int samon_zako;
    int samon_boss;
    int wave;
};
class FPS{
public:
    int time;
    int count;
    int rest;
    int now;
    int sp_up;//加速
    double tyousei;
};
class GLAFIC{
public:
    int unit[30][12];
    int ene[15][12];
    int shot[30];
    int icon[40];
    int font[50];
    int chip[10];
    int wskin[4][96];
    int kill[5];
    int beam;
};
class COLOR{
public:
    int siro;
    int kuro;
    int aka;
    int ao;
    int mido;
    int hai;//色
};
class SELECT{
public:
    int nando;
    int stage;
    int bonus;
    int x;//選択している砲台等
    int y;
    int no;
    int scroll;
    int file;
};
class FONT{
public:
    int a;
    int b;
    int s;
};
class SYSTEM{
public:
    int e_cnt;
    int s_cnt;
    int u_cnt;
    int w_no;
    int w_time;
    int p_time;
    int stage_no;
    int game_sp;
    int ene_on[30][30];
    int goal_check;
    int m_mode;
    int tutorial_on;
    int tu_x;//チュートリアル時マウス用
    int tu_y;
    int tu_px;
    int tu_py;
    int debug[3];//デバッグモード
};
class SOUND{
public:
    int wav[50];
};
class UNITDATA unit[200];
class SHOTDATA shot[10000];
class ENEDATA ene[10000];
class SYUDATA syu[15];
class JOBDATA job[30];
class MAPDATA map;
class MAPDATA map_c;
class MAPDATA map_f;
class BOMDATA bom_efe[100];
class BEAMDATA beam_efe[100];
class EFEDATA kill_efe[100];
class PLAYER player;
class AWARD award;
class STAGE stage[20];
class INPUt inp;
class SIKIKANDATA sikikan[8];
class BONUS bonus;
class TILE tile;
class OPTION option;
class HELP help[45];
class REPLAY replay;
class NANDO nando[12];
class FPS fps;
class GLAFIC gf;
class COLOR color;
class SELECT sel;
class FONT font;
class SYSTEM sys;
class SOUND se;
