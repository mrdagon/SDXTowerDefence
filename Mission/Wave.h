//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Material.h"

namespace SDX_TD
{
	using namespace SDX;
	class Wave
	{
	private:

	public:
		bool isStop = true;//Wave進行停止
		int 現在Wave;
		int 待ち時間;
		int 最終Wave;
		int Wave間隔;

		EnemyType 敵種類[MAX_WAVE];
		bool isBoss[MAX_WAVE];

		void Init()
		{
			isStop = true;

			現在Wave = 0;
			待ち時間 = 0;
			Wave間隔 = StageDataS[TDSystem::選択ステージ].Wave間隔;

			if (TDSystem::isトライアル)
			{
				最終Wave = TrialDataS[TDSystem::難易度].Wave数;
			}
			else
			{
				最終Wave = LimitlessDataS[TDSystem::難易度].Wave数;
			}

			for (int a = 0; a < MAX_WAVE; ++a)
			{
				敵種類[a] = StageDataS[TDSystem::選択ステージ].敵種類[a];
				isBoss[a] = StageDataS[TDSystem::選択ステージ].isBoss[a];
			}

		}

		/**Wave時間経過判定.*/
		bool Check()
		{
			if (isStop || 最終Wave == 現在Wave) return false;

			待ち時間--;

			if (待ち時間 <= 0)
			{
				待ち時間 = Wave間隔;
				return true;
			}

			return false;
		}

		void Draw()
		{
			int no = 現在Wave - 1;
			int x = -2;
			int y = 待ち時間 * 80 / Wave間隔;

			if (no == -1)
			{
				no = 0;
			}
			else
			{
				y -= 80;
			}

			while (true)
			{
				if (isBoss[no % 100])
				{
					MSystem::フレーム[4].Draw({ x, y, 40, 80 });
					MUnit::敵[敵種類[no % 100]][1]->DrawRotate({ x + 20, y + 50 }, 2, 0);
				}
				else
				{
					MSystem::フレーム[4].Draw({ x, y, 40, 80 });
					MUnit::敵[敵種類[no % 100]][1]->Draw({ x + 4, y + 36 });
					MUnit::敵[敵種類[no % 100]][1]->Draw({ x + 4 + 16, y + 36 });
					MUnit::敵[敵種類[no % 100]][1]->Draw({ x + 4 + 8, y + 36 + 8 });
				}
				//Wave数
				int size = 2;
				if (no >= 100){ size = 1; }

				MFont::BMP黒.DrawExtend({ x , y + 4 }, size, size, Color::White, { std::setw(3), no + 1 });

				y += 80;
				++no;

				if (y > 480 || no >= 最終Wave) break;
			}
		}

		void DrawInfo()
		{
		}
	};
}