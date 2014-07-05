#pragma once//☀SDXFramework
#include "Framework\IModel.h"
#include "EnumType.h"

namespace SDX_TD
{
    /**Objectのインターフェース.*/
    class IObject
    {
    public:
    /**消滅判定を行う.*/
        virtual bool RemoveCheck() = 0;
    public:
        /**毎フレームの更新処理.*/
        virtual void Update() = 0;

        /**経過フレームを取得.*/
        virtual int& timer() = 0;

        /**死亡フラグの取得.*/
        virtual bool& IsRemove() = 0;

        /**選択フラグの取得.*/
        virtual bool& IsSelect() = 0;

        /**所属レイヤーを取得.*/
        virtual Belong& BelongLayer() = 0;

        /**Stage右枠のの説明を表示.*/
        virtual void DrawInfo() = 0;

        /**Update時の追加処理.*/
        virtual void Act() = 0;

        /**消滅時の追加処理.*/
        virtual void Remove() = 0;
    };

}