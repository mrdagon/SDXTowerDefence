#pragma once//☀Unicode
#include <SDXFrameWork.h>
#include <Framework/ModelMove.h>
#include "RouteMap.h"
#include "EnumType.h"

namespace SDX_TD
{
    using namespace SDX;
    /**.*/
    template <class T> class Layer;
    class Object : public Model, public ModelMove , private BanCopy
    {

        template<class T> friend class Layer;

    protected:
        int timer = 0;///発生してから経過したフレーム数
        int lifeTime = -1;///生存期間
        Belong belong;///所属するレイヤー

        /**消滅判定を行う.*/
        virtual bool RemoveCheck()
        {
            if (timer == lifeTime)
            {
                isRemove = true;
            }

            if (isRemove) Remove();

            return isRemove;
        }

        /**経過フレームをセット.*/
        void SetTimer(int フレーム数)
        {
            timer = フレーム数;
        }

    public:
        bool    isSelect = false;

        /**.*/
        Object(Shape *当たり判定 = nullptr, Sprite *デフォルトスプライト = nullptr, Belong 所属 = Belong::その他) :
            Model(当たり判定, デフォルトスプライト),
            ModelMove(this),
            belong(所属)
        {}

        /**.*/
        virtual ~Object(){}

        /**経過フレームを取得.*/
        int GetTimer()
        {
            return timer;
        }

        /**毎フレームの更新処理.*/
        virtual void Update()
        {
            this->timer++;
            AnimeUpdate();
            this->Act();
        }

        /**.*/
        Belong GetBelong()
        {
            return belong;
        }

        /**Stage右枠のの説明を表示.*/
        virtual void DrawInfo(){}

        /**Update時の追加処理.*/
        virtual void Act(){}

        /**消滅時の追加処理.*/
        virtual void Remove(){}

        /**ダメージ処理.*/
        virtual void Damaged(Object* 衝突相手){}
    };
}
