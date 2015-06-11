//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include <SDXFramework.h>
#include <Framework/IScene.h>

namespace SDX_TD
{
	using namespace SDX;
	class IObject;
	class IEnemy;
	class IUnit;
	class IShot;
	class Wave;
	class Land;
	class Unit;
	class Enemy;

	/**.*/
	class IStage : public IScene
	{
	public:
		IObject* selected = nullptr;//選択中のオブジェクト
		Enemy* selectEnemy = nullptr;//選択中の敵
		Unit* selectUnit = nullptr;//選択中の魔法
		Land land;//
		bool isReplay;
		int score;

		/**敵や魔法が消滅する前に呼び出す.*/
		void ResetSelect(IObject* 消滅するオブジェクト)
		{
			if (selected == 消滅するオブジェクト )
			{
				selected = nullptr;
				selectUnit = nullptr;
				selectEnemy = nullptr;
			}
		}

		virtual void ResetJobList() = 0;
		virtual void Add(IObject *追加するオブジェクト, int 待機時間 = 0) = 0;
		virtual void Add(const Unit &追加するオブジェクト, int 待機時間 = 0) = 0;
		virtual void Add(Enemy *追加するオブジェクト, int 待機時間 = 0) = 0;
		virtual void Add(IShot *追加するオブジェクト, int 待機時間 = 0) = 0;
		virtual void AddFront(IObject* 追加するオブジェクト, int 待機時間 = 0) = 0;
		virtual void AddBack(IObject* 追加するオブジェクト, int 待機時間 = 0) = 0;
		virtual Enemy* GetNearEnemy(const IPosition* 比較対象, bool is地上, bool is空中) = 0;
		virtual Enemy* GetNearEnemyCloss(const IPosition* 比較対象, bool is地上, bool is空中 , int 幅 , double 射程) = 0;
		virtual int GetClossDistance(const IPosition* 対象A, const IPosition* 対象B, int 幅, double 射程) = 0;

		virtual void Support() = 0;
		virtual int GetWave() = 0;

		virtual void 大魔法効果(bool is発動) = 0;

		virtual void SaveReplay(ResultType 結果 , double スコア) = 0;
	};

	/**アクティブなStage.*/
	namespace
	{
		IStage* SStage;
	}
}