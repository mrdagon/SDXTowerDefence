//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#include "Utility/IMotion.h"
#include "Shot.h"

namespace SDX_TD
{
	namespace MOTION
	{
		using namespace SDX;
		using namespace SDX::MOTION;

		//ライナ:勇者強化
		class ライナ : public IMotion
		{
		private:
			Point center;
			int count = 0;
			int radius;
		public:
			ライナ(const Point &初期座標 , int 半径):
				center(初期座標),
				radius(半径)
			{}

			bool Update(IShape* 移動対象) override
			{
				//一定時間まで広がり

				//一番近い敵orターゲットに向かう

				return true;
			}
		};

		//ナツメ:武闘家強化、

		//ルコウ:減速しつつ後方へ、急加速

		//ディアネラ:

		//ミナエ
		//トレニア:範囲型吹き飛ばし
		//ロチエ
		//バロゥ
		//フィオナ:ただのビーム
		//ナズナ:ふらふら吹き飛ばし
		//委員長:単純な範囲攻撃
		//ミルラ:単純な範囲攻撃

		//技師
		//勇者

		//師範:周りぐるぐる
		//狩人:曲射

	}

}