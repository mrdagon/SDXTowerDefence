//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#include "DataType.h"

namespace SDX_TD
{
    using namespace SDX;
    class IUnit;

    namespace TDSystem
    {
        Difficulty 難易度;
        StageData* 現在ステージ;
        bool isトライアル;
        bool isシングル;

        bool is魔法選択 = false;
        bool is一覧選択 = false;
        bool is敵選択 = false;

        std::vector<std::unique_ptr<IUnit>> 魔法リスト;
        EnumArray<int,UnitType> 詠唱回数;

        int Hp = 20;
        int 素材数[4];

        //実績関連

        //設定関連
        double 効果音の音量;
        double BGMの音量;
        bool isグリッド;
        bool isHPゲージ;
        bool isエフェクト;

        static void SaveAndLoad( FileMode 読み込みor書込)
        {

        }

    }
}