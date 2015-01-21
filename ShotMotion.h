//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#include "Utility/IMotion.h"
#include "IStage.h"
#include "Shot.h"
#include "Enemy.h"

namespace SDX
{
	using namespace SDX_TD;

	namespace MOTION
	{
		/**ライナ/勇者:勇者強化.*/
		/**@todo 対地or対空を区別せず追尾する*/
		class 勇者 : public IMotion
		{
		private:
			Point center;
			int count = 0;
			double angle;
			double speed;
			int radius;
		public:
			勇者(const Point &初期座標, int 半径, double 角度 , double 角速度 ) :
				center(初期座標),
				angle(角度),
				radius(半径),
				speed(角速度)
			{}

			bool Update(IPosition* 移動対象) override
			{
				//一定時間まで広がり
				count++;
				if (count < 120)
				{
					double X = center.x + std::sin(angle) * radius * count / 120;
					double Y = center.y + std::cos(angle) * radius * count / 120;

					angle += speed;

					移動対象->SetPos( X , Y );
				}
				else
				{
					if (count == 120)
					{
						//一番近い敵orターゲットに向かう
						IObject* enemy = nullptr;

						if (SStage->selectEnemy)
						{
							enemy = SStage->selectEnemy;
						}
						else
						{
							enemy = SStage->GetNearEnemy(&center,true,true);
						}

						if ( enemy )
						{
							移動対象->SetAngle(移動対象->GetDirect(enemy));
						}
					}
					
					移動対象->MoveF( speed * 30 );
				}

				return true;
			}
		};

		//ナツメ:武闘家強化、
		class ナツメ : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{
				return false;
			}
		};

		//ルコウ:減速しつつ後方へ、急加速
		class ルコウ : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{
				return false;
			}
		};

		//ディアネラ:
		class ディアネラ : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{
				return false;
			}
		};

		//ミナエ
		class ミナエ : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{
				return false;
			}
		};

		//トレニア:範囲型吹き飛ばし
		class トレニア : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{
				return false;
			}
		};

		//ロチエ
		class ロチエ : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{
				return false;
			}
		};

		//バロゥ
		class バロゥ : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{
				return false;
			}
		};

		//フィオナ:ただのビーム

		//ナズナ:螺旋吹き飛ばし
		class 螺旋 : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{
				return false;
			}
		};

		//委員長:単純な範囲攻撃
		//ミルラ:単純な範囲攻撃

		/** 一番近い敵orターゲットを追尾する.*/
		/**@todo 対地or対空限定の実装が途中*/
		template <class TSpeed>
		class 追尾 : public IMotion
		{
		private:
			TSpeed speed;
			double homing;
		public:
			追尾( const TSpeed &速度 , double 毎フレームの追尾角度 ):
				speed(速度),
				homing(毎フレームの追尾角度)
			{}

			bool Update(IPosition* 移動対象) override
			{
				double angle;
				auto 対象 = SStage->selectEnemy;
				//敵を選択していないなら一番近い敵
				if (対象 == nullptr)
				{
					対象 = SStage->GetNearEnemy(移動対象,true,true);
				}

				if ( 対象 )
				{
					//角度の差を取得
					angle = ( 移動対象->GetAngle() , 移動対象->GetDirect(対象));
					if (std::abs(angle) < homing)
					{
						移動対象->SetAngle(homing);
					}
					else if (angle > 0)
					{
						移動対象->Rotate( -homing );
					}
					else
					{
						移動対象->Rotate( homing );
					}
				}

				移動対象->MoveF(speed.Update());

				return true;
			}
		};

		//師範:周りぐるぐる
		class 回転 : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{
				return false;
			}
		};

	}

}