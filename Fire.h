#pragma once//©SDXFramework http://sourceforge.jp/projects/dxframework/
#include "IStage.h"
#include "Shot.h"
namespace SDX_TD
{
/**発射方法のポリシー.*/
namespace FIRE
{
    /**前方に単発弾.*/
    class Normal
    {
        void Fire(double 角度)
        {
            //SStage->Add(MakeShot(角度));
        }
    };
}

}