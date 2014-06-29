#pragma once//☀Unicode
#include "TDSystem.h"

namespace SDX_TD
{
    using namespace SDX;
    /**魔女.*/
    namespace Witch
    {

    class Witch
    {
    public:
        WitchType 種類;
        WitchData 基礎ステ;//レベル上昇や大魔法発動補正前のステータス
        WitchData 実ステ;//レベル上昇や強化アイテム、大魔法発動補正後のステータス

        //固定パラメータ
        Element 属性;
        UnitType 魔法タイプ[12];

        //変動パラメータ
        double MP = 1000;
        double SP;
        int    レベル;
        int    経験値;
        int    大魔法残り時間;
        int    被ダメージ;

        //戦闘開始時の初期化処理
        void Init(){};

        //大魔法発動時の性能計算、効果処理
        virtual void 大魔法発動() = 0;

        /**通常時の性能計算.*/
        /**MP等は初期化しない*/
        void 実ステ計算()
        {
            //アイテムや成長あり
            if ( !TDSystem::isトライアル)
            {
                レベル補正();
                アイテム補正();
            }
        }

        //レベルによる補正計算
        virtual void レベル補正() = 0;

        //アイテムによる補正計算
        void アイテム補正(){};

    };

    class ライナ : public Witch
    {
    public:
        ライナ()
        {
            種類 = WitchType::ライナ;
            属性 = Element::炎;

            基礎ステ.攻撃補正 = 1.05;//やや強い
            基礎ステ.連射補正 = 1.05;//やや強い
            基礎ステ.範囲補正 = 1.0;
            基礎ステ.射程補正 = 1.0;
            基礎ステ.支援補正 = 1.0;
            基礎ステ.弾速補正 = 1.0;

            基礎ステ.MP消費 = 1.0;
            基礎ステ.回収率 = 0.7;
            基礎ステ.回収速度 = 1.0;
            基礎ステ.強化速度 = 1.0;

            基礎ステ.弱点補正 = 1.1;
            基礎ステ.特殊補正[DebuffType::吹飛] = 1.0;
            基礎ステ.特殊補正[DebuffType::防壊] = 1.0;
            基礎ステ.特殊補正[DebuffType::麻痺] = 1.0;
            基礎ステ.特殊補正[DebuffType::鈍足] = 1.0;

            基礎ステ.大魔法時間 = 3000;
            基礎ステ.必要SP = 1.0;
            基礎ステ.逆境補正 = 0.02;//通常の2倍

            基礎ステ.初期HP = 20;
            基礎ステ.初期MP = 50;

            基礎ステ.詠唱回数補正 = 1.0;

            魔法タイプ[0] = UnitType::踊り子;
            魔法タイプ[1] = UnitType::踊り子;
            魔法タイプ[2] = UnitType::踊り子;
            魔法タイプ[3] = UnitType::踊り子;
            魔法タイプ[4] = UnitType::踊り子;
            魔法タイプ[5] = UnitType::踊り子;
            魔法タイプ[6] = UnitType::踊り子;
            魔法タイプ[7] = UnitType::踊り子;
            魔法タイプ[8] = UnitType::踊り子;
            魔法タイプ[9] = UnitType::踊り子;
            魔法タイプ[10] = UnitType::踊り子;
            魔法タイプ[11] = UnitType::踊り子;
        }

        void 大魔法発動() override
        {}

        void レベル補正() override
        {}
        
    };

