//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#include "Utility/IMotion.h"
#include "IStage.h"
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
				auto 対象 = SStage->selectEnemy;
				//敵を選択していないなら一番近い敵
				if (対象 == nullptr)
				{
					対象 = SStage->GetNearEnemy(移動対象,true,true);
				}

				if ( 対象 )
				{
					移動対象->SetAngle(移動対象->GetDirect(対象));
				}

				移動対象->MoveF(speed.Update());

				return true;
			}
		};

		/** 最初に後方に飛んで、その後追尾.*/
		class 追跡 : public IMotion
		{
		private:
			double 速度;
			int timer = 0;
		public:
			追跡(double 速度):
				速度(速度)
			{}

			bool Update(IPosition* 移動対象) override
			{
				++timer;

				//最初は減速しつつ移動
				if (timer < 60)
				{
					移動対象->MoveA(速度 * (60 - timer) / 60 , PAI + 移動対象->GetAngle());
					return true;
				}

				//以降は加速しつつ追尾
				auto 対象 = SStage->selectEnemy;
				//敵を選択していないなら一番近い敵
				if (対象 == nullptr)
				{
					対象 = SStage->GetNearEnemy(移動対象, true, true);
				}

				if (対象)
				{
					移動対象->SetAngle(移動対象->GetDirect(対象));
				}

				移動対象->MoveF( (速度 * timer) / 30);

				return true;
			}

		};

		//師範:周りぐるぐる
		class 回転 : public IMotion
		{
		private:
			double angle = 0;
			double speed = 0;
			double range = 0;
			double timer = 0;			
			int length = 0;
			Point center;
		public:
			回転(const Point &中心, double 初角, double 速度 , double 半径 ):
				center(中心),
				angle(初角),
				range(半径),
				speed(速度)
			{}

			bool Update(IPosition* 移動対象) override
			{
				++timer;

				if (timer < 60)
				{
					++length;
				}
				else if (timer > 120)
				{
					center.x += std::sin(移動対象->GetAngle()) * speed;
					center.y += std::cos(移動対象->GetAngle()) * speed;
				}

				angle += DEG * 32;

				const double x = center.x + std::sin(angle) * range * length / 120;
				const double y = center.y + std::cos(angle) * range * length / 120;
				移動対象->SetPos(x, y);

				return false;
			}
		};

	}

}