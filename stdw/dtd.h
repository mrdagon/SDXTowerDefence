//���C�u�����ݒ�
#include "DxLib.h"
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#define PI 3.14159265358979323846f
//�f�[�^�̓Ǎ�
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
//�^�C�g���ƭ�
void title();
void top_menu();
//�X�e�[�W�Z���N�g
void stage_select();
void stage_select_syori();
void stage_select_byouga();
//�{�[�i�X�^�C�����
void bonus_select();
void bonus_byouga();
void bonus_open();
void tile_make();
//�������
void history_select();
void history_byouga();
//�w���v���
void help_select();
void help_byouga();
void help_gazou(int);
//���v���C�֘A
void replay_select();
void replay_byouga();
void replay_kensaku();
//�I�v�V����
void option_select();
void option_byouga();
//�퓬���C���֐�
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
//���j���[���
void vs_menu();
//����֘A
void mouse_check();
void vs_sousa();
void vs_sousa_jikkou();
//�z�u�֌W
int set_check();
int kabe_check();
int check_sel();
void syougai_check();
void kyori_keisan(int X,int Y);
void set_unit(int T);
void sell_unit(int U);
void up_unit(int U);
void sien_check();
//�����蔻��֘A
void shot_hantei(int U);
void hit_hantei();
void han_hantei(int S);
void str_hantei(int S);
void hit_damege(int E,int S);
//�����֘A
void shot_make(int U ,int E);
void ene_make(int E,int X,int Y,int L,int T);
void sort_ene(int i);
void sort_shot(int i);
//�`��֘A
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
//�`���[�g���A���p
void tuto_byouga();
void tuto_mes(int T,int E,char mes_a[100],char mes_b[100],char mes_c[100],int I);
void tuto_mou(int T,int E,int X,int Y);
//���̑�
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
//�e�e�̏���
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
class UNITDATA {//���j�b�g�X�e�[�^�X
public:
    int type;//�W���u�^�C�v
    int lv;//�C�䃌�x��
    int atk;//�U����
    int ren;//�ˌ��Ԋu
    int spd;//�e��
    int han;//�ˌ��͈�
    int stn;//�X�^������
    int stn_p;//�X�^������
    int kuu;//�΋�␳
    int poi;//�Ō���
    int bom;//�y���͈�
    int chr;//�`���[�W���E
    int tame;//���݂̗��ߎ���
    int cost;//���j�b�g�R�X�g
    int x,y;//���W��
    int wait;//�҂����ԍő�
    int sell;//���p�t���O
    int anti;//�Α���
    int arm;//�h��ቺ
    int sum;//������΂�
};
class SHOTDATA{//�ˌ��f�[�^
public:
    int type;//�^�C�v
    int atk;//�U����
    int stn;//�X�^������
    int stn_p;//�X�^���m��
    int poi;//�Ō���
    int bom;//�y���͈�
    int sp,sx,sy;//���x����
    int time;//����
    int x,y;//���W��
    int nai_x,nai_y;//���������pX,Y
    int target;//�Ώ�
    int kuu;//�΋�Βn
    int arm;//�h��ቺ
    int ref;//���ˉ�
    int anti;//�Α���
    int sum;//������΂�����
    double r;//�p�x
};
class ENEDATA{//�G�f�[�^
public:
    int type;//�G�^�C�v
    int lv;//���x��
    int money;//����
    int hp_max;//�ő�HP
    int hp;//HP
    int spd;//���x
    int muki;//����
    int x,y;//X,Y���W
    int stan;//�X�^���c�莞��
    int poi;//�Ŏc�莞��
    int def;//�h���
    int heal;//�񕜔\��
    int fly;//��s�t���O
    int boss;//�{�X�t���O
    int nai_x,nai_y;//���������pX,Y
    int time;//�������ʗp
    int ani;//�A�j���[�V�����p
    int avoid;//���
    int steru;//�X�e���X�\��
    int muteki;//���G���
    int mx,my;//�G���ʒu���擾������W
    int m_muki;//�G�����ۑ�
    int hx,hy;//�G�������
};
class JOBDATA{//����f�[�^
public:
    char name[60];//���햼
    char info[3][60];//������
    int cost[6];//�A�b�v�O���[�h�R�X�g
    int atk[6];//�U����
    int ren[6];//�ˌ��Ԋu
    int spd[6];//�e��
    int han[6];//�ˌ��͈�
    int stn[6];//�X�^������
    int stn_p[6];//�X�^���m��
    int kuu[6];//�΋�␳
    int poi[6];//�Ō���
    int bom[6];//�y���͈�
    int chr[6];//�`���[�W���E
    int sum[6];//�X�}�b�V������
    int armer;//�h��ቺ���ʂ̗L��
    int anti;//�Α����̗L��
    int set_rest;//�ݒu�c�萔
    int up_rest;//�������
    int set_max;//�ݒu���E�@�����l
};
class SYUDATA{//�G�푰�f�[�^
public:
    char name[60];//�푰��
    char info[3][60];//������
    int hp;//HP
    int spd;//��
    int money;//����
};
class MAPDATA{//�}�b�v�f�[�^
public:
    int ok[30][30];//�ݒu�\�t���O
    int muki[30][30];//�ŒZ����
    int kyori[30][30];//�S�[���܂ł̋���
    int kabe[30][30];//�ǂ̗L��
    int goal[30][30];//�S�[���t���O
    int g_check[30][30];
    int sien[30][30];//�x������
};
class BOMDATA{
public:
    int x;
    int y;
    int r;//���a
    int color;//�F
    int time;
};
class BEAMDATA{
public:
    int x;
    int y;
    double s;//����
    double r;//�p�x
    int time;
    int type;//�F
};
class EFEDATA{
public:
    int x;//�w���W
    int y;//�x���W
    int t;//�G�t�F�N�g�c�莞��
    int s;//�G�t�F�N�g�T�C�Y
};
class SIKIKANDATA{
public:
    char name[60];//���O
    char info[6][60];//������
    int job_set[12];//�C��̎��
    int brave_t;//�K�E�Z��{��������
    int sell_sp;//���p���x
    int up_sp;//�A�b�v�O���[�h���x
    int sell_cost;//���������
};
class PLAYER{
public:
    int life;//�̗�
    int money;//����
    int brave;//�E�C���ߗ�
    int brave_time;//�E�C�c�莞��
    int brave_time_n;//�E�C�c�莞�ԓ���
    int brave_long;//�E�C��������
    int brave_rate;//�E�C���܂�Ղ�
    int brave_point;//�E�C���܂�����v�Z�p
    int score;//�X�R�A
    int siki_no;//�g�p���R�ԍ�
    int point;//�p�l���p�|�C���g
    int sell_s;//���p���x
    int up_s;//�������x
    int sell_rate;//�����
    int sozai_hitu[4];//�f�ޕK�v��
    int date;//�Ō�ɗV�񂾓��t
};
class AWARD{
public://�̍���X�e�[�^�X�㏸�t���O
    int kunsyou[160];//�M�� 160��ތ�
    int sikikan_ok[8];//���R�g�p�t���O
    int play_mode;//�e�v���C���[�h�g�p�t���O
    int stage_ok[20];//�X�e�[�W�v���C�\�t���O

    int maxup_cnt[30];//�ő�A�b�v�O���[�h��
    int set_cnt[30];//�z�u��
    int enemy_cnt[15];//�G���j��
    int boss_cnt[15];//�{�X���j��
    int enemy_maxlv[15];//�{�X�ő匂�j���x��

    int siki_siyou[8];//�w�����g�p��
    int siki_brave[8];//�u���C�u������

    int stage_clear[20];//�e�X�e�[�W�̃N���A��
    int stage_boss[20];//�e�X�e�[�W�̍ő�{�X���jLV

    int thi_score;//�g�[�^���n�C�X�R�A
    int tget_money;//���l������
    int tget_sozai;//���l���f��
    int tget_wave;//��WAVE��
    int tget_bonus;//���l���{�[�i�X
    int sozai[4];//�e�f�ނ̐�
    int help_ok[40];//�w���v���������ǂ���
    int version;//�o�[�W����
};
class BONUS{
    //�l�������{�[�i�X
public:
    int unit_setp[30];//���j�b�g�z�u�񐔁{
    int unit_upp[30];//���j�b�g�����񐔁{
    int unit_powp[30];//���j�b�g�X�e�[�^�X���
    int unit_setp_max[30];//�Z�b�g���������E
    int money_p;//���������{�[�i�X
    int life_p;//�������C�t�{�[�i�X
    int luck;//�^
};
class STAGE{
public:
    char name[60];//�X�e�[�W��
    char info[100];//������
    int samon_iti[32];//���ҏꏊ
    int samon_no;//���ҏꏊ�̐�
    int samon_time;//���ҊԊu
    int wave_type[100];//���̃X�e�[�W��WEVE�f�[�^
    int wave_sp;//wave�i�s���x
    int fly_mode;//��s���j�b�g���������i�����邩
    int map_set[30][30];//�}�b�v�f�[�^
    int hi_score[2][8];//�n�C�X�R�A�A�{�[�i�X�̗L���A���R
    int best_score[2];//�x�X�g�X�R�A�̕����ԍ�
    int max_nando[2];//�ő�N���A��Փx
    int max_siki[2][8];//�V�L�J�����̍ō��N���A��Փx
};
class INPUt{
//���͊֘A
public:
    int mou_x,mou_y,mou_LC,mou_LD,mou_RC,mou_RD,mou_h,mou_ht;//����֘A
    char p_k[256];//��������p
    char d_k[256];//������������p
    int sousa[6];//�e�푀�씻��p// WAVE�i�s,�ݒu,����,����,�d��,�u���C�u
    int select;//�I�𑀍�//
};
class OPTION{
public:
    int sc_key[6];//�e�V���[�g�J�b�g�L�[ M B N S U W
    int efe_on;//�G�t�F�N�g�̗L��
    int bgm_on;//���y�̑傫��
    int se_on;//���ʉ��̑傫��
    int grid_on;//�O���b�h�̔Z��
    int hp_on;//�G�g�o�̕\��
    int key_set[26];//�Ή�����L�[
};
class TILE{
    public://�̍���X�e�[�^�X�㏸�t���O
    int naka[10][10];//�^�C���̒��g
    int open[10][10];//�^�C���߂���t���O
    int ok[10][10];//�^�C��������t���O
    int chance[93];//�^�C���o��m��
    int hitu[93][4];//�K�v�f��
};
class HELP{
public:
    char name[60];//�w���v���o��
    char info[16][60];//�w���v���e
    int x;//���������炷����
};
class REPLAY{
public:
    //�t�@�C���w�b�_�p
    char name[100][60];
    int stage[100];
    int sikikan[100];
    int mode[100];
    int time[100];
    int score[100];
    //�ǂݍ���
    int rand;
    int sousa[100000];//������e//WAVE�i�s,�ݒu,���p,����,�d��,�u���C�u�̋L�^�ƍĐ��p
    int select[100000];//�I��//�G�I���A����I���A���j�b�g�I��
    int count[100000];//���쎞��
    int iti[100000];//�ݒu�ʒu
    int no;//���݂ǂ��܂ōĐ��A�L�^������
    int ok;//��
    int kazu;//���v���C�̐�

    int aut;//�I�[�g�ۑ�
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
    int sp_up;//����
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
    int hai;//�F
};
class SELECT{
public:
    int nando;
    int stage;
    int bonus;
    int x;//�I�����Ă���C�䓙
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
    int tu_x;//�`���[�g���A�����}�E�X�p
    int tu_y;
    int tu_px;
    int tu_py;
    int debug[3];//�f�o�b�O���[�h
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