    class ディアネラ : public Witch
    {
    public:
        ディアネラ()
        {
            種類 = WitchType::ディアネラ;
            属性 = Element::空;

            基礎ステ.攻撃補正 = 1.0;//普通
            基礎ステ.連射補正 = 1.0;
            基礎ステ.範囲補正 = 1.0;
            基礎ステ.射程補正 = 1.0;
            基礎ステ.支援補正 = 1.0;
            基礎ステ.弾速補正 = 1.0;

            基礎ステ.MP消費 = 0.9;//10%OFF
            基礎ステ.回収率 = 0.7;
            基礎ステ.回収速度 = 1.0;
            基礎ステ.強化速度 = 1.0;

            基礎ステ.弱点補正 = 1.1;
            基礎ステ.特殊補正[DebuffType::吹飛] = 1.0;
            基礎ステ.特殊補正[DebuffType::防壊] = 1.0;
            基礎ステ.特殊補正[DebuffType::麻痺] = 1.0;
            基礎ステ.特殊補正[DebuffType::鈍足] = 1.0;

            基礎ステ.大魔法時間 = 3000;
            基礎ステ.必要SP = 1.0;
            基礎ステ.逆境補正 = 0.01;

            基礎ステ.初期HP = 20;
            基礎ステ.初期MP = 50;

            基礎ステ.詠唱回数補正 = 1.0;

            魔法タイプ[0] = UnitType::ディアネラ;
            魔法タイプ[1] = UnitType::兵士;//A
            魔法タイプ[2] = UnitType::技師;
            魔法タイプ[3] = UnitType::斧士;
            魔法タイプ[4] = UnitType::魔術師;
            魔法タイプ[5] = UnitType::執事;
            魔法タイプ[6] = UnitType::騎士;//B
            魔法タイプ[7] = UnitType::闘士;
            魔法タイプ[8] = UnitType::司祭;
            魔法タイプ[9] = UnitType::くノ一;
            魔法タイプ[10] = UnitType::将軍;
            魔法タイプ[11] = UnitType::踊り子;//None
        }

        void 大魔法発動() override
        {}

        void レベル補正() override
        {}
        
    };

    class バロゥ : public Witch
    {
    public:
        バロゥ()
        {
            種類 = WitchType::バロゥ;
            属性 = Element::空;

            基礎ステ.攻撃補正 = 0.7;//低い
            基礎ステ.連射補正 = 1.5;//早い
            基礎ステ.範囲補正 = 1.0;
            基礎ステ.射程補正 = 1.0;
            基礎ステ.支援補正 = 1.0;
            基礎ステ.弾速補正 = 1.0;

            基礎ステ.MP消費 = 1.0;
            基礎ステ.回収率 = 0.7;
            基礎ステ.回収速度 = 1.0;
            基礎ステ.強化速度 = 1.0;

            基礎ステ.弱点補正 = 1.1;
            基礎ステ.特殊補正[DebuffType::吹飛] = 1.0;
            基礎ステ.特殊補正[DebuffType::防壊] = 1.0;
            基礎ステ.特殊補正[DebuffType::麻痺] = 1.0;
            基礎ステ.特殊補正[DebuffType::鈍足] = 1.0;

            基礎ステ.大魔法時間 = 3000;
            基礎ステ.必要SP = 1.0;
            基礎ステ.逆境補正 = 0.01;

            基礎ステ.初期HP = 20;
            基礎ステ.初期MP = 50;

            基礎ステ.詠唱回数補正 = 1.0;

            魔法タイプ[0] = UnitType::バロゥ;
            魔法タイプ[1] = UnitType::足軽;//A
            魔法タイプ[2] = UnitType::狩人;
            魔法タイプ[3] = UnitType::剣士;
            魔法タイプ[4] = UnitType::盗賊;
            魔法タイプ[5] = UnitType::踊り子;
            魔法タイプ[6] = UnitType::射手;//B
            魔法タイプ[7] = UnitType::剣豪;
            魔法タイプ[8] = UnitType::勇者;
            魔法タイプ[9] = UnitType::賢者;
            魔法タイプ[10] = UnitType::給仕;
            魔法タイプ[11] = UnitType::料理人;
        }

        void 大魔法発動() override
        {}

        void レベル補正() override
        {}
        
    };


    }

    namespace
    {
        Witch::Witch* MainWitch;//現在アクティブなウィッチ
        Witch::Witch* SubWitch;//控えのウィッチ
    }

}