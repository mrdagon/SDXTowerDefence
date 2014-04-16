#pragma once//☀Unicode

namespace SDX_TD
{
    using namespace SDX;
    class Object;

    //メニュー項目を配置
    class IMenu : public IScene
    {
    public:
        //ボタンやエフェクトの追加
        /**.*/
        virtual void Add(Object *追加するオブジェクト, int 待機時間 = 0) = 0;

        /**.*/
        virtual void AddFront(Object *追加するオブジェクト, int 待機時間 = 0) = 0;

        /**.*/
        virtual void AddBack(Object *追加するオブジェクト, int 待機時間 = 0) = 0;
    };

    /**唯一のアクティブなMenu.*/
    namespace{ IMenu* SMenu; }
}