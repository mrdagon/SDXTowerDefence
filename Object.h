#pragma once//☀Unicode
#include <SDXFrameWork.h>
#include "RouteMap.h"
#include "EnumType.h"
#include "IObject.h"

namespace SDX_TD
{
    using namespace SDX;
    /**.*/
    template <class TShape = Point , class TSprite = SpImage>
    class Object : public Model<TShape,TSprite> , public IObject
    {
    protected:
        int lifeTime = -1;///生存期間

        int timer = 0;///発生してから経過したフレーム数
        Belong belong;///所属するレイヤー
        bool isSelect = false;
        bool isRemove = false;

        /**消滅判定を行う.*/
        bool RemoveCheck() override
        {
            if (timer == lifeTime)
            {
                isRemove = true;
            }

            if (isRemove) Remove();

            return isRemove;
        }

    public:
        /**.*/
        Object(const TShape &当たり判定 , const TSprite &デフォルトスプライト , Belong 所属 = Belong::その他) :
            Model<TShape,TSprite>(当たり判定, デフォルトスプライト),
            belong(所属)
        {}

        /**.*/
        virtual ~Object(){}

        /**毎フレームの更新処理.*/
        void Update()
        {
            this->timer++;
            AnimeUpdate();
            this->Act();
        }

        bool& IsRemove()
        {
            return isRemove();
        }

        bool& IsSelect()
        {
            return isSelect;
        }

        /**経過フレームを取得.*/
        int& Timer()
        {
            return timer;
        }

        /**所属レイヤーを返す.*/
        Belong& BelongLayer()
        {
            return belong;
        }

        /**Stage右枠のの説明を表示.*/
        void DrawInfo() override{}

        /**Update時の追加処理.*/
        void Act() override{}

        /**消滅時の追加処理.*/
        void Remove() override{}
    };
}
