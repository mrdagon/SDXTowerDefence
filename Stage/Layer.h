//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "Enemy.h"
#include "Shot.h"

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
				objectS.emplace_back(挿入するObject);
			}
			else{
				suspendS.emplace_back(挿入するObject);
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

	/**静的確保向けのコンテナクラス.*/
	template <class TObject>
	class StaticLayer
	{
	public:
		std::vector<TObject> objectS;
		std::vector<TObject> suspendS;
		
		void Add(const TObject && 追加するオブジェクト , int 待機フレーム = 0)
		{
			if (待機フレーム <= 0)
			{
				objectS.push_back(追加するオブジェクト);
				objectS.back().SetTimer(-待機フレーム);
			}
			else
			{
				suspendS.push_back(追加するオブジェクト);
				suspendS.back().SetTimer(-待機フレーム);
			}

		}

		/**.*/
		void Update()
		{
			auto it = suspendS.begin();

			while (it != suspendS.end())
			{				
				it->SetTimer(it->GetTimer() + 1);
				if (it->GetTimer() >= 0)
				{
					objectS.push_back(*it);
					it = suspendS.erase(it);
					continue;
				}
				++it;
			}

			for (auto && it : objectS)
			{
				it.Update();
			}
		}

		/**.*/
		void Draw() const
		{
			for (auto &&it : objectS)
			{
				it.Draw();
			}
		}

		/**.*/
		void ExeRemove()
		{
			for (auto && it : objectS)
			{
				it.RemoveCheck();
			}

			auto  it = objectS.begin();
			while (it != objectS.end())
			{
				if (it->GetRemoveFlag())
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
				double dist = 比較対象->GetDistance( &it );
				if (dist < nearest || nearest == -1)
				{
					nearest = dist;
					nearObject = &it;
				}
			}

			return nearObject;
		}

		/**.*/
		TObject& operator[](int index)
		{
			return objectS[index];
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

//	/**弾用の共用体.*/
//	class ShotUnion
//	{
//		using S勇者 = Shot < Circle, SpImage, MOTION::勇者 >;
//		using S追尾 = Shot < Circle, SpImage, MOTION::追尾<SPEED::Liner> >;
//		using S直進 = Shot < Circle, SpImage, MOTION::ToFront<SPEED::Liner> >;
//		using S加速 = Shot < Circle, SpImage, MOTION::ToFront<SPEED::AccelLimit> >;
//		using S回転 = Shot < Circle, SpImage, MOTION::回転 >;
//		using S追跡 = Shot < Circle, SpImage, MOTION::追跡 >;
//	public:
//#define U_TYPE(name) mutable S##name s##name; UShot(const S##name &shot , ShotType& type ) : s##name(shot) { type = ShotType::S##name; }
//#define U_DEST(name) case ShotType::S##name : uShot.s##name.~Shot();break;
//#define U_CONST(name) case ShotType::S##name : new(&uShot.s##name) S##name(src.uShot.s##name);break;
//#define U_GET(name) case ShotType::S##name: return &uShot.s##name;
//
//		enum class ShotType
//		{
//			S勇者,
//		} typeNo;
//
//		union UShot
//		{
//		public:
//			U_TYPE(勇者)
//
//				UShot() {}
//			~UShot() {};
//		}uShot;
//
//		void Destoract()
//		{
//			switch (typeNo)
//			{
//				U_DEST(勇者)
//			default:break;
//			}
//		}
//
//		void Constract(const ShotUnion &src)
//		{
//			typeNo = src.typeNo;
//
//			switch (typeNo)
//			{
//				U_CONST(勇者)
//			default:break;
//			}
//		}
//
//		IShot* Get() const
//		{
//			switch (typeNo)
//			{
//				U_GET(勇者)
//			}
//			return nullptr;
//		}
//
//		//以下はunionの型数によらない
//		template< class TShot>
//		ShotUnion(const TShot &shot) : uShot(shot, typeNo) {}
//
//		ShotUnion(const ShotUnion& src)
//		{
//			Constract(src);
//		}
//		ShotUnion& operator=(const ShotUnion& src)
//		{
//			Destoract();
//			Constract(src);
//			return *this;
//		}
//		~ShotUnion() { Destoract(); }
//	};
//
//	/**共用体で違う型を同じコンテナに静的確保用クラス.*/
//	template <class TUnion>
//	class UnionLayer
//	{
//	public:
//		std::vector<TUnion> objectS;
//		std::vector<TUnion> suspendS;
//		
//		template<class TShot>
//		void Add(TShot && 追加する弾, int 待機フレーム = 0)
//		{
//			追加する弾.SetTimer(-待機フレーム);
//
//			if (待機フレーム != 0)
//			{
//				objectS.push_back(追加する弾);
//			}
//			else
//			{
//				suspendS.push_back(追加する弾);
//			}
//		}
//
//		/**.*/
//		void Update()
//		{
//			auto it = suspendS.begin();
//
//			while (it != suspendS.end())
//			{
//
//				it->Get()->SetTimer(it->Get()->GetTimer() + 1);
//				if (it->Get()->GetTimer() >= 0)
//				{
//					objectS.push_back((*it));
//					it = suspendS.erase(it);
//				}
//				++it;
//			}
//
//			for (auto && it : objectS)
//			{
//				const_cast<IShot*>(it.Get())->Update();
//			}
//		}
//		
//		/**.*/
//		void Draw() const
//		{
//			for (auto &&it : objectS)
//			{
//				it.Get()->Draw();
//			}
//		}
//
//		/**.*/
//		void ExeRemove()
//		{
//			for (auto && it : objectS)
//			{
//				it.Get()->RemoveCheck();
//			}
//
//			auto  it = objectS.begin();
//
//			while (it != objectS.end())
//			{
//				if (it->Get()->GetRemoveFlag())
//				{
//					objectS.erase(it);
//				}
//				++it;
//			}
//		}
//
//		/**.*/
//		void Clear()
//		{
//			objectS.clear();
//			suspendS.clear();
//		}
//
//		/**.*/
//		inline int GetCount()
//		{
//			return (int)objectS.size();
//		}
//
//		/**.*/
//		IShot* GetNearest(IObject* 比較対象)
//		{
//			double nearest = -1;
//			IShot* nearObject = nullptr;
//
//			for (auto && it : objectS)
//			{
//				double dist = 比較対象->GetDistance(it.Get());
//				if (dist < nearest || nearest == -1)
//				{
//					nearest = dist;
//					nearObject = it.Get();
//				}
//			}
//
//			return nearObject;
//		}
//
//		/**.*/
//		ShotUnion& operator[](int index)
//		{
//			return objectS[index];
//		}
//
//		/** 範囲for用.*/
//		auto begin() ->decltype(objectS.begin())
//		{
//			return objectS.begin();
//		}
//
//		/** 範囲for用.*/
//		auto end() ->decltype(objectS.end())
//		{
//			return objectS.end();
//		}
//
//		/** 範囲for用.*/
//		auto begin() const ->decltype(objectS.begin())
//		{
//			return objectS.begin();
//		}
//
//		/** 範囲for用.*/
//		auto end() const ->decltype(objectS.end())
//		{
//			return objectS.end();
//		}
//	};
//
}