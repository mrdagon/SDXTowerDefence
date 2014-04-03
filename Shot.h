#pragma    once//☀Unicode
#include    "Object.h"

namespace    SDX
{
class    Shot    :    public    Object
{
public:
                bool    is貫通    =    false;
                bool    isSmall    =    true;//20×20以下のサイズ
                int        属性;
                std::unique_ptr<ISpeed>    速度;

                Shot(int    X座標,    int    Y座標    ,    double    角度    ,    double    攻撃力):
                                Object(new    Rect(X座標,Y座標,10,10),nullptr,Belong::Shot,攻撃力),
                                速度(new    Speed::Liner(2))
                {
                                SetAngle(角度);
                }

                //消滅判定
                virtual    bool    RemoveCheck()
                {
                                const    double    x    =    GetX();
                                const    double    y    =    GetY();

                                if    (x    <    -10    ||    x    >    490    ||    y    <    -10    ||    y    >    490)    isRemove    =    true;

                                return    isRemove;
                }

                //デバッグ用描画処理
                void    Draw()    const
                {
                                shape->Draw(Color::Yellow    ,    255);
                }

                //相手にダメージを与える処理
                virtual    void    Damaged(double    被ダメージ)
                {
                                if(    !is貫通    )
                                {
                                                this->isRemove    =    true;
                                }
                                React();
                }

                //衝突した時の特殊処理
                virtual    void    React()    {};

                //毎フレームの処理
                virtual    void    Act()
                {
                                if    (速度)
                                {
                                                MoveFront(速度->Ease());
                                }
                }
};
}