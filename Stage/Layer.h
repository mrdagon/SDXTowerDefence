//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"

namespace SDX_TD
{
	using namespace SDX;
	/**Objectのコンテナクラス.*/
	template <class TObject>
	class Layer
	{
	public:
		std::vector<std::shared_ptr<TObject>> objectS;
		std::vector<std::shared_ptr<TObject>> suspendS;

		/**.*/
		void Add(TObject *挿入するObject, int 待機フレーム数 = 0)
		{
			挿入するObject->SetTimer(-待機フレーム数);

			if (挿入するObject->GetTimer() >= 0)
			{
				this->objectS.push_back(std::shared_ptr<TObject>(挿入するObject));
			}
			else{
				this->suspendS.push_back(std::shared_ptr<TObject>(挿入するObject));
			}
		}

		/**.*/
		void Update()
		{
			auto it = suspendS.begin();

			while (it != suspendS.end())
			{
				(*it)->SetTimer((*it)->GetTimer() + 1);
				if ((*it)->GetTimer() >= 0)
				{
					objectS.push_back((*it));
					it = suspendS.erase(it);
					continue;
				}
				++it;
			}

			for (auto && it : objectS)
			{
				it->Update();
			}
		}

		/**.*/
		void Draw() const
		{
			for (auto &&it : objectS)
			{
				it->Draw();
			}
		}

		/**.*/
		void ExeRemove()
		{
			for (auto && it : objectS)
			{
				it->RemoveCheck();
			}

			auto  it = objectS.begin();
			while (it != objectS.end())
			{
				if ((*it)->GetRemoveFlag())
				{
					it = objectS.erase(it);
				}
				else
				{
					++it;
				}
			}
		}

		/**.*/
		void Clear()
		{
			objectS.clear();
			suspendS.clear();
		}

		/**.*/
		inline int GetCount()
		{
			return (int)objectS.size();
		}

		/**.*/
		TObject* GetNearest(IObject* 比較対象)
		{
			double   nearest = -1;
			TObject* nearObject = nullptr;

			for (auto it : objectS)
			{
				double dist = 比較対象->GetDistance(it.get());
				if (dist < nearest || nearest == -1)
				{
					nearest = dist;
					nearObject = it.get();
				}
			}

			return nearObject;
		}

		/**.*/
		TObject* operator[](int index)
		{
			return objectS[index].get();
		}

		/** 範囲for用.*/
		auto begin() ->decltype(objectS.begin())
		{
			return objectS.begin();
		}

		/** 範囲for用.*/
		auto end() ->decltype(objectS.end())
		{
			return objectS.end();
		}

		/** 範囲for用.*/
		auto begin() const ->decltype(objectS.begin())
		{
			return objectS.begin();
		}

		/** 範囲for用.*/
		auto end() const ->decltype(objectS.end())
		{
			return objectS.end();
		}


	};
}