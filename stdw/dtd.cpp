//���C�u�����ݒ�
#include "dtd.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ){

	int SMODE=0;
	if(MessageBox
		(GetMainWindowHandle(),
	"�t���X�N���[���ŋN�����܂����H","�N�����[�h"
	,MB_YESNO)==IDNO)SMODE=1;
	

	SetMainWindowText( "STDW ver1.13" ) ;
	if(SMODE==1)ChangeWindowMode( TRUE ) ;//�E�B���h�E���[�h�ɕύX
	SetGraphMode( 640 , 480 ,16) ;//�O���t�B�b�N���[�h����
	SetScreenMemToVramFlag( FALSE ) ;//�u�������g�p���Ȃ�
	SetOutApplicationLogValidFlag( FALSE ) ;//���O�o�͂��Ȃ�
	if( DxLib_Init() == -1 )return -1 ;//�c�w���C�u�������������� �G���[���N�����璼���ɏI��
	SetDrawScreen( DX_SCREEN_BACK ) ;//�`�ʐ�𗠉�ʂɐݒ�
	SetTransColor( 190 , 179 , 145 ) ;// ���ߐF��ύX
	SetMouseDispFlag( 1 ) ;//�}�E�X�J�[�\���\������

	//�t�H���g�̍쐬
	font.s= CreateFontToHandle( NULL , 12 , 5 ) ;
	font.a= CreateFontToHandle( "HGS�n�p�p�߯�ߑ�" , 32 , 9 ) ;
	font.b= CreateFontToHandle( "HGS�n�p�p�߯�ߑ�" , 64 , 9 ) ;

	mes(400,420,"Now Loading...",GetColor(255,255,255),GetColor(122,122,122),font.a);

	ScreenFlip();

	//�����t���O
	award.play_mode=2;
	int X,H;
	for(X=0;X<8;X++){
		award.sikikan_ok[X]=1;
	}
	award.stage_ok[0]=1;

	for(H=0;H<24;H++){
		award.help_ok[H]=1;
	}
	award.help_ok[29]=1;
	award.sozai[0]=100000;
	award.sozai[1]=100000;
	award.sozai[2]=100000;
	award.sozai[3]=100000;
	srand(GetNowCount());
	gazou_load();
	sound_load();
	map_load();
	job_load();
	text_load();
	sikikan_data();
	ene_data();
	nando_data();
	tile_make();
	option_data();

	data_load();
	data_save();

	title();

	DxLib_End();// �c�w���C�u�����g�p�̏I������
	return 0;// �I��
}
//�f�[�^�̓Ǎ�
void gazou_load(){
	//�摜,�����̓Ǎ�
	//���j�b�g�摜
	LoadDivGraph( "File/unit/03a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[0]);//���j�b�g�@�����@30�@70�@�ݒu�R�X�g 3
	LoadDivGraph( "File/unit/06a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[1]);//���j�b�g�@�����@15�@60�@�����؂�
	LoadDivGraph( "File/unit/05a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[2]);//���j�b�g�@�����@15�@60�@�RWAY
	LoadDivGraph( "File/unit/40a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[3]);//���j�b�g�@�����@15�@60�@�u�[�������@���
	LoadDivGraph( "File/unit/13a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[4]);//���j�b�g�@�|���@15�@60�@�΋�@�RWAY
	LoadDivGraph( "File/unit/08a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[5]);//���j�b�g�@�����@10�@50�@�͈͒e
	LoadDivGraph( "File/unit/07a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[6]);//���j�b�g�@�m���@10�@50�@�Βn�͈�
	LoadDivGraph( "File/unit/10a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[7]);//���j�b�g�@�����@10�@50�@�ŒP��
	LoadDivGraph( "File/unit/12a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[8]);//���j�b�g�@�x�q�@10�@50�@�x��.��
	LoadDivGraph( "File/unit/42a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[9]);//���j�b�g�@�����@10�@50�@�g�́A���
	LoadDivGraph( "File/unit/09a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[10]);//���j�b�g �b���@15�@60�@�z�[�~���O

	LoadDivGraph( "File/unit/16a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[11]);//���j�b�g�@�V�� 10 50�@�ݒu�R�X�g 1
	LoadDivGraph( "File/unit/24a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[12]);//���j�b�g�@���m 5�@25�@���C�h�؂�
	LoadDivGraph( "File/unit/26a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[13]);//���j�b�g�@�R�m 5�@25�@�ǔ��˂Q��@*2,*2
	LoadDivGraph( "File/unit/18a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[14]);//���j�b�g�@���m 5�@25�@�S�A�U��񂵔���
	LoadDivGraph( "File/unit/25a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[15]);//���j�b�g�@�ˎ� 5�@25�@�΋��p
	LoadDivGraph( "File/unit/44a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[16]);//���j�b�g�@���� 5�@25�@�z�[�~���O�͈�
	LoadDivGraph( "File/unit/27a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[17]);//���j�b�g�@�_�� 5�@25�@�����͈�
	LoadDivGraph( "File/unit/11a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[18]);//���j�b�g�@�E�� 5�@25�@�͈͓�
	LoadDivGraph( "File/unit/41a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[19]);//���j�b�g�@�R�t 5�@25�@�x��.��
	LoadDivGraph( "File/unit/38a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[20]);//���j�b�g�@���d 5�@25�@�g�́A���[�U�[
	LoadDivGraph( "File/unit/19a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[21]);//���j�b�g�@�E�� 5�@25�@����z�[�~���O
	LoadDivGraph( "File/unit/20a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[22]);//���j�b�g�@�p�Y 1�@0�@ �E�ҋ���
	LoadDivGraph( "File/unit/47a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[23]);//���j�b�g�@�p�Y 1�@0�@ ���˒��A����
	LoadDivGraph( "File/unit/39a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[24]);//���j�b�g�@�p�Y 1�@0�@ �x����ŋ�
	LoadDivGraph( "File/unit/15a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[25]);//���j�b�g�@�p�Y 1�@0�@ ���͖h��ቺ�͈�
	LoadDivGraph( "File/unit/11e.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[26]);//���j�b�g�@�p�Y 1�@0�@ �R�m�A�G���h���X
	LoadDivGraph( "File/unit/45a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[27]);//���j�b�g�@�p�Y 1�@0�@ ���ҁA�͈̓z�[�~���O
	LoadDivGraph( "File/unit/37a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[28]);//���j�b�g�@�p�Y 1�@0�@ �m���A���͓�
	LoadDivGraph( "File/unit/29a.bmp" ,12, 3 , 4 , 16 , 16 , gf.unit[29]);//���j�b�g�@�p�Y 1�@0�@ �_���A���[�U�[

	//�G�摜
	LoadDivGraph( "File/unit/00b.bmp" ,12, 3 , 4 , 16 , 16 , gf.ene[0]);//�X���C��
	LoadDivGraph( "File/unit/36b.bmp" ,12, 3 , 4 , 16 , 16 , gf.ene[1]);//�S�u����
	LoadDivGraph( "File/unit/02b.bmp" ,12, 3 , 4 , 16 , 16 , gf.ene[2]);//�I�[�K
	LoadDivGraph( "File/unit/30b.bmp" ,12, 3 , 4 , 16 , 16 , gf.ene[3]);//�R�{���h
	LoadDivGraph( "File/unit/43b.bmp" ,12, 3 , 4 , 16 , 16 , gf.ene[4]);//�P�b�g�V�[
	LoadDivGraph( "File/unit/17b.bmp" ,12, 3 , 4 , 16 , 16 , gf.ene[5]);//�V���[�}��
	LoadDivGraph( "File/unit/28b.bmp" ,12, 3 , 4 , 16 , 16 , gf.ene[6]);//�X�P���g��
	LoadDivGraph( "File/unit/31b.bmp" ,12, 3 , 4 , 16 , 16 , gf.ene[7]);//�C���v
	LoadDivGraph( "File/unit/32b.bmp" ,12, 3 , 4 , 16 , 16 , gf.ene[8]);//�O���t�H��
	LoadDivGraph( "File/unit/33b.bmp" ,12, 3 , 4 , 16 , 16 , gf.ene[9]);//�P���x���X
	LoadDivGraph( "File/unit/29b.bmp" ,12, 3 , 4 , 16 , 16 , gf.ene[10]);//�S�[����
	LoadDivGraph( "File/unit/34b.bmp" ,12, 3 , 4 , 16 , 16 , gf.ene[11]);//�h���S��
	LoadDivGraph( "File/unit/35b.bmp" ,12, 3 , 4 , 16 , 16 , gf.ene[12]);//�L���O�X���C��
	
	LoadDivGraph( "File/system/shot.png" , 30 , 10 , 3 , 32 , 32 , gf.shot);//�ˌ��摜
	LoadDivGraph( "File/system/font.bmp" , 50 , 10 , 5 , 10 , 10 , gf.font);//�t�H���g�摜
	LoadDivGraph( "File/system/kill.bmp" , 5 , 5 , 1 , 32 , 32 , gf.kill);//�t�H���g�摜
	LoadDivGraph( "File/system/mapchip.png" , 10 , 10 , 1 , 16 , 16 , gf.chip);
	LoadDivGraph( "File/system/icon.bmp" , 40 , 10 , 4 , 24 , 24 , gf.icon);//�A�C�R���摜
	
	LoadDivGraph( "File/system/wskin_a.bmp" ,96, 12 , 8 , 16 , 16 , gf.wskin[0]);//�E�B���h�E�X�L��
	LoadDivGraph( "File/system/wskin_b.bmp" ,96, 12 , 8 , 16 , 16 , gf.wskin[1]);
	LoadDivGraph( "File/system/wskin_c.bmp" ,96, 12 , 8 , 16 , 16 , gf.wskin[2]);
	LoadDivGraph( "File/system/wskin_d.bmp" ,96, 12 , 8 , 16 , 16 , gf.wskin[3]);

	gf.beam=LoadGraph("File/system/beam.bmp");

	color.siro=GetColor(255,255,255);//�F�ł�����
	color.kuro=GetColor(0,0,0);
	color.aka=GetColor(255,0,0);
	color.ao=GetColor(0,0,255);
	color.mido=GetColor(0,255,0);
	color.hai=GetColor(128,128,128);
	return;
}
void sound_load(){
	int S;
	for(S=0;S<50;S++){
		se.wav[S] = LoadSoundMem( "File/sound/set.wav" ) ;
	}
		se.wav[0] = LoadSoundMem( "File/sound/bom11.wav" ) ;//�{�X���j
		se.wav[1] = LoadSoundMem( "File/sound/bom23.wav" ) ;//�G�����j
		se.wav[2] = LoadSoundMem( "File/sound/coin03.wav" ) ;//�^�C��
		se.wav[3] = LoadSoundMem( "File/sound/coin06.wav" ) ;//����
		se.wav[4] = LoadSoundMem( "File/sound/cursor01.wav" ) ;//�߂�
		se.wav[5] = LoadSoundMem( "File/sound/cursor16.wav" ) ;//�؂�ւ�
		se.wav[6] = LoadSoundMem( "File/sound/cursor18.wav" ) ;//����
		se.wav[7] = LoadSoundMem( "File/sound/power39.wav" ) ;//���i
		se.wav[8] = LoadSoundMem( "File/sound/beep14.wav" ) ;//�ے�
		se.wav[9] = LoadSoundMem( "File/sound/voice015.wav" ) ;//�˔j
		se.wav[10] = LoadSoundMem("File/sound/weapon00.wav" ) ;//�ݒu
		se.wav[11] = LoadSoundMem("File/sound/power34.wav" ) ;//WAVE
		//�U����
		se.wav[12] = LoadSoundMem( "File/sound/shoot19.wav" ) ;//����
		se.wav[13] = LoadSoundMem( "File/sound/swing02.wav" ) ;//��
		se.wav[14] = LoadSoundMem( "File/sound/swing06.wav" ) ;//��
		se.wav[15] = LoadSoundMem( "File/sound/swing07.wav" ) ;//��
		se.wav[16] = LoadSoundMem( "File/sound/arrow01.wav" ) ;//�|
		se.wav[17] = LoadSoundMem( "File/sound/swing27.wav" ) ;//��
		se.wav[18] = LoadSoundMem( "File/sound/bom34.wav" ) ;//�m
		se.wav[19] = LoadSoundMem( "File/sound/sha00.wav" ) ;//����
		se.wav[20] = LoadSoundMem( "File/sound/shoot19.wav" ) ;//�x��q
		se.wav[21] = LoadSoundMem( "File/sound/bom13_c.wav" ) ;//����
		se.wav[22] = LoadSoundMem( "File/sound/shoot23_a.wav" ) ;//����
		se.wav[23] = LoadSoundMem( "File/sound/swing14.wav" ) ;//�b��
		se.wav[24] = LoadSoundMem( "File/sound/swing28.wav" ) ;//��
		se.wav[25] = LoadSoundMem( "File/sound/shoot13.wav" ) ;//�R�m
		se.wav[26] = LoadSoundMem( "File/sound/swing41.wav" ) ;//���m
		se.wav[27] = LoadSoundMem( "File/sound/arrow02.wav" ) ;//�ˎ�
		se.wav[28] = LoadSoundMem( "File/sound/don19.wav" ) ;//����
		se.wav[29] = LoadSoundMem( "File/sound/eco00_r.wav" ) ;//�_��
		se.wav[30] = LoadSoundMem( "File/sound/swing37_b.wav" ) ;//�E��
		se.wav[31] = LoadSoundMem( "File/sound/shoot10.wav" ) ;//�R�t
		se.wav[32] = LoadSoundMem( "File/sound/freeze02.wav" ) ;//���d
		se.wav[33] = LoadSoundMem( "File/sound/shoot23_a.wav" ) ;//�E��
		se.wav[34] = LoadSoundMem( "File/sound/shoot23_b.wav" ) ;//�س�
		se.wav[35] = LoadSoundMem( "File/sound/shoot12.wav" ) ;//���
		se.wav[36] = LoadSoundMem( "File/sound/shoot19.wav" ) ;//�n�Q
		se.wav[37] = LoadSoundMem( "File/sound/gun17.wav" ) ;//����
		se.wav[38] = LoadSoundMem( "File/sound/swing29.wav" ) ;//�ֺ
		se.wav[39] = LoadSoundMem( "File/sound/hit64.wav" ) ;//п�
		se.wav[40] = LoadSoundMem( "File/sound/smoke00.wav" ) ;//���
		se.wav[41] = LoadSoundMem( "File/sound/gun11_r.wav" ) ;//�����
	return;
}
void map_load(){
	//�e�X�e�[�W�̃}�b�v��WAVE�f�[�^�̓Ǎ�
	int X,Y,Z,S=0;
	char FILE_NAME[30];
	strcpy_s(FILE_NAME, "File/stage/stage00.map");
	//�t�@�C�����J��
	FILE *fp;
	errno_t err;
	for(S=0;S<20;S++){
		FILE_NAME[16]=S/10+48;
		FILE_NAME[17]=S%10+48;
		if( (err = fopen_s( &fp,FILE_NAME , "rb+" )) !=0 ){
			DxLib_End() ;//DX���C�u�����̎g�p�I��
			exit(1);//�v���O�����̏I��
		}
		//�}�b�v�̓Ǎ����X�e�[�W���̓Ǎ�
		Z=0;
		fseek(fp, 16, SEEK_SET);
		stage[S].samon_no=0;
		for(Y=0;Y<30;Y++){
			for(X=0;X<30;X++){
			fread( &stage[S].map_set[X][Y] , 1 , 1 , fp ) ;
			if(stage[S].map_set[X][Y]==4){
				stage[S].samon_iti[Z]=X	+Y*30;//���҈ʒu
				stage[S].samon_no++;
				Z++;
				}
			}
		}

		if(S%5==0)		stage[S].samon_time=80;
		else if(S%5==0)	stage[S].samon_time=50;
		else if(S%5==0)	stage[S].samon_time=40;
		else if(S%5==0)	stage[S].samon_time=60;
		else			stage[S].samon_time=50;
		stage[S].wave_sp=4000;
		stage[S].fly_mode=0;
		fclose( fp );
	}
	stage[4].fly_mode=1;//��s���j�b�g�����i�����
	stage[9].fly_mode=1;
	stage[16].fly_mode=1;
	stage[18].fly_mode=1;

	stage[0].wave_sp=5000;
	stage[1].wave_sp=4500;
	stage[2].wave_sp=4500;
	stage[3].wave_sp=5000;
	stage[10].wave_sp=3500;
	stage[11].wave_sp=3500;
	stage[12].wave_sp=3500;
	stage[15].wave_sp=3500;
	stage[17].wave_sp=5000;
	stage[18].wave_sp=2000;

	strcpy_s(FILE_NAME, "File/stage/enemy00.map");
	for(S=0;S<20;S++){
		//��������G�z�u
		FILE_NAME[16]=S/10+48;
		FILE_NAME[17]=S%10+48;
		if( (err = fopen_s( &fp,FILE_NAME , "rb+" )) !=0 ){
			DxLib_End() ;//DX���C�u�����̎g�p�I��
			exit(1);//�v���O�����̏I��
		}
		fseek(fp, 16, SEEK_SET);
		//���j�b�g�f�[�^�̓Ǎ�
		for(Y=0;Y<100;Y++){
			fread( &stage[S].wave_type[Y] , 1 , 1 , fp ) ;
		}
		fclose( fp );
	}
	return;
}
void unit_load(){
	int J,L;
	//�t�@�C�����J��
	FILE *fp;
	errno_t err;

	if( (err = fopen_s( &fp,"File/data/unit.dat" , "rb+" )) !=0 ){
		DxLib_End() ;//DX���C�u�����̎g�p�I��
		exit(1);//�v���O�����̏I��
	}
	//���j�b�g�f�[�^�̓Ǎ�
	for(J=0;J<30;J++){
		for(L=0;L<6;L++){
		/* �t�@�C���̐擪�Ɉړ� */
		job[J].atk[L]=0;
		job[J].ren[L]=0;
		job[J].spd[L]=0;
		job[J].han[L]=0;
		job[J].stn[L]=0;
		job[J].poi[L]=0;
		job[J].bom[L]=0;
		job[J].chr[L]=0;
		fread( &job[J].cost[L] , 2 , 1 , fp ) ;
		fread( &job[J].atk[L] , 2 , 1 , fp ) ;
		fread( &job[J].ren[L] , 2 , 1 , fp ) ;
		job[J].ren[L]*=10;
		fread( &job[J].spd[L] , 2 , 1 , fp ) ;
		fread( &job[J].han[L] , 2 , 1 , fp ) ;
		fread( &job[J].stn[L] , 2 , 1 , fp ) ;
		fread( &job[J].stn_p[L] , 1 , 1 , fp ) ;
		fread( &job[J].kuu[L] , 1 , 1 , fp ) ;
		fread( &job[J].poi[L] , 2 , 1 , fp ) ;
		fread( &job[J].bom[L] , 2 , 1 , fp ) ;
		fread( &job[J].chr[L] , 1 , 1 , fp ) ;
			if(player.siki_no==1){//�J�m��
			job[J].han[L]+=job[J].han[L]/5;//20%�˒��{
			job[J].spd[L]-=job[J].spd[L]/10;//10%-
			}
			if(player.siki_no==2){//�c���n�Q
			job[J].cost[L]=job[J].cost[L]*4/5;//20%�l�i�����؎̂�
			job[J].atk[L]-=job[J].atk[L]/5;//20%�U���͒ቺ
			job[J].chr[L]+=job[J].chr[L]/10;//10%�x������
			}
			if(player.siki_no==3){//�A�b�N�X
			if(job[J].han[L]>64 && job[J].han[L]<84)job[J].han[L]=64;//64�ȉ��ɂ͉�����Ȃ�
			else if(job[J].han[L]>=84)				job[J].han[L]-=20;//�ቺ
			job[J].atk[L]+=job[J].atk[L]/5;//20%�U���͏㏸
			}
			if(player.siki_no==4){//���q
			job[J].cost[L]+=job[J].cost[L]/3;//33%�㏸�؎̂�
			job[J].atk[L]+=job[J].atk[L]*9/20;//45%�U���͏㏸
			}
			if(player.siki_no==5){//�~�\��
			job[J].ren[L]+=job[J].ren[L]/2;//50%�㏸�؎̂�
			job[J].atk[L]-=job[J].atk[L]/3;//33%�U���͒ቺ
			job[J].spd[L]+=job[J].spd[L]/5;//20%+
			}
			if(player.siki_no==6){//���
			job[J].poi[L]+=job[J].poi[L]/3;//��33%�㏸
			job[J].stn[L]+=job[J].stn[L]/3;//���33%�㏸
			}
			if(player.siki_no==7){//���[���܂�
			job[J].bom[L]+=job[J].bom[L]/5;//����20%�㏸
			}
		}
	}
	//�t�@�C�������
	fclose( fp ) ;
	return;
}
void job_load(){
	//�e�X�e�[�W�̃}�b�v��WAVE�f�[�^�̓Ǎ�
	int X,J;
	//�t�@�C�����J��
	FILE *fp;
	errno_t err;

	if( (err = fopen_s( &fp,"File/data/unit.dat" , "r+" )) !=0 ){
		DxLib_End() ;//DX���C�u�����̎g�p�I��
		exit(1);//�v���O�����̏I��
	}

	fseek(fp, 3420, SEEK_SET);

	//���j�b�g�f�[�^�̓Ǎ�
	for(X=0;X<30;X++){
		fread( &tile.hitu[X*3][0] , 1 , 1 , fp );
		fread( &tile.hitu[X*3][1] , 1 , 1 , fp );
		fread( &tile.hitu[X*3][2] , 1 , 1 , fp );
		fread( &tile.hitu[X*3][3] , 1 , 1 , fp );
		fread( &job[X].anti		  , 1 , 1 , fp );
		fread( &job[X].set_max	  , 1 , 1 , fp );
		fread( &job[X].sum[0]	  , 1 , 1 , fp );
		fread( &job[X].sum[1]	  , 1 , 1 , fp );
		fread( &job[X].sum[2]	  , 1 , 1 , fp );
		fread( &job[X].sum[3]	  , 1 , 1 , fp );
		fread( &job[X].sum[4]	  , 1 , 1 , fp );
		fread( &job[X].sum[5]	  , 1 , 1 , fp );
	}
	fclose( fp );

	job[14].armer=1;
	job[25].armer=1;

	for(J=0;J<30;J++){//�����A�ݒu�͑S��������p
		for(X=0;X<4;X++){
		tile.hitu[J*3][X]*=1000;//�ǂݍ��񂾒l��1000�{
		tile.hitu[J*3+1][X]=tile.hitu[J*3][X];
		tile.hitu[J*3+2][X]=tile.hitu[J*3][X];
		}
	}

	for(X=0;X<30;X++){//�ݒu���E�����l��
		bonus.unit_setp[X]=job[X].set_max;//1.5�{
		if(X<22)	bonus.unit_setp_max[X]=job[X].set_max*5;
		else		bonus.unit_setp_max[X]=1;
		if(bonus.unit_setp_max[X]>99)bonus.unit_setp_max[X]=99;
		if(X<22)bonus.unit_upp[X]=10;
		else	bonus.unit_upp[X]=2;
		tile.chance[X*3]=500;//100%
		tile.chance[X*3+1]=500;//100%
		if(X<22){//�w�����n�͋����m���O�X�^�[�g
		tile.chance[X*3+2]=500;//100%
		}
	}
	tile.hitu[90][0]=125000;tile.hitu[90][1]=125000;
	tile.hitu[91][2]=125000;tile.hitu[91][3]=125000;
	tile.hitu[92][0]=1000;tile.hitu[92][1]=1000;
	tile.hitu[92][2]=1000;tile.hitu[92][3]=1000;

	bonus.luck=100;//�f�ރ{�[�i�X��=100

	return;
}
void text_load(){
	//���������̓Ǎ�
	int X,J,C;
	//�t�@�C�����J��
	FILE *fp;
	errno_t err;

	if( (err = fopen_s( &fp,"File/data/unitinfo.txt" , "r" )) !=0 ){
		DxLib_End() ;//DX���C�u�����̎g�p�I��
		exit(1);//�v���O�����̏I��
	}

	for(X=0;X<30;X++){
	fgets(job[X].name, 59, fp);
	job[X].name[text_check(job[X].name)]=' ';
		for(J=0;J<3;J++){
		fgets(job[X].info[J], 59, fp);
		job[X].info[J][text_check(job[X].info[J])]=' ';
		}
	}
	fclose(fp);

	if( (err = fopen_s( &fp,"File/data/stageinfo.txt" , "r" )) !=0 ){
		DxLib_End() ;//DX���C�u�����̎g�p�I��
		exit(1);//�v���O�����̏I��
	}

	for(X=0;X<20;X++){
	fgets(stage[X].name, 59, fp);
	stage[X].name[text_check(stage[X].name)]=' ';
	fgets(stage[X].info, 59, fp);
	stage[X].info[text_check(stage[X].info)]=' ';
	}
	fclose(fp);

	if( (err = fopen_s( &fp,"File/data/sikikaninfo.txt" , "r" )) !=0 ){
		DxLib_End() ;//DX���C�u�����̎g�p�I��
		exit(1);//�v���O�����̏I��
	}

	for(X=0;X<8;X++){
	fgets(sikikan[X].name, 59, fp);
	sikikan[X].name[text_check(sikikan[X].name)]=' ';
		for(J=0;J<6;J++){
		fgets(sikikan[X].info[J], 59, fp);
		sikikan[X].info[J][text_check(sikikan[X].info[J])]=' ';
		}
	}
	fclose(fp);

	if( (err = fopen_s( &fp,"File/data/enemyinfo.txt" , "r" )) !=0 ){
		DxLib_End() ;//DX���C�u�����̎g�p�I��
		exit(1);//�v���O�����̏I��
	}

	for(X=0;X<13;X++){
	fgets(syu[X].name, 59, fp);
	syu[X].name[text_check(syu[X].name)]=' ';
		for(J=0;J<2;J++){
		fgets(syu[X].info[J], 59, fp);
		syu[X].info[J][text_check(syu[X].info[J])]=' ';
		}
	}
	fclose(fp);

	if( (err = fopen_s( &fp,"File/data/helpinfo.txt" , "r" )) !=0 ){
		DxLib_End() ;//DX���C�u�����̎g�p�I��
		exit(1);//�v���O�����̏I��
	}

	for(X=0;X<30;X++){
	fgets(help[X].name, 59, fp);
	help[X].name[text_check(help[X].name)]=' ';
		for(J=0;J<16;J++){
		fgets(help[X].info[J], 59, fp);
		C=text_check(help[X].info[J]);
		help[X].info[J][C]=' '; 
			if(C==0)break;
		}
	}
	fclose(fp);

	return;
}
int  text_check(char TEX[60]){
	//���s��T��
	int C;
	for(C=0;C<59;C++){
		if(TEX[C]=='\n')break;
	}
	return C;
}
void sikikan_data(){
	//���R�f�[�^�̑ł�����
	//�}���E�X
	sikikan[0].job_set[0]=0;//����	012  5  
	sikikan[0].job_set[1]=1;//����	0 2 45  
	sikikan[0].job_set[2]=2;//����	0123    
	sikikan[0].job_set[3]=3;//����	0 23 5  
	sikikan[0].job_set[4]=4;//�|��	012   6 
	sikikan[0].job_set[5]=10;//�c��	01  45  
	sikikan[0].job_set[6]=5;//����	012    7
	sikikan[0].job_set[7]=6;//�m��	0  3 5 7
	sikikan[0].job_set[8]=7;//����	0 23  6 
	sikikan[0].job_set[9]=8;//�x�q	012  5  
	sikikan[0].job_set[10]=9;//����	0  3  67
	sikikan[0].job_set[11]=22;
	sikikan[0].brave_t=3000;//�K�E�Z��{��������
	sikikan[0].sell_sp=70;//���p���x
	sikikan[0].up_sp=100;//�A�b�v�O���[�h���x
	sikikan[0].sell_cost=80;//���������
	//�J�m��
	sikikan[1].job_set[0]=0;//����	012  5  
	sikikan[1].job_set[1]=2;//����	0123    
	sikikan[1].job_set[2]=4;//�|��	012   6 
	sikikan[1].job_set[3]=15;//�ˎ�	 1  45 7
	sikikan[1].job_set[4]=10;//�c��	01  45  
	sikikan[1].job_set[5]=21;//�E��	 123 5  
	sikikan[1].job_set[6]=5;//����	012    7
	sikikan[1].job_set[7]=16;//����	 1  4 67
	sikikan[1].job_set[8]=18;//�E��	 1  456 
	sikikan[1].job_set[9]=8;//�x�q	012  5  
	sikikan[1].job_set[10]=20;//���d	 1  4 67
	sikikan[1].job_set[11]=23;
	sikikan[1].brave_t=3000;//�K�E�Z��{��������
	sikikan[1].sell_sp=100;//���p���x
	sikikan[1].up_sp=70;//�A�b�v�O���[�h���x
	sikikan[1].sell_cost=60;//���������
	//�c���n�Q
	sikikan[2].job_set[0]=0;//����	012  5  
	sikikan[2].job_set[1]=1;//����	0 2 45  
	sikikan[2].job_set[2]=2;//����	0123    
	sikikan[2].job_set[3]=3;//����	0 23 5  
	sikikan[2].job_set[4]=4;//�|��	012   6 
	sikikan[2].job_set[5]=21;//�E��	 123 5  
	sikikan[2].job_set[6]=5;//����	012    7
	sikikan[2].job_set[7]=17;//�_��	  23  67
	sikikan[2].job_set[8]=7;//����	0 23  6 
	sikikan[2].job_set[9]=8;//�x�q	012  5 
	sikikan[2].job_set[10]=19;//�R�t	  234  7
	sikikan[2].job_set[11]=24;
	sikikan[2].brave_t=3000;//�K�E�Z��{��������
	sikikan[2].sell_sp=100;//���p���x
	sikikan[2].up_sp=100;//�A�b�v�O���[�h���x
	sikikan[2].sell_cost=60;//���������
	//�A�b�N�X
	sikikan[3].job_set[0]=11;//�b��	   34 67
	sikikan[3].job_set[1]=2;//����	0123    
	sikikan[3].job_set[2]=13;//�R�m	   3456 
	sikikan[3].job_set[3]=3;//����	0 23 5  
	sikikan[3].job_set[4]=14;//�啀	   34 67
	sikikan[3].job_set[5]=15;//�ˎ�	0  3 5 7
	sikikan[3].job_set[6]=21;//�E��	 123 5  
	sikikan[3].job_set[7]=17;//�_��	  23  67
	sikikan[3].job_set[8]=9;//����	0  3  67
	sikikan[3].job_set[9]=7;//����	0 23  6 
	sikikan[3].job_set[10]=19;//�R�t	  234  7
	sikikan[3].job_set[11]=25;
	sikikan[3].brave_t=3000;//�K�E�Z��{��������
	sikikan[3].sell_sp=100;//���p���x
	sikikan[3].up_sp=100;//�A�b�v�O���[�h���x
	sikikan[3].sell_cost=60;//���������
	//���q
	sikikan[4].job_set[0]=11;//�b��	   34 67
	sikikan[4].job_set[1]=1;//����	0 2 45  
	sikikan[4].job_set[2]=12;//����	    4567
	sikikan[4].job_set[3]=13;//�R�m	   3456 
	sikikan[4].job_set[4]=14;//�啀	   34 67
	sikikan[4].job_set[5]=10;//�c��	01  45  
	sikikan[4].job_set[6]=16;//����	 1  4 67
	sikikan[4].job_set[7]=6;//�ˎ�	 1  45 7
	sikikan[4].job_set[8]=18;//�E��	 1  456 
	sikikan[4].job_set[9]=19;//�R�t	  234  7
	sikikan[4].job_set[10]=20;//���d	 1  4 67
	sikikan[4].job_set[11]=26;
	sikikan[4].brave_t=3000;//�K�E�Z��{��������
	sikikan[4].sell_sp=100;//���p���x
	sikikan[4].up_sp=100;//�A�b�v�O���[�h���x
	sikikan[4].sell_cost=0;//���������
	//�~�\��
	sikikan[5].job_set[0]=0;//����	012  5
	sikikan[5].job_set[1]=1;//����	0 2 45
	sikikan[5].job_set[2]=12;//����	    4567
	sikikan[5].job_set[3]=13;//�R�m	   3456 
	sikikan[5].job_set[4]=3;//����	0 23 5
	sikikan[5].job_set[5]=15;//�ˎ�	 1  45 7
	sikikan[5].job_set[6]=21;//�E��	 123 5  
	sikikan[5].job_set[7]=17;//�_��	  23  67
	sikikan[5].job_set[8]=18;//�E��	 1  456
	sikikan[5].job_set[9]=8;//�x�q	012  5  
	sikikan[5].job_set[10]=20;//���d	 1  4 67
	sikikan[5].job_set[11]=27;
	sikikan[5].brave_t=3000;//�K�E�Z��{��������
	sikikan[5].sell_sp=90;//���p���x
	sikikan[5].up_sp=90;//�A�b�v�O���[�h���x
	sikikan[5].sell_cost=60;//���������
	//����
	sikikan[6].job_set[0]=11;//�b��	   34 67
	sikikan[6].job_set[1]=12;//����	    4567
	sikikan[6].job_set[2]=13;//�R�m	   3456 
	sikikan[6].job_set[3]=14;//�啀	   34 67
	sikikan[6].job_set[4]=4;//�|��	012   6 
	sikikan[6].job_set[5]=10;//�c��	01  45
	sikikan[6].job_set[6]=16;//����	 1  4 67
	sikikan[6].job_set[7]=6;//�m��	0  3 5 7
	sikikan[6].job_set[8]=7;//����	0 23  6 
	sikikan[6].job_set[9]=18;//�E��	 1  456 
	sikikan[6].job_set[10]=9;//����	0  3  67
	sikikan[6].job_set[11]=28;
	sikikan[6].brave_t=4500;//�K�E�Z��{��������
	sikikan[6].sell_sp=100;//���p���x
	sikikan[6].up_sp=100;//�A�b�v�O���[�h���x
	sikikan[6].sell_cost=60;//���������
	//�^�R�{�E�Y
	sikikan[7].job_set[0]=11;//�b��	   34 67
	sikikan[7].job_set[1]=12;//����	    4567
	sikikan[7].job_set[2]=14;//�啀	   34 67
	sikikan[7].job_set[3]=15;//�ˎ�	 1  45 7
	sikikan[7].job_set[4]=5;//����	012    7
	sikikan[7].job_set[5]=16;//����	 1  4 67
	sikikan[7].job_set[6]=6;//�m��	0  3 5 7
	sikikan[7].job_set[7]=17;//�_��	  23  67
	sikikan[7].job_set[8]=19;//�R�t	  234  7
	sikikan[7].job_set[9]=9;//����	0  3  67
	sikikan[7].job_set[10]=20;//���d	 1  4 67
	sikikan[7].job_set[11]=29;
	sikikan[7].brave_t=3000;//�K�E�Z��{��������
	sikikan[7].sell_sp=100;//���p���x
	sikikan[7].up_sp=10;//�A�b�v�O���[�h���x
	sikikan[7].sell_cost=60;//���������
	return;
}
void ene_data(){
	//�G���\�ō�
	syu[0].hp =50	;syu[0].spd	=40		;syu[0]	.money=15	;//�X���C���@ �U�R
	syu[1].hp =40	;syu[1].spd	=50		;syu[1]	.money=10	;//�S�u�����@ ���������U�R
	syu[2].hp =130	;syu[2].spd	=15		;syu[2]	.money=20	;//�I�[�K�@�@ �ᑬ�@������΂Ȃ�
	syu[3].hp =40	;syu[3].spd	=70		;syu[3]	.money=15	;//�R�{���h�@ ��g�o�A���
	syu[4].hp =30	;syu[4].spd	=120	;syu[4]	.money=15	;//�P�b�g�V�[ ����
	syu[5].hp =50	;syu[5].spd	=50		;syu[5]	.money=20	;//�V���[�}�� ����
	syu[6].hp =30	;syu[6].spd	=80		;syu[6]	.money=15	;//�X�P���g�� ������
	syu[7].hp =40	;syu[7].spd	=35		;syu[7]	.money=15	;//�C���v�@�@ ��s�@��
	syu[8].hp =90	;syu[8].spd	=25		;syu[8]	.money=20	;//�O���t�H�� ��s�@�x�@��g�o�Ŕ�s�𓾂�
	syu[9].hp =50	;syu[9].spd	=60		;syu[9]	.money=20	;//�P���x���X �X�e���X
	syu[10].hp=60	;syu[10].spd=20		;syu[10].money=20	;//�S�[�����@ �����h��
	syu[11].hp=80	;syu[11].spd=40		;syu[11].money=25	;//�h���S���@ ��h��A��Ԗ���
	syu[12].hp=30	;syu[12].spd=40		;syu[12].money=20	;//�L���O�X���C���A����
	return;
}
void nando_data(){

	//TRYAL
	nando[0].hp_hosei=100;
	nando[0].lv_hosei=100;
	nando[0].samon_boss=2;
	nando[0].samon_zako=16;
	nando[0].wave=24;

	nando[1].hp_hosei=125;
	nando[1].lv_hosei=110;
	nando[1].samon_boss=2;
	nando[1].samon_zako=20;
	nando[1].wave=49;

	nando[2].hp_hosei=150;
	nando[2].lv_hosei=120;
	nando[2].samon_boss=2;
	nando[2].samon_zako=24;
	nando[2].wave=69;

	nando[3].hp_hosei=175;
	nando[3].lv_hosei=130;
	nando[3].samon_boss=2;
	nando[3].samon_zako=28;
	nando[3].wave=84;

	nando[4].hp_hosei=200;
	nando[4].lv_hosei=140;
	nando[4].samon_boss=2;
	nando[4].samon_zako=32;
	nando[4].wave=99;

	nando[5].hp_hosei=250;
	nando[5].lv_hosei=150;
	nando[5].samon_boss=2;
	nando[5].samon_zako=44;
	nando[5].wave=129;
	//POWER
	nando[6].hp_hosei=120;
	nando[6].lv_hosei=110;
	nando[6].samon_boss=3;
	nando[6].samon_zako=24;
	nando[6].wave=29;

	nando[7].hp_hosei=130;
	nando[7].lv_hosei=125;
	nando[7].samon_boss=3;
	nando[7].samon_zako=24;
	nando[7].wave=54;

	nando[8].hp_hosei=140;
	nando[8].lv_hosei=140;
	nando[8].samon_boss=3;
	nando[8].samon_zako=24;
	nando[8].wave=79;

	nando[9].hp_hosei=200;
	nando[9].lv_hosei=160;
	nando[9].samon_boss=4;
	nando[9].samon_zako=32;
	nando[9].wave=119;

	nando[10].hp_hosei=300;
	nando[10].lv_hosei=180;
	nando[10].samon_boss=4;
	nando[10].samon_zako=32;
	nando[10].wave=299;

	nando[11].hp_hosei=500;
	nando[11].lv_hosei=200;
	nando[11].samon_boss=5;
	nando[11].samon_zako=40;
	nando[11].wave=999;
	return;
}
void option_data(){
	//�I�v�V�����f�[�^�̑ł�����
	option.key_set[0]=KEY_INPUT_A;
	option.key_set[1]=KEY_INPUT_B;
	option.key_set[2]=KEY_INPUT_C;
	option.key_set[3]=KEY_INPUT_D;
	option.key_set[4]=KEY_INPUT_E;
	option.key_set[5]=KEY_INPUT_F;
	option.key_set[6]=KEY_INPUT_G;
	option.key_set[7]=KEY_INPUT_H;
	option.key_set[8]=KEY_INPUT_I;
	option.key_set[9]=KEY_INPUT_J;
	option.key_set[10]=KEY_INPUT_K;
	option.key_set[11]=KEY_INPUT_L;
	option.key_set[12]=KEY_INPUT_M;
	option.key_set[13]=KEY_INPUT_N;
	option.key_set[14]=KEY_INPUT_O;
	option.key_set[15]=KEY_INPUT_P;
	option.key_set[16]=KEY_INPUT_Q;
	option.key_set[17]=KEY_INPUT_R;
	option.key_set[18]=KEY_INPUT_S;
	option.key_set[19]=KEY_INPUT_T;
	option.key_set[20]=KEY_INPUT_U;
	option.key_set[21]=KEY_INPUT_V;
	option.key_set[22]=KEY_INPUT_W;
	option.key_set[23]=KEY_INPUT_X;
	option.key_set[24]=KEY_INPUT_Y;
	option.key_set[25]=KEY_INPUT_Z;
	option.sc_key[0]=12;
	option.sc_key[1]=1;
	option.sc_key[2]=13;
	option.sc_key[3]=18;
	option.sc_key[4]=20;
	option.sc_key[5]=22;
	option.bgm_on=1;
	option.efe_on=1;
	option.grid_on=1;
	option.se_on=1;
	option.hp_on=1;
	return;
}
void data_save(){
	//�f�[�^�̕ۑ�
	int X,Y;
	//�t�@�C�����J��
	FILE *fp;
	errno_t err;

	if( (err = fopen_s( &fp,"File/save/save.dat" , "wb" )) !=0 ){
		DxLib_End() ;//DX���C�u�����̎g�p�I��
		exit(1);//�v���O�����̏I��
	}
	//�v���C���[�֘A
	fprintf_s(fp,"%d\n",bonus.luck);

	for(X=0;X<4;X++)
	fprintf_s(fp,"%d\n",award.sozai[X]);

	for(X=0;X<160;X++)
		fprintf_s(fp,"%d\n",award.kunsyou[X]);

	for(X=0;X<8;X++)
	fprintf_s(fp,"%d\n",award.sikikan_ok[X]);

	fprintf_s(fp,"%d\n",award.play_mode);

	for(X=0;X<20;X++)
	fprintf_s(fp,"%d\n",award.stage_ok[X]);

	for(X=0;X<30;X++)
	fprintf_s(fp,"%d\n",award.maxup_cnt[X]);

	for(X=0;X<30;X++)
	fprintf_s(fp,"%d\n",award.set_cnt[X]);

	for(X=0;X<15;X++)
	fprintf_s(fp,"%d\n",award.enemy_cnt[X]);

	for(X=0;X<15;X++)
	fprintf_s(fp,"%d\n",award.boss_cnt[X]);

	for(X=0;X<15;X++)
	fprintf_s(fp,"%d\n", award.enemy_maxlv[X]);

	for(X=0;X<8;X++)
	fprintf_s(fp,"%d\n", award.siki_siyou[X]);

	for(X=0;X<8;X++)
	fprintf_s(fp,"%d\n", award.siki_brave[X]);

	for(X=0;X<20;X++)
	fprintf_s(fp,"%d\n", award.stage_clear[X]);

	for(X=0;X<20;X++)
	fprintf_s(fp,"%d\n", award.stage_boss[X]);

	fprintf_s(fp,"%d\n", award.thi_score);
	fprintf_s(fp,"%d\n", award.tget_money);
	fprintf_s(fp,"%d\n", award.tget_sozai);
	fprintf_s(fp,"%d\n", award.tget_wave);
	fprintf_s(fp,"%d\n", award.tget_bonus);

	for(X=0;X<30;X++)
	fprintf_s(fp,"%d\n", bonus.unit_setp[X]);

	for(X=0;X<30;X++)
	fprintf_s(fp,"%d\n", bonus.unit_upp[X]);

	for(X=0;X<30;X++)
	fprintf_s(fp,"%d\n", bonus.unit_powp[X]);

	fprintf_s(fp,"%d\n", bonus.money_p);
	fprintf_s(fp,"%d\n", bonus.life_p);

	for(X=0;X<20;X++){
		for(Y=0;Y<16;Y++)
			fprintf_s(fp,"%d\n", stage[X].hi_score[Y/8][Y%8]);
		for(Y=0;Y<2;Y++)
			fprintf_s(fp,"%d\n", stage[X].best_score[Y]);
	}

	for(X=0;X<100;X++){
	fprintf_s(fp,"%d\n",tile.naka[X/10][X%10]);
	fprintf_s(fp,"%d\n",tile.ok[X/10][X%10]);
	fprintf_s(fp,"%d\n",tile.open[X/10][X%10]);
	}

	for(X=0;X<92;X++){
	fprintf_s(fp,"%d\n",tile.chance[X]);
	}

	for(X=0;X<6;X++){
		fprintf_s(fp,"%d\n",option.sc_key[X]);
	}

	fprintf_s(fp,"%d\n",option.efe_on);
	fprintf_s(fp,"%d\n",option.bgm_on);
	fprintf_s(fp,"%d\n",option.se_on);
	fprintf_s(fp,"%d\n",option.grid_on);
	fprintf_s(fp,"%d\n",option.hp_on);

	fprintf_s(fp,"%d\n",player.date);

	for(X=0;X<30;X++){
		fprintf_s(fp,"%d\n", award.help_ok[X]);
	}
	

	for(X=0;X<20;X++){
		for(Y=0;Y<2;Y++)
			fprintf_s(fp,"%d\n", stage[X].max_nando[Y]);
	}

	for(X=0;X<20;X++){
		for(Y=0;Y<16;Y++)
			fprintf_s(fp,"%d\n", stage[X].max_siki[Y/8][Y%8]);
	}

	fprintf_s(fp,"%d\n",award.version);

	fclose(fp);
	return;
}
void data_load(){
	//�f�[�^�̓Ǎ�
	int X,Y;
	//�t�@�C�����J��
	FILE *fp;
	errno_t err;

	if( (err = fopen_s( &fp,"File/save/save.dat" , "rb" )) !=0 ){
		return;//���^�[������
	}
	//�v���C���[�֘A
	fscanf_s(fp,"%d\n",&bonus.luck);

	for(X=0;X<4;X++)
	fscanf_s(fp,"%d\n",&award.sozai[X]);

	for(X=0;X<160;X++)
		fscanf_s(fp,"%d\n",&award.kunsyou[X]);

	for(X=0;X<8;X++)
	fscanf_s(fp,"%d\n",&award.sikikan_ok[X]);

	fscanf_s(fp,"%d\n",&award.play_mode);

	for(X=0;X<20;X++)
	fscanf_s(fp,"%d\n",&award.stage_ok[X]);

	for(X=0;X<30;X++)
	fscanf_s(fp,"%d\n",&award.maxup_cnt[X]);

	for(X=0;X<30;X++)
	fscanf_s(fp,"%d\n",&award.set_cnt[X]);

	for(X=0;X<15;X++)
	fscanf_s(fp,"%d\n",&award.enemy_cnt[X]);

	for(X=0;X<15;X++)
	fscanf_s(fp,"%d\n",&award.boss_cnt[X]);

	for(X=0;X<15;X++)
	fscanf_s(fp,"%d\n", &award.enemy_maxlv[X]);

	for(X=0;X<8;X++)
	fscanf_s(fp,"%d\n", &award.siki_siyou[X]);

	for(X=0;X<8;X++)
	fscanf_s(fp,"%d\n", &award.siki_brave[X]);

	for(X=0;X<20;X++)
	fscanf_s(fp,"%d\n", &award.stage_clear[X]);

	for(X=0;X<20;X++)
	fscanf_s(fp,"%d\n", &award.stage_boss[X]);

	fscanf_s(fp,"%d\n", &award.thi_score);
	fscanf_s(fp,"%d\n", &award.tget_money);
	fscanf_s(fp,"%d\n", &award.tget_sozai);
	fscanf_s(fp,"%d\n", &award.tget_wave);
	fscanf_s(fp,"%d\n", &award.tget_bonus);

	for(X=0;X<30;X++)
	fscanf_s(fp,"%d\n", &bonus.unit_setp[X]);

	for(X=0;X<30;X++)
	fscanf_s(fp,"%d\n", &bonus.unit_upp[X]);

	for(X=0;X<30;X++)
	fscanf_s(fp,"%d\n", &bonus.unit_powp[X]);

	fscanf_s(fp,"%d\n", &bonus.money_p);
	fscanf_s(fp,"%d\n", &bonus.life_p);

	for(X=0;X<20;X++){
		for(Y=0;Y<16;Y++)
			fscanf_s(fp,"%d\n", &stage[X].hi_score[Y/8][Y%8]);
		for(Y=0;Y<2;Y++)
			fscanf_s(fp,"%d\n", &stage[X].best_score[Y]);
	}

	for(X=0;X<100;X++){
	fscanf_s(fp,"%d\n",&tile.naka[X/10][X%10]);
	fscanf_s(fp,"%d\n",&tile.ok[X/10][X%10]);
	fscanf_s(fp,"%d\n",&tile.open[X/10][X%10]);
	}

	for(X=0;X<92;X++){
	fscanf_s(fp,"%d\n",&tile.chance[X]);
	}

	for(X=0;X<6;X++){
		fscanf_s(fp,"%d\n",&option.sc_key[X]);
	}

	fscanf_s(fp,"%d\n",&option.efe_on);
	fscanf_s(fp,"%d\n",&option.bgm_on);
	fscanf_s(fp,"%d\n",&option.se_on);
	fscanf_s(fp,"%d\n",&option.grid_on);
	fscanf_s(fp,"%d\n",&option.hp_on);

	fscanf_s(fp,"%d\n",&player.date);

	for(X=0;X<30;X++)
		fscanf_s(fp,"%d\n", &award.help_ok[X]);


	for(X=0;X<20;X++){
		for(Y=0;Y<2;Y++)
			fscanf_s(fp,"%d\n", &stage[X].max_nando[Y]);
	}

	for(X=0;X<20;X++){
		for(Y=0;Y<16;Y++)
			fscanf_s(fp,"%d\n", &stage[X].max_siki[Y/8][Y%8]);
	}

	fscanf_s(fp,"%d\n",&award.version);

	fclose(fp);
	return;
}

void replay_save(){
	//�f�[�^�̕ۑ�
	int X;
	//�t�@�C�����J��
	FILE *fp;
	errno_t err;
	
	char FILENAME[100];
	
	time_t T;
	struct tm T_ST;
	time(&T);

	localtime_s(&T_ST, &T);

	sprintf_s(FILENAME,100,"replay/%4d%2d%2d%2d%2d%2d.rep",
	T_ST.tm_year+1900,
	T_ST.tm_mon+1,
	T_ST.tm_mday,
	T_ST.tm_hour,
	T_ST.tm_min,
	T_ST.tm_sec
	);

	if(replay.aut==1){//�����ۑ�
	sprintf_s(FILENAME,100,"replay/auto.rep");
	}

	
	if( (err = fopen_s( &fp,FILENAME , "wb" )) !=0 ){
		DxLib_End() ;//DX���C�u�����̎g�p�I��
		exit(1);//�v���O�����̏I��
	}
	//�w�b�_���
	fprintf_s(fp,"%d\n", sys.stage_no);
	fprintf_s(fp,"%d\n", player.siki_no);
	fprintf_s(fp,"%d\n", sel.nando+sel.bonus*6);
	fprintf_s(fp,"%d\n", sys.p_time);
	fprintf_s(fp,"%d\n", player.score);
	fprintf_s(fp,"%d\n", replay.rand);
	//�{�[�i�X���
	for(X=0;X<30;X++)
	fprintf_s(fp,"%d\n", bonus.unit_setp[X]);

	for(X=0;X<30;X++)
	fprintf_s(fp,"%d\n", bonus.unit_upp[X]);

	for(X=0;X<30;X++)
	fprintf_s(fp,"%d\n", bonus.unit_powp[X]);

	fprintf_s(fp,"%d\n", bonus.money_p);
	fprintf_s(fp,"%d\n", bonus.life_p);
	//���v���C���e
	for(X=0;X<100000;X++){
		fprintf_s(fp,"%d\n", replay.sousa[X]);
		fprintf_s(fp,"%d\n", replay.select[X]);
		fprintf_s(fp,"%d\n", replay.count[X]);
		fprintf_s(fp,"%d\n", replay.iti[X]);
		if(X>=replay.no)break;
	}

	fclose(fp);
	return;
}
void replay_load(){
	//�f�[�^�̓Ǎ�
	int X;
	//�t�@�C�����J��
	FILE *fp;
	errno_t err;
	char FILENAME[100];

	sprintf_s(FILENAME,100,"replay/%s",replay.name[sel.file]);

	if(sys.tutorial_on==1){//�`���[�g���A���p
		sprintf_s(FILENAME,100,"File/data/demo.rep",replay.name[sel.file]);
	}

	if( (err = fopen_s( &fp,FILENAME , "rb" )) !=0 ){
		return;//���^�[������
	}
	//�w�b�_���
	fscanf_s(fp,"%d\n", &sys.stage_no);
	fscanf_s(fp,"%d\n", &player.siki_no);
	fscanf_s(fp,"%d\n", &sel.nando);
	sel.bonus=sel.nando/6;
	sel.nando=sel.nando%6;
	fscanf_s(fp,"%d\n", &X);//�g��Ȃ��f�[�^
	fscanf_s(fp,"%d\n", &X);
	fscanf_s(fp,"%d\n", &replay.rand);
	//�{�[�i�X���
	for(X=0;X<30;X++)
	fscanf_s(fp,"%d\n", &bonus.unit_setp[X]);

	for(X=0;X<30;X++)
	fscanf_s(fp,"%d\n", &bonus.unit_upp[X]);

	for(X=0;X<30;X++)
	fscanf_s(fp,"%d\n", &bonus.unit_powp[X]);

	fscanf_s(fp,"%d\n", &bonus.money_p);
	fscanf_s(fp,"%d\n", &bonus.life_p);
	//���v���C���e
	for(X=0;X<100000;X++){
		replay.count[X]=0;
		fscanf_s(fp,"%d\n", &replay.sousa[X]);
		fscanf_s(fp,"%d\n", &replay.select[X]);
		fscanf_s(fp,"%d\n", &replay.count[X]);
		fscanf_s(fp,"%d\n", &replay.iti[X]);
		if(replay.count[X]==0)break;
	}
	fclose(fp);
	return;
}
//�^�C�g���ƭ�
void title(){
	int S,T,WX,WY,EX,X,A;
	
	PlayMusic( "File/bgm/menu.mp3" , DX_PLAYTYPE_LOOP ) ;
	SetVolumeMusic(option.bgm_on*option.bgm_on*option.bgm_on*option.bgm_on ) ;

	for(S=0;S<50;S++){
		ChangeVolumeSoundMem( option.se_on*option.se_on*option.se_on*option.se_on, se.wav[S] ) ;
	}
	T=0;
	WX=680;WY=100;EX=542-600;
	while(inp.mou_LC==0 && inp.mou_RC==0){//��ʖ��邭
		T++;
		mouse_check();

		DrawBox(0,0,640,480,color.kuro,1);

		for(X=0;X<=T;X+=2){//�g���J��
			waku((20-X)*16,(15-X*13/18)*16,X*2,X*13/9,0,3);
			if(X==20)break;
		}

		if(T<150){//�G�������Ă��違�^�C�g�����X���C�h
			if(WX>80)WX-=4;
			if(EX<542)EX+=4;
		}else if(T<190){
			WX=75+randam(10);
			WY=95+randam(10);
		}else if(T<200){
			WX=80;
			WY=100+(T-190)*20;
		}else if(T>210){
			if(WY>100)WY-=2;
			if(T>300){
			for(X=0;X<=T-300;X++){//�g���J��
				waku((20-X)*16,(15-X/2)*16+80,X*2,X,0,3);
				if(X==6)break;
			}
			mes(270,300,"!click!",color.siro,color.hai,font.a);
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255-T*5%255 ) ;
			mes(270,300,"!click!",color.aka,color.hai,font.a);
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
			}
		}
			waku(WX,WY,30,8,0,1);
			mes(WX+10,WY+8,"Super Tower",color.siro,color.hai,font.a);
			mes(WX+10,WY+58,"Defence Wars",color.siro,color.hai,font.b);
	
	
			if(T<260){
				if(T/10%4==0)		A=9;
				else if(T/10%4==2)	A=11;
				else				A=10;
				if(T>150) A-=9;
				for(X=0;X<13;X++){
					if(T<200)		DrawRotaGraph( EX-X*36 , 400 , 2 , 0 , gf.ene[X][A] , TRUE ) ;
					else			DrawRotaGraph( EX-X*36 , 390 , 2 , 0 , gf.kill[(T-200)/12] , TRUE ) ;
				}
			}

		if(T==200)se_ok(0);

		if(T==300)se_ok(6);

		if(fps.sp_up==0){
			fps_check();
			ScreenFlip();
		}else{
			fps.sp_up=0;
		}
		err_c();//�G���[�`�F�b�N
	}

	for(X=0;X<=20;X+=2){//�g���J��
		waku((20-X)*16,(15-X*13/18)*16,X*2,X*13/9,0,3);
		ScreenFlip();
		err_c();
	}

	top_menu();
	return;
}
void top_menu(){

	int S,I,M;

	okodukai_check();

	if(award.version==0){//�o�[�W�����X�V����
		for(S=0;S<20;S++){
			for(M=0;M<2;M++){
				award.sozai[S%4]-=stage[S].hi_score[M][stage[S].best_score[M]];
				for(I=0;I<8;I++){
				award.sozai[S%4]+=stage[S].hi_score[M][I];
				}
			}
		}
	}

		award.version=106;

	for(S=0;S<4;S++){
		if(award.sozai[S]<0 || award.sozai[S]>2000000000)award.sozai[S]=2000000000;//�I�[�o�[�t���[�Ń}�C�i�X�Ȃ�Q�O��
	}

	if(award.help_ok[0]==1) help_gazou(0);

	while(1){
	mouse_check();
	sys.stage_no=0;
	//�w�i�`��
	waku(0,0,40,30,0,3);

	waku(2*16,8*16,16,21,0,3);
	mes(10,28,"Super Tower Defence Wars",color.siro,color.kuro,font.a);
	//�`��
	mes(90,140,"Play Game",color.siro,color.kuro,font.a);
	mes(90,180,"Bonus Tile",color.siro,color.kuro,font.a);
	mes(90,220,"History",color.siro,color.kuro,font.a);
	mes(90,260,"Replay",color.siro,color.kuro,font.a);
	mes(90,300,"Help",color.siro,color.kuro,font.a);
	mes(90,340,"Option",color.siro,color.kuro,font.a);
	mes(90,380,"Tutorial",color.siro,color.kuro,font.a);
	mes(90,420,"Exit",color.siro,color.kuro,font.a);	

	if(inp.mou_x>60 && inp.mou_x<280 && inp.mou_y>130){
		switch((inp.mou_y-130)/40){
		case 0:
			mes(90,140,"Play Game",color.aka,color.kuro,font.a);
			if(inp.mou_LC==1) stage_select();//�X�e�[�W�Z���N�g��ʂ�
		break;
		case 1:
			mes(90,180,"Bonus Tile",color.aka,color.kuro,font.a);
			if(inp.mou_LC==1) bonus_select();//�X�L���^�C���擾��ʂ�
		break;

		case 2:
			mes(90,220,"History",color.aka,color.kuro,font.a);
			if(inp.mou_LC==1) history_select();//������ʂ�
		break;

		case 3:
			mes(90,260,"Replay",color.aka,color.kuro,font.a);
			if(inp.mou_LC==1) replay_select();//������ʂ�
		break;

		case 4:
			mes(90,300,"Help",color.aka,color.kuro,font.a);
			if(inp.mou_LC==1) help_select();
		break;
	
		case 5:
			mes(90,340,"Option",color.aka,color.kuro,font.a);
			if(inp.mou_LC==1) option_select();
		break;

		case 6:
			mes(90,380,"Tutorial",color.aka,color.kuro,font.a);
			if(inp.mou_LC==1){
				if(award.help_ok[7]==1)help_gazou(7);
				sys.tutorial_on=1;
				data_save();
				replay_load();
				replay.ok=1;
				vs_main();
				sys.tutorial_on=0;
				data_load();
				replay.ok=0;
			}
		break;
		case 7:
			mes(90,420,"Exit",color.aka,color.kuro,font.a);
			if(inp.mou_LC==1){
				data_save();
				return;
			}
		break;
		}
	}


	ScreenFlip();
	err_c();//�G���[�`�F�b�N
	}
	return;
}
//�X�e�[�W�I�����
void stage_select(){//�X�e�[�W

	se_ok(6);
	if(award.help_ok[1]==1) help_gazou(1);
	while(1){
		mouse_check();
		stage_select_syori();
		stage_select_byouga();
		if(inp.mou_RC==1)break;//�߂�
		ScreenFlip();
		err_c();//
	}
	inp.mou_LC=0;
	se_ok(4);
	return;
}
void stage_select_syori(){
	sys.stage_no=sel.stage;

	if(inp.mou_LC==1 && inp.mou_y>400 && inp.mou_y<464 && inp.mou_x>32 && inp.mou_x<288){
		se_ok(6);
		replay.ok=0;
		replay.rand=randam(99999);//�����������p
		vs_main();//�X�^�[�g
	}


	if(inp.mou_y>76 && inp.mou_y<144 && inp.mou_x>50 && inp.mou_x<288){//�X�e�[�W�I��
		if(award.stage_ok[(inp.mou_x-50)/24+(inp.mou_y-76)/40*10]==1){//�o���ς�
		sys.stage_no=(inp.mou_x-50)/24+(inp.mou_y-76)/40*10;
		if(inp.mou_LC==1){
			sel.stage=sys.stage_no;
			se_ok(5);
			}
		}
	}

	if(inp.mou_y>195 && inp.mou_y<225 && inp.mou_LC==1){
		if(inp.mou_x>40 && inp.mou_x<60){
			sel.nando=(sel.nando+(award.play_mode-1))%award.play_mode;//���[�h�ύX
			se_ok(5);
		}
		if(inp.mou_x>170 && inp.mou_x<190){
			sel.nando=(sel.nando+1)%award.play_mode;
			se_ok(5);
		}
		if(inp.mou_x>195 && inp.mou_x<290){
			sel.bonus=(sel.bonus+1)%2;//�{�[�i�X�I���I�t
			se_ok(5);
		}
	}

	if(inp.mou_y>275 && inp.mou_y<371 && inp.mou_x>45 && inp.mou_x<290 && inp.mou_LC==1){//�w�����I��
		if(award.sikikan_ok[(inp.mou_x-45)/125*4+(inp.mou_y-275)/24]==1){
		player.siki_no=(inp.mou_x-45)/125*4+(inp.mou_y-275)/24;
		se_ok(5);
		}
	}

	return;
}
void stage_select_byouga(){
	int X,Y,U,S;
	//�w�i�`��
	waku(0,0,40,30,0,3);
	//����
	//�X�e�[�W�ԍ��̃��X�g/
	waku(2*16,3*16,17,7,0,3);
	mes(50,30,"Stage",color.siro,color.kuro,font.a);
	for(X=0;X<10;X++){
		for(Y=0;Y<2;Y++){
		if(award.stage_ok[X+Y*10]==0)continue;
		if(sel.stage==Y*10+X)SetDrawBright(255,0,0);
		DrawRotaGraph( 50+X*24+12,96+Y*36 , 1 , 0 , gf.icon[20+(X+Y*10)%5] , TRUE ) ;
		DrawRotaGraph( 50+X*24+19,96+Y*36+7 , 1 , 0 , gf.font[(X+1)%10+40] , TRUE ) ;
		DrawRotaGraph( 50+X*24+12,96+Y*36+7 , 1 , 0 , gf.font[(Y*10+X+1)/10+40] , TRUE ) ;

		if(sel.stage==Y*10+X)DrawBox(50+X*24,86+Y*36,72+X*24,108+Y*36,color.aka,0);
		SetDrawBright(255,255,255);
		}
	}
	//���[�h���X�g/2,11
	waku(2*16,11*16,17,4,0,3);
	mes(50,160,"Nannido",color.siro,color.kuro,font.a);

	if(sel.nando%6==0)		mes_bmf(80,215,"NORMAL",14,2);
	else if(sel.nando%6==1)	mes_bmf(80,215,"_HARD",14,2);
	else if(sel.nando%6==2)	mes_bmf(80,215,"MANIAC",14,2);
	else if(sel.nando%6==3)	mes_bmf(80,215,"_LUNA",14,2);
	else if(sel.nando%6==4)	mes_bmf(80,215,"_HELL",14,2);
	else					mes_bmf(80,215,"DMARCH",14,2);

	DrawRotaGraph( 50 , 213 , 1 , 0 , gf.icon[6] , TRUE ) ;
	DrawRotaGraph( 180 , 213 , 1 , 0 , gf.icon[7] , TRUE ) ;

	if(sel.bonus==0)	mes_bmf(200,215,"TRIAL",14,2);
	else				mes_bmf(200,215,"POWER",14,2);
	DrawRotaGraph( 282 , 213 , 1 , 0 , gf.icon[38+sel.bonus] , TRUE ) ;
	//�w����,2,16
	waku(2*16,16*16,17,8,0,3);
	mes(50,240,"Sikikan",color.siro,color.kuro,font.a);
	for(X=0;X<8;X++){//�w�����摜�ƃn�C�X�R�A
		if(award.sikikan_ok[X]==0)continue;
		if(X==player.siki_no)	S=2;
		else					S=1;
		DrawRotaGraph( 60+X/4*120 , 290+X%4*24 , S , 0 , gf.unit[22+X][1] , TRUE ) ;
		U=stage[sys.stage_no].hi_score[sel.bonus][X];
		for(Y=0;Y<stage[sys.stage_no].max_siki[sel.bonus][X];Y++){
		DrawRotaGraph( 80+X/4*120+Y%3*5 , 286+X%4*24+Y/3*8 , 1 , 0 , gf.font[39] , TRUE ) ;
		}
		suu_bmf(60+X/4*120+86 , 290+X%4*24,1,U,7,0);
	}
	//�n�߂�A�߂�
	waku(2*16,25*16,17,4,0,3);
	mes(130,415,"Start",color.siro,color.kuro,font.a);
	//��ʉE��
	//�}�b�v��
	waku(21*16,3*16,17,16,0,3);
	//�~�j�}�b�v
	for(X=2;X<28;X++){//�w�i�`��
		for(Y=2;Y<28;Y++){
			DrawRotaGraph( X*8+356 , Y*8+48 , 0.5 , 0 , gf.chip[stage[sys.stage_no].map_set[X][Y]] , TRUE ) ;
		}
	}
	mes(350,278,"Best Score",color.siro,color.kuro,font.s);
	DrawRotaGraph( 430 , 285 , 1 , 0 , gf.unit[22+stage[sys.stage_no].best_score[sel.bonus]][1] , TRUE ) ;
	U=stage[sys.stage_no].hi_score[sel.bonus][stage[sys.stage_no].best_score[sel.bonus]];
	suu_bmf( 570 , 285 , 2 , U , 14 , 0 ) ;
	//��������X�R�A
	waku(21*16,20*16,17,9,0,3);

	if(inp.mou_y>195 && inp.mou_y<225 && inp.mou_x>195 && inp.mou_x<290){
		mes(350,312,"�Q�[�����[�h",color.siro,color.kuro,font.a);
		mes(350,352,"TRIAL�F",color.siro,color.kuro,font.s);
		mes(350,366,"�ݒu����A�����������Փx�Ō��܂�",color.siro,color.kuro,font.s);
		mes(350,384,"�{�[�i�X�^�C���̌��ʂ��o�Ȃ����[�h",color.siro,color.kuro,font.s);
		mes(350,406,"POWER�F",color.siro,color.kuro,font.s);
		mes(350,420,"TRIAL���G��������",color.siro,color.kuro,font.s);
		mes(350,438,"�{�[�i�X�^�C���̌��ʂ��o�郂�[�h",color.siro,color.kuro,font.s);
	}else if(inp.mou_y>275 && inp.mou_y<371 && inp.mou_x>45 && inp.mou_x<290){//�w�����I��
		X=(inp.mou_x-45)/125*4+(inp.mou_y-275)/24;
		mes(350,312,sikikan[X].name,color.siro,color.kuro,font.a);
		for(Y=0;Y<6;Y++)mes(350,352+Y*18,sikikan[X].info[Y],color.siro,color.kuro,font.s);
		for(Y=0;Y<12;Y++)DrawRotaGraph( 360+Y*16 , 394 , 1 , 0 , gf.unit[sikikan[X].job_set[Y]][1] , TRUE ) ;
	}else{
		mes(350,312,stage[sys.stage_no].name,color.siro,color.kuro,font.a);
		mes(350,352,stage[sys.stage_no].info,color.siro,color.kuro,font.s);
		mes(350,380,"�U�R���F�@�@�@�@ ��",color.siro,color.kuro,font.s);
		suu_bmf(440,386,2,nando[sel.nando+sel.bonus*6].samon_zako,14,0);
		mes(480,380,"�{�X���F�@�@�@�@ ��",color.siro,color.kuro,font.s);
		suu_bmf(570,386,2,nando[sel.nando+sel.bonus*6].samon_boss,14,0);
		mes(350,398,"�G�g�o�F�@�@�@�@ ��",color.siro,color.kuro,font.s);
		suu_bmf(440,404,2,nando[sel.nando+sel.bonus*6].hp_hosei,14,0);
		mes(480,398,"�G�k�u�F�@�@�@�@ ��",color.siro,color.kuro,font.s);
		suu_bmf(570,404,2,nando[sel.nando+sel.bonus*6].lv_hosei,14,0);

		mes(350,416,"WAVE���F�@�@�@�@ �g",color.siro,color.kuro,font.s);
		suu_bmf(440,422,2,nando[sel.nando+sel.bonus*6].wave+1,14,0);

		mes(480,416,"�f�ށ@�F",color.siro,color.kuro,font.s);
		DrawRotaGraph( 560 , 422 , 1 , 0 , gf.icon[25+sys.stage_no%4] , TRUE ) ;

		DrawRotaGraph( 360 , 444 , 1 , 0 , gf.icon[38] , TRUE ) ;
		DrawRotaGraph( 490 , 444 , 1 , 0 , gf.icon[39] , TRUE ) ;

		for(X=0;X<2;X++){
			switch(stage[sys.stage_no].max_nando[X]){
			case 0:mes_bmf(380+X*130,445,"  NO   CLEAR",7,1);break;
			case 1:mes_bmf(380+X*130,445,"NORMAL CLEAR",7,1);break;
			case 2:mes_bmf(380+X*130,445," HARD  CLEAR",7,1);break;
			case 3:mes_bmf(380+X*130,445,"MANIAC CLEAR",7,1);break;
			case 4:mes_bmf(380+X*130,445," LUNA  CLEAR",7,1);break;
			case 5:mes_bmf(380+X*130,445," HELL  CLEAR",7,1);break;
			case 6:mes_bmf(380+X*130,445,"DMARCH CLEAR",7,1);break;
			}
		}
	}

	DrawBox(540,6,628,30,color.mido,0);

	mes_bmf(560,16,"BACK",14,2);
	mes_bmf(547,26,"RIGHT CLICK",7,1);
	return;
}
//�X�L���^�C���擾���
void bonus_select(){//�X�L���^�C�����
	int T=0;
	se_ok(6);
	if(award.help_ok[2]==1) help_gazou(2);
	while(1){
		mouse_check();
		bonus_open();//�{�[�i�X�l������A�V�^�C���쐬����
		if(inp.mou_RC==1)break;//�O��ʂɖ߂�
		if(inp.d_k[KEY_INPUT_SPACE]==1)T++;
		else T=0;
		if(inp.d_k[KEY_INPUT_SPACE]==0 || T<120 || T%100==0){
		bonus_byouga();
		ScreenFlip();
		}
		err_c();//�G���[�`�F�b�N
	}
	se_ok(4);
	return;
}
void bonus_byouga(){
	int X,Y,U,C,T;
	waku(0,0,40,30,0,3);
	waku(2*16,2*16,22,26,0,3);
	waku(26*16,2*16,12,26,0,3);
	mes(50,30,"Bonus Tile",color.siro,color.hai,font.a);
	mes(450,30,"Sozai",color.siro,color.hai,font.a);

	//���ɍ��ڕ\��//�E�ɔ�p�\��
	for(X=0;X<10;X++){
		for(Y=0;Y<10;Y++){
			if(tile.ok[X][Y]==0){//���J��
				DrawRotaGraph( X*32+64 , Y*32+128 , 2 , 0 , gf.icon[8] , TRUE ) ;
			}else if(tile.naka[X][Y]<90){//���j�b�g����
				DrawRotaGraph( X*32+64 , Y*32+128 , 2 , 0 , gf.unit[tile.naka[X][Y]/3][1] , TRUE ) ;
				if(tile.naka[X][Y]%3==0)		{C=GetColor(0,255,0);mes_bmf(X*32+56 , Y*32+120,"POW",7,1);}//���\
				else if(tile.naka[X][Y]%3==1)	{C=GetColor(0,0,255);mes_bmf(X*32+56 , Y*32+120,"SET",7,1);}//�z�u��
				else if(tile.naka[X][Y]%3==2)	{C=GetColor(255,0,0);mes_bmf(X*32+56 , Y*32+120,"UP",7,1);}//������
				DrawBox(X*32+49,Y*32+113,X*32+79,Y*32+143,C,0);
			}else{//��or���C�tor���Ȃ���
				DrawRotaGraph( X*32+64 , Y*32+128 , 2 , 0 , gf.icon[tile.naka[X][Y]-90+tile.naka[X][Y]/92] , TRUE ) ;
				DrawBox(X*32+49,Y*32+113,X*32+79,Y*32+143,GetColor(255,255,0),0);//��
			}
			if(tile.open[X][Y]==1)DrawRotaGraph( X*32+64 , Y*32+128 , 1.5 , 0 , gf.icon[9] , TRUE );//�J���ς�
		}
		//�^�C���`��
	}
	if(sel.no>=0) DrawBox(sel.no%10*32+48,sel.no/10*32+112,sel.no%10*32+80,sel.no/10*32+144,GetColor(0,255,255),0);//��

	//�f�ވꗗ�\��
	for(X=0;X<4;X++){
		DrawRotaGraph( 440,80+X*48 , 1 , 0 , gf.icon[25+X] , TRUE ) ;
		mes_bmf( 450,80+X*48,"X",8,1);
		U=award.sozai[X];
		if(player.sozai_hitu[X]>award.sozai[X])SetDrawBright(122,122,122);
		suu_bmf( 580,X*48+80 , 2 , U , 14 , 1 ) ;
		//����\��
		U=player.sozai_hitu[X];//�f�ޕK�v��
		if(U<=0)continue;
		SetDrawBright(255,0,0);
		suu_bmf( 580,X*48+96 , 2 , U , 14 , 1 ) ;
		SetDrawBright(255,255,255);
	}
	if(sel.no!=-1){//�������\��
		T=tile.naka[sel.no%10][sel.no/10];
		if(tile.open[sel.no%10][sel.no/10]==1)mes(480,360,"�I����ρI",color.siro,color.hai,font.s);
		if(T<90){
			mes(430,300,job[T/3].name,color.siro,color.hai,font.s);
			if(T%3==0)		{
				if(T<33)		mes(460,300,"��1%���炢�����Ȃ�",color.siro,color.hai,font.s);
				else if(T<66)	mes(460,300,"��1%���炢�����Ȃ�",color.siro,color.hai,font.s);
				else			mes(460,300,"��4%���炢�����Ȃ�",color.siro,color.hai,font.s);
				U=bonus.unit_powp[T/3];
			}else if(T%3==1){
				mes(460,300,"�̔z�u�񐔁{�P",color.siro,color.hai,font.s);
				U=bonus.unit_setp[T/3];
			}else {
				mes(460,300,"�̏��i�񐔁{�P",color.siro,color.hai,font.s);
				U=bonus.unit_upp[T/3];
			}
		}else if(T==90){//����
			mes(430,300,"���������{�[�i�X�{�T",color.siro,color.hai,font.s);
			U=bonus.money_p;
		}else if(T==91){//ײ�
			mes(430,300,"�������C�t�{�[�i�X�{�Q",color.siro,color.hai,font.s);
			U=bonus.life_p;
		}else if(T=92){
			mes(430,300,"�f�ރ{�[�i�X��+0.1�A�^�C���ω�",color.siro,color.hai,font.s);
			U=bonus.luck;
		}
		//���ݒl
		mes(430,330,"���ݒl",color.siro,color.hai,font.s);
		if(U>=0)suu_bmf(580,338,2,U,14,1);
	}

	DrawBox(540,6,628,30,color.mido,0);
	mes_bmf(560,16,"BACK",14,2);
	mes_bmf(547,26,"RIGHT CLICK",7,1);
	return;
}
void bonus_open(){
	int X,N;
	
	sel.no=(inp.mou_x-48)/32+(inp.mou_y-112)/32*10;

	if(inp.d_k[KEY_INPUT_SPACE]==1){//�X�y�[�X�Ń����_���߂���
		while(1){
		sel.no=randam(99);
		if(tile.open[sel.no%10][sel.no/10]==0 && tile.ok[sel.no%10][sel.no/10]==1)break;
		}
		inp.mou_LC=1;
	}

	if(inp.mou_x>48 && inp.mou_x<368 && inp.mou_y>112 && inp.mou_y<430 && tile.ok[sel.no%10][sel.no/10]==1){
		N=tile.naka[sel.no%10][sel.no/10];
		for(X=0;X<4;X++){//�K�v�f�ސ�
			player.sozai_hitu[X]=tile.hitu[N][X];
			if(N<90){
				if(N%3==0){
					if(bonus.unit_powp[N/3]<100)player.sozai_hitu[X]=int(player.sozai_hitu[X]*pow(1.02,bonus.unit_powp[N/3]));//�����n��1.02�擾����
					else						player.sozai_hitu[X]*=8;
				}
			if(N%3==1)player.sozai_hitu[X]=player.sozai_hitu[X]*bonus.unit_setp[N/3]/job[N/3].set_max/job[N/3].set_max;
			if(N%3==2){
				if(N>66)	player.sozai_hitu[X]=player.sozai_hitu[X]*bonus.unit_upp[N/3]/2;
				else		player.sozai_hitu[X]=player.sozai_hitu[X]*bonus.unit_upp[N/3]/50;
				}
			}else{
				if(N==90){
					if(bonus.money_p<15)	player.sozai_hitu[X]=int(player.sozai_hitu[X]*pow(2.0,bonus.money_p/5.0));
					else					player.sozai_hitu[X]*=8;
				}
				if(N==91){
					if(bonus.life_p<6)		player.sozai_hitu[X]=int(player.sozai_hitu[X]*pow(2.0,bonus.life_p/2.0));
					else					player.sozai_hitu[X]*=8;
				}
			}
			if(player.sozai_hitu[X]>999999)player.sozai_hitu[X]=1000000;
		}
		if(inp.mou_LC==1 && tile.open[sel.no%10][sel.no/10]==0 && tile.ok[sel.no%10][sel.no/10]==1 &&//�I�[�v����������
			award.sozai[0]>=player.sozai_hitu[0] && award.sozai[1]>=player.sozai_hitu[1] &&
			award.sozai[2]>=player.sozai_hitu[2] && award.sozai[3]>=player.sozai_hitu[3]){
			for(X=0;X<4;X++){//�f�ގx����
				award.sozai[X]-=player.sozai_hitu[X];
			}
			if(N==92){
				bonus.luck++;
				if(bonus.luck>10000)bonus.luck=10000;
			}else if(N==90){
				bonus.money_p+=5;//�����{�[�i�X
				if(bonus.money_p>10000)bonus.money_p=10000;
			}else if(N==91){
				bonus.life_p+=2;//ײ̃{�[�i�X
				if(bonus.life_p>4000)bonus.life_p=4000;
			}else if(N%3==0){
				bonus.unit_powp[N/3]++;
				if(bonus.unit_powp[N/3]>10000)bonus.unit_powp[N/3]=10000;
			}else if(N%3==1)bonus.unit_setp[N/3]++;
			else if(N%3==2)bonus.unit_upp[N/3]++;

			award.tget_bonus++;
			tile.open[sel.no%10][sel.no/10]=1;//�J��
			se_ok(2);
			if(sel.no%10 != 0)tile.ok[sel.no%10-1][sel.no/10]=1;
			if(sel.no%10 != 9)tile.ok[sel.no%10+1][sel.no/10]=1;
			if(sel.no/10 != 0)tile.ok[sel.no%10][sel.no/10-1]=1;
			if(sel.no/10 != 9)tile.ok[sel.no%10][sel.no/10+1]=1;

			if(N==92){
				tile_make();//�^�C����蒼��
			}
			if(inp.d_k[KEY_INPUT_SPACE]!=1 || N==92)data_save();//�f�[�^�̕ۑ�
		}
		if(tile.ok[sel.no%10][sel.no/10]==0)sel.no=-1;
	}else{
		for(X=0;X<4;X++)player.sozai_hitu[X]=0;
		sel.no=-1;
		N=-1;
	}
	return;
}
void tile_make(){
	int X,R,C,Y;
	int DETA[92];//�^�C�����o����
	for(X=0;X<92;X++)DETA[X]=0;

	for(X=0;X<100;X++){
		while(1){
		R=randam(91);
		C=randam(999);
			if(R<90){
				if(R%3==1 &&(bonus.unit_setp[R/3]+DETA[R]>=bonus.unit_setp_max[R/3]))continue;
				if(R%3==2 &&(bonus.unit_upp[R/3]+DETA[R]>=50 || (R>66 && bonus.unit_upp[R/3]+DETA[R]>=5 )))continue;
			}
			if(tile.chance[R]>C){
				tile.chance[R]-=20;//�o�������z�͊m������
				DETA[R]++;
				if(R>66 && (R%3!=0 || R==90))tile.chance[R]=-1;
				for(Y=0;Y<92;Y++){
					tile.chance[Y]++;
					if(tile.chance[Y]>1000)tile.chance[Y]=1000;
				}
			break;
			}
		}
		tile.naka[X%10][X/10]=R;
		tile.open[X%10][X/10]=0;
		tile.ok[X%10][X/10]=0;
	}
	//�S�ӏ��J��
	tile.ok[4][4]=1;
	tile.ok[4][5]=1;
	tile.ok[5][4]=1;
	tile.ok[5][5]=1;
	//�^�C�����Ȃ����z�u
	tile.naka[randam(9)][randam(9)]=92;
	return;
}
//�����m�F���
void history_select(){
	int G=0;
	se_ok(6);
	if(award.help_ok[3]==1) help_gazou(3);
	award_check();//�A���[�h�̊m�F
	//�A���[�h�m�F���
	while(1){
	mouse_check();
	sel.scroll-=inp.mou_h*15;
	if(inp.mou_LD==0)G=0;
	if(inp.mou_LC==1 && inp.mou_x>290 && inp.mou_x<350)G=1;
	if(G==1) sel.scroll=(inp.mou_y-60)*135/360;
	if(sel.scroll<0)sel.scroll=0;
	else if(sel.scroll>135)sel.scroll=135;
	history_byouga();
	ScreenFlip();
	err_c();//�G���[�`�F�b�N
	if(inp.mou_RC==1)break;
	}
	se_ok(4);
	return;
}
void history_byouga(){
	int X,Y,Z;
	waku(0,0,40,30,0,3);
	waku(2*16,2*16,18,26,0,3);
	waku(21*16,2*16,17,26,0,3);
	mes(50,30,"Award",color.siro,color.hai,font.a);
	mes(354,30,"BONUS",color.siro,color.hai,font.a);
	//�擾�A���[�h���X�g�\��
	for(Y=0;Y<25;Y++){
		Z=sel.scroll+Y;
		for(X=0;X<award.kunsyou[Z];X++){
		DrawRotaGraph( X*7+50 , Y*14+80 , 1 , 0 , gf.icon[30+X] , TRUE ) ;
		}
		if(Z<30){//���j�b�g�ŋ�����
		DrawRotaGraph( 102 , Y*14+80 , 1 , 0 , gf.unit[Z][1] , TRUE ) ;
		mes_bmf(119,Y*14+80,"MAX UP",7,1);
		suu_bmf(290,Y*14+80,1, award.maxup_cnt[Z] ,7,1);
		}else if(Z<60){//���j�b�g�z�u��
		DrawRotaGraph( 102 , Y*14+80 , 1 , 0 , gf.unit[Z-30][1] , TRUE ) ;
		mes_bmf(119,Y*14+80,"SET COUNT",7,1);
		suu_bmf(290,Y*14+80,1, award.set_cnt[Z-30] ,7,1);
		}else if(Z<73){//�G�����j
		DrawRotaGraph( 102 , Y*14+80 , 1 , 0 , gf.ene[Z-60][1] , TRUE ) ;
		mes_bmf(119,Y*14+80,"KILL COUNT",7,1);
		suu_bmf(290,Y*14+80,1, award.enemy_cnt[Z-60] ,7,1);
		}else if(Z<86){//�{�X���j
		DrawRotaGraph( 102 , Y*14+80 , 1 , 0 , gf.ene[Z-73][1] , TRUE ) ;
		mes_bmf(119,Y*14+80,"KILL BOSS",7,1);
		suu_bmf(290,Y*14+80,1, award.boss_cnt[Z-73] ,7,1);
		}else if(Z<99){//�ō��{�X���j�k�u
		DrawRotaGraph( 102 , Y*14+80 , 1 , 0 , gf.ene[Z-86][1] , TRUE ) ;
		mes_bmf(119,Y*14+80,"MAX BOSSLV",7,1);
		suu_bmf(290,Y*14+80,1, award.enemy_maxlv[Z-86] ,7,1);
		}else if(Z<107){//�N���A��
		DrawRotaGraph( 102 , Y*14+80 , 1 , 0 , gf.unit[Z-77][1] , TRUE ) ;
		mes_bmf(119,Y*14+80,"CLEAR",7,1);
		suu_bmf(290,Y*14+80,1, award.siki_siyou[Z-99] ,7,1);
		}else if(Z<115){//�u���C�u��
		DrawRotaGraph( 102 , Y*14+80 , 1 , 0 , gf.unit[Z-85][1] , TRUE ) ;
		mes_bmf(119,Y*14+80,"BRAVE",7,1);
		suu_bmf(290,Y*14+80,1, award.siki_brave[Z-107] ,7,1);
		}else if(Z<135){//�X�e�[�W�N���A��
		DrawRotaGraph( 102 , Y*14+80 , 0.5 , 0 , gf.icon[Z%5+20] , TRUE ) ;
		suu_bmf(104,Y*14+82,1, Z-114 ,7,1);
		mes_bmf(119,Y*14+80,"CLEAR",7,1);
		suu_bmf(290,Y*14+80,1, award.stage_clear[Z-115] ,7,1);
		}else if(Z<155){//�ō��{�X���j�k�u
		DrawRotaGraph( 102 , Y*14+80 , 0.5 , 0 , gf.icon[Z%5+20] , TRUE ) ;
		suu_bmf(104,Y*14+82,1, Z-134 ,7,1);
		mes_bmf(119,Y*14+80,"MAX BOSSLV",7,1);
		suu_bmf(290,Y*14+80,1, award.stage_boss[Z-135] ,7,1);
		}else if(Z==155){//���n�C�X�R�A
		mes_bmf(119,Y*14+80,"SOU HISCORE",7,1);
		suu_bmf(290,Y*14+80,1, award.thi_score ,7,1);
		}else if(Z==156){//�l������
		mes_bmf(119,Y*14+80,"SOU MONEY",7,1);
		suu_bmf(290,Y*14+80,1, award.tget_money ,7,1);
		}else if(Z==157){//�l���f��
		mes_bmf(119,Y*14+80,"SOU SOZAI",7,1);
		suu_bmf(290,Y*14+80,1, award.tget_sozai ,7,1);
		}else if(Z==158){//���v�`�u�d
		mes_bmf(119,Y*14+80,"SOU WAVE",7,1);
		suu_bmf(290,Y*14+80,1, award.tget_wave ,7,1);
		}else if(Z==159){//���{�[�i�X�^�C��
		mes_bmf(119,Y*14+80,"SOU TILE",7,1);
		suu_bmf(290,Y*14+80,1, award.tget_bonus ,7,1);
		}
	}
	//�{�[�i�X�擾���\��
	mes_bmf(377,68,"POW   SET  UP",7,1);
	mes_bmf(507,68,"POW   SET  UP",7,1);
	for(X=0;X<30;X++){//�e���j�b�g���\�A�z�u�A����
	if(X<22){Z=X/11;Y=X%11;}
	else{Z=X/26;Y=(X-22)%4+11;}
	DrawRotaGraph( 350+Z*130 , Y*16+80 , 1 , 0 , gf.unit[X][1] , TRUE ) ;
	suu_bmf(400+Z*130,Y*16+80,1, bonus.unit_powp[X] ,7,1);
	suu_bmf(430+Z*130,Y*16+80,1, bonus.unit_setp[X] ,7,1);
	suu_bmf(460+Z*130,Y*16+80,1, bonus.unit_upp[X] ,7,1);
	}
	mes_bmf(365,350,"MONEY BONUS",14,2);
	suu_bmf(580,350,2, bonus.money_p ,14,1);
	mes_bmf(365,386,"LIFE  BONUS",14,2);
	suu_bmf(580,386,2, bonus.life_p ,14,1);
	mes_bmf(365,422,"SOZAI BONUS",14,2);
	suu_bmf(570,422,2, bonus.luck/10 ,14,1);
	suu_bmf(582,424,1, bonus.luck%10 ,7,1);
	//�X�N���[���o�[�\��
	DrawBox(310,40,330,440,color.siro,0);
	DrawBox(312,42+sel.scroll*360/135,328,78+sel.scroll*360/135,color.siro,1);
	DrawBox(540,6,628,30,color.mido,0);
	mes_bmf(560,16,"BACK",14,2);
	mes_bmf(547,26,"RIGHT CLICK",7,1);
	return;
}
void award_check(){
	int X,Y;
	//�A���[�h�l���`�F�b�N
	for(X=0;X<30;X++){
		Y=award.maxup_cnt[X];
		if(award.kunsyou[X]==0 && Y>=(job[X].set_max+1)/2){award.kunsyou[X]=1;bonus.luck++;}
		if(award.kunsyou[X]==1 && Y>=job[X].set_max*2){award.kunsyou[X]=2;bonus.luck++;}
		if(award.kunsyou[X]==2 && Y>=job[X].set_max*10){award.kunsyou[X]=3;bonus.luck+=2;}
		if(award.kunsyou[X]==3 && Y>=job[X].set_max*25){award.kunsyou[X]=4;bonus.luck+=2;}
		if(award.kunsyou[X]==4 && Y>=job[X].set_max*50){award.kunsyou[X]=5;bonus.luck+=4;}
		Y=award.set_cnt[X];
		if(award.kunsyou[X+30]==0 && Y>=job[X].set_max*5){award.kunsyou[X+30]=1;bonus.luck++;}
		if(award.kunsyou[X+30]==1 && Y>=job[X].set_max*20){award.kunsyou[X+30]=2;bonus.luck++;}
		if(award.kunsyou[X+30]==2 && Y>=job[X].set_max*100){award.kunsyou[X+30]=3;bonus.luck+=2;}
		if(award.kunsyou[X+30]==3 && Y>=job[X].set_max*250){award.kunsyou[X+30]=4;bonus.luck+=2;}
		if(award.kunsyou[X+30]==4 && Y>=job[X].set_max*500){award.kunsyou[X+30]=5;bonus.luck+=4;}
	}
	for(X=0;X<13;X++){
		Y=award.enemy_cnt[X];
		if(award.kunsyou[X+60]==0 && Y>=1000){award.kunsyou[X+60]=1;bonus.luck++;}
		if(award.kunsyou[X+60]==1 && Y>=5000){award.kunsyou[X+60]=2;bonus.luck++;}
		if(award.kunsyou[X+60]==2 && Y>=25000){award.kunsyou[X+60]=3;bonus.luck+=2;}
		if(award.kunsyou[X+60]==3 && Y>=70000){award.kunsyou[X+60]=4;bonus.luck+=2;}
		if(award.kunsyou[X+60]==4 && Y>=150000){award.kunsyou[X+60]=5;bonus.luck+=4;}
		Y=award.boss_cnt[X];
		if(award.kunsyou[X+73]==0 && Y>=10){award.kunsyou[X+73]=1;bonus.luck++;}
		if(award.kunsyou[X+73]==1 && Y>=50){award.kunsyou[X+73]=2;bonus.luck++;}
		if(award.kunsyou[X+73]==2 && Y>=250){award.kunsyou[X+73]=3;bonus.luck+=2;}
		if(award.kunsyou[X+73]==3 && Y>=1000){award.kunsyou[X+73]=4;bonus.luck+=2;}
		if(award.kunsyou[X+73]==4 && Y>=3000){award.kunsyou[X+73]=5;bonus.luck+=4;}
		Y=award.enemy_maxlv[X];
		if(award.kunsyou[X+86]==0 && Y>=10){award.kunsyou[X+86]=1;bonus.luck++;}
		if(award.kunsyou[X+86]==1 && Y>=40){award.kunsyou[X+86]=2;bonus.luck++;}
		if(award.kunsyou[X+86]==2 && Y>=90){award.kunsyou[X+86]=3;bonus.luck+=2;}
		if(award.kunsyou[X+86]==3 && Y>=160){award.kunsyou[X+86]=4;bonus.luck+=2;}
		if(award.kunsyou[X+86]==4 && Y>=250){award.kunsyou[X+86]=5;bonus.luck+=4;}
	}
	for(X=0;X<8;X++){
		Y=award.siki_siyou[X];
		if(award.kunsyou[X+99]==0 && Y>=10){award.kunsyou[X+99]=1;bonus.luck++;}
		if(award.kunsyou[X+99]==1 && Y>=25){award.kunsyou[X+99]=2;bonus.luck++;}
		if(award.kunsyou[X+99]==2 && Y>=50){award.kunsyou[X+99]=3;bonus.luck+=2;}
		if(award.kunsyou[X+99]==3 && Y>=100){award.kunsyou[X+99]=4;bonus.luck+=2;}
		if(award.kunsyou[X+99]==4 && Y>=200){award.kunsyou[X+99]=5;bonus.luck+=4;}
		Y=award.siki_brave[X];
		if(award.kunsyou[X+107]==0 && Y>=15){award.kunsyou[X+107]=1;bonus.luck++;}
		if(award.kunsyou[X+107]==1 && Y>=40){award.kunsyou[X+107]=2;bonus.luck++;}
		if(award.kunsyou[X+107]==2 && Y>=75){award.kunsyou[X+107]=3;bonus.luck+=2;}
		if(award.kunsyou[X+107]==3 && Y>=150){award.kunsyou[X+107]=4;bonus.luck+=2;}
		if(award.kunsyou[X+107]==4 && Y>=300){award.kunsyou[X+107]=5;bonus.luck+=4;}
	}

	for(X=0;X<20;X++){
		Y=award.stage_clear[X];
		if(award.kunsyou[X+115]==0 && Y>=2){award.kunsyou[X+115]=1;bonus.luck++;}
		if(award.kunsyou[X+115]==1 && Y>=10){award.kunsyou[X+115]=2;bonus.luck++;}
		if(award.kunsyou[X+115]==2 && Y>=25){award.kunsyou[X+115]=3;bonus.luck+=2;}
		if(award.kunsyou[X+115]==3 && Y>=50){award.kunsyou[X+115]=4;bonus.luck+=2;}
		if(award.kunsyou[X+115]==4 && Y>=100){award.kunsyou[X+115]=5;bonus.luck+=4;}
		Y=award.stage_boss[X];
		if(award.kunsyou[X+135]==0 && Y>=25){award.kunsyou[X+135]=1;bonus.luck++;}
		if(award.kunsyou[X+135]==1 && Y>=50){award.kunsyou[X+135]=2;bonus.luck++;}
		if(award.kunsyou[X+135]==2 && Y>=100){award.kunsyou[X+135]=3;bonus.luck+=2;}
		if(award.kunsyou[X+135]==3 && Y>=200){award.kunsyou[X+135]=4;bonus.luck+=2;}
		if(award.kunsyou[X+135]==4 && Y>=300){award.kunsyou[X+135]=5;bonus.luck+=4;}
	}
		if(award.thi_score<0)award.thi_score=2000000000;
		Y=award.thi_score;
		if(award.kunsyou[155]==0 && Y>=1000000){award.kunsyou[155]=1;bonus.luck++;}
		if(award.kunsyou[155]==1 && Y>=5000000){award.kunsyou[155]=2;bonus.luck++;}
		if(award.kunsyou[155]==2 && Y>=25000000){award.kunsyou[155]=3;bonus.luck+=2;}
		if(award.kunsyou[155]==3 && Y>=10000000){award.kunsyou[155]=4;bonus.luck+=2;}
		if(award.kunsyou[155]==4 && Y>=50000000){award.kunsyou[155]=5;bonus.luck+=4;}
		Y=award.tget_money;
		if(award.tget_money<0)award.tget_money=2000000000;
		if(award.kunsyou[156]==0 && Y>=10000){award.kunsyou[156]=1;bonus.luck++;}
		if(award.kunsyou[156]==1 && Y>=50000){award.kunsyou[156]=2;bonus.luck++;}
		if(award.kunsyou[156]==2 && Y>=250000){award.kunsyou[156]=3;bonus.luck+=2;}
		if(award.kunsyou[156]==3 && Y>=1000000){award.kunsyou[156]=4;bonus.luck+=2;}
		if(award.kunsyou[156]==4 && Y>=5000000){award.kunsyou[156]=5;bonus.luck+=4;}
		Y=award.tget_sozai;
		if(award.tget_sozai<0)award.tget_sozai=2000000000;
		if(award.kunsyou[157]==0 && Y>=1000000){award.kunsyou[157]=1;bonus.luck++;}
		if(award.kunsyou[157]==1 && Y>=5000000){award.kunsyou[157]=2;bonus.luck++;}
		if(award.kunsyou[157]==2 && Y>=25000000){award.kunsyou[157]=3;bonus.luck+=2;}
		if(award.kunsyou[157]==3 && Y>=100000000){award.kunsyou[157]=4;bonus.luck+=2;}
		if(award.kunsyou[157]==4 && Y>=500000000){award.kunsyou[157]=5;bonus.luck+=4;}
		Y=award.tget_wave;
		if(award.kunsyou[158]==0 && Y>=1000){award.kunsyou[158]=1;bonus.luck++;}
		if(award.kunsyou[158]==1 && Y>=5000){award.kunsyou[158]=2;bonus.luck++;}
		if(award.kunsyou[158]==2 && Y>=25000){award.kunsyou[158]=3;bonus.luck+=2;}
		if(award.kunsyou[158]==3 && Y>=100000){award.kunsyou[158]=4;bonus.luck+=2;}
		if(award.kunsyou[158]==4 && Y>=500000){award.kunsyou[158]=5;bonus.luck+=4;}
		Y=award.tget_bonus;
		if(award.kunsyou[159]==0 && Y>=50){award.kunsyou[159]=1;bonus.luck++;}
		if(award.kunsyou[159]==1 && Y>=250){award.kunsyou[159]=2;bonus.luck++;}
		if(award.kunsyou[159]==2 && Y>=1000){award.kunsyou[159]=3;bonus.luck+=2;}
		if(award.kunsyou[159]==3 && Y>=3000){award.kunsyou[159]=4;bonus.luck+=2;}
		if(award.kunsyou[159]==4 && Y>=10000){award.kunsyou[159]=5;bonus.luck+=4;}

		if(bonus.luck>10000)bonus.luck=10000;

	return;
}
//���v���C�I�����
void replay_select(){
	se_ok(6);
	if(award.help_ok[4]==1) help_gazou(4);
	int G=0;
	sel.file=0;
	replay_kensaku();
	while(1){
	mouse_check();
	sel.scroll-=inp.mou_h*15;
	if(inp.mou_LD==0)G=0;
	if(inp.mou_LC==1 && inp.mou_x>290 && inp.mou_x<350)G=1;
	if(G==1) sel.scroll=(inp.mou_y-180*15/replay.kazu)*(replay.kazu-15)/(400-360*15/replay.kazu);//�o�[�̒���;
	if(sel.scroll>replay.kazu-15)sel.scroll=(replay.kazu-15);
	if(sel.scroll<0)sel.scroll=0;
	//���v���C�̑I��
	sel.no=sel.file;
	if(inp.mou_x>50 && inp.mou_x<280 && inp.mou_y>62 && inp.mou_y<435 && sel.scroll+(inp.mou_y-62)/25<replay.kazu){
		sel.no=sel.scroll+(inp.mou_y-62)/25;
		if(inp.mou_LC==1){
			sel.file=sel.no;//�t�@�C���I��
			se_ok(5);
		}
	}
	if(inp.mou_RC==1)break;
	if(inp.mou_LC==1 && inp.mou_x>368 && inp.mou_x<576 && inp.mou_y>58 && inp.mou_y<266 && replay.kazu>0){
		se_ok(6);
		data_save();
		replay_load();
		replay.ok=1;
		vs_main();
		data_load();
		replay.ok=0;
		sel.no=0;
		sel.nando=0;
		}
	replay_byouga();
	ScreenFlip();
	err_c();//�G���[�`�F�b�N
	}

	se_ok(4);
	return;
}
void replay_byouga(){
	int X,Y,L;
	waku(0,0,40,30,0,3);
	waku(2*16,2*16,16,26,0,3);
	waku(20*16,2*16,18,26,0,3);
	mes(50,30,"Replay",color.siro,color.hai,font.a);
	mes(350,30,"Info",color.siro,color.hai,font.a);
	//���v���C���X�g
	for(X=0;X<15;X++){
	if(X+sel.scroll==sel.file)	DrawString(60,62+25*X,replay.name[X+sel.scroll],color.aka);
	else if(X+sel.scroll==sel.no)	DrawString(60,62+25*X,replay.name[X+sel.scroll],color.mido);
	else						DrawString(60,62+25*X,replay.name[X+sel.scroll],color.siro);
	}
	//���v���C���e
	if(replay.kazu>0){
		//�~�j�}�b�v
		for(X=2;X<28;X++){//�w�i�`��
			for(Y=2;Y<28;Y++){
				DrawRotaGraph( X*8+356 , Y*8+48 , 0.5 , 0 , gf.chip[stage[replay.stage[sel.no]].map_set[X][Y]] , TRUE ) ;
			}
		}
		mes_bmf(356,290,"STAGE",14,2);
		suu_bmf(580,290,2,replay.stage[sel.no]+1,14,1);
		mes_bmf(356,315,"SIKIKAN",14,2);
		DrawRotaGraph( 580 , 315 , 1 , 0 , gf.unit[22+replay.sikikan[sel.no]][1] , TRUE ) ;
		mes_bmf(356,340,"SCORE",14,2);
		suu_bmf(580,340,2,replay.score[sel.no],14,1);
		mes_bmf(356,365,"NANNIDO",14,2);
		if(replay.mode[sel.no]%6==0)		mes_bmf(500,365,"NORMAL",14,2);
		else if(replay.mode[sel.no]%6==1)	mes_bmf(500,365,"_HARD",14,2);
		else if(replay.mode[sel.no]%6==2)	mes_bmf(500,365,"MANIAC",14,2);
		else if(replay.mode[sel.no]%6==3)	mes_bmf(500,365,"_LUNA",14,2);
		else if(replay.mode[sel.no]%6==4)	mes_bmf(500,365,"_HELL",14,2);
		else					mes_bmf(500,365,"DMARCH",14,2);
		mes_bmf(356,390,"MODE",14,2);
		if(replay.mode[sel.no]/6==0)	mes_bmf(500,390,"TRIAL",14,2);
		else			mes_bmf(500,390,"POWER",14,2);
		DrawRotaGraph( 580 , 390 , 1 , 0 , gf.icon[38+replay.mode[sel.no]/6] , TRUE ) ;

		mes_bmf(356,415,"TIME",14,2);
		suu_bmf(580,415,2,replay.time[sel.no]/60%60,14,1);
		suu_bmf(540,415,2,replay.time[sel.no]/3600%60,14,1);
		suu_bmf(500,415,2,replay.time[sel.no]/216000,14,1);
		if(inp.mou_x>368 && inp.mou_x<576 && inp.mou_y>58 && inp.mou_y<266)	mes(420,140,"START",color.aka,color.kuro,font.a);
		else																mes(420,140,"START",color.siro,color.kuro,font.a);
	}else{
			mes(400,140,"NO DATA",color.siro,color.kuro,font.a);
	}
	//�X�N���[���o�[�\��
	if(replay.kazu>15){
	L=360*15/replay.kazu;//�o�[�̒���
	DrawBox(290,40,310,440,color.siro,0);
	DrawBox(292,42+sel.scroll*(400-L)/(replay.kazu-15),308,38+L+sel.scroll*(400-L)/(replay.kazu-15),color.siro,1);
	}
	DrawBox(540,6,628,30,color.mido,0);
	mes_bmf(560,16,"BACK",14,2);
	mes_bmf(547,26,"RIGHT CLICK",7,1);
	return;
}
void replay_kensaku(){
	//���v���C�t�@�C���̌����ƃw�b�_�̓Ǎ�
	FILE *fp;
	errno_t err;
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	char FILENAME[100];
	/* �ŏ��̃t�@�C������ */
	hFind = FindFirstFile("replay/*.rep", &fd);

	replay.kazu=0;

	if(hFind == INVALID_HANDLE_VALUE){//�t�@�C������
		return;
	}

	do {

		strcpy_s(replay.name[replay.kazu],fd.cFileName);//�t�@�C����
		strcpy_s(FILENAME,"replay/");
		strcat_s(FILENAME,fd.cFileName);
		sprintf_s(FILENAME,100,"replay/%s",
		fd.cFileName
		);

		//�w�b�_�̓Ǎ�
		if( (err = fopen_s( &fp, FILENAME , "rb" )) !=0 ){
			return;
		}
		fscanf_s(fp,"%d\n", &replay.stage[replay.kazu]);
		fscanf_s(fp,"%d\n", &replay.sikikan[replay.kazu]);
		fscanf_s(fp,"%d\n", &replay.mode[replay.kazu]);
		fscanf_s(fp,"%d\n", &replay.time[replay.kazu]);
		fscanf_s(fp,"%d\n", &replay.score[replay.kazu]);
		fclose(fp);
		replay.kazu++;
		if(replay.kazu>=100)break;
	} while(FindNextFile(hFind, &fd));

	/* �����I�� */
	FindClose(hFind);

	return;
}
//�w���v�I�����
void help_select(){
	se_ok(6);
	if(award.help_ok[5]==1) help_gazou(5);
	while(1){
	mouse_check();
	sel.no=-1;
	if(inp.mou_x>120 && inp.mou_x<530 && inp.mou_y>70 && inp.mou_y<440){
		sel.no=inp.mou_x/320*15+(inp.mou_y-70)/25;
	}
	help_byouga();
	ScreenFlip();
	err_c();
	if(inp.mou_RC==1)break;
	if(inp.mou_LC==1 && sel.no>=0 && award.help_ok[sel.no]>0)help_gazou(sel.no);
	}
	se_ok(4);
	return;
}
void help_byouga(){
	int X;
	waku(0,0,40,30,0,3);
	waku(2*16,2*16,36,26,0,3);
	mes(50,30,"Help",color.siro,color.hai,font.a);
	//�w���v���ڂ̕\��//2���ǂ͔�,1,���ǂ͊D�F,0�ǂ߂Ȃ��̂́H�H�H�H
	for(X=0;X<30;X++){
		suu_bmf(155+X/15*190,X%15*25+80,2,X+1,14,1);
		if(award.help_ok[X]>0){
		DrawString(172+X/15*190,X%15*25+72,help[X].name,color.kuro);
		if(sel.no==X)	DrawString(170+X/15*190,X%15*25+70,help[X].name,color.mido);
		else		DrawString(170+X/15*190,X%15*25+70,help[X].name,color.siro);
		}else{
		DrawString(172+X/15*190,X%15*25+72,"�H�H�H�H",color.kuro);
		if(sel.no==X)	DrawString(170+X/15*190,X%15*25+70,"�H�H�H�H",color.mido);
		else		DrawString(170+X/15*190,X%15*25+70,"�H�H�H�H",color.siro);
		}
	}
	DrawBox(540,6,628,30,color.mido,0);
	mes_bmf(560,16,"BACK",14,2);
	mes_bmf(547,26,"RIGHT CLICK",7,1);
	return;
}
void help_gazou(int H){
	int X;
		award.help_ok[H]=2;
		if(replay.ok==1)return;

	for(X=0;X<=18;X+=2){//�g���J��
		waku((20-X)*16,(15-X*13/18)*16,X*2,X*13/9,0,1);
		ScreenFlip();
		err_c();
	}
	//�^�C�g��
	mes(50,50,help[H].name,color.siro,color.kuro,font.a);
	//���ɉ摜(������)
	switch(H){
	case 10://���j�b�g���\
	mes_bmf(70,128,"LV",14,2);
	DrawRotaGraph( 75 , 148 , 1 , 0 , gf.icon[0] , TRUE ) ;
	DrawRotaGraph( 75 , 168 , 1 , 0 , gf.icon[10] , TRUE ) ;
	DrawRotaGraph( 75 , 188 , 1 , 0 , gf.icon[11] , TRUE ) ;
	SetDrawBright(255,255,0);DrawRotaGraph( 75 , 228 , 1 , 0 , gf.icon[14] , TRUE ) ;
	SetDrawBright(150,0,150);DrawRotaGraph( 75 , 248 , 1 , 0 , gf.icon[15] , TRUE ) ;
	SetDrawBright(122,255,122);DrawRotaGraph( 75 , 268 , 1 , 0 , gf.icon[16] , TRUE ) ;
	SetDrawBright(255,122,122);DrawRotaGraph( 75 , 288 , 1 , 0 , gf.icon[13] , TRUE ) ;
	SetDrawBright(255,0,0);DrawRotaGraph( 75 , 308 , 1 , 0 , gf.icon[18] , TRUE ) ;
	break;
	case 11://���j�b�g��P
		for(X=0;X<11;X++){
		DrawRotaGraph( 75 , 128+X*20 , 1 , 0 , gf.unit[X][1] , TRUE ) ;
		}
	break;
	case 12://���j�b�g��P
		for(X=0;X<11;X++){
		DrawRotaGraph( 75 , 128+X*20 , 1 , 0 , gf.unit[X+11][1] , TRUE ) ;
		}
	break;
	case 13://���j�b�g��P
		for(X=0;X<8;X++){
		DrawRotaGraph( 75 , 128+X*20 , 1 , 0 , gf.unit[X+22][1] , TRUE ) ;
		}
	break;
	case 15://���j�b�g��P
		mes_bmf(70,128,"LV",14,2);
		DrawRotaGraph( 75 , 148 , 1 , 0 , gf.icon[1] , TRUE ) ;
		DrawRotaGraph( 75 , 168 , 1 , 0 , gf.icon[2] , TRUE ) ;
		DrawRotaGraph( 75 , 188 , 1 , 0 , gf.icon[0] , TRUE ) ;
		DrawRotaGraph( 75 , 208 , 1 , 0 , gf.icon[4] , TRUE ) ;
		DrawRotaGraph( 75 , 228 , 1 , 0 , gf.icon[19] , TRUE ) ;
		DrawRotaGraph( 75 , 248 , 1 , 0 , gf.icon[5] , TRUE ) ;
	break;
	case 16://���j�b�g��P
		mes_bmf(190,108,"HP SP",14,2);
		for(X=0;X<13;X++){
		DrawRotaGraph( 75 , 128+X*20 , 1 , 0 , gf.ene[X][1] , TRUE ) ;
		suu_bmf(204,128+X*20,2,syu[X].hp,14,1);
		suu_bmf(240,128+X*20,2,syu[X].spd/5,14,1);
		}
	break;
	case 18://�n�`
		for(X=0;X<9;X++){
		DrawRotaGraph( 75 , 148+X*20 , 1 , 0 , gf.chip[X] , TRUE ) ;
		}
	break;
	case 19://�V�L�J��
		for(X=0;X<8;X++){
		DrawRotaGraph( 75 , 188+X*20 , 1 , 0 , gf.unit[X+22][1] , TRUE ) ;
		}
	break;
	}

	SetDrawBright(255,255,255);
	//�E�ɉ��
	for(X=0;X<16;X++){
		DrawString(70,120+X*20,help[H].info[X],color.siro);
	}
	ScreenFlip();
	
	while(1){//�N���b�N�܂őҋ@
		mouse_check();
		if(inp.mou_LC==1 || inp.mou_RC==1)break;
		err_c();
	}
	return;
}
//�I�v�V�������
void option_select(){
	se_ok(6);
	if(award.help_ok[6]==1) help_gazou(6);
	int S;
	//�ݒ�ύX
	while(1){
	mouse_check();
	option_byouga();
	ScreenFlip();
	err_c();//�G���[�`�F�b�N
	sel.no=(inp.mou_x-36)/46;
	if(inp.mou_LC==1){
		//�V���[�g�J�b�g�L�[
		if(inp.mou_y>145 && inp.mou_y<170 && inp.mou_x>36 && inp.mou_x<588){
		if(sel.no%2==0) option.sc_key[sel.no/2]--;
		else		 option.sc_key[sel.no/2]++;
		if(option.sc_key[sel.no/2]==26)		option.sc_key[sel.no/2]=0;
		else if(option.sc_key[sel.no/2]==-1)	option.sc_key[sel.no/2]=25;
		se_ok(5);
		}
		//�G�t�F�N�g�ق�
		if(inp.mou_y>180 && inp.mou_y<230 && inp.mou_x>290 && inp.mou_x<370){
			option.bgm_on=0;
			SetVolumeMusic(option.bgm_on*option.bgm_on*option.bgm_on*option.bgm_on ) ;
			se_ok(5);
		}
		if(inp.mou_y>230 && inp.mou_y<280 && inp.mou_x>290 && inp.mou_x<370){
			option.se_on=0;
			for(S=0;S<50;S++){
			ChangeVolumeSoundMem( 0, se.wav[S] ) ;
			}
		}
		if(inp.mou_y>280 && inp.mou_y<330 && inp.mou_x>290 && inp.mou_x<370){
			option.efe_on=0;
			se_ok(5);
		}
		if(inp.mou_y>330 && inp.mou_y<380 && inp.mou_x>290 && inp.mou_x<370){
			option.grid_on=0;
			se_ok(5);
		}
		if(inp.mou_y>380 && inp.mou_y<430 && inp.mou_x>290 && inp.mou_x<370){
			option.hp_on=0;
			se_ok(5);
		}
		if(inp.mou_y>180 && inp.mou_y<230 && inp.mou_x>390 && inp.mou_x<590){
			option.bgm_on=(inp.mou_x-340)/50;
			SetVolumeMusic( option.bgm_on*option.bgm_on*option.bgm_on*option.bgm_on ) ;
			se_ok(5);
		}
		if(inp.mou_y>230 && inp.mou_y<280 && inp.mou_x>390 && inp.mou_x<590){
			option.se_on=(inp.mou_x-340)/50;
			for(S=0;S<50;S++){
			ChangeVolumeSoundMem( option.se_on*option.se_on*option.se_on*option.se_on, se.wav[S] ) ;
			}
			se_ok(0);
		}
		if(inp.mou_y>280 && inp.mou_y<330 && inp.mou_x>430 && inp.mou_x<510){
			option.efe_on=1;
			se_ok(5);
		}
		if(inp.mou_y>330 && inp.mou_y<380 && inp.mou_x>430 && inp.mou_x<510){
			option.grid_on=1;
			se_ok(5);
		}
		if(inp.mou_y>380 && inp.mou_y<430 && inp.mou_x>430 && inp.mou_x<510){
			option.hp_on=1;
			se_ok(5);
		}
	}
	if(inp.mou_RC==1)break;
	}
	se_ok(4);
	return;
}
void option_byouga(){
	int I,IRO[5];
	for(I=0;I<5;I++){
		IRO[I]=color.siro;
	}
	waku(0,0,40,30,0,3);
	waku(2*16,2*16,36,26,0,3);
	mes(50,30,"Option",color.siro,color.hai,font.a);
	mes(50,80,"�V���[�g�J�b�g",color.siro,color.hai,font.a);
	mes_bmf(66,130,"MENU",14,2);
	mes_bmf(144,130,"BRAVE",14,2);
	mes_bmf(250,130,"NEXT",14,2);
	mes_bmf(340,130,"SELL",14,2);
	mes_bmf(444,130,"UP",14,2);
	mes_bmf(520,130,"WORK",14,2);
	for(I=0;I<6;I++){
		DrawRotaGraph( 80+I*92 , 160 , 3 , 0 , gf.font[option.sc_key[I]+10] , TRUE ) ;
		DrawRotaGraph( 50+I*92 , 160 , 1 , 0 , gf.icon[6] , TRUE ) ;
		DrawRotaGraph( 110+I*92 , 160 , 1 , 0 , gf.icon[7] , TRUE ) ;
	}
	mes(50,190,"�a�f�l",color.siro,color.hai,font.a);
	IRO[option.bgm_on]=color.aka;
	mes(300,190,"OFF",IRO[0],color.hai,font.a);
	mes(400,190,"1",IRO[1],color.hai,font.a);
	mes(450,190,"2",IRO[2],color.hai,font.a);
	mes(500,190,"3",IRO[3],color.hai,font.a);
	mes(550,190,"4",IRO[4],color.hai,font.a);
	IRO[option.bgm_on]=color.siro;
	IRO[option.se_on]=color.aka;
	mes(50,240,"���ʉ�",color.siro,color.hai,font.a);
	mes(300,240,"OFF",IRO[0],color.hai,font.a);
	mes(400,240,"1",IRO[1],color.hai,font.a);
	mes(450,240,"2",IRO[2],color.hai,font.a);
	mes(500,240,"3",IRO[3],color.hai,font.a);
	mes(550,240,"4",IRO[4],color.hai,font.a);
	IRO[option.se_on]=color.siro;
	IRO[option.efe_on]=color.aka;
	mes(50,290,"�G�t�F�N�g",color.siro,color.hai,font.a);
	mes(300,290,"OFF",IRO[0],color.hai,font.a);
	mes(450,290,"ON",IRO[1],color.hai,font.a);
	IRO[option.efe_on]=color.siro;
	IRO[option.grid_on]=color.aka;
	mes(50,340,"�O���b�h",color.siro,color.hai,font.a);
	mes(300,340,"OFF",IRO[0],color.hai,font.a);
	mes(450,340,"ON",IRO[1],color.hai,font.a);
	IRO[option.grid_on]=color.siro;
	IRO[option.hp_on]=color.aka;
	mes(50,390,"�g�o�\��",color.siro,color.hai,font.a);
	mes(300,390,"OFF",IRO[0],color.hai,font.a);
	mes(450,390,"ON",IRO[1],color.hai,font.a);
	DrawBox(540,6,628,30,color.mido,0);
	mes_bmf(560,16,"BACK",14,2);
	mes_bmf(547,26,"RIGHT CLICK",7,1);
	return;
}
//���퓬���C���֐�������//
void vs_syokika(){//�퓬���̏�����
	int X,Y;

	sys.e_cnt=0;
	sys.u_cnt=0;
	sys.s_cnt=0;
	sys.debug[0]=0;
	sys.debug[1]=0;
	sys.debug[2]=0;

	unit_load();//���j�b�g�f�[�^�Ǎ������R�␳�̔��f

	sel.x=-1;sel.y=-1;
	for(X=0;X<30;X++)
		for(Y=0;Y<30;Y++){
		sys.ene_on[X][Y]=0;
		map.ok[X][Y]=0;//�ݒu�\�t���O
		map.kyori[X][Y]=0;//�S�[���܂ł̋���
		map.kabe[X][Y]=0;//�ǂ̗L��
		map.goal[X][Y]=0;//�S�[���t���O
		if(stage[sys.stage_no].map_set[X][Y]==2){map.kabe[X][Y]=1;}//�R
		if(stage[sys.stage_no].map_set[X][Y]==4){map.goal[X][Y]=1;}//���
		if(stage[sys.stage_no].map_set[X][Y]==5){map.goal[X][Y]=2;}//��
	}
	set_check();
	map_f=map_c;
	for(X=0;X<30;X++)
		for(Y=0;Y<30;Y++){
		map.ok[X][Y]=0;//�ݒu�\�t���O
		map.kyori[X][Y]=0;//�S�[���܂ł̋���
		map.kabe[X][Y]=0;//�ǂ̗L��
		map.goal[X][Y]=0;//�S�[���t���O
		//���n
		if(stage[sys.stage_no].map_set[X][Y]==1){map.kabe[X][Y]=1;}//�X
		if(stage[sys.stage_no].map_set[X][Y]==2){map.kabe[X][Y]=1;map.ok[X][Y]=1;}//�R
		if(stage[sys.stage_no].map_set[X][Y]==3){map.ok[X][Y]=1;}//��
		if(stage[sys.stage_no].map_set[X][Y]==4){map.ok[X][Y]=1;map.goal[X][Y]=1;}//���
		if(stage[sys.stage_no].map_set[X][Y]==5){map.ok[X][Y]=1;map.goal[X][Y]=2;}//��
		if(stage[sys.stage_no].map_set[X][Y]==8){map.kabe[X][Y]=1;map.ok[X][Y]=1;}//�C
		if(stage[sys.stage_no].map_set[X][Y]==9){map.kabe[X][Y]=1;map.ok[X][Y]=1;}//�\
	}
	set_check();
	map=map_c;

	if(player.siki_no==2)	player.money=60;
	else					player.money=50;
	if(player.siki_no==3)	player.life=24;
	else					player.life=20;
	sys.p_time=0;
	sys.w_no=-1;//������ޖڂ�
	sys.w_time=-1;

	sys.m_mode=0;//���j���[���J���Ȃ�
	sel.no=-1;
	
	
	player.brave_rate=5;//�E�C
	player.brave_point=0;
	player.brave_time=0;
	player.brave_long=sikikan[player.siki_no].brave_t;
	player.brave=0;

	player.sell_s=sikikan[player.siki_no].sell_sp;//
	player.up_s=sikikan[player.siki_no].up_sp;
	player.sell_rate=sikikan[player.siki_no].sell_cost;
	player.score=0;
	player.point=0;
	//�{�[�i�X�̌v�Z
	for(X=0;X<30;X++){
		if(sel.bonus==1){
		job[X].up_rest=bonus.unit_upp[X];
		job[X].set_rest=bonus.unit_setp[X];
		}else{
		job[X].up_rest=sel.nando*8+10;
		job[X].set_rest=job[X].set_max*(2+sel.nando)/2;
		if(X>21){
			job[X].set_rest=1;
			job[X].up_rest=5;
			}
		}
		if(player.siki_no==0)job[X].set_rest=job[X].set_rest*6/5;
		if(player.siki_no==0 || player.siki_no==7)job[X].up_rest=job[X].up_rest*6/5;
		if(job[X].set_rest>100)job[X].set_rest=99;
	}
	if(sel.bonus==1)bonus_hosei();

	replay.no=0;

	fps.time=GetNowCount();
	fps.count=0;
	fps.now=60;
	fps.rest=0;
	fps.tyousei=0.0;
	if(sys.game_sp==2 && replay.ok==1)sys.game_sp=4;
	if(sys.game_sp==8 && replay.ok==1)sys.game_sp=64;

	sys.tu_px=240;
	sys.tu_py=240;
	sys.tu_x=240;
	sys.tu_y=240;

	for(X=0;X<100;X++){
		bom_efe[X].time=0;
		beam_efe[X].time=0;
		kill_efe[X].t=0;
	}

	return;
}
void bonus_hosei(){
	int J,L,SP;
	for(J=0;J<30;J++){
		if(J<11)	 SP=1;
		else if(J<22)SP=1;
		else		 SP=4;
		for(L=0;L<6;L++){
		job[J].atk[L]=int(double(job[J].atk[L])*double(100+SP*bonus.unit_powp[J])/100);
		job[J].ren[L]=int(double(job[J].ren[L])*double(300+SP*bonus.unit_powp[J])/300);
		job[J].han[L]=int(double(job[J].han[L])*double(300+SP*bonus.unit_powp[J])/300);
		job[J].stn[L]=int(double(job[J].stn[L])*double(300+SP*bonus.unit_powp[J])/300);
		job[J].poi[L]=int(double(job[J].poi[L])*double(300+SP*bonus.unit_powp[J])/300);
		job[J].bom[L]=int(double(job[J].bom[L])*double(300+SP*bonus.unit_powp[J])/300);
		job[J].chr[L]=int(double(job[J].chr[L])*double(300+SP*bonus.unit_powp[J])/300);
		if(job[J].han[L]>300) job[J].han[L]=300;
		if(job[J].bom[L]>150) job[J].bom[L]=150;
		}
	}
	player.money+=bonus.money_p;//���������{�[�i�X
	player.life+=bonus.life_p;//�������C�t�{�[�i�X
	return;
}
void vs_main(){//�퓬���[�h���C��
	PlayMusic( "File/bgm/sentou.mp3" , DX_PLAYTYPE_LOOP ) ;
	SetVolumeMusic(option.bgm_on*option.bgm_on*option.bgm_on*option.bgm_on ) ;
	vs_syokika();
	while(1){
		mouse_check();//����`�F�b�N
		if(sys.m_mode==0){//�ʏ펞
		sys.p_time++;
		vs_sousa();
		replay_syori();
		vs_sousa_jikkou();
		srand((replay.rand+sys.p_time)%10000);//����������
		player_syori();
		wave_syori();
		unit_syori();
		shot_syori();
		ene_syori();
		hit_hantei();
		sien_check();
		gameover_syori();
			if(sys.p_time%(sys.game_sp)==0 || (sys.w_no==-1 && replay.ok==0)){//�Q�[���X�s�[�h�ω�
				if(fps.sp_up<=0){	
				byouga_syori();
				fps_check();
				ScreenFlip();
				if(award.help_ok[8]==1) help_gazou(8);
				if(award.help_ok[9]==1) help_gazou(9);
				}else{
				fps.sp_up--;
				}
			}
		}else if(sys.m_mode==1){//�|�[�Y
			vs_menu();
			byouga_syori();
			menu_byouga();
			fps.time=GetNowCount();
			ScreenFlip();
		}
		if(sys.m_mode>1)break;//�I��or��蒼��
		err_c();
	}
	if(sys.m_mode==3)vs_main();//��蒼��

	inp.mou_LC=0;
	PlayMusic( "File/bgm/menu.mp3" , DX_PLAYTYPE_LOOP ) ;
	SetVolumeMusic(option.bgm_on*option.bgm_on*option.bgm_on*option.bgm_on ) ;
	return;
}
void player_syori(){
	if(player.brave_time>0){
		player.brave_time_n--;
		player.brave_time=player.brave_time_n*100/player.brave_long;
		if(player.brave_time_n>0)player.brave_time++;
		player.brave_point=0;
		player.brave=0;
		if(player.brave_time_n==1){
			PlayMusic( "File/bgm/sentou.mp3" , DX_PLAYTYPE_LOOP ) ;
			SetVolumeMusic(option.bgm_on*option.bgm_on*option.bgm_on*option.bgm_on ) ;
		}
	}else{
		player.brave=player.brave_point/player.brave_rate;
		if(player.brave>100)player.brave=100;
	}

	if(award.help_ok[20]==1 && player.brave>=100) help_gazou(20);

	return;
}
void wave_syori(){
	int I,J,C,wave_kazu,wave_type,iti_sort[32];
	if(player.brave_time>0 && player.siki_no==1)return;//���~��
	if(sys.w_time>0)sys.w_time--;
	if(sys.w_time==0 && sys.w_no<nando[sel.nando+sel.bonus*6].wave){
	if(sys.e_cnt>9999-nando[sel.nando+sel.bonus*6].samon_zako*2)return;//�G����������ꍇ
	se_ok(11);
	award.tget_wave++;//��WAVE
	sys.w_no++;
	wave_type=stage[sys.stage_no].wave_type[sys.w_no%100];
	wave_kazu=nando[sel.nando+sel.bonus*6].samon_zako;
	if(wave_type>12){
		if(award.help_ok[17]==1) help_gazou(17);
		wave_kazu=nando[sel.nando+sel.bonus*6].samon_boss;
	}
	if(wave_type%15==1)wave_kazu*=2;
	//���҈ʒu�������_���ŕ��ёւ���
	for(I=0;I<32;I++){
		iti_sort[I]=-1;
	}
	for(I=0;I<stage[sys.stage_no].samon_no;I++){
		J=randam(stage[sys.stage_no].samon_no-I-1);
		for(C=0;J!=-1;C++){
			if(iti_sort[C]==-1)J--;
			if(J==-1)iti_sort[C]=stage[sys.stage_no].samon_iti[I];
		}
	}
	//�G�̔���
	for(I=0;I<wave_kazu;I++){
		ene_make(wave_type,iti_sort[I%stage[sys.stage_no].samon_no]%30,iti_sort[I%stage[sys.stage_no].samon_no]/30,(sys.w_no+1)*nando[sel.nando+sel.bonus*6].lv_hosei/100,-I*stage[sys.stage_no].samon_time-1);
		}
	sys.w_time=stage[sys.stage_no].wave_sp;
	}
	if(sys.w_no==nando[sel.nando+sel.bonus*6].wave)sys.w_time=stage[sys.stage_no].wave_sp;//�I��
	
	return;
}
void unit_syori(){//�ˌ�����
	int U;
	for(U=0;U<sys.u_cnt;U++){
		if(unit[U].tame>=0){
			unit[U].tame+=unit[U].ren;
			if(player.brave_time>0 && player.siki_no==5)unit[U].tame+=unit[U].ren;//�u���C�u���{��
		}else{
			unit[U].tame++;
			if(sys.w_no==-1 || (player.brave_time>0 && player.siki_no==0))unit[U].tame=-1;
		}
		if(unit[U].tame>=6000){
			shot_hantei(U);
			if(unit[U].tame>6000)unit[U].tame=6000;
		}
		if(unit[U].tame==-1){//���por����
			if(unit[U].sell==1){
				sell_unit(U);//���p
				se_ok(3);
			}else{
				up_unit(U);//����
				se_ok(7);
			}
		}
	}
	return;
}
void shot_syori(){
	int S,sdel=0;
	for(S=0;S<sys.s_cnt;S++){
		shot[S].time++;
		if(shot[S].time<0)continue;
		switch(shot[S].type){
			case 0:
			case 1:
			case 2:
			case 4:
			case 7:
			case 8:
			case 11:
			case 12:
			case 15:
			case 18:
			case 19:
			case 23:
			case 24:
			sdel+=shot_move_n(S);//�ʏ풼�i
			break;
			case 6:
			case 9:
			case 17:
			case 20:
			case 25:
			case 28:
			case 29:
			sdel+=shot_move_s(S);//����or�͈�
			break;
			case 13:
			case 26:
			sdel+=shot_move_r(S);//����
			break;
			case 16:
			case 27:
			sdel+=shot_move_hm(S);//�z�[�~���O�~�T�C��
			break;
			//���̑�
			case 3:sdel+=shot_move03(S);break;
			case 5:sdel+=shot_move05(S);break;
			case 10:sdel+=shot_move10(S);break;
			case 14:sdel+=shot_move14(S);break;
			case 21:sdel+=shot_move21(S);break;
			case 22:sdel+=shot_move22(S);break;
		}
	}
	if(sdel>0)sort_shot(sdel);

	return;
}

void ene_syori(){//�ړ�����
	int E,spd,sibou=0,C,R,B;
	for(E=0;E<sys.e_cnt;E++){//�o��҂�
		if(ene[E].time<0){
			if(player.brave_time>0 && player.siki_no==1) continue;
			if(ene[E].time==-1)ene[E].time=0;
			else{ene[E].time++;continue;}
		}
		if(ene[E].type==8 && ene[E].hp<ene[E].hp_max/2)ene[E].fly=1;//�O���t�H��
		spd=ene[E].spd;
		ene[E].ani++;
		if(ene[E].heal>0 && sys.p_time%60==0 && ene[E].poi<=0){//������
			ene[E].hp+=ene[E].heal;
			if(ene[E].hp>ene[E].hp_max)ene[E].hp=ene[E].hp_max;
		}
		//�ŁA��ე���
		if(ene[E].stan>0){spd=0;ene[E].stan--;}//���
		if(ene[E].muteki>0){ene[E].muteki--;spd/=4;};//��������x�ቺ
		if(ene[E].poi>0){
			if(player.siki_no==6)spd/=3;//���
			else				 spd/=2;
			ene[E].poi--;
		}//��
		if(ene[E].fly==0){
			if(stage[sys.stage_no].map_set[ene[E].x/16][ene[E].y/16]==7)spd/=2;//��
			if(stage[sys.stage_no].map_set[ene[E].x/16][ene[E].y/16]==6)spd*=2;//�����}�X
		}
		//���`����
		if(player.brave_time>0){
			if(player.siki_no==1){
				spd=0;//�J�m�����`�A�U����[���h���C�h�X�i�C�s���O
				ene[E].hx=0;
				ene[E].hy=0;
			}
			if(player.siki_no==6 && ene[E].poi>0){//�łŒ��x���Ȃ�
				spd/=3;
				ene[E].hp-=ene[E].lv/8*(1+ene[E].boss*3);//���x���ɉ�����
			}
		}
		//�����͂ݏo������
		ene_move(E);
		if(ene[E].fly==0)ene_kabe(E);
		switch (ene[E].muki){
		case 0:ene[E].nai_x-=spd*7;ene[E].nai_y-=spd*7;ene[E].time+=spd*7;break;
		case 1:					   ene[E].nai_y-=spd*10;ene[E].time+=spd*10;break;
		case 2:ene[E].nai_x+=spd*7;ene[E].nai_y-=spd*7;ene[E].time+=spd*7;break;
		case 3:ene[E].nai_x-=spd*10;ene[E].time+=spd*10;break;
		case 4:break;
		case 5:ene[E].nai_x+=spd*10;ene[E].time+=spd*10;break;
		case 6:ene[E].nai_x-=spd*7;ene[E].nai_y+=spd*7;ene[E].time+=spd*7;break;
		case 7:					   ene[E].nai_y+=spd*10;ene[E].time+=spd*10;break;
		case 8:ene[E].nai_x+=spd*7;ene[E].nai_y+=spd*7;ene[E].time+=spd*7;break;
		}
		//�������
		ene[E].nai_x+=ene[E].hx/8;
		ene[E].nai_y+=ene[E].hy/8;
		if(ene[E].fly==0 && stage[sys.stage_no].map_set[ene[E].x/16][ene[E].y/16]==7){
			ene[E].hx=ene[E].hx*3/4;
			ene[E].hy=ene[E].hy*3/4;
		}else if(ene[E].fly==0 && stage[sys.stage_no].map_set[ene[E].x/16][ene[E].y/16]==6){
			ene[E].hx=ene[E].hx*15/16;
			ene[E].hy=ene[E].hy*15/16;
		}else{
			ene[E].hx=ene[E].hx*7/8;
			ene[E].hy=ene[E].hy*7/8;
		}

		ene[E].x=ene[E].nai_x/10000;
		ene[E].y=ene[E].nai_y/10000;
		//�S�[������
		if((map.goal[ene[E].x/16][ene[E].y/16]>1 || ene[E].x<16 || ene[E].x>464 || ene[E].y<16 || ene[E].y>464 ) && ene[E].hp>0){
			se_ok(9);
			if(sel.no-1000==E)sel.no=-1;
			if(player.life>0)player.life--;
			if(replay.ok==1 && replay.count[replay.no]!=0 && player.life<=0)player.life=1;//���ȂȂ�
			ene[E].hp=0;
			player.brave_point+=player.brave_rate*5;
			sibou++;
		}else if(ene[E].hp<=0){//���S����
			se_ok(1-ene[E].boss);
			if(sel.no-1000==E)sel.no=-1;
			ene[E].hp=0;
			player.money+=ene[E].money;
			award.tget_money+=ene[E].money;
			player.score+=ene[E].money*10;
			player.brave_point+=ene[E].money;
			award.sozai[randam(3)]+=5+ene[E].boss*95;
			award.tget_sozai+=1+ene[E].boss*19;
			award.enemy_cnt[ene[E].type]++;
			if(ene[E].boss==1){
				award.boss_cnt[ene[E].type]++;
				if(ene[E].lv>award.enemy_maxlv[ene[E].type])award.enemy_maxlv[ene[E].type]=ene[E].lv;
				if(ene[E].lv>award.stage_boss[sys.stage_no])award.stage_boss[sys.stage_no]=ene[E].lv;
			}
			for(B=0;B<100;B++){
				if(kill_efe[B].t<=0){
				kill_efe[B].x=ene[E].x;
				kill_efe[B].y=ene[E].y;
				kill_efe[B].t=40;
				kill_efe[B].s=ene[E].boss+1;
				break;
				}
			}
			sibou++;
			if(ene[E].type==12 && map.kabe[ene[E].x/16][ene[E].y/16]!=1 && sys.e_cnt<9995){//����X���C��
				for(C=0;C<4;C++){//���͂�4�̃X���C��
					ene_make(ene[E].boss*15,(ene[E].x/16),(ene[E].y/16),ene[E].lv,0);
					ene[sys.e_cnt-1].money=0;
					ene[sys.e_cnt-1].hp_max/=4;
					ene[sys.e_cnt-1].hp/=4;
					ene[sys.e_cnt-1].stan=120;
					R=randam(1000);
					ene[sys.e_cnt-1].hx=int(cos(double(R))*480000);
					ene[sys.e_cnt-1].hy=int(sin(double(R))*480000);
				}
			}
		}
		//���Ҕ���//
		if(ene[E].type==5 && randam(960)<=ene[E].boss*15 && map.kabe[ene[E].x/16][ene[E].y/16]!=1 && sys.e_cnt<9999 && ene[E].hp>ene[E].lv*3 && ene[E].stan<=0){
			if(player.brave_time>0 && player.siki_no==1) continue;//���Ԏ~�߂�
			ene_make(6,ene[E].x/16,ene[E].y/16,ene[E].lv,-1);//����
			ene[sys.e_cnt-1].money=0;
			ene[sys.e_cnt-1].hp_max/=4;
			ene[sys.e_cnt-1].hp/=4;
			ene[sys.e_cnt-1].stan=120;
			ene[sys.e_cnt-1].heal/=4;
			R=randam(1000);
			ene[sys.e_cnt-1].hx=int(cos(double(R))*320000);
			ene[sys.e_cnt-1].hy=int(sin(double(R))*320000);
			ene[E].hp-=ene[E].lv*3;
		}
	}
	sort_ene(sibou);
	return;
}
void ene_move(int E){
	if(ene[E].mx*16+24<=ene[E].x || ene[E].mx*16-8>=ene[E].x || 
		ene[E].my*16+24<=ene[E].y || ene[E].my*16-8>=ene[E].y ){
		ene[E].mx=ene[E].x/16;
		ene[E].my=ene[E].y/16;
	}

	if(ene[E].fly==1){
		if(stage[sys.stage_no].fly_mode==0 || ene[E].type!=7)ene[E].muki=map_f.muki[ene[E].mx][ene[E].my];//���i���[�h�ł͖����ꍇ
	}else{
		ene[E].m_muki=map.muki[ene[E].mx][ene[E].my];
		ene[E].muki=ene[E].m_muki;
	}

	return;
}
void ene_kabe(int E){
	//�͂ݏo������
	int kabe[9]={0,0,0,0,0,0,0,0,0};//�ǔ���p
	int hit[9]={0,0,0,0,0,0,0,0,0};//�Փ˔���p
	int XHIT=0,YHIT=0;//���W�C���p

	if(map.kyori[ene[E].x/16-1][ene[E].y/16-1]==-1)kabe[0]=1;
	if(map.kyori[ene[E].x/16+0][ene[E].y/16-1]==-1)kabe[1]=1;
	if(map.kyori[ene[E].x/16+1][ene[E].y/16-1]==-1)kabe[2]=1;
	if(map.kyori[ene[E].x/16-1][ene[E].y/16+0]==-1)kabe[3]=1;

	if(map.kyori[ene[E].x/16+1][ene[E].y/16+0]==-1)kabe[5]=1;
	if(map.kyori[ene[E].x/16-1][ene[E].y/16+1]==-1)kabe[6]=1;
	if(map.kyori[ene[E].x/16+0][ene[E].y/16+1]==-1)kabe[7]=1;
	if(map.kyori[ene[E].x/16+1][ene[E].y/16+1]==-1)kabe[8]=1;
	//�Փ˔���p�t���O
	if(ene[E].x%16<7 && ene[E].y%16<7)hit[0]=1;
	if(					ene[E].y%16<7)hit[1]=1;
	if(ene[E].x%16>9 && ene[E].y%16<7)hit[2]=1;
	if(ene[E].x%16<7				 )hit[3]=1;

	if(ene[E].x%16>9				 )hit[5]=1;
	if(ene[E].x%16<7 && ene[E].y%16>9)hit[6]=1;
	if(					ene[E].y%16>9)hit[7]=1;
	if(ene[E].x%16>9 && ene[E].y%16>9)hit[8]=1;

	if(kabe[1]==1 && hit[1]==1)YHIT=1;
	if(kabe[3]==1 && hit[3]==1)XHIT=1;
	if(kabe[5]==1 && hit[5]==1)XHIT=1;
	if(kabe[7]==1 && hit[7]==1)YHIT=1;

		//

	if(XHIT==0 && YHIT==0){//�΂ߓ����蔻��
		if(kabe[0]==1 && hit[0]==1){
			if(ene[E].x%16==ene[E].y%16 || ene[E].hx+ene[E].hy<16){XHIT=1;YHIT=1;}
			else	if(ene[E].x%16<ene[E].y%16)		XHIT=1;
			else									YHIT=1;
		}else if(kabe[2]==1 && hit[2]==1){
			if(16-ene[E].x%16==ene[E].y%16 || ene[E].hx+ene[E].hy<16)			{XHIT=1;YHIT=1;}
			else if(16-ene[E].x%16<ene[E].y%16)		XHIT=1;
			else									YHIT=1;
		}else if(kabe[6]==1 && hit[6]==1){
			if(16-ene[E].x%16-ene[E].y%16==0 || ene[E].hx+ene[E].hy<16)		{XHIT=1;YHIT=1;}
			else	if(16-ene[E].x%16<ene[E].y%16)	YHIT=1;
			else									XHIT=1;
		}else if(kabe[8]==1 && hit[8]==1){
			if(ene[E].x%16==ene[E].y%16 || ene[E].hx+ene[E].hy<16)			{XHIT=1;YHIT=1;}
			else	if(ene[E].x%16<ene[E].y%16)		YHIT=1;
			else									XHIT=1;
		}
	}
	
	//�i�i�����蔲��
	if(kabe[0]==0 && kabe[1]==1 && kabe[3]==1 && hit[0]==1){XHIT=-1;YHIT=-1;}
	if(kabe[2]==0 && kabe[1]==1 && kabe[5]==1 && hit[2]==1){XHIT=3;YHIT=-1;}
	if(kabe[6]==0 && kabe[3]==1 && kabe[7]==1 && hit[6]==1){XHIT=-1;YHIT=3;}
	if(kabe[8]==0 && kabe[5]==1 && kabe[7]==1 && hit[8]==1){XHIT=3;YHIT=3;}

	
	if(XHIT!=0){
		ene[E].x=ene[E].x/16*16+8*XHIT;
		ene[E].nai_x=ene[E].x*10000;
		ene[E].mx=ene[E].x/16;
		ene[E].my=ene[E].y/16;
		ene[E].hx=0;
	}
	if(YHIT!=0){
		ene[E].y=ene[E].y/16*16+8*YHIT;
		ene[E].nai_y=ene[E].y*10000;
		ene[E].my=ene[E].y/16;
		ene[E].mx=ene[E].x/16;
		ene[E].hy=0;
	}
	
	
	return;
}
void gameover_syori(){
	int BSC=stage[sys.stage_no].hi_score[sel.bonus][stage[sys.stage_no].best_score[sel.bonus]];//�x�X�g�X�R�A
	int HSC=stage[sys.stage_no].hi_score[sel.bonus][player.siki_no];//�n�C�X�R�A
	int LB=int(player.life*50*pow(5.0,double(sel.nando)));
	int SC=player.score+LB;
	if(	(sys.w_no==nando[sel.nando+sel.bonus*6].wave && sys.e_cnt<=0 && sys.s_cnt==0) || (player.life<=0)){//�G�S�Ń��C�t����

		if(player.life>0)	PlayMusic( "File/bgm/syouri.mp3" , DX_PLAYTYPE_BACK ) ;
		else				PlayMusic( "File/bgm/color.haiboku.mp3" , DX_PLAYTYPE_BACK ) ;
		SetVolumeMusic(option.bgm_on*option.bgm_on*option.bgm_on*option.bgm_on ) ;

		if(award.help_ok[21]==1 && player.life>0) help_gazou(21);

		//�X�R�A��\����I�����Ė߂�
		while(1){
		mouse_check();
		byouga_syori();//�`�揈��
		gameover_byouga();//�Q�[���I�[�o�[�`��
		if(inp.mou_LC==1){
			if(inp.mou_x>130 && inp.mou_x<330 && inp.mou_y>330 && inp.mou_y<360){
				sys.m_mode=2;
				break;
			}
			else if(inp.mou_x>130 && inp.mou_x<330 && inp.mou_y>370 && inp.mou_y<400 && replay.ok==0){
				sys.m_mode=3;
				break;
			}
			else if(inp.mou_x>130 && inp.mou_x<330 && inp.mou_y>410 && inp.mou_y<440 && replay.ok==0 && replay.no>0){
				player.score+=LB;
				replay_save();
				player.score-=LB;
				replay.no=0;
				se_ok(6);
			}
		}
		if(sys.tutorial_on==1){sys.m_mode=2;break;}//�`���[�g���A�����͑�����
		ScreenFlip();//��ʔ��f
		err_c();
		}
		//�n�C�X�R�A�̍X�V�ƃ|�C���g�̊l��
		if(SC>BSC){
			player.point+=(SC-BSC)*3;//3�{�|�C���g
			stage[sys.stage_no].best_score[sel.bonus]=player.siki_no;
		}
		if(SC>HSC){
			player.point+=(SC-HSC)*2;//2�{�|�C���g
			award.thi_score+=(SC-HSC);//���n�C�X�R�A�X�V
			stage[sys.stage_no].hi_score[sel.bonus][player.siki_no]=SC;//�n�C�X�R�A�X�V
		}
		if(player.life>0){//ײ̂O�ȏ�őf�ރ{�[�i�X
			player.point+=int(double(SC)*bonus.luck/1000);//
			award.siki_siyou[player.siki_no]++;//�w�����N���A��
			award.stage_clear[sys.stage_no]++;//�e�X�e�[�W�̃N���A��
		}
		//�f�ނ̊l��
		if(player.point>2000000000 || player.point<0){
			 award.sozai[sys.stage_no%4]=2000000000;//�ő�Q�O��
		}else award.sozai[sys.stage_no%4]+=player.point;

		award.tget_sozai+=player.point;
		
		if(sel.nando>=stage[sys.stage_no].max_nando[sel.bonus] && player.life>0)stage[sys.stage_no].max_nando[sel.bonus]=sel.nando+1;
		//��Փx�ǉ�����
		if(award.play_mode==sel.nando+1 && award.play_mode<6 && player.life>0){
			award.play_mode++;
			help_gazou(sel.nando+23);
		}
		if(stage[sys.stage_no].max_siki[sel.bonus][player.siki_no]<sel.nando+1 && player.life>0)stage[sys.stage_no].max_siki[sel.bonus][player.siki_no]=sel.nando+1;
		if(award.help_ok[28]==0 && sel.nando==5 && player.life>0)help_gazou(28);
		if(sys.stage_no<19 && sel.nando>=sys.stage_no/100 && player.life>0)award.stage_ok[sys.stage_no+1]=1;//�m�[�}���ȏ�N���A�Ŏ��X�e�[�W��
		if(replay.ok==0){
			award_check();
			data_save();//�f�[�^�̕ۑ�
		}
		//���v���C�̃o�b�N�A�b�v
		if(replay.no!=0 && replay.ok==0){
			replay.aut=1;
			player.score+=LB;
			replay_save();
			player.score-=LB;
			replay.aut=0;
		}
	}
	
	
	int S;
	for(S=0;S<4;S++){
		if(award.sozai[S]<0 || award.sozai[S]>2000000000)award.sozai[S]=2000000000;
	}
	return;
}
//����֘A
void mouse_check(){
	int I;
	char Buf[ 256 ] ;
	//����`�F�b�N
	GetMousePoint( &inp.mou_x , &inp.mou_y ) ;
	if(sys.tutorial_on==1 && sys.m_mode==0){
		inp.mou_x=sys.tu_x;
		inp.mou_y=sys.tu_y;
	}
	inp.mou_h=GetMouseWheelRotVol() ;
	inp.mou_ht+=inp.mou_h;
	sel.x=(inp.mou_x-8)/16;sel.y=(inp.mou_y-8)/16;
	GetHitKeyStateAll( Buf ) ;



	if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 ){// ������Ă���
		if(inp.mou_LD==0)inp.mou_LC=1;
		else		 inp.mou_LC=0;
		inp.mou_LD=1;
	}else{
		inp.mou_LC=0;// ������Ă��Ȃ�
		inp.mou_LD=0;
	}

	if( ( GetMouseInput() & MOUSE_INPUT_RIGHT ) != 0 ){// ������Ă���
		if(inp.mou_RD==0)inp.mou_RC=1;
		else		 inp.mou_RC=0;
		inp.mou_RD=1;
	}else{
		inp.mou_RC=0;// ������Ă��Ȃ�
		inp.mou_RD=0;
	}
	
	for(I=0;I<256;I++){
		inp.p_k[I]=0;
		if( Buf[ I ] == 1 ){
			if(inp.d_k[I]==0)inp.p_k[I]=1;
			inp.d_k[I]=1;
		}else	inp.d_k[I]=0;
	}
	return;
}
void vs_sousa(){
	int I,S=sel.no;
	for(I=0;I<6;I++){// WAVE�i�s,�ݒu,����,����,�d��,�u���C�u
		inp.sousa[I]=0;
	}
	inp.select=-10;

	if(replay.ok!=0)return;//���v���C���͖߂�

	if(sel.no>=200 && sel.no<230 && job[sel.no-200].set_rest==0){
		sel.no=-1;//�Z�b�g�s�\�ȕ���I��
		inp.select=sel.no;
		return;
	}

	if(inp.mou_RC==1){
		sel.no=-1;
		inp.select=sel.no;
		return;
	}

	if(inp.mou_LC==1){
		if(sel.no>=200 && sel.no<=230 && sel.x>=0 && sel.x<=29 && sel.y>=0 && sel.y<=27)inp.sousa[1]=1;//����z�u
		else if(sel.x>=0 && sel.x<=29 && sel.y>=28 && sel.y<=29) inp.sousa[0]=1 ;//WAVE�i�s
		else sel.no=check_sel();//�z�u���I��//����I��//�G�I��
		//�I��ύX
		if(S!=sel.no){
			inp.select=sel.no;
			return;//�I���Ƒ��̑���͓�������s�\
		}
	}
	//�u���C�u����
	if(inp.p_k[option.key_set[option.sc_key[1]]]==1 || (inp.mou_x>565 && inp.mou_x<625 && inp.mou_y>5 && inp.mou_y<30 && inp.mou_LC==1)){//���`
		if(player.brave>=100){
			inp.sousa[5]=1;
		}
	}
	//�A�b�v�O���[�h
	if(sel.no>=0 && sel.no<200 && (inp.p_k[option.key_set[option.sc_key[4]]]==1 || (inp.mou_x>565 && inp.mou_x<625 && inp.mou_y>285 && inp.mou_y<310 && inp.mou_LC==1))
		&& unit[sel.no].tame>=0){
		if(unit[sel.no].lv<=4 && player.money>=job[unit[sel.no].type].cost[unit[sel.no].lv+1]-unit[sel.no].cost && job[unit[sel.no].type].up_rest>0){
			inp.sousa[3]=1;
		}
	}
	//�P��
	if(sel.no>=0 && sel.no<200 && (inp.p_k[option.key_set[option.sc_key[3]]]==1 || (inp.mou_x>495 && inp.mou_x<555 && inp.mou_y>285 && inp.mou_y<310 && inp.mou_LC==1)) 
		&& unit[sel.no].tame>=0 && (unit[sel.no].ren>0 || sys.w_no==-1)){
			inp.sousa[2]=1;
	}
	//�d��
	if(sel.no>=0 && sel.no<200 && (inp.p_k[option.key_set[option.sc_key[5]]]==1 || (inp.mou_x>495 && inp.mou_x<555 && inp.mou_y>285 && inp.mou_y<310 && inp.mou_LC==1)) 
		&& unit[sel.no].tame>=0 && sys.w_no>=0){
			inp.sousa[4]=1;
	}
	//��wave�ڍs
	if((inp.p_k[option.key_set[option.sc_key[2]]]==1 || inp.d_k[KEY_INPUT_SPACE]==1 || (inp.mou_LC==1 && inp.mou_y>450 && inp.mou_x<480)) && (sys.w_time>2 || sys.w_time<0)){
		inp.sousa[0]=1;
	}
	return;
}
void vs_sousa_jikkou(){
	int E,S;
	class ENEDATA ENE;
	if(inp.select!=-10)sel.no=inp.select;

	if(inp.select>=2000){//�G�I��
		ENE=ene[0];
		ene[0]=ene[inp.select-2000];
		ene[inp.select-2000]=ENE;
		sel.no=1000;
	}

	if(inp.sousa[0]==1){//WAVE�i�s
		if(sys.w_no<nando[sel.nando+sel.bonus*6].wave)player.score+=sys.w_time*100/stage[sys.stage_no].wave_sp;
		sys.w_time=2;
	}

	if(inp.sousa[1]==1){//�ݒu
		set_unit(sel.no-200);
	}

	if(inp.sousa[2]==1){//����
		unit[sel.no].tame=(-60-sys.w_no*6)*player.sell_s/100;
		unit[sel.no].wait=-unit[sel.no].tame;
		unit[sel.no].sell=1;//���p
	}

	if(inp.sousa[3]==1){//����
		player.money-=job[unit[sel.no].type].cost[unit[sel.no].lv+1]-unit[sel.no].cost;//�����}�C�i�X
		unit[sel.no].tame=-((unit[sel.no].lv+1)*(unit[sel.no].lv+1))*60*player.up_s/100;
		unit[sel.no].wait=-unit[sel.no].tame;
		job[unit[sel.no].type].up_rest--;//�z�u���}�C�i�X
	}

	if(inp.sousa[4]==1){//�d��
		if(unit[sel.no].type==9){
			shot_make(sel.no ,0);
			sell_unit(sel.no);//�P��
			se_ok(21);
		}else if(unit[sel.no].type==20){
			for(S=0;S<4;S++){//�\������
			shot_make(sel.no,0);//�P����{
			shot[sys.s_cnt-1].r=PI*S/2;
			shot[sys.s_cnt-1].target=-2;//�����͈�
			shot[sys.s_cnt-1].sx=int(10000*cos(shot[sys.s_cnt-1].r));
			shot[sys.s_cnt-1].sy=int(10000*sin(shot[sys.s_cnt-1].r));
			}
			sell_unit(sel.no);//�P��
			se_ok(32);
		}
	}

	if(inp.sousa[5]==1){//�u���C�u
		player.brave_time_n=player.brave_long;//���ʎ��ԑ��
		player.brave_time=100;
		player.brave_rate*=2;//���܂�Ղ�����
		award.siki_brave[player.siki_no]++;//�E�C������
		if(player.siki_no==2)player.money=player.money*12/10;//�}���n�Q
		if(player.siki_no==4){
			for(E=0;E<sys.e_cnt;E++){//HP������딼��
			if(ene[E].time<0)continue;
			ene[E].hp/=2;
			ene[E].hp_max/=2;
			ene[E].def/=2;
			ene[E].heal/=2;
			}
		}
		PlayMusic( "File/bgm/brave.mp3" , DX_PLAYTYPE_LOOP ) ;
		SetVolumeMusic(option.bgm_on*option.bgm_on*option.bgm_on*option.bgm_on ) ;
		brave_byouga();
		fps.time=GetNowCount();
	}
	//���v���C�Đ������ʏ펞������

	//�Q�[���X�s�[�h����
	if(sys.tutorial_on==0){
		if(inp.mou_x>240 && inp.mou_x<440 && inp.mou_y>0 && inp.mou_y<30 && inp.mou_LC==1){
			if(inp.mou_x<290)		sys.game_sp=1;
			else if(inp.mou_x<340)	sys.game_sp=2;
			else if(inp.mou_x<390)	sys.game_sp=4;
			else					sys.game_sp=8;
			se_ok(5);
		}
		if(inp.mou_ht>1){
			sys.game_sp*=(2+(replay.ok-sys.tutorial_on)*2);
			inp.mou_ht=0;
			if(sys.game_sp<=8+(replay.ok-sys.tutorial_on)*56)se_ok(5);
		}else if(inp.mou_ht<-1){
			sys.game_sp/=(2+(replay.ok-sys.tutorial_on)*2);
			inp.mou_ht=0;
			if(sys.game_sp!=0)se_ok(5);
		}
	}
		if(sys.game_sp<1)sys.game_sp=1;//*1 *2 *4 *8//�S�i�K
		if(sys.game_sp>8+(replay.ok-sys.tutorial_on)*56)sys.game_sp=8+(replay.ok-sys.tutorial_on)*56;
		if(sys.debug[2]==1)sys.game_sp=64;

	//�f�o�b�O����
	if(inp.p_k[KEY_INPUT_F1]==1)sys.debug[0]=1-sys.debug[0];
	if(inp.p_k[KEY_INPUT_F2]==1)sys.debug[1]=1-sys.debug[1];
	if(inp.p_k[KEY_INPUT_F3]==1)sys.debug[2]=1-sys.debug[2];

	//���j���[���J��
	if(inp.p_k[option.key_set[option.sc_key[0]]]==1 || (inp.mou_x>495 && inp.mou_x<555 && inp.mou_y>5 && inp.mou_y<30 && inp.mou_LC==1)){//�ƭ�
		sys.m_mode=1;
		se_ok(6);
	}else if(replay.ok==1 && (inp.mou_LC==1 || inp.mou_RC==1)){
		sys.m_mode=1;
		se_ok(6);
	}

	return;
}
int check_sel(){
	int U,E;
	if(sel.x>=0 && sel.x<=28 && sel.y>=0 && sel.y<=28){//�}�b�v����
		for(E=0;E<sys.e_cnt;E++){//�G��I��
			if(abs(ene[E].x-inp.mou_x)<12 && abs(ene[E].y-inp.mou_y)<12 && ene[E].time>=0){
				return 2000+E;
			}
		}
		for(U=0;U<sys.u_cnt;U++){
			if(unit[U].x+1>=inp.mou_x/16 && unit[U].x+1<=inp.mou_x/16+1 && unit[U].y+1>=inp.mou_y/16 && unit[U].y+1<=inp.mou_y/16+1){
			return U;
			}
		}
		return -1;
	}else{//����I��or���j���[����
		for(U=0;U<12;U++){
			if(inp.mou_x>496+U%4*32 && inp.mou_x<528+U%4*32 && inp.mou_y>32+U/4*32 && inp.mou_y<64+U/4*32){
			return 200+sikikan[player.siki_no].job_set[(inp.mou_x-496)/32+(inp.mou_y-32)/32*4];
			}
		}
	}
	return sel.no;//�ω�����;
}
void replay_syori(){
	int R=0,I,J,T;

	if(replay.ok==0){//�L�^
		replay.sousa[replay.no]=0;
		if(inp.sousa[0]==1){replay.sousa[replay.no]=1;R=1;}
		if(inp.sousa[1]==1){replay.sousa[replay.no]+=2;R=1;}
		if(inp.sousa[2]==1){replay.sousa[replay.no]+=4;R=1;}
		if(inp.sousa[3]==1){replay.sousa[replay.no]+=8;R=1;}
		if(inp.sousa[4]==1){replay.sousa[replay.no]+=16;R=1;}
		if(inp.sousa[5]==1){replay.sousa[replay.no]+=32;R=1;}
		if(inp.select!=-10){R=1;}
		if(R==1){//�Ȃ�炩�̑��������
		replay.select[replay.no]=inp.select;
		replay.iti[replay.no]=sel.x+sel.y*60;
		replay.count[replay.no]=sys.p_time;
		replay.no++;
		}
	}else if(replay.no<100000){//�Ǎ�
		if(replay.count[replay.no]==sys.p_time){
		sel.x=replay.iti[replay.no]%60;
		sel.y=replay.iti[replay.no]/60;
		inp.select=replay.select[replay.no];
		J=replay.sousa[replay.no];
		for(I=0;I<6;I++){
			if(J%2==1)inp.sousa[I]=1;
			J/=2;
		}
		replay.no++;
		}
	}

	if(replay.iti>=0){//����̕\��
		R=replay.count[replay.no];
		if(replay.no>0)	R-=replay.count[replay.no-1];
		if(R>180)R=180;
		T=replay.count[replay.no]-R;
		tuto_mou(T,R,replay.iti[replay.no]%60*16,replay.iti[replay.no]/60*16+32);
	}

	return;
}
//���j���[�֘A
void vs_menu(){
	//���C�����j���[�ł̑���
	//�^�C�g���֖߂�
	//�ŏ������蒼��
	//�L�����Z��
	if(inp.mou_x>160 && inp.mou_x<320 && inp.mou_y>150 && inp.mou_y<180 && inp.mou_LC==1)sys.m_mode=2;//�^�C�g���֖߂�
	if(inp.mou_x>160 && inp.mou_x<320 && inp.mou_y>190 && inp.mou_y<220 && inp.mou_LC==1)sys.m_mode=3;//��蒼��
	if(inp.mou_x>160 && inp.mou_x<320 && inp.mou_y>230 && inp.mou_y<260 && inp.mou_LC==1)sys.m_mode=0;//���j���[�����
	if(inp.mou_RC==1) sys.m_mode=0;
	return;
}
//�z�u�֌W
int kabe_check(){
	int X,Y,E;
	for(X=0;X<30;X++)
		for(Y=0;Y<30;Y++)
		sys.ene_on[X][Y]=0;//������

	if((sel.x<3 || sel.y<3 || sel.x>25 || sel.y>25) && sel.x>=0) return 0;
	
	//�ǁA�G�̗L������
	for(E=0;E<sys.e_cnt;E++){
		if(ene[E].fly==1 || ene[E].time<0 || map_c.kyori[ene[E].x/16][ene[E].y/16]==-1)continue;//
		sys.ene_on[ene[E].x/16    ][ene[E].y/16    ]=1;//�G������
		sys.ene_on[(ene[E].x-7)/16][(ene[E].y-7)/16]=1;
		sys.ene_on[ene[E].x/16    ][(ene[E].y-7)/16]=1;
		sys.ene_on[(ene[E].x+7)/16][(ene[E].y-7)/16]=1;
		sys.ene_on[(ene[E].x-7)/16][ene[E].y/16    ]=1;
		sys.ene_on[(ene[E].x+7)/16][ene[E].y/16    ]=1;
		sys.ene_on[(ene[E].x-7)/16][(ene[E].y+7)/16]=1;
		sys.ene_on[ene[E].x    /16][(ene[E].y+7)/16]=1;
		sys.ene_on[(ene[E].x+7)/16][(ene[E].y+7)/16]=1;
	}
	//��u���m�F
	if(sel.x>-1)for(X=sel.x;X<sel.x+2;X++){
		for(Y=sel.y;Y<sel.y+2;Y++){
			if(map.ok[X][Y]==1 || map.goal[X][Y]!=0 || (sys.ene_on[X][Y]==1 && map.kabe[X][Y]==0))return 0;//�����Ȃ�
		}
	}
	
	return 1;//������
}
int set_check(){//�Z�b�g�m�F
	int X,Y,E,muk,mx;

	if(kabe_check()==0)return 0;//�z�u�s�\

	map_c=map;
	if(sel.x>-1){
	map_c.kabe[sel.x][sel.y]=1;//���ݒu
	map_c.kabe[sel.x+1][sel.y]=1;
	map_c.kabe[sel.x][sel.y+1]=1;
	map_c.kabe[sel.x+1][sel.y+1]=1;
	map_c.ok[sel.x][sel.y]=1;//���ݒu
	map_c.ok[sel.x+1][sel.y]=1;
	map_c.ok[sel.x][sel.y+1]=1;
	map_c.ok[sel.x+1][sel.y+1]=1;
	}
	for(X=0;X<30;X++){
		for(Y=0;Y<30;Y++){
			if(map_c.goal[X][Y]==2)	map_c.kyori[X][Y]=0;//�S�[��
			else					map_c.kyori[X][Y]=9999999;//�ʍs�s�\
			if(map_c.kabe[X][Y]==1)	map_c.kyori[X][Y]=-1;//�ǗL��
			if(map_c.goal[X][Y]==1) map_c.g_check[X][Y]=1;
			else					map_c.g_check[X][Y]=0;
		}
	}
	//�����v�Z
	for(X=0;X<30;X++){
		for(Y=0;Y<30;Y++){
			if(map_c.goal[X][Y]==2){
				sys.goal_check=0;
				kyori_keisan(X,Y);
				if(sys.goal_check==0) return 0;
				else{
					for(E=0;E<900;E++) if(map_c.kyori[E/30][E%30]>0 && map_c.kyori[E/30][E%30]<9999999) map_c.g_check[E/30][E%30]=1;
					map_c.g_check[X][Y]=1;
				}
			}
		}
	}
	//�ʍs�m�F
	for(X=0;X<30;X++){
		for(Y=0;Y<30;Y++){
			if(map_c.kyori[X][Y]>=9999999 && (map_c.goal[X][Y]==1 || sys.ene_on[X][Y]==1))return 0;//�ݒu�s�\
		}
	}
	
	//�����v�Z
	for(X=1;X<29;X++)
		for(Y=1;Y<29;Y++){
			if(map_c.kyori[X][Y]==9999999)map_c.kyori[X][Y]=-1;
			if(map_c.kyori[X][Y]==-1){
				map_c.muki[X][Y]=4;
				continue;
			}
			mx=9999999;
			muk=0;
			if(map_c.kyori[X-1][Y-1]<mx && map_c.kyori[X-1][Y-1]!=-1 && map_c.kyori[X-1][Y]!=-1 && map_c.kyori[X][Y-1]!=-1){muk=0;mx=map_c.kyori[X-1][Y-1];}
			if(map_c.kyori[X  ][Y-1]<mx && map_c.kyori[X  ][Y-1]!=-1															  ){muk=1;mx=map_c.kyori[X  ][Y-1];}
			if(map_c.kyori[X+1][Y-1]<mx && map_c.kyori[X+1][Y-1]!=-1 && map_c.kyori[X+1][Y]!=-1 && map_c.kyori[X][Y-1]!=-1){muk=2;mx=map_c.kyori[X+1][Y-1];}
			if(map_c.kyori[X-1][Y  ]<mx && map_c.kyori[X-1][Y  ]!=-1															  ){muk=3;mx=map_c.kyori[X-1][Y  ];}

			if(map_c.kyori[X+1][Y  ]<mx && map_c.kyori[X+1][Y  ]!=-1															  ){muk=5;mx=map_c.kyori[X+1][Y  ];}
			if(map_c.kyori[X-1][Y+1]<mx && map_c.kyori[X-1][Y+1]!=-1 && map_c.kyori[X-1][Y]!=-1 && map_c.kyori[X][Y+1]!=-1){muk=6;mx=map_c.kyori[X-1][Y+1];}
			if(map_c.kyori[X  ][Y+1]<mx && map_c.kyori[X  ][Y+1]!=-1															  ){muk=7;mx=map_c.kyori[X  ][Y+1];}
			if(map_c.kyori[X+1][Y+1]<mx && map_c.kyori[X+1][Y+1]!=-1 && map_c.kyori[X+1][Y]!=-1 && map_c.kyori[X][Y+1]!=-1){muk=8;mx=map_c.kyori[X+1][Y+1];}
			map_c.muki[X][Y]=muk;
		}
	return 1;
}
void kyori_keisan(int X,int Y){
	int K[8]={0,0,0,0,0,0,0,0};
	
	//012
	//345
	//678
	//���v����Ɍv�Z
	if(map_c.kyori[X-1][Y-1]>map_c.kyori[X][Y]+10 && map_c.kyori[X][Y-1]!=-1 && map_c.kyori[X-1][Y]!=-1)
	{map_c.kyori[X-1][Y-1]=map_c.kyori[X][Y]+10;K[0]=1;}else K[0]=0;
	if(map_c.kyori[X  ][Y-1]>map_c.kyori[X][Y]+ 7 )
	{map_c.kyori[X  ][Y-1]=map_c.kyori[X][Y]+ 7;K[1]=1;}else K[1]=0;
	if(map_c.kyori[X+1][Y-1]>map_c.kyori[X][Y]+10 && map_c.kyori[X][Y-1]!=-1 && map_c.kyori[X+1][Y]!=-1)
	{map_c.kyori[X+1][Y-1]=map_c.kyori[X][Y]+10;K[2]=1;}else K[2]=0;
	if(map_c.kyori[X-1][Y  ]>map_c.kyori[X][Y]+ 7 )
	{map_c.kyori[X-1][Y  ]=map_c.kyori[X][Y]+ 7;K[3]=1;}else K[3]=0;

	if(map_c.kyori[X+1][Y  ]>map_c.kyori[X][Y]+ 7 )
	{map_c.kyori[X+1][Y  ]=map_c.kyori[X][Y]+ 7;K[4]=1;}else K[4]=0;
	if(map_c.kyori[X-1][Y+1]>map_c.kyori[X][Y]+10 && map_c.kyori[X][Y+1]!=-1 && map_c.kyori[X-1][Y]!=-1)
	{map_c.kyori[X-1][Y+1]=map_c.kyori[X][Y]+10;K[5]=1;}else K[5]=0;
	if(map_c.kyori[X  ][Y+1]>map_c.kyori[X][Y]+ 7 )
	{map_c.kyori[X  ][Y+1]=map_c.kyori[X][Y]+ 7;K[6]=1;}else K[6]=0;
	if(map_c.kyori[X+1][Y+1]>map_c.kyori[X][Y]+10 && map_c.kyori[X][Y+1]!=-1 && map_c.kyori[X+1][Y]!=-1)
	{map_c.kyori[X+1][Y+1]=map_c.kyori[X][Y]+10;K[7]=1;}else K[7]=0;

	if(K[0]==1)kyori_keisan(X-1,Y-1);
	if(K[1]==1)kyori_keisan(X  ,Y-1);
	if(K[2]==1)kyori_keisan(X+1,Y-1);
	if(K[3]==1)kyori_keisan(X-1,Y  );
	if(K[4]==1)kyori_keisan(X+1,Y  );
	if(K[5]==1)kyori_keisan(X-1,Y+1);
	if(K[6]==1)kyori_keisan(X  ,Y+1);
	if(K[7]==1)kyori_keisan(X+1,Y+1);


	if(map_c.g_check[X][Y]==1) sys.goal_check=1;
	return;
}
void set_unit(int T){
	//�������ݒu�������
	if(player.money>=job[T].cost[0] && sys.u_cnt<200 && job[T].set_rest>0 && set_check()==1){//�Z�b�g�\
		map=map_c;
		job[T].set_rest--;//�c��Z�b�g���|
		award.set_cnt[T]++;
		player.money-=job[T].cost[0];//�����ቺ
		unit[sys.u_cnt].type=T;
		unit[sys.u_cnt].x=sel.x;
		unit[sys.u_cnt].y=sel.y;
		unit[sys.u_cnt].type=T;
		unit[sys.u_cnt].lv=-1;
		sys.u_cnt++;
		up_unit(sys.u_cnt-1);
		se_ok(10);
	}else se_ok(8);
	return;
}
void sell_unit(int U){//�C��̔��p

	if(unit[U].tame<0){
		if(sys.w_no==-1 || (player.siki_no==0 && player.brave_time>0)){//���
			player.money+=unit[U].cost;
			job[unit[U].type].set_rest+=1;
			job[unit[U].type].up_rest+=unit[U].lv;
		}else		player.money+=unit[U].cost*player.sell_rate/100;
	}
	if(stage[sys.stage_no].map_set[unit[U].x][unit[U].y]!=1	 ){map.kabe[unit[U].x][unit[U].y]=0;}
	if(stage[sys.stage_no].map_set[unit[U].x+1][unit[U].y]!=1  ){map.kabe[unit[U].x+1][unit[U].y]=0;}
	if(stage[sys.stage_no].map_set[unit[U].x][unit[U].y+1]!=1  ){map.kabe[unit[U].x][unit[U].y+1]=0;}
	if(stage[sys.stage_no].map_set[unit[U].x+1][unit[U].y+1]!=1){map.kabe[unit[U].x+1][unit[U].y+1]=0;}

	map.ok[unit[U].x][unit[U].y]=0;
	map.ok[unit[U].x+1][unit[U].y]=0;
	map.ok[unit[U].x][unit[U].y+1]=0;
	map.ok[unit[U].x+1][unit[U].y+1]=0;

	sel.x-=100;
	set_check();
	map=map_c;
	sel.x+=100;
	if(sel.no==U)sel.no=-1;
	unit[U]=unit[sys.u_cnt-1];
	sys.u_cnt--;
	return;
}
void up_unit(int U){
	int T,L;
	T=unit[U].type;
	L=unit[U].lv+1;
	unit[U].lv++;
	unit[U].cost=job[T].cost[L];
	unit[U].atk=job[T].atk[L];//�U����
	unit[U].ren=job[T].ren[L];//�ˌ��Ԋu
	unit[U].spd=job[T].spd[L];//�e��
	unit[U].han=job[T].han[L];//�ˌ��͈�
	unit[U].stn=job[T].stn[L];//�X�^������
	unit[U].stn_p=job[T].stn_p[L];//�X�^���m��
	unit[U].kuu=job[T].kuu[L];//�΋�␳
	unit[U].poi=job[T].poi[L];//�Ō���
	unit[U].bom=job[T].bom[L];//�y���͈�
	unit[U].chr=job[T].chr[L];//�x������
	unit[U].tame=0;//���݂̗��ߎ���
	unit[U].sell=0;
	unit[U].anti=job[T].anti;//�ΓG
	unit[U].arm=job[T].armer;//�h��ቺ����
	unit[U].sum=job[T].sum[L];//������΂�
	unit[U].wait=0;
	if(T==9)unit[U].han=unit[U].bom;
	else if(T==20)unit[U].han=unit[U].bom-16;

	if(L==5)award.maxup_cnt[T]++;

	return;
}
void sien_check(){
	int X,Y,U,XP,YP,EFE=0;
	if(player.brave_time>0){
		if(player.siki_no==0)EFE=50;
		if(player.siki_no==1)EFE=20;
		if(player.siki_no==2)EFE=player.money/10;
		if(player.siki_no==3)EFE=20;
		if(player.siki_no==4)EFE=100;
		if(player.siki_no==5)EFE=5;
		if(player.siki_no==6)EFE=20;
		if(player.siki_no==7)EFE=50;
	}

	//�x�����ʂ̌v�Z
	for(X=0;X<30;X++){
		for(Y=0;Y<30;Y++){
			map.sien[X][Y]=EFE;
		}
	}
	//�x���}�X�v�Z
	for(X=2;X<28;X++){
		for(Y=2;Y<28;Y++){
			if(stage[sys.stage_no].map_set[X][Y]==9){
				for(XP=X-2;XP<X+2;XP++){
					for(YP=Y-2;YP<Y+2;YP++){
						map.sien[XP][YP]+=10;//�␳10%
					}
				}
			}
		}
	}
	//�x�����j�b�g�v�Z
	for(U=0;U<sys.u_cnt;U++){
		if(unit[U].chr>0 && unit[U].tame>=0){
			for(XP=unit[U].x-2;XP<unit[U].x+3;XP++){
				for(YP=unit[U].y-2;YP<unit[U].y+3;YP++){
				if(XP==unit[U].x && YP==unit[U].y)continue;
					map.sien[XP][YP]+=unit[U].chr;//�␳10%
				}
			}
		}
	}
	return;
}

//�����蔻��֘A
void shot_hantei(int U){
	int E,R,RMAX,K,S,C;
	R=-1;
	RMAX=unit[U].han*unit[U].han;
	if(player.brave_time>0 && player.siki_no==1) RMAX=999999;//�˒���
	E=sel.no-1000;
	K=(ene[E].x-unit[U].x*16-16)*(ene[E].x-unit[U].x*16-16)+(ene[E].y-unit[U].y*16-16)*(ene[E].y-unit[U].y*16-16);
	if(K<RMAX && sel.no>=1000 && ene[E].fly!=unit[U].kuu){//�͈͔���
		if(ene[E].steru==0 || K<=64*64){
		RMAX=0;
		R=E;
		}
	}
	for(E=0;E<sys.e_cnt;E++){
		if(ene[E].time<0)continue;//���o��
		//�����蔻��
		K=(ene[E].x-unit[U].x*16-16)*(ene[E].x-unit[U].x*16-16)+(ene[E].y-unit[U].y*16-16)*(ene[E].y-unit[U].y*16-16);
		if(K<RMAX && ene[E].fly!=unit[U].kuu){//�͈͔���
			if(ene[E].steru==1 && K>64*64) continue;//�X�e���X
			RMAX=K;
			R=E;
		}
	}
	if(R>=0){
		unit[U].tame-=6000;
		se_ok(12+unit[U].type);
		switch(unit[U].type){
		//�ʏ�P��
		case 0:
		case 1:
		case 3:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 15:
		case 18:
		case 19:
		case 24:
		case 25:
		case 28:
		shot_make(U,R);break;
		case 2:
		S=3,C=2;
		if(unit[U].lv==5)C=4;//���x���ő�
		for(S=0;S<C+1;S++){
		shot_make(U,R);
		shot[sys.s_cnt-1].r+=PI/12*S-C*PI/24;
		shot[sys.s_cnt-1].sx=int(unit[U].spd*100*cos(shot[sys.s_cnt-1].r));
		shot[sys.s_cnt-1].sy=int(unit[U].spd*100*sin(shot[sys.s_cnt-1].r));
		}
		break;
		case 4:
		for(C=0;C<1+ene[R].fly*2;C++){
		shot_make(U,R);//�P����{
		shot[sys.s_cnt-1].time=C*-10;
		}
		break;
		case 12:
		if(unit[U].lv==5)S=8;
		else if(unit[U].lv>=3)S=6;
		else S=4;
		for(C=0;C<S;C++){
		shot_make(U,R);
		shot[sys.s_cnt-1].r+=(randam(100)-50)*PI*S/1200;//60~120�x
		shot[sys.s_cnt-1].sx=int(unit[U].spd*100*cos(shot[sys.s_cnt-1].r));
		shot[sys.s_cnt-1].sy=int(unit[U].spd*100*sin(shot[sys.s_cnt-1].r));
		}
		break;
		case 13:
		if(unit[U].lv==5)S=5;//5�A
		else S=3;
		for(;S>0;S--){//�O�A��
		shot_make(U,R);//�P����{
		shot[sys.s_cnt-1].time=-S*8;
		shot[sys.s_cnt-1].ref=1;//��񔽎�
		shot[sys.s_cnt-1].sx=unit[U].spd;
		if(unit[U].lv==5)shot[sys.s_cnt-1].ref=2;
		}
		break;
		case 14:
		for(S=0;S<4;S++){
		shot_make(U,R);//�P����{
		shot[sys.s_cnt-1].r+=PI/2*S;
		}
		break;
		case 16:
		for(S=0;S<3;S++){
		shot_make(U,R);//�P����{
		shot[sys.s_cnt-1].time=S*-15;
		}
		break;
		case 17:
		for(S=0;S<30;S++){
		shot_make(U,R);//�P����{
		shot[sys.s_cnt-1].target=-2;//�����͈�
		shot[sys.s_cnt-1].time=-S*15/2;
		}
		break;
		case 20:
		for(S=0;S<4;S++){//�\������
		shot_make(U,R);//�P����{
		shot[sys.s_cnt-1].r=PI*S/2;
		shot[sys.s_cnt-1].target=-2;//�����͈�
		shot[sys.s_cnt-1].sx=int(10000*cos(shot[sys.s_cnt-1].r));
		shot[sys.s_cnt-1].sy=int(10000*sin(shot[sys.s_cnt-1].r));
		}
		break;
		case 21:
		if(unit[U].lv>=3)C=16;
		else C=8;
		for(S=0;S<C;S++){
		shot_make(U,R);//�P����{
		shot[sys.s_cnt-1].r=PI*S/4+S/8*PI/8;//�p�x
		shot[sys.s_cnt-1].time=-S/8*32;
		}
		break;
		case 22:
		if(unit[U].lv==5) C=24;
		else if(unit[U].lv>=3)C=16;
		else C=8;
		for(S=0;S<C;S++){
			shot_make(U,R);
			shot[sys.s_cnt-1].r=6.28*S/8;//�p�x
			shot[sys.s_cnt-1].time=S/8*-10;
		}
		break;
		case 23:
		S=8+unit[U].lv*2;
		if(unit[U].lv==5)S+=12;//30�A//�S����
		for(C=0;C<S;C++){
			shot_make(U,R);
			shot[sys.s_cnt-1].r+=(randam(100)-50)*S*PI/3600;//60~120�x/
			shot[sys.s_cnt-1].sx=int(unit[U].spd*100*cos(shot[sys.s_cnt-1].r));
			shot[sys.s_cnt-1].sy=int(unit[U].spd*100*sin(shot[sys.s_cnt-1].r));
			shot[sys.s_cnt-1].time=-C*15/S;
		}
		break;
		case 26:
		S=5+unit[U].lv;//MAX10�A��
		for(;S>0;S--){
			shot_make(U,R);//�P����{
			shot[sys.s_cnt-1].time=-S*8;
			shot[sys.s_cnt-1].ref=1+(unit[U].lv+1)/2;//�ő�S�񔽎�
			shot[sys.s_cnt-1].sx=unit[U].spd;
		}
		break;
		case 27:
		if(unit[U].lv==5)S=5;//���x���l�`�w�łT��
		else S=3;
		for(;S>0;S--){
			shot_make(U,R);//�P����{
			shot[sys.s_cnt-1].time=S*-15;
		}
		break;
		case 29:
		if(unit[U].lv==5)S=60;
		else S=30;
		for(;S>0;S--){
			shot_make(U,R);//�P����{
			shot[sys.s_cnt-1].target=-2;//�����͈�
			shot[sys.s_cnt-1].time=-S*15/2;
			}
		break;
		}
	}

	return;
}
void hit_hantei(){//�����蔻��
	int E,S,sdel=0;
	for(S=0;S<sys.s_cnt;S++){
		if(shot[S].time<0)continue;
		for(E=0;E<sys.e_cnt;E++){
			if(ene[E].time<0)continue;//���o��
			//�����蔻��
			if((((ene[E].x-shot[S].x)*(ene[E].x-shot[S].x)+(ene[E].y-shot[S].y)*(ene[E].y-shot[S].y)<12*12+ene[E].boss*144) && shot[S].kuu!=ene[E].fly)|| shot[S].target<0){
				if(shot[S].target==-2){//�����͈͍U��
				str_hantei(S);
				}else if(shot[S].bom>0){//�y������
				han_hantei(S);
				}else{//�ʏ픻��
					if(ene[E].avoid>randam(99) && shot[S].type!=10 && ene[E].stan<=0){//��𔻒�
						if(ene[E].muteki<=0)ene[E].muteki=5;//��莞�Ԍ���
						shot[S].nai_x+=int(100*shot[S].sp*cos(shot[S].r));
						shot[S].nai_y+=int(100*shot[S].sp*sin(shot[S].r));
						continue;
					}
					hit_damege(E,S);
				}
			sdel++;
			shot[S].atk=0;
			break;
			}
		}
	}
	if(sdel!=0) sort_shot(sdel);//�e�̕��ёւ�
	return;
}
void han_hantei(int S){//�͈͍U������
	int E,B;

	for(E=0;E<sys.e_cnt;E++){
		if(ene[E].time<0)continue;
		//�����蔻��
		if((ene[E].x-shot[S].x)*(ene[E].x-shot[S].x)+(ene[E].y-shot[S].y)*(ene[E].y-shot[S].y)<(shot[S].bom+12)*(shot[S].bom+12)+ene[E].boss*144 && ene[E].fly!=shot[S].kuu){			
			hit_damege(E,S);
		}
	}
	for(B=0;B<100;B++){
		if(bom_efe[B].time<=0){//�����G�t�F�N�g
		bom_efe[B].x=shot[S].x;
		bom_efe[B].y=shot[S].y;
		bom_efe[B].r=shot[S].bom;
		bom_efe[B].time=30;
		bom_efe[B].color=shot[S].type;
		if(shot[S].type==5)			bom_efe[B].color=GetColor(255,0,0);//����
		else if(shot[S].type==6)	bom_efe[B].color=GetColor(180,180,0);//�m��
		else if(shot[S].type==9)	bom_efe[B].color=GetColor(122,122,255);//����
		else if(shot[S].type==16)	bom_efe[B].color=GetColor(255,122,0);//����
		else if(shot[S].type==18)	bom_efe[B].color=GetColor(255,0,255);//�E��
		else if(shot[S].type==25)	bom_efe[B].color=GetColor(255,255,255);//����
		else if(shot[S].type==27)	bom_efe[B].color=GetColor(255,255,0);//п�
		else if(shot[S].type==28)	bom_efe[B].color=GetColor(0,255,0);//���
		else						bom_efe[B].color=GetColor(255,122,0);

		break;
		}
	}

	return;
}
void str_hantei(int S){
	int E;//�����v�Z
	double A=0,B=0,C=0,K;//�X���v�ZAX+BY+C=0;
	double a=0,b=0,c=0;//���s���钼��
	//B=1//Y=AX+C;//
	//�����ƒ��s�����̌v�Z
	if(shot[S].sy!=0 && shot[S].sx!=0){//�X���v�Z
		A=double(shot[S].sy)/shot[S].sx;
		B=1;
		C=shot[S].y-A*shot[S].x;
		a=-1/A;
		b=1;
		c=shot[S].y-a*shot[S].x;
	}
	//��������
	for(E=0;E<sys.e_cnt;E++){
		if(ene[E].time<0 || ene[E].fly==shot[S].kuu)continue;//�ΏۊO
		//��������
		if(shot[S].sx==0){//�㉺����
			if(shot[S].sy>0 && ene[E].y<shot[S].y) continue;
			if(shot[S].sy<0 && ene[E].y>shot[S].y) continue;
			K=abs(ene[E].x-shot[S].x);
		}else if(shot[S].sy==0){//�㉺����
			if(shot[S].sx>0 && ene[E].x<shot[S].x) continue;
			if(shot[S].sx<0 && ene[E].x>shot[S].x) continue;
			K=abs(ene[E].y-shot[S].y);
		}else if(shot[S].sy>0){//�����
			if(ene[E].y-ene[E].x*a-c<=0)continue;
			K=abs(-A*ene[E].x+B*ene[E].y-C)/sqrt(A*A+B*B);
		}else{//������
			if(ene[E].y-ene[E].x*a-c>=0)continue;
			K=abs(-A*ene[E].x+B*ene[E].y-C)/sqrt(A*A+B*B);
		}
		//�����v�Z
		//�����蔻��
		if(K*2<double(shot[S].bom+16)+ene[E].boss*12){//bom+8�ȓ�
			hit_damege(E,S);
		}else continue;
	}
	for(E=0;E<100;E++){
		if(beam_efe[E].time<=0){//�����G�t�F�N�g
		beam_efe[E].x=shot[S].x+int(shot[S].bom*256/10*cos(shot[S].r));
		beam_efe[E].y=shot[S].y+int(shot[S].bom*256/10*sin(shot[S].r));
		beam_efe[E].r=shot[S].r;//�p�x
		beam_efe[E].s=double(shot[S].bom)/10;//���a
		beam_efe[E].time=30;
		if(option.efe_on==0)beam_efe[E].time=8;
		beam_efe[E].type=shot[S].type;
		break;
		}
	}
	return;
}
void hit_damege(int E,int S){//�_���[�W����

	int ATK;

	if(player.brave_time>0 && player.siki_no==7 && ene[E].boss==0){//�X���C�����U��
		ene[E].type=0;
		ene[E].fly=0;
		ene[E].spd=400;
		ene[E].heal=0;
		ene[E].def=0;
		ene[E].avoid=0;
		ene[E].steru=0;
	}

	if(shot[S].arm>0){
		ene[E].def-=int(sqrt(double(shot[S].atk)))/5;//�h��ቺ����
		if(ene[E].def<0)ene[E].def=0;
	}
	ATK=shot[S].atk-ene[E].def;
	if(ene[E].type==shot[S].anti)ATK+=shot[S].atk/2;//�Α����L
	if(ATK<1)ATK=1;//�Œ�P
	ene[E].hp-=ATK;//�_���[�W

	if(shot[S].stn>0 && ene[E].stan<=0 && shot[S].stn_p>randam(99)) ene[E].stan=shot[S].stn;//��ე���

	if(ene[E].type!=11){//�h���S���ɂ͓Ŗ���
		if(ene[E].poi<shot[S].poi)ene[E].poi=shot[S].poi;//�Ō���
	}

	if(shot[S].sum>0 && ene[E].type!=2){//������΂�����//�I�[�K�ɂ͖���
		ene[E].hx=int(cos(shot[S].r)*shot[S].sum*1000);
		ene[E].hy=int(sin(shot[S].r)*shot[S].sum*1000);
	}

	return;
}
//�����֘A
void shot_make(int U ,int E){
	if(sys.s_cnt>=9999)return;

	int S=sys.s_cnt;
	double rad;
	shot[S].type=unit[U].type;
	shot[S].atk=int(double(unit[U].atk)*double(100+map.sien[unit[U].x][unit[U].y])/100);
	shot[S].x=unit[U].x*16+16;
	shot[S].y=unit[U].y*16+16;
	shot[S].nai_x=unit[U].x*160000+160000;
	shot[S].nai_y=unit[U].y*160000+160000;
	rad=kakudo(unit[U].x*16+16,unit[U].y*16+16 ,ene[E].x,ene[E].y);//�G�̊p�x
	shot[S].r=rad;
	shot[S].sx=int(unit[U].spd*100*cos(rad));
	shot[S].sy=int(unit[U].spd*100*sin(rad));
	shot[S].sp=unit[U].spd;
	shot[S].time=0;
	shot[S].target=E;
	if(unit[U].spd==0)shot[S].target=-1;//�ڂ�
	shot[S].kuu=unit[U].kuu;
	shot[S].stn=unit[U].stn;
	shot[S].stn_p=unit[U].stn_p;
	shot[S].poi=unit[U].poi;
	shot[S].bom=unit[U].bom;
	shot[S].anti=unit[U].anti;
	shot[S].arm=unit[U].arm;
	shot[S].sum=unit[U].sum;
	shot[S].ref=0;
	if(player.brave_time>0 && player.siki_no==3)shot[S].bom+=24;//�͈͍U����

	if(player.brave_time>0 && player.siki_no==5){
		shot[S].stn+=60;
		shot[S].stn_p=100;
	}//��჌��ʕt��
	sys.s_cnt++;
	return;
}
void ene_make(int E,int X,int Y,int L,int T){

	ene[sys.e_cnt].type=E%15;
	ene[sys.e_cnt].lv=L;//���x��
	ene[sys.e_cnt].money=syu[E%15].money*(30+L)/300;//���� LV*3%UP
	ene[sys.e_cnt].hp_max=int(syu[E%15].hp*(double(100+(L-1)*20+(L-1)*(L-1)*6)/100));//�ő�HP
	ene[sys.e_cnt].spd=syu[E%15].spd*10;//���x

	if(X<=2)ene[sys.e_cnt].muki=5;
	else if(X>=27)ene[sys.e_cnt].muki=3;
	else if(Y<=2)ene[sys.e_cnt].muki=7;
	else if(Y>=27)ene[sys.e_cnt].muki=1;

	ene[sys.e_cnt].x=X*16+8;//X,Y���W
	ene[sys.e_cnt].y=Y*16+8;
	ene[sys.e_cnt].mx=X;
	ene[sys.e_cnt].my=Y;
	ene[sys.e_cnt].hx=0;
	ene[sys.e_cnt].hy=0;
	ene[sys.e_cnt].stan=0;//�X�^���c�莞��
	ene[sys.e_cnt].poi=0;//�Ŏc�莞��
	ene[sys.e_cnt].muteki=0;
	ene[sys.e_cnt].m_muki=ene[sys.e_cnt].muki;
	if(E%15==10)			ene[sys.e_cnt].def=L*2;//�S�[����
	else if(E%15==11)		ene[sys.e_cnt].def=L/2;//�h���S��
	else					ene[sys.e_cnt].def=0;//�h���
	if(E%15==7)				ene[sys.e_cnt].fly=1;
	else					ene[sys.e_cnt].fly=0;//��s�t���O
	if(E%15==9)				ene[sys.e_cnt].steru=1;//�X�e���X
	else					ene[sys.e_cnt].steru=0;

	if(E%15==3){
		ene[sys.e_cnt].avoid=10*int(sqrt(double(L+1)));//���
		if(ene[sys.e_cnt].avoid>90)ene[sys.e_cnt].avoid=90;//�ő�90%
		ene[sys.e_cnt].hp_max=int(ene[sys.e_cnt].hp_max*double(1000/(1000+(ene[sys.e_cnt].avoid-100)*5/4)));
	}else					ene[sys.e_cnt].avoid=0;


	ene[sys.e_cnt].boss=E/15;//�{�X�t���O
	ene[sys.e_cnt].time=T;
	if(ene[sys.e_cnt].type==2)ene[sys.e_cnt].time/=2;//�I�[�K�͌ł܂��ďo��


	ene[sys.e_cnt].nai_x=X*160000+80000;
	ene[sys.e_cnt].nai_y=Y*160000+80000;//���������pX,Y
	if(E>12){//�{�X
		ene[sys.e_cnt].spd=ene[sys.e_cnt].spd*2/3;//���x66%
		ene[sys.e_cnt].def*=2;//�h��Q�{
		ene[sys.e_cnt].money*=16;
		ene[sys.e_cnt].boss=1;
		ene[sys.e_cnt].hp_max*=16;//�g�o16�{
		ene[sys.e_cnt].heal*=16;
	}
	ene[sys.e_cnt].hp_max=int(ene[sys.e_cnt].hp_max*double(nando[sel.nando+sel.bonus*6].hp_hosei/100));
	if(ene[sys.e_cnt].hp_max<0)ene[sys.e_cnt].hp_max=2100000000;//�I�[�o�[�t���[�̏ꍇ21��

	if(ene[sys.e_cnt].type==6)ene[sys.e_cnt].heal=ene[sys.e_cnt].hp_max/60;//������
	else ene[sys.e_cnt].heal=0;//�����񕜖���

	ene[sys.e_cnt].hp=ene[sys.e_cnt].hp_max;

	sys.e_cnt++;
	return;
}
void sort_ene(int i){//�G�̍폜
	int E,EB,S;
	if(ene[0].hp<=0 && sel.no==1000)sel.no=-1;

	for(E=0;E<sys.e_cnt;E++){
		if(ene[E].hp<=0){//���ō�
			for(EB=sys.e_cnt-1;EB>E;EB--){
				if(ene[EB].hp>0){//����
				ene[E]=ene[EB];
				ene[EB].hp=0;//�󂫂�
				for(S=0;S<sys.s_cnt;S++){
					if(shot[S].target==EB)shot[S].target=E;
				}
				break;
				}
			}
		}
	}

	sys.e_cnt-=i;

	for(S=0;S<sys.s_cnt;S++){
		if(shot[S].target>=sys.e_cnt)shot[S].target=randam(sys.s_cnt-1);
	}

	return;
}
void sort_shot(int i){//�e�̍폜

	int S,SB;
	for(S=0;S<sys.s_cnt;S++){
		if(shot[S].atk==0){//���ō�
			for(SB=sys.s_cnt-1;SB>S;SB--){
				if(shot[SB].atk>0){//����
				shot[S]=shot[SB];
				shot[SB].atk=0;//�󂫂�
				break;
				}
			}
		}
	}
	sys.s_cnt-=i;
	return;
}
//�`��֘A
void byouga_syori(){//�`��
	back_byouga();//�w�i�`��
	unit_byouga();//���j�b�g�`��
	if(sys.debug[0]==0)ene_byouga();//�G�̕`��
	if(sys.debug[1]==0)shot_byouga();//�e�`��
	wave_byouga();//Wave���̕`��
	status_byouga();//�I�𕺁A�G�̃X�e�[�^�X�\��
	if(replay.ok==1)tuto_byouga();
	return;
}
void back_byouga(){//�w�i�`��
	int X,Y;
	for(X=2;X<28;X++){//�w�i�`��
		for(Y=2;Y<28;Y++){
			DrawRotaGraph( X*16+8 , Y*16+8 , 1 , 0 , gf.chip[stage[sys.stage_no].map_set[X][Y]] , TRUE ) ;
		}
	}
	//�O���b�h�\��
	if(option.grid_on!=0){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 150 ) ;
		for(X=2;X<28;X++){//�w�i�`��
			DrawLine( 40 , X*16-1 , 440 , X*16-1 , color.kuro ) ;
			DrawLine( X*16-1 , 40 , X*16-1 , 440 , color.kuro ) ;
		}
		//���S
		DrawBox( 13*16-8 , 15*16-2 , 17*16+8 , 15*16+2 , color.siro ,1) ;
		DrawBox( 15*16-2 , 13*16-8 , 15*16+2 , 17*16+8 , color.siro ,1) ;
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
	}

	return;
}
void unit_byouga(){//���j�b�g�`��
	int U,L;
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 128 ) ;// �`��u�����h���[�h���A���t�@�u�����h�i�T�O���j�ɂ���
	for(U=0;U<sys.u_cnt;U++){
	if(unit[U].tame<0){
		if(unit[U].sell==1)	DrawBox(unit[U].x*16+1,unit[U].y*16+1,unit[U].x*16+31,unit[U].y*16+31,color.ao,1);
		else				DrawBox(unit[U].x*16+1,unit[U].y*16+1,unit[U].x*16+31,unit[U].y*16+31,color.aka,1);
	}else	if(sel.no==U)	DrawBox(unit[U].x*16+1,unit[U].y*16+1,unit[U].x*16+31,unit[U].y*16+31,color.aka,1);
	else					DrawBox(unit[U].x*16+1,unit[U].y*16+1,unit[U].x*16+31,unit[U].y*16+31,color.siro,1);
	}
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
	for(U=0;U<sys.u_cnt;U++){
		if(map.sien[unit[U].x][unit[U].y]>0)DrawBox(unit[U].x*16,unit[U].y*16,unit[U].x*16+32,unit[U].y*16+32,color.aka,0);//�x�����ʂ���
		DrawBox(unit[U].x*16+1,unit[U].y*16+1,unit[U].x*16+31,unit[U].y*16+31,color.ao,0);
		if(unit[U].tame>=0){//�ʏ펞
		DrawRotaGraph( unit[U].x*16+16 , unit[U].y*16+16 , 1+0.2*unit[U].lv , 0 , gf.unit[unit[U].type][1] , TRUE ) ;
		}else{//���������p��
		DrawRotaGraph( unit[U].x*16+10 , unit[U].y*16+16 , 2 , 0 , gf.font[-unit[U].tame*100/unit[U].wait/10+40] , TRUE ) ;
		DrawRotaGraph( unit[U].x*16+22 , unit[U].y*16+16 , 2 , 0 , gf.font[-unit[U].tame*100/unit[U].wait%10+40] , TRUE ) ;
		}
		if(unit[U].lv==5) SetDrawBright(255,0,0);
		for(L=0;L<unit[U].lv;L++){//���j�b�g�̃��x���\��
			DrawRotaGraph( unit[U].x*16+8+L*4 , unit[U].y*16+24 , 1 , 0 , gf.font[39] , TRUE ) ;
		}
		if(unit[U].lv==5) SetDrawBright(255,255,255);
	}
	return;
}
void ene_byouga(){//�G�̕`��
	int E,H;
	for(E=sys.e_cnt-1;E>=0;E--){
		if(ene[E].time<0)continue;
		if(ene[E].muteki>0)SetDrawBlendMode( DX_BLENDMODE_ALPHA , 128 ) ;//�����������
		else SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 255 ) ;
		if(ene[E].muki<2)H=3;//��
		else if(ene[E].muki>6)H=0;//��
		else if(ene[E].muki==2 || ene[E].muki==5)H=9;//�E
		else H=6;//��
		if(ene[E].ani/10%4==1)		H+=1;
		else if(ene[E].ani/10%4==2) H+=2;
		else if(ene[E].ani/10%4==3) H+=1;
		if(ene[E].poi>0) SetDrawBright(0,255,0);
		else			 SetDrawBright(255,255,255);
		if(ene[E].stan<=0)DrawRotaGraph( ene[E].x, ene[E].y , 1+ene[E].boss , 0 , gf.ene[ene[E].type][H] , TRUE ) ;
		else			  DrawRotaGraph( ene[E].x+randam(6)-3 , ene[E].y+randam(6)-3 , 1+ene[E].boss , 0 , gf.ene[ene[E].type][H] , TRUE ) ;
		if(sel.no>=1000 && E==0){//�^�[�Q�b�g�\��
		SetDrawBright(255,255,255);
		DrawRotaGraph( ene[E].x , ene[E].y , 2 , 0 , gf.icon[35+sys.p_time/10%3] , TRUE ) ;
		}
	}
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 255 ) ;
	SetDrawBright(255,255,255);
	//�̗͕`��
	if(option.hp_on==1)for(E=0;E<sys.e_cnt;E++){
		if(ene[E].time<0 || ene[E].hp<0)continue;
		if(ene[E].boss==0){//�G��
		DrawBox(ene[E].x-8,ene[E].y+8,ene[E].x+8,ene[E].y+10,color.ao,0);
		DrawBox(ene[E].x-8,ene[E].y+8,ene[E].x-8+int(double(ene[E].hp)*16/ene[E].hp_max),ene[E].y+10,color.aka,0);
		}else{//�{�X
		DrawBox(ene[E].x-16,ene[E].y+16,ene[E].x+16,ene[E].y+18,color.ao,0);
		DrawBox(ene[E].x-16,ene[E].y+16,ene[E].x-16+int(double(ene[E].hp)*32/ene[E].hp_max),ene[E].y+18,color.aka,0);
		}
	}
	return;
}
void shot_byouga(){//�e�`��

	int S,B,C;
	double R;
	for(S=0;S<sys.s_cnt;S++){//�e
		if(shot[S].time<0)continue;
		R=shot[S].r;
		if(shot[S].type==14 || shot[S].type==18 || shot[S].type==21 || shot[S].type==22 || shot[S].type==26) R+=PI*3/4;
		else if(shot[S].type==3) R=double(shot[S].time)/3;
		DrawRotaGraph( shot[S].x , shot[S].y , 1 , R , gf.shot[shot[S].type] , TRUE ) ;
	}
	SetDrawBright(255,255,255);
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

	for(B=0;B<100;B++){//�͈͍U��
		if(bom_efe[B].time>0){
		if(option.efe_on==1)SetDrawBlendMode( DX_BLENDMODE_ALPHA , bom_efe[B].time*5 ) ;
		DrawCircle(bom_efe[B].x,bom_efe[B].y,bom_efe[B].r,bom_efe[B].color,option.efe_on);
		bom_efe[B].time-=sys.game_sp;
		}
	}
	for(B=0;B<100;B++){//�с[��
		if(beam_efe[B].time>0){
			if(option.efe_on==1){
			if(beam_efe[B].type==17)SetDrawBright(255,122,0);//�I�����W
			if(beam_efe[B].type==20)SetDrawBright(122,122,122);//�O���[
			if(beam_efe[B].type==29)SetDrawBright(122,122,255);//�u���[
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , beam_efe[B].time*5 ) ;
			DrawRotaGraph( beam_efe[B].x , beam_efe[B].y , beam_efe[B].s , beam_efe[B].r , gf.beam , TRUE ) ;
			beam_efe[B].time-=sys.game_sp;
			}else{
			if(beam_efe[B].type==17)C=GetColor(255,122,0);//�I�����W
			if(beam_efe[B].type==20)C=GetColor(122,122,122);//�O���[
			if(beam_efe[B].type==29)C=GetColor(122,122,255);//�u���[

			DrawLine(beam_efe[B].x-int(cos(beam_efe[B].r)*beam_efe[B].s*256)+int(cos(beam_efe[B].r+PI/2)*beam_efe[B].s*5),
					 beam_efe[B].y-int(sin(beam_efe[B].r)*beam_efe[B].s*256)+int(sin(beam_efe[B].r+PI/2)*beam_efe[B].s*5),
					 beam_efe[B].x-int(cos(beam_efe[B].r)*beam_efe[B].s*256)-int(cos(beam_efe[B].r+PI/2)*beam_efe[B].s*5),
					 beam_efe[B].y-int(sin(beam_efe[B].r)*beam_efe[B].s*256)-int(sin(beam_efe[B].r+PI/2)*beam_efe[B].s*5),
					 C);

			DrawLine(beam_efe[B].x+int(cos(beam_efe[B].r)*beam_efe[B].s*256)+int(cos(beam_efe[B].r+PI/2)*beam_efe[B].s*5),
					 beam_efe[B].y+int(sin(beam_efe[B].r)*beam_efe[B].s*256)+int(sin(beam_efe[B].r+PI/2)*beam_efe[B].s*5),
					 beam_efe[B].x-int(cos(beam_efe[B].r)*beam_efe[B].s*256)+int(cos(beam_efe[B].r+PI/2)*beam_efe[B].s*5),
					 beam_efe[B].y-int(sin(beam_efe[B].r)*beam_efe[B].s*256)+int(sin(beam_efe[B].r+PI/2)*beam_efe[B].s*5),
					 C);

			DrawLine(beam_efe[B].x+int(cos(beam_efe[B].r)*beam_efe[B].s*256)-int(cos(beam_efe[B].r+PI/2)*beam_efe[B].s*5),
					 beam_efe[B].y+int(sin(beam_efe[B].r)*beam_efe[B].s*256)-int(sin(beam_efe[B].r+PI/2)*beam_efe[B].s*5),
					 beam_efe[B].x-int(cos(beam_efe[B].r)*beam_efe[B].s*256)-int(cos(beam_efe[B].r+PI/2)*beam_efe[B].s*5),
					 beam_efe[B].y-int(sin(beam_efe[B].r)*beam_efe[B].s*256)-int(sin(beam_efe[B].r+PI/2)*beam_efe[B].s*5),
					 C);

			beam_efe[B].time-=sys.game_sp;
			}
		}
	}

	if(option.efe_on==1)for(B=0;B<100;B++){//���j
		if(kill_efe[B].t>0){
		DrawRotaGraph( kill_efe[B].x , kill_efe[B].y , kill_efe[B].s , 0 , gf.kill[(40-kill_efe[B].t)/8] , TRUE ) ;
		if(inp.sousa[5]==1)	kill_efe[B].t--;
		else				kill_efe[B].t-=sys.game_sp;
		}
	}
	SetDrawBright(255,255,255);
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;

	return;
}
void wave_byouga(){
	int W=sys.w_no,J,X,Y;
	waku(2*16,2*16,26,26,1,1);
	for(X=0;X<30;X++){
		for(Y=0;Y<30;Y++){
		if(Y==2 && X>1 && X<28)Y=28;
		DrawGraph(X*16,Y*16,gf.wskin[1][X%8+Y%8*12],1);
		}
	}
	X=sys.w_time*80/stage[sys.stage_no].wave_sp-80;
	//�eWAVE�̕`��
	for(J=0;J<7;J++){
		if(W+J>nando[sel.nando+sel.bonus*6].wave)break;
		if(W+J<0)continue;

		DrawBox(J*80+1+X,449,J*80+79+X,479,color.hai,1);
		DrawBox(J*80+1+X,449,J*80+79+X,479,color.kuro,0);
		if(stage[sys.stage_no].wave_type[abs((W+J)%100)]<15){//���
		DrawBox(J*80+3+X,451,J*80+77+X,477,color.ao,0);
		DrawRotaGraph( J*80+12+X , 460 , 1 , 0 , gf.ene[stage[sys.stage_no].wave_type[abs((W+J)%100)]%15][1] , TRUE ) ;
		DrawRotaGraph( J*80+28+X , 460 , 1 , 0 , gf.ene[stage[sys.stage_no].wave_type[abs((W+J)%100)]%15][1] , TRUE ) ;
		DrawRotaGraph( J*80+20+X , 468 , 1 , 0 , gf.ene[stage[sys.stage_no].wave_type[abs((W+J)%100)]%15][1] , TRUE ) ;
		}else{//�{�X
		DrawRotaGraph( J*80+20+X , 464 , 2 , 0 , gf.ene[stage[sys.stage_no].wave_type[abs((W+J)%100)]%15][1] , TRUE ) ;
		DrawBox(J*80+3+X,451,J*80+77+X,477,color.aka,0);
		}
		Y=0;
		//WAVE���̕\��
		if(W+J+1>999)DrawRotaGraph( J*80+35+X+Y , 466 , 2 , 0 , gf.font[(W+J+1)/1000%10+40] , TRUE ) ;
		if(W+J+1>99) DrawRotaGraph( J*80+45+X+Y , 466 , 2 , 0 , gf.font[(W+J+1)/100%10+40] , TRUE ) ;
		if(W+J+1>9)	 DrawRotaGraph( J*80+55+X+Y , 466 , 2 , 0 , gf.font[(W+J+1)/10%10+40] , TRUE ) ;
		else Y-=7;
		DrawRotaGraph( J*80+65+X+Y , 466 , 2 , 0 , gf.font[(W+J+1)%10+40] , TRUE ) ;	
	}
	mes_bmf(10,440,"NEXT",14,2);
	DrawBox(1,449,79,479,color.mido,0);
	return;
}
void brave_byouga(){
	int X,B;
	if(option.efe_on==0)return;

	//��ʂ���߂���A�t���b�V��
	for(X=0;X<200;X++){
		//���������Ŕ���
			if(X<120)for(B=0;B<100;B++){
				if(kill_efe[B].t<=0){
				kill_efe[B].x=randam(480);
				kill_efe[B].y=randam(480);
				kill_efe[B].t=40;
				kill_efe[B].s=3;
				break;
				}
			}
		byouga_syori();//�`�揈��
		//�u���C�u����\��
		if(X<30){
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255*X/60 ) ;
			DrawBox(0,0,640,480,color.kuro,1);
		}else if(X<60){
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , 122 ) ;
			DrawBox(0,0,640,480,color.kuro,1);
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255*(X-30)/30 ) ;
			mes(100,185,"SIKIKAN BRAVE",color.siro,color.kuro,font.b);
		}else if(X<90){
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , 122 ) ;
			DrawBox(0,0,640,480,color.kuro,1);
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255*(90-X)/30 ) ;
			mes(100,185,"SIKIKAN BRAVE",color.siro,color.kuro,font.b);
		}else if(X<170){
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , 122 ) ;
			DrawBox(0,0,640,480,color.kuro,1);
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255*(X-90)/30 ) ;
			switch(player.siki_no){
			case 0:
				mes(100,150,"�A���e�B���b�g",color.siro,color.kuro,font.b);
				mes(120,220,"�A�b�v�O���C�h",color.siro,color.kuro,font.b);
			break;
			case 1:
				mes(90,150,"�U�E���[���h",color.siro,color.kuro,font.b);
				mes(40,220,"���C�h�X�i�C�s���O",color.siro,color.kuro,font.b);
			break;
			case 2:
				mes(80,150,"�I�[���C�Y�}�l�[",color.siro,color.kuro,font.b);
				mes(100,220,"�}�l�[�C�Y�I�[��",color.siro,color.kuro,font.b);
			break;
			case 3:
				mes(80,150,"�}�b�X�����L���L",color.siro,color.kuro,font.b);
				mes(100,220,"�t�F�X�e�B�o��",color.siro,color.kuro,font.b);
			break;
			case 4:
				mes(100,150,"�L�N�C�`�����W",color.siro,color.kuro,font.b);
				mes(60,220,"�C�b�g�[�����[�_��",color.siro,color.kuro,font.b);
			break;
			case 5:
				mes(80,150,"���C�g�j���O",color.siro,color.kuro,font.b);
				mes(100,220,"�T���_�[�h���C�u",color.siro,color.kuro,font.b);
			break;
			case 6:
				mes(130,150,"�}�C���C�t",color.siro,color.kuro,font.b);
				mes(150,220,"�t�B�i�[��",color.siro,color.kuro,font.b);
			break;
			case 7:
				mes(100,150,"�t���X���C��",color.siro,color.kuro,font.b);
				mes(120,220,"�W���b�N�|�b�g",color.siro,color.kuro,font.b);
				break;
			}
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255*(X-140)/30 ) ;
			DrawBox(0,0,640,480,color.siro,1);
		}else{
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255*(200-X)/30 ) ;
			DrawBox(0,0,640,480,color.siro,1);
		}
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
		if(fps.sp_up==0){
			fps_check();
			ScreenFlip();
		}else{
			fps.sp_up=0;
		}
		err_c();//�G���[�`�F�b�N
	}
	
	return;
}
void menu_byouga(){
	//�w�i�𔖈Â�
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 128 ) ;// �`��u�����h���[�h���A���t�@�u�����h�i�T�O���j�ɂ���
	DrawBox(0,0,640,480,color.kuro,1);
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
	//�����`��

	if(sys.tutorial_on==1)	DrawString(182,162,"�`���[�g���A���I��",color.kuro);
	else	if(replay.ok==0)DrawString(182,162,"�X�e�[�W�I���֖߂�",color.kuro);
	else					DrawString(182,162,"���v���C�I���֖߂�",color.kuro);
	
	DrawString(182,202,"��蒼��",color.kuro);
	DrawString(182,242,"���j���[�����",color.kuro);


	if(sys.tutorial_on==1){
	if(inp.mou_x>160 && inp.mou_x<320 && inp.mou_y>150 && inp.mou_y<180)DrawString(180,160,"�`���[�g���A���I��",color.aka);
	else																DrawString(180,160,"�`���[�g���A���I��",color.siro);
	}else if(replay.ok==0){
	if(inp.mou_x>160 && inp.mou_x<320 && inp.mou_y>150 && inp.mou_y<180)DrawString(180,160,"�X�e�[�W�I���֖߂�",color.aka);
	else																DrawString(180,160,"�X�e�[�W�I���֖߂�",color.siro);
	}else{
	if(inp.mou_x>160 && inp.mou_x<320 && inp.mou_y>150 && inp.mou_y<180)DrawString(180,160,"���v���C�I���֖߂�",color.aka);
	else																DrawString(180,160,"���v���C�I���֖߂�",color.siro);
	}

	if(inp.mou_x>160 && inp.mou_x<320 && inp.mou_y>190 && inp.mou_y<220)DrawString(180,200,"��蒼��",color.aka);
	else												DrawString(180,200,"��蒼��",color.siro);
	if(inp.mou_x>160 && inp.mou_x<320 && inp.mou_y>230 && inp.mou_y<260)DrawString(180,240,"���j���[�����",color.aka);
	else												DrawString(180,240,"���j���[�����",color.siro);

	return;
}
void gameover_byouga(){
	int BSC=stage[sys.stage_no].hi_score[sel.bonus][stage[sys.stage_no].best_score[sel.bonus]];//�x�X�g�X�R�A
	int HSC=stage[sys.stage_no].hi_score[sel.bonus][player.siki_no];//�n�C�X�R�A
	int LB=int(player.life*50*pow(5.0,double(sel.nando)));
	int SC=player.score+LB;
	int I,U=0;
	//�Q�[���I�[�o�[�`��
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 122 ) ;
	waku(7*16,7*16,16,21,0,3);//�g�`��
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
	if(player.life>0)mes(150,120,"Stage Clear",color.siro,color.hai,font.a);//�N���Aor���s
	else			 mes(200,120,"Miss",color.siro,color.hai,font.a);
	//�x�X�g�X�R�A�\��//�X�V�œ_��
	mes_bmf(130,180,"BEST_SCORE",16,2);
	if(BSC<SC){//�X�V��
		SetDrawBright(255,122,122);
		mes_bmf(130,200,"NEW",8,1);
		U=SC;
	}else U=BSC;
	for(I=0;I<100;I++){
	if(U<=0 && I>0) break;
	DrawRotaGraph( 338-14*I , 200 , 2 , 0 , gf.font[U%10] , TRUE ) ;
	U/=10;
	}
	SetDrawBright(255,255,255);
	//�n�C�X�R�A�\��//�X�V�œ_��
	mes_bmf(130,220,"HI_SCORE",16,2);
	if(HSC<SC){//�X�V��
		U=SC;
		SetDrawBright(255,122,122);
		mes_bmf(130,240,"NEW",8,1);
	}else U=HSC;

	suu_bmf(338,250,2,U,14,0);

	SetDrawBright(255,255,255);
	//�X�R�A�\��//
	mes_bmf(130,260,"SCORE",16,2);
	U=SC-LB;
	suu_bmf(338,280,2,U,14,0);
	SetDrawBright(255,255,255);
	//���C�t�{�[�i�X�\��
	mes_bmf(130,300,"LIFEBONUS",8,1);
	U=LB;
	suu_bmf(338,300,2,U,14,0);
	SetDrawBright(255,255,255);
	//�f�ގ擾���\��
	if(player.life>0)U=int(double(SC)*bonus.luck/1000);
	if(SC>BSC)U+=(SC-BSC)*3;//3�{�|�C���g
	if(SC>HSC)U+=(SC-HSC)*2;//2�{�|�C���g
	if(U<0)U=2000000000;
	if(U>0){
	mes_bmf(130,320,"SOZAIGET",8,1);
	DrawRotaGraph( 200 , 320 , 1 , 0 , gf.icon[25+sys.stage_no%4] , TRUE ) ;
	if(U>0)suu_bmf(338, 320 , 2,U,14,0);
	}
	//�X�R�A�\��
	if(replay.ok==0){
	if(inp.mou_x>130 && inp.mou_x<330 && inp.mou_y>330 && inp.mou_y<360)mes(130,330,"�X�e�[�W�I��",color.aka,color.hai,font.a);
	else																mes(130,330,"�X�e�[�W�I��",color.siro,color.hai,font.a);
	if(inp.mou_x>130 && inp.mou_x<330 && inp.mou_y>370 && inp.mou_y<400)mes(130,370,"�Ē���",color.aka,color.hai,font.a);
	else																mes(130,370,"�Ē���",color.siro,color.hai,font.a);
	if(replay.no==0)															mes(130,410,"�ۑ�����",color.ao,color.hai,font.a);
	else	if(inp.mou_x>130 && inp.mou_x<330 && inp.mou_y>410 && inp.mou_y<450)mes(130,410,"���v���C�ۑ�",color.aka,color.hai,font.a);
	else																		mes(130,410,"���v���C�ۑ�",color.siro,color.hai,font.a);
	

	}else{
	if(inp.mou_x>130 && inp.mou_x<330 && inp.mou_y>330 && inp.mou_y<360)mes(130,330,"�I��",color.aka,color.hai,font.a);
	else																mes(130,330,"�I��",color.siro,color.hai,font.a);
	}
	return;
}
void status_byouga(){//�I�𕺁A�G�̃X�e�[�^�X�\��
	int U,i,j,S;
	waku(30*16,0,10,30,0,1);

	DrawBox(490,190,630,470,color.hai,1);
	//����`��
	for(U=0;U<12;U++){
	if(sel.no-200==sikikan[player.siki_no].job_set[U])					DrawBox(U%4*32+1+496,U/4*32+33,U%4*32+31+496,U/4*32+63,color.aka,1);
	else	if(job[sikikan[player.siki_no].job_set[U]].set_rest<=0)	DrawBox(U%4*32+1+496,U/4*32+33,U%4*32+31+496,U/4*32+63,color.hai,1);
	else									DrawBox(U%4*32+1+496,U/4*32+33,U%4*32+31+496,U/4*32+63,color.siro,1);
	}
	for(U=0;U<12;U++){
	DrawBox(U%4*32+1+496,U/4*32+33,U%4*32+31+496,U/4*32+63,color.ao,0);
	DrawRotaGraph( U%4*32+16+496 , U/4*32+48 , 1 , 0 , gf.unit[sikikan[player.siki_no].job_set[U]][1] , TRUE ) ;
	}
	//���j���[�����`�{�^���@�\��
	if(inp.mou_x>495 && inp.mou_x<555 && inp.mou_y>5 && inp.mou_y<30 )	DrawBox(495,5,555,30,GetColor(255,122,0),1);
	else																DrawBox(495,5,555,30,GetColor(200,200,200),1);
	if(inp.mou_x>565 && inp.mou_x<615 && inp.mou_y>5 && inp.mou_y<30 )	DrawBox(565,5,625,30,GetColor(0,255,255),1);
	else																DrawBox(565,5,625,30,GetColor(200,200,200),1);
	DrawBox(495,5,555,30,GetColor(128,64,0),0);
	DrawBox(565,5,625,30,GetColor(0,64,128),0);
	SetDrawBright(255,122,0);
	mes_bmf(512,20,"M",10,2);
	mes_bmf(526,22,"ENU",7,1);
	SetDrawBright(0,255,255);
	mes_bmf(578,20,"B",10,2);
	mes_bmf(592,22,"RAVE",7,1);
	SetDrawBright(255,255,255);

	if(sel.no<200){//�z�u���j�b�g�I��
		if(sel.no>=0){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 128 ) ;// �`��u�����h���[�h���A���t�@�u�����h�i�T�O���j�ɂ���
		DrawCircle(unit[sel.no].x*16+16,unit[sel.no].y*16+16,unit[sel.no].han,color.siro,1);//�U���͈͕`��
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
		DrawCircle(unit[sel.no].x*16+16,unit[sel.no].y*16+16,unit[sel.no].han,color.aka,0);
		}
	}else if(sel.no<230){//����I��
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 128 ) ;// �`��u�����h���[�h���A���t�@�u�����h�i�T�O���j�ɂ���
		DrawCircle(sel.x*16+16,sel.y*16+16,job[sel.no-200].han[0],color.siro,1);//�U���͈͕`��
		if(kabe_check()==0)	DrawBox(sel.x*16,sel.y*16,sel.x*16+32,sel.y*16+32,color.aka,1);//�ݒu����ꏊ�`��
		else				DrawBox(sel.x*16,sel.y*16,sel.x*16+32,sel.y*16+32,color.mido,1);
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
		DrawCircle(sel.x*16+16,sel.y*16+16,job[sel.no-200].han[0],color.aka,0);
	}
	if(sel.no>=0){
		if(sel.no<230){//���j�b�g�I��//����ޑI��//���ɓ���
		status_unit(sel.no);
		}else{//�G�I��
		status_ene(sel.no-1000);
		}
	}
	//�w�����摜���w�����u���C�u�c��\��
	DrawRotaGraph( 508 , 150 , 2 , 0 , gf.unit[player.siki_no+22][1] , TRUE ) ;
	DrawRotaGraph( 545 , 150 , 1 , 0 , gf.icon[38+sel.bonus] , TRUE ) ;
	switch(sel.nando){
		case 0:mes_bmf(525,159,"NORMAL",7,1);break;
		case 1:mes_bmf(525,159," HARD ",7,1);break;
		case 2:mes_bmf(525,159,"MANIAC",7,1);break;
		case 3:mes_bmf(525,159," LUNA ",7,1);break;
		case 4:mes_bmf(525,159," HELL ",7,1);break;
		case 5:mes_bmf(525,159,"DMARCH",7,1);break;
	}
	if(player.brave_time>0){//�������\��
	SetDrawBright(255,sys.p_time%25*10,sys.p_time%25*10);
	mes_bmf(574,136,"BRAVE",8,1);
	SetDrawBright(255,255,255);
	}
	//�X�R�A���`��
	DrawRotaGraph( 575 , 150 , 1 , 0 , gf.icon[3] , TRUE ) ;
	DrawRotaGraph( 505 , 175 , 1 , 0 , gf.icon[0] , TRUE ) ;
	DrawRotaGraph( 575 , 175 , 1 , 0 , gf.icon[1] , TRUE ) ;

	mes_bmf(10,10,"HI",5,1);
	mes_bmf(28,10,"SCORE",8,1);

	mes_bmf(28,22,"SCORE",8,1);

	mes_bmf(200,10,"GAME",8,1);
	mes_bmf(200,22,"SPEED",8,1);

	//�Q�[���X�s�[�h�`��
	for(i=0,j=1;i<4;i++,j*=2+(replay.ok-sys.tutorial_on)*2){
		DrawBox(244+i*50,2,290+i*50,28,GetColor(180,180,122),1);
		if(j==sys.game_sp){
			S=2;
			DrawBox(244+i*50,2,290+i*50,28,color.aka,0);
		}else S=1;
		DrawRotaGraph( 260+i*50 , 15 , S , 0 , gf.font[36] , TRUE ) ;
		suu_bmf(276+i*50,17,S,j,S*7,1);
	}
	
	SetDrawBright(255,122,0) ;
	suu_bmf(550,177,2,player.money,12,0);//�����`��

	SetDrawBright(255,0,0) ;
	suu_bmf(617,177,2,player.life,12,0);//ײ̕`��

	if(player.brave_time<=0){//�������Ă��Ȃ�
	SetDrawBright(0,255,255) ;
	suu_bmf(617,152,2,player.brave,12,0);
	}else{//������
	SetDrawBright(255,sys.p_time%25*10,sys.p_time%25*10);
	suu_bmf(617,152,2,player.brave_time,12,0);
	}
	SetDrawBright(255,255,255) ;
	//�X�R�A�\��
	i=player.score;
	for(j=0;j<100;j++){
	if(i<=0 && j>0) break;
	DrawRotaGraph( 180-7*j , 22 , 1 , 0 , gf.font[i%10] , TRUE ) ;
	i/=10;
	}
	//�n�C�X�R�A�\��
	i=stage[sys.stage_no].hi_score[sel.bonus][player.siki_no];
	for(j=0;j<100;j++){
	if(i<=0 && j>0) break;
	DrawRotaGraph( 180-7*j , 10 , 1 , 0 , gf.font[i%10] , TRUE ) ;
	i/=10;
	}
	return;
}
void status_unit(int U){
	int T,L,EFE,I,C,N;//���x���ƃG�t�F�N�g�ƃ^�C�v

	if(award.help_ok[10]==1) help_gazou(10);

	if(U<200){T=unit[U].type;L=unit[U].lv;EFE=map.sien[unit[U].x][unit[U].y];}
	else	 {T=U-200;L=0;EFE=0;}
	//���j�b�g�摜
	DrawRotaGraph( 510 , 215 , 2 , 0 , gf.unit[T][1] , TRUE ) ;

	DrawString(530,195,job[T].name,color.kuro);


	DrawStringToHandle(500,240,job[T].info[0],color.kuro,font.s);
	DrawStringToHandle(500,255,job[T].info[1],color.kuro,font.s);
	DrawStringToHandle(500,270,job[T].info[2],color.kuro,font.s);

	DrawString(525,215,"SET",color.siro);
	DrawString(582,215,"UP",color.siro);
	//���O,�ݒu�c��
	if(job[T].set_rest==0)	SetDrawBright(60,60,60);
	else					SetDrawBright(80,255,255);
	suu_bmf(570 , 223 ,2,job[T].set_rest,12,0);
	//�c������
	if(job[T].up_rest==0)	SetDrawBright(60,60,60);
	else					SetDrawBright(255,122,122);
	suu_bmf(620 , 223 ,2,job[T].up_rest,12,0);
	SetDrawBright(255,255,255);

	DrawRotaGraph( 500 , 350 , 2 , 0 , gf.font['L'-55] , TRUE ) ;DrawRotaGraph( 514 , 350 , 2 , 0 , gf.font['V'-55] , TRUE ) ;
	DrawRotaGraph( 507 , 372 , 1 , 0 , gf.icon[10] , TRUE ) ;
	DrawRotaGraph( 507 , 394 , 1 , 0 , gf.icon[11] , TRUE ) ;
	
	//���p���P�����d���{�^��
	if(sel.no<200){
		if(inp.mou_x>495 && inp.mou_x<555 && inp.mou_y>285 && inp.mou_y<310 )	DrawBox(495,285,555,310,GetColor(122,122,255),1);
		else																	DrawBox(495,285,555,310,GetColor(200,200,200),1);
		if(inp.mou_x>565 && inp.mou_x<615 && inp.mou_y>285 && inp.mou_y<310 )	DrawBox(565,285,625,310,GetColor(255,122,122),1);
		else																	DrawBox(565,285,625,310,GetColor(200,200,200),1);
		DrawBox(495,285,555,310,color.ao,0);
		DrawBox(565,285,625,310,color.aka,0);
		if(job[T].ren[0]>0 || sys.w_no==-1){
			SetDrawBright(180,180,255);
			mes_bmf(510,300,"S",10,2);
			mes_bmf(524,302,"ELL",7,1);
		}else{
			SetDrawBright(180,180,255);
			mes_bmf(510,300,"W",10,2);
			mes_bmf(524,302,"ORK",7,1);
		}
		SetDrawBright(255,0,0);
		mes_bmf(588,300,"U",10,2);
		mes_bmf(602,302,"P",7,1);
	}else{
		DrawBox(500,290,610,305,color.kuro,0);
		DrawRotaGraph( 555 , 298 , 1 , 0 , gf.icon[0] , TRUE ) ;
		mes_bmf(510,300,"C",10,2);
		mes_bmf(520,302,"OST",7,1);
		suu_bmf(598,300,2,job[T].cost[L],12,0);
	}
	SetDrawBright(255,255,255);
	//�X�e�[�^�X�`��
	for(I=0;I<4;I++){//��b�X�e�[�^�X
	
		if(I==0){
			if(sys.w_no==-1 || (player.siki_no==0 && player.brave_time>0))U=job[T].cost[L];
			else U=job[T].cost[L]*sikikan[player.siki_no].sell_cost/100;
			SetDrawBright(180,180,255);
		}else if(I==1){U=L+1;SetDrawBright(255,255,255);}
		else if(I==2){U=job[T].atk[L];SetDrawBright(255,0,0);}
		else if(I==3){U=job[T].ren[L];SetDrawBright(0,255,255);}
		if(I==0){
		DrawString(500,318+I*22,"+",color.ao);
		suu_bmf(552,328+I*22,2,U,12,0);
		}else suu_bmf(564,328+I*22,2,U,12,0);
	}
	//���x���A�b�v��\��
	if(L<=4){
		L++;
		for(I=0;I<4;I++){
		if(I==0)	SetDrawBright(255,0,0);//���F
		else		SetDrawBright(255,255,0);//���F
		if(I==0){U=job[T].cost[L]-job[T].cost[L-1];}
		else if(I==1) U=1;
		else if(I==2){U=job[T].atk[L]-job[T].atk[L-1];}
		else if(I==3){U=job[T].ren[L]-job[T].ren[L-1];}
			if(U>0){
			if(I>0)	DrawString(576,318+I*22,"+",color.siro);
			else	DrawString(576,318+I*22,"-",color.siro);
			suu_bmf(620,328+I*22,2,U,12,0);
			}
		}
		L--;
	}
	//�������
	for(I=0,C=0;I<4;I++){
	U=0;N=0;
	if((job[T].sum[L]>0	 || job[T].sum[(L+1)%6]>0	) && I==0){U=job[T].sum[L];N=job[T].sum[(L+1)%6];SetDrawBright(255,122,122);}//�{��
	if((job[T].stn[L]>0	 || job[T].stn[(L+1)%6]>0	) && I==1){U=job[T].stn[L];N=job[T].stn[(L+1)%6];SetDrawBright(255,255,0);}//���
	if((job[T].poi[L]>0	 || job[T].poi[(L+1)%6]>0   ) && I==2){U=job[T].poi[L];N=job[T].poi[(L+1)%6];SetDrawBright(150,0,150);}//��
	if((job[T].chr[L]>0	 || job[T].chr[(L+1)%6]>0   ) && I==3){U=job[T].chr[L];N=job[T].chr[(L+1)%6];SetDrawBright(122,255,122);}//�x��
	if(U==0 && N==0)continue;
	N-=U;
	DrawRotaGraph( 507 , 416+C*22 , 1 , 0 , gf.icon[13+I] , TRUE ) ;//�A�C�R���\��
	//�����O�̃X�e�[�^�X�\��
	suu_bmf(564,416+C*22,2,U,12,0);
	if(L<=4){//������
			if(N>0){
			SetDrawBright(255,255,0);
			DrawString(576,406+C*22,"+",color.siro);
			suu_bmf(620,416+C*22,2,N,12,0);
			}
		}
	C++;
	}
	//�x������
	if(EFE>0){
		SetDrawBright(255,0,0);
		DrawRotaGraph( 564 , 460 , 1 , 0 , gf.icon[18] , TRUE ) ;
		DrawString(576,450,"+",color.siro);
		suu_bmf(620 , 460 , 2,EFE,12,0);
	}
	SetDrawBright(255,255,255);
	return;
}
void status_ene(int E){
	int U,I;

	if(award.help_ok[15]==1) help_gazou(15);
	//�G�摜
	DrawRotaGraph( 510 , 215 , 2+ene[E].boss , 0 , gf.ene[ene[E].type][1] , TRUE ) ;
	//�G���O�Ɛ�����
	DrawString(530,215,syu[ene[E].type].name,color.kuro);
	DrawStringToHandle(500,240,syu[ene[E].type].info[0],color.kuro,font.s);
	DrawStringToHandle(500,255,syu[ene[E].type].info[1],color.kuro,font.s);
	DrawStringToHandle(500,270,syu[ene[E].type].info[2],color.kuro,font.s);
	//���x��
	DrawRotaGraph( 500 , 306 , 2 , 0 , gf.font['L'-55] , TRUE ) ;DrawRotaGraph( 514 , 306 , 2 , 0 , gf.font['V'-55] , TRUE ) ;
	DrawRotaGraph( 507 , 328 , 1 , 0 , gf.icon[1] , TRUE ) ;
	DrawRotaGraph( 507 , 350 , 1 , 0 , gf.icon[2] , TRUE ) ;
	DrawRotaGraph( 507 , 372 , 1 , 0 , gf.icon[0] , TRUE ) ;
	if(ene[E].def>0)DrawRotaGraph( 507 , 394 , 1 , 0 , gf.icon[4] , TRUE ) ;
	else if(ene[E].heal>0)DrawRotaGraph( 507 , 394 , 1 , 0 , gf.icon[5] , TRUE ) ;
	else if(ene[E].avoid>0)DrawRotaGraph( 507 , 394 , 1 , 0 , gf.icon[19] , TRUE ) ;

	for(I=0;I<5;I++){
	if(I==0) U=ene[E].lv;
	else if(I==1){U=int(ene[E].hp);SetDrawBright(255,0,0);}//�̗�
	else if(I==2){U=ene[E].spd/20;SetDrawBright(0,255,255);}//���x
	else if(I==3){U=ene[E].money;SetDrawBright(255,122,0);}//�R�X�g
	else if(I==4){
		if(ene[E].def>0){//����\��
			U=ene[E].def;SetDrawBright(255,122,255);
		}else if(ene[E].heal>0){
			U=ene[E].heal;SetDrawBright(122,122,255);
		}else if(ene[E].avoid>0){
			U=ene[E].avoid;SetDrawBright(255,122,255);
		}else break;
	}
	suu_bmf(620,306+I*22,2,U,14,0);
	}
	SetDrawBright(255,255,255);
	return;
}
//�`���[�g���A���p
void tuto_byouga(){
	if(sys.tutorial_on==1){
	if(sys.p_time>5300) sys.game_sp=8;
	else if(sys.p_time>=5200) sys.game_sp=4;
	else if(sys.p_time>=5100) sys.game_sp=2;
	tuto_mes(	0,800	,"����̐������s���܂�"
						,"�E�̃��X�g���烆�j�b�g��I�у}�b�v���N���b�N�����"
						,"����������ă��j�b�g��ݒu���܂�",0);
	tuto_mes(1000,800	,"�m�L�[����ʉ����N���b�N�Ő퓬�J�n"
						,"�ݒu�������j�b�g���G���U�����܂�"
						,"",0);
	//WAVE�i�s
	tuto_mes(2000,800	,"�m�L�[����ʉ����N���b�N�Ŏ��v�`�u�d�փX�L�b�v"
						,"�����_������̂ŗ]�T������΃X�L�b�v���܂��傤"
						,"",0);
	//�U���͈�
	tuto_mes(3000,600	,"���j�b�g�ɂ��A�U���͈͂��قȂ�܂�"
						,"�~�ŕ\�������̂��U���͈͂ł�"
						,"",0);
	//
	tuto_mes(3800,500	,"���j�b�g��I�����t�o���N���b�N���邩�A�t�L�[��"
						,"����������ă��j�b�g�̃��x�����グ�܂�"
						,"���x�����オ��ƃ��j�b�g�͋����Ȃ�܂�",0);
	//����
	tuto_mes(4400,500	,"���j�b�g��I�����r�d�k�k���N���b�N���邩"
						,"�r�L�[�Ń��j�b�g�����ق��܂�"
						,"���ق���Ǝ����������炩�߂��Ă��܂�",0);
	//�Q�[���X�s�[�h
	tuto_mes(5000,600	,"�}�E�X�z�C�[���ŃQ�[���X�s�[�h��ύX�o���܂�"
						,"���K�ȑ��x�ŗV��ł�������"
						,"",0);
	//�Q�[��
	tuto_mes(6000,600	,"�G�ɂ���Ăg�o�̍�����A�f�������قȂ�"
						,"���ɂ͓���\�͂��������G�����܂�"
						,"",0);
	//���x��
	tuto_mes(8000,600	,"�v�`�u�d���i�ނɂ�G�̃��x�����オ��"
						,"�G�̂g�o���㏸���Ă����܂�"
						,"",0);

	//�{�X
	tuto_mes(12500,600	,"�{�X�̂��o�܂��ł�"
						,"�{�X�̓T�C�Y���傫���A�g�o�������A�������x���ł�"
						,"�����𑽂������Ă���̂Ŋm���Ɏd���߂܂��傤",0);
	//�Ń��j�b�g
	tuto_mes(14000,600	,"�����Ȃǂ̃��j�b�g�͓G�ɓł�^���܂�"
						,"�ł��󂯂��G�͗΂ɂȂ�ꎞ�I�ɒx���Ȃ�܂�"
						,"",0);
	//�ő勭��
	tuto_mes(19000,600	,"���j�b�g�̃��x���͍ő�U�ł�"
						,"�ő僌�x���ɂȂ�Ƒ傫���˒����L�т���"
						,"��C�ɋ����Ȃ�ꍇ������܂�",0);
	//�͈͍U��
	tuto_mes(28000,600	,"�͈͍U���͔����͈͓��̑S�Ă̓G�Ƀ_���[�W"
						,"��^���܂��A�ł܂��ďo������G�ɗL���ł�"
						,"",0);
	//�G�I��
	tuto_mes(41000,600	,"�G�����N���b�N����ƓG�̏�񂪕\������܂�"
						,"�܂��A���j�b�g�͑I�����ꂽ�G��D�悵�đ_���܂�"
						,"",0);
	//�d�����j�b�g
	tuto_mes(43000,600	,"�d�����j�b�g�͂v�`�q�j���N���b�N���邩"
						,"�v�L�[�������ƁA��x�����U�������܂�"
						,"��჌��ʂ������Ă���̂ő��~�߂ɂ��g���܂�",0);
	//�_���[�W
	tuto_mes(46000,600	,"�G���S�[���ɓ��B����ƃ_���[�W���󂯂܂�"
						,"���C�t���O�ɂȂ�ƁA�Q�[���I�[�o�[�ł�"
						,"",0);
	//�G�I��
	tuto_mes(50000,600	,"�x�����j�b�g�ɗאڂ������j�b�g�͉�ʉE���̐��l����"
						,"�U���͂��㏸���܂�"
						,"",0);
	//�G�I��
	tuto_mes(53000,600	,"���j�b�g�ɂ���Ă͓���̓G�ɓ���������"
						,"1.5�{�̃_���[�W��^���܂�"
						,"",0);
	//�u���C�u����
	tuto_mes(57800,600	,"�^�}�V�C�����܂�����Ԃ�BRAVE���N���b�N���邩"
						,"�a�L�[�������ƁA�^�}�V�C�������"
						,"�V�L�J���u���C�u�𔭓����܂�",0);
	//�u���C�u����
	tuto_mes(58600,600	,"�V�L�J���u���C�u�̌��ʂ̓V�L�J���ɂ��قȂ�"
						,"�}���E�X�̏ꍇ�A���i�Ɖ��ق���u�ŉ\�ɂȂ�"
						,"���َ��A�������i���ݒu����100%������܂�",0);
	//�I��
	tuto_mes(60000,600	,"�`���[�g���A���͏I���ł�"
						,"����ł́I"
						,"",0);
	}
	DrawRotaGraph( sys.tu_x , sys.tu_y , 1 , 0 , gf.icon[29] , TRUE ) ;
	return;
}
void tuto_mes(int T,int E,char mes_a[100],char mes_b[100],char mes_c[100],int I){
	if(sys.p_time>=T && sys.p_time<T+E){
		waku(20,380-I*370,28,6,0,3);
		sys.game_sp=1;
		DrawString(30,395-I*370,mes_a,color.siro);
		DrawString(30,420-I*370,mes_b,color.siro);
		DrawString(30,445-I*370,mes_c,color.siro);
	}
	return;
}
void tuto_mou(int T,int E,int X,int Y){
	if(E<=0)return;

	if(sys.p_time>=T && sys.p_time<=T+E){
		sys.tu_x=(sys.tu_px)*(T+E-sys.p_time)/E+(X)*(sys.p_time-T)/E;
		sys.tu_y=(sys.tu_py)*(T+E-sys.p_time)/E+(Y)*(sys.p_time-T)/E;
		if(sys.p_time==T+E-1){
		sys.tu_px=X;
		sys.tu_py=Y;
		}
	}
	
	return;
}
//���̑�
void err_c(){
	if( ProcessMessage() == -1 || CheckHitKey( KEY_INPUT_ESCAPE ) == 1){//ESC�������G���[�ŏI��
	//�ۑ�
	DxLib_End() ;//DX���C�u�����̎g�p�I��
	exit(1);//�v���O�����̏I��
	}
	return;
}
double kakudo(int x_1,int y_1 ,int x_2,int y_2){
	double kyori,kaku,cos_;
	kyori=sqrt(double((x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2)));
	if(kyori==0) kyori=1;
		if (kyori!=0){
		cos_=(x_1-x_2)/kyori;
		}
		if (y_1>=y_2){
		kaku=acos(cos_)+PI;
		}
		else{
		kaku=PI*2-acos(cos_)+PI;
		}
	if (kaku>=PI*2) kaku-=PI*2;
	return kaku;
}
void waku(int XU,int YU,int XS,int YS,int TYPE,int NO){
	int X,Y;
	XS--;YS--;
	if(TYPE==0){//���g
		for(X=0;X<XS+1;X++){//��
			for(Y=0;Y<YS+1;Y++){//�c
			DrawGraph(XU+X*16,YU+Y*16,gf.wskin[NO][X%8+Y%8*12],1);
			}
		}
	}
	//�S��
	DrawGraph(XU,YU,gf.wskin[NO][8],1);
	DrawGraph(XU+XS*16,YU,gf.wskin[NO][11],1);
	DrawGraph(XU,YU+YS*16,gf.wskin[NO][44],1);
	DrawGraph(XU+XS*16,YU+YS*16,gf.wskin[NO][47],1);
	for(X=1;X<XS;X++){//��
	DrawGraph(XU+X*16,YU,gf.wskin[NO][9],1);
	DrawGraph(XU+X*16,YU+YS*16,gf.wskin[NO][45],1);
	}
	for(Y=1;Y<YS;Y++){//�c
	DrawGraph(XU,YU+Y*16,gf.wskin[NO][20],1);
	DrawGraph(XU+XS*16,YU+Y*16,gf.wskin[NO][23],1);
	}
	
	return;
}
void mes(int X,int Y,char M[100],int C,int C2,int F){
	//�e�����`��֐�
	DrawStringToHandle(X+2,Y+2,M,C2,F);
	DrawStringToHandle(X,Y,M,C,F);
	return;
}
void mes_bmf(int X,int Y,char M[30],int XKAN,double SIZE){
	int I;
	for(I=0;I<30;I++){
	if(M[I]==NULL) break;
	if(M[I]-55>0 && M[I]-55<40)DrawRotaGraph( X+I*XKAN , Y , SIZE , 0 , gf.font[M[I]-55] , TRUE ) ;
	}
	return;
}
void suu_bmf(int X,int Y,double SIZE,int U,int XKAN,int T){
	int I=0;
	if(U<0)U=0;

	do{
	DrawRotaGraph( X-XKAN*I , Y , SIZE , 0 , gf.font[U%10+T*40] , TRUE ) ;
	U/=10;
	I++;
	}while(U>0);

	return;
}
void se_ok(int S){
	if(option.se_on==0)return;
	PlaySoundMem( se.wav[S] , DX_PLAYTYPE_BACK ) ;
	return;
}
void okodukai_check(){
	time_t T;
	struct tm T_ST;
	time(&T);
	
	localtime_s(&T_ST, &T);
	
	if(T_ST.tm_mday!=player.date && player.date!=0){//�����Â�������
		if(award.sozai[0]<award.sozai[1] && award.sozai[0]<award.sozai[2] && award.sozai[0]<award.sozai[3])	award.sozai[0]+=200000;
		else if(award.sozai[1]<award.sozai[2] && award.sozai[1]<award.sozai[3])								award.sozai[1]+=200000;
		else if(award.sozai[2]<award.sozai[3] )																award.sozai[2]+=200000;
		else																								award.sozai[3]+=200000;
		bonus.luck+=2;
		award.tget_sozai+=200000;
		help_gazou(22);
	}

	player.date=T_ST.tm_mday;
	return;
}
void fps_check(){
	int NTIME=GetNowCount();
	fps.rest+=NTIME-fps.time;
	fps.tyousei+=NTIME-fps.time-16.3333;
	if(fps.tyousei<0)fps.tyousei=0;
	if(fps.sp_up<0)fps.sp_up=0;
	if(fps.tyousei>16.3333){
		fps.sp_up=1;
		fps.tyousei=0;
	}
	if(fps.rest>=1000){
		fps.now=fps.count;
		fps.count=0;
		fps.rest-=1000;
	}
	fps.time=GetNowCount();
	return;
}
int randam(int R){
	if(R<=0)R=0;
	return rand()%(R+1);
}
//�e�̏����֘A
int shot_move_n(int S){
	//�e 0�̏���
	shot[S].nai_x+=shot[S].sx;
	shot[S].nai_y+=shot[S].sy;
	shot[S].x=shot[S].nai_x/10000;
	shot[S].y=shot[S].nai_y/10000;
	if(shot[S].x<-10 || shot[S].y<-10 || shot[S].x>490 || shot[S].y>490){
		shot[S].atk=0;
		return 1;
	}
	return 0;
}
int shot_move_s(int S){
	shot[S].x=shot[S].nai_x/10000;
	shot[S].y=shot[S].nai_y/10000;
	if(shot[S].time>=0){
		if(shot[S].target==-2)str_hantei(S);//�����͈͔���
		else				  han_hantei(S);//�͈͔���
		shot[S].atk=0;
		return 1;
	}
	return 0;
}
int shot_move_r(int S){
	shot[S].nai_x+=int((shot[S].time-20)*shot[S].sp*cos(shot[S].r));
	shot[S].nai_y+=int((shot[S].time-20)*shot[S].sp*sin(shot[S].r));
	shot[S].x=shot[S].nai_x/10000;
	shot[S].y=shot[S].nai_y/10000;
	if(shot[S].time>300)shot[S].time=300;

	if((shot[S].x<30 || shot[S].y<30 || shot[S].x>450 || shot[S].y>450) && shot[S].time>60){//����
		shot[S].ref--;
		if(shot[S].x<30)shot[S].x=30;
		else if(shot[S].x>450)shot[S].x=450;
		else if(shot[S].y<30)shot[S].y=30;
		else if(shot[S].y>450)shot[S].y=450;
		shot[S].sp=shot[S].sp*3/2;//2�{����
		shot[S].sum+=40;//������΂��t��
		if(shot[S].x==30)shot[S].r=-shot[S].r+PI;
		else if(shot[S].x==450)shot[S].r=-shot[S].r+PI;
		else if(shot[S].y==30)shot[S].r=-shot[S].r;
		else if(shot[S].y==450)shot[S].r=-shot[S].r;
		shot[S].atk=shot[S].atk*3/2;//2�{��
		if(shot[S].ref<0){
			shot[S].atk=0;
			return 1;
		}
	}
	return 0;
}
int shot_move_hm(int S){
	if(shot[S].time<1200 && shot[S].time>60 && sys.e_cnt>0){
	if(sel.no>=1000)						shot[S].target=0;
	shot[S].r=kakudo(shot[S].x,shot[S].y ,ene[shot[S].target].x,ene[shot[S].target].y);
	}

	if(shot[S].time>60)shot[S].time+=2;
	shot[S].nai_x+=int((shot[S].time-60)*shot[S].sp*cos(shot[S].r));
	shot[S].nai_y+=int((shot[S].time-60)*shot[S].sp*sin(shot[S].r));
	shot[S].x=shot[S].nai_x/10000;
	shot[S].y=shot[S].nai_y/10000;
	if(shot[S].x<-160 || shot[S].y<-160 || shot[S].x>640 || shot[S].y>640){
		shot[S].atk=0;
		return 1;
	}
	return 0;
}
int shot_move03(int S){
	//���̏���
	shot[S].nai_x+=shot[S].sx*(-50+shot[S].time)/100;
	shot[S].nai_y+=shot[S].sy*(-50+shot[S].time)/100;
	shot[S].x=shot[S].nai_x/10000;
	shot[S].y=shot[S].nai_y/10000;
	if(shot[S].x<-160 || shot[S].y<-160 || shot[S].x>640 || shot[S].y>640){
		shot[S].atk=0;
		return 1;
	}
	return 0;
}
int shot_move05(int S){
	shot[S].nai_x+=shot[S].sx*shot[S].time*shot[S].time/3200;
	shot[S].nai_y+=shot[S].sy*shot[S].time*shot[S].time/3200;
	shot[S].x=shot[S].nai_x/10000;
	shot[S].y=shot[S].nai_y/10000;
	if(shot[S].x<-10 || shot[S].y<-10 || shot[S].x>490 || shot[S].y>490){
		shot[S].atk=0;
		return 1;
	}
	return 0;
}
int shot_move10(int S){
	//�z�[�~���O�e
	if(shot[S].time<1200 && sys.e_cnt>0){
	if(sel.no>=1000)						shot[S].target=0;
	shot[S].r=kakudo(shot[S].x,shot[S].y ,ene[shot[S].target].x,ene[shot[S].target].y);
	}
	shot[S].nai_x+=int(shot[S].sp*100*cos(shot[S].r));
	shot[S].nai_y+=int(shot[S].sp*100*sin(shot[S].r));
	shot[S].x=shot[S].nai_x/10000;
	shot[S].y=shot[S].nai_y/10000;
	if(shot[S].x<-10 || shot[S].y<-10 || shot[S].x>490 || shot[S].y>490){
		shot[S].atk=0;
		return 1;
	}
	return 0;
}
int shot_move14(int S){
	//��]��
	if(shot[S].time>120){
	shot[S].nai_x+=shot[S].sx;
	shot[S].nai_y+=shot[S].sy;
	shot[S].time=120;
	}
	shot[S].x=shot[S].nai_x/10000+int(shot[S].time*cos(shot[S].r)/6);
	shot[S].y=shot[S].nai_y/10000+int(shot[S].time*sin(shot[S].r)/6);
	shot[S].r+=0.15;
	if(shot[S].x<-10 || shot[S].y<-10 || shot[S].x>490 || shot[S].y>490){
		shot[S].atk=0;
		return 1;
	}
	return 0;
}
int shot_move21(int S){
	if(shot[S].time<64){//�W�J
		shot[S].x=shot[S].nai_x/10000+int(shot[S].time*cos(shot[S].r));
		shot[S].y=shot[S].nai_y/10000+int(shot[S].time*sin(shot[S].r));
	}else if(shot[S].time==64){//�����_���z�[�~���O
		if(sys.e_cnt>0){
		if(sel.no>=1000)	shot[S].target=0;
		shot[S].r=kakudo(shot[S].x,shot[S].y,ene[shot[S].target].x,ene[shot[S].target].y);
		}
		shot[S].nai_x=shot[S].x*10000;
		shot[S].nai_y=shot[S].y*10000;
		shot[S].sx=int(shot[S].sp*100*cos(shot[S].r));
		shot[S].sy=int(shot[S].sp*100*sin(shot[S].r));
	}else{//���i
		shot[S].nai_x+=shot[S].sx;
		shot[S].nai_y+=shot[S].sy;
		shot[S].x=shot[S].nai_x/10000;
		shot[S].y=shot[S].nai_y/10000;
	}
	//�e 0�̏���
	if(shot[S].x<-160 || shot[S].y<-160 || shot[S].x>640 || shot[S].y>640){
		shot[S].atk=0;
		return 1;
	}
	return 0;
}
int shot_move22(int S){
	if(shot[S].time<128){//��]���Ȃ���W�J
		shot[S].x=shot[S].nai_x/10000+int(shot[S].time*cos(shot[S].r-PI/2)/2);
		shot[S].y=shot[S].nai_y/10000+int(shot[S].time*sin(shot[S].r-PI/2)/2);
		shot[S].r+=0.1;
	}else if(shot[S].time==128){//�����_���z�[�~���O
		if(sys.e_cnt>0){
		if(sel.no>=1000)	shot[S].target=0;
		shot[S].r=kakudo(shot[S].x,shot[S].y,ene[shot[S].target].x,ene[shot[S].target].y);
		}
		shot[S].nai_x=shot[S].x*10000;
		shot[S].nai_y=shot[S].y*10000;
		shot[S].sx=int(shot[S].sp*100*cos(shot[S].r));
		shot[S].sy=int(shot[S].sp*100*sin(shot[S].r));
	}else{//���i
		shot[S].nai_x+=shot[S].sx;
		shot[S].nai_y+=shot[S].sy;
		shot[S].x=shot[S].nai_x/10000;
		shot[S].y=shot[S].nai_y/10000;
	}
	//�e 0�̏���
	if(shot[S].x<-160 || shot[S].y<-160 || shot[S].x>640 || shot[S].y>640){
		shot[S].atk=0;
		return 1;
	}
	return 0;
}

