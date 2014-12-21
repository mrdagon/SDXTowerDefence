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
		//ライナ/勇者:勇者強化
		class 勇者 : public IMotion
		{
		private:
			Point center;
			int count = 0;
			double angle;
			double speed;
			double radius;
		public:
			勇者(const Point &初期座標, double 半径, double 角度 , double 角速度 ) :
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
							enemy = SStage->GetNearEnemy(&center);
						}

						if ( enemy )
						{
							移動対象->SetAngle(移動対象->GetDirect(enemy));
						}
					}
					
					移動対象->MoveF( 10 );
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

			}
		};

		//ルコウ:減速しつつ後方へ、急加速
		class ルコウ : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{

			}
		};

		//ディアネラ:
		class ディアネラ : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{

			}
		};

		//ミナエ
		class ミナエ : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{

			}
		};

		//トレニア:範囲型吹き飛ばし
		class トレニア : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{

			}
		};

		//ロチエ
		class ロチエ : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{

			}
		};

		//バロゥ
		class バロゥ : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{

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

			}
		};

		//委員長:単純な範囲攻撃
		//ミルラ:単純な範囲攻撃

		//技師:追尾
		/** 最大追尾可能な角度を指定.*/
		class 追尾 : public IMotion
		{
		private:
			double homing;
		public:
			追尾(double 一F辺りの追尾角度 = 0.0 ):
				homing(一F辺りの追尾角度)
			{}

			bool Update(IPosition* 移動対象) override
			{
				if (SStage->selectEnemy)
				{
					//選択した敵に向かう
					移動対象->SetAngle( 移動対象->GetDirect(SStage->selectEnemy) );
				}
				else
				{
					//一番近い敵に向かう
					移動対象->SetAngle( SStage->GetNearDirect(移動対象) );
				}
			}
		};

		//師範:周りぐるぐる
		class 回転 : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{

			}
		};

		//狩人:曲射
		class 曲射 : public IMotion
		{
		private:
		public:
			bool Update(IPosition* 移動対象) override
			{

			}
		};
	}

}