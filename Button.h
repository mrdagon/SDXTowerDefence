#pragma once//☀Unicode
#include "Object.h"
#include "IStage.h"

namespace SDX_TD
{
    using namespace SDX;

    class Button : public Object
    {
        private:
            std::function<void()> 押下時の処理 = nullptr;
        public:
            void PushCheck()
            {
                if ( Hit(&Point(Input::mouse.x, Input::mouse.y)) )
                {
                    SStage->selected = this;
                    if (押下時の処理 != nullptr) 押下時の処理();
                    Pushed();
                }
            }

            /**ボタンが押された時の派生クラスでの共通処理.*/
            virtual void Pushed(){}

    };
}