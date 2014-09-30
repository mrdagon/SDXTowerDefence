//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_TD
{
    using namespace SDX;
    class IObject;

    //メニュー項目を配置
    class IMenu : public IScene
    {
    public:
        //ボタンやエフェクトの追加
        /**.*/
        virtual void Add(IObject* 追加するオブジェクト, int 待機時間 = 0) = 0;

        /**.*/
        virtual void AddFront(IObject* 追加するオブジェクト, int 待機時間 = 0) = 0;

        /**.*/
        virtual void AddBack(IObject* 追加するオブジェクト, int 待機時間 = 0) = 0;
    };

    /**唯一のアクティブなMenu.*/
    namespace{ IMenu* SMenu; }
}