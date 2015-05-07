//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX_TD
{
    using namespace SDX;

    class SceneSkill : public SDX::IScene
    {
    public:
        //@Define
        UI_Button 攻撃 = { 162, {85,6,80,70} , 0.000000,3};
        UI_Button リセット = { 175, {445,442,170,32} , 0.000000,3};
        UI_Frame レベル = { 177, {85,442,170,32} , 0.000000,5};
        UI_Frame 残りポイント = { 178, {265,442,170,32} , 0.000000,5};
        UI_Button 拡散 = { 179, {175,6,80,70} , 0.000000,3};
        UI_Button 防壊 = { 180, {265,6,80,70} , 0.000000,3};
        UI_Button 節約 = { 181, {355,6,80,70} , 0.000000,3};
        UI_Button 対獣 = { 182, {445,6,80,70} , 0.000000,3};
        UI_Button 対闇 = { 183, {535,6,80,70} , 0.000000,3};
        UI_Button 対人 = { 190, {445,86,80,70} , 0.000000,3};
        UI_Button 対竜 = { 191, {535,86,80,70} , 0.000000,3};
        UI_Button 連射 = { 192, {85,86,80,70} , 0.000000,3};
        UI_Button 体力 = { 193, {355,86,80,70} , 0.000000,3};
        UI_Button 麻痺 = { 194, {175,86,80,70} , 0.000000,3};
        UI_Button 回収 = { 195, {265,86,80,70} , 0.000000,3};
        UI_Button 幸運 = { 196, {535,166,80,70} , 0.000000,3};
        UI_Button 射程 = { 197, {85,166,80,70} , 0.000000,3};
        UI_Button 対水 = { 198, {445,166,80,70} , 0.000000,3};
        UI_Button 鈍足 = { 199, {175,166,80,70} , 0.000000,3};
        UI_Button 魔力 = { 200, {355,166,80,70} , 0.000000,3};
        UI_Button 強化 = { 201, {265,166,80,70} , 0.000000,3};
        UI_Button 吹飛 = { 202, {175,246,80,70} , 0.000000,3};
        UI_Button 必殺 = { 203, {355,246,80,70} , 0.000000,3};
        UI_Button 試練 = { 204, {535,246,80,70} , 0.000000,3};
        UI_Button 対樹 = { 205, {445,246,80,70} , 0.000000,3};
        UI_Button 支援 = { 206, {85,246,80,70} , 0.000000,3};
        UI_Button 逆境 = { 207, {265,246,80,70} , 0.000000,3};
        UI_Frame スキル説明 = { 209, {85,324,528,108} , 0.000000,5};
        //@End
        std::string 説明文;

        SceneSkill()
        {
            LoadGUI();
            Init();
        }

        //初期化
        void Init() override
        {
            //@Init
            //@End
        }

        //終了時
        void Final() override
        {
            //@Final
            //@End
        }


        void PushSB(UI_Button &ボタン , SkillType スキル種)
        {
            if (ボタン.rect.Hit(&Input::mouse.GetPoint()) )
            {
                double pt = 0;
                double pt2 = 0;

                if (Witch::スキルLv[スキル種] < 100)
                {
                    //レベル1で2%上昇
                    for (int b = 0; b < Witch::スキルLv[スキル種]; ++b)
                    {
                        //レベル5毎に+補正-0.1%
                        pt += (20 - b / 5);
                    }
                    pt2 = (20 - Witch::スキルLv[スキル種] / 5);
                    pt /= 10;
                    pt2 /= 10;
                }
                else
                {
                    //レベル100で105%上昇
                    //レベル100以降は+0.1%される
                    pt = 105 + (Witch::スキルLv[スキル種] - 100) * 0.1;
                    pt2 = 0.1;
                }

                TDSystem::最大スキルポイント = 100;

                //説明文更新
                switch (スキル種)
                {
                case SkillType::攻撃:説明文 = "攻撃＋\n\nユニットが与えるダメージが上昇する\n\n";break;
                default:
                    説明文 = "";
                    break;
                }

                if (スキル種 != SkillType::試練)
                {
                    説明文 += VariadicStream({ "[Lv ", Witch::スキルLv[スキル種], "] ", pt, "% + ", pt2 ,"%"}).StringS[0];
                }
                else
                {
                    説明文 += VariadicStream({ "[Lv ", Witch::スキルLv[スキル種], "] +", Witch::スキルLv[スキル種], "Wave + 1Wave" }).StringS[0];
                }

                if (!Input::mouse.Left.on){ return; }


                if (Input::mouse.GetPoint().y < ボタン.rect.GetCenter().GetY())
                {
                    //Lv+1
                    if (TDSystem::残りスキルポイント > 0)
                    {
                        Witch::スキルLv[スキル種]++;
                        TDSystem::残りスキルポイント--;
                    }
                }
                else
                {
                    //Lv-1
                    if (Witch::スキルLv[スキル種] > 0)
                    {
                        Witch::スキルLv[スキル種]--;
                        TDSystem::残りスキルポイント++;
                    }
                }
            }
        }

        //更新
        void Update() override
        {
            if(リセット.isClick())
            {
                for (auto &it : Witch::スキルLv)
                {
                    it = 0;
                }
                TDSystem::残りスキルポイント = TDSystem::最大スキルポイント;
            }

            PushSB(攻撃,SkillType::攻撃);
            PushSB(拡散, SkillType::拡散);
            PushSB(防壊, SkillType::防壊);
            PushSB(節約, SkillType::節約);
            PushSB(対獣, SkillType::対獣);
            PushSB(対闇, SkillType::対闇);
            PushSB(対人, SkillType::対人);
            PushSB(対竜, SkillType::対竜);
            PushSB(連射, SkillType::連射);
            PushSB(体力, SkillType::体力);
            PushSB(麻痺, SkillType::麻痺);
            PushSB(回収, SkillType::回収);
            PushSB(幸運, SkillType::幸運);
            PushSB(射程, SkillType::射程);
            PushSB(対水, SkillType::対水);
            PushSB(鈍足, SkillType::鈍足);
            PushSB(魔力, SkillType::魔力);
            PushSB(強化, SkillType::強化);
            PushSB(吹飛, SkillType::吹飛);
            PushSB(必殺, SkillType::必殺);
            PushSB(試練, SkillType::試練);
            PushSB(対樹, SkillType::対樹);
            PushSB(支援, SkillType::支援);
            PushSB(逆境, SkillType::逆境);
            //@End
        }

        //
        void DrawSB(UI_Button &ボタン , const char* 名前 , SkillType スキル種)
        {
            //枠表示
            MSystem::frameS[ボタン.frameNo].Draw(ボタン.rect);
            //スキル名
            MFont::fontS[1].DrawRotate(ボタン.rect.GetCenter() - Point(0,10), 1, 0, Color::Black, 名前);
            //現在レベル
            MFont::fontS[1].DrawRotate(ボタン.rect.GetCenter() + Point(0, 10), 1, 0, Color::Black, { "Lv ", Witch::スキルLv[スキル種] });
            //▲▼マーク
           

        }

        //描画
        void Draw() override
        {
#ifdef _DEBUG			
            if (Input::key.Return.on){ LoadGUI(); }
#endif
            DrawSB(攻撃, "攻撃", SkillType::攻撃);
            DrawSB(拡散, "拡散", SkillType::拡散);
            DrawSB(防壊, "防壊", SkillType::防壊);
            DrawSB(節約, "節約", SkillType::節約);
            DrawSB(対獣, "対獣", SkillType::対獣);
            DrawSB(対闇, "対闇", SkillType::対闇);
            DrawSB(対人, "対人", SkillType::対人);
            DrawSB(対竜, "対竜", SkillType::対竜);
            DrawSB(連射, "連射", SkillType::連射);
            DrawSB(体力, "体力", SkillType::体力);
            DrawSB(麻痺, "麻痺", SkillType::麻痺);
            DrawSB(回収, "回収", SkillType::回収);
            DrawSB(幸運, "幸運", SkillType::幸運);
            DrawSB(射程, "射程", SkillType::射程);
            DrawSB(対水, "対水", SkillType::対水);
            DrawSB(鈍足, "鈍足", SkillType::鈍足);
            DrawSB(魔力, "魔力", SkillType::魔力);
            DrawSB(強化, "強化", SkillType::強化);
            DrawSB(吹飛, "吹飛", SkillType::吹飛);
            DrawSB(必殺, "必殺", SkillType::必殺);
            DrawSB(試練, "試練", SkillType::試練);
            DrawSB(対樹, "対樹", SkillType::対樹);
            DrawSB(支援, "支援", SkillType::支援);
            DrawSB(逆境, "逆境", SkillType::逆境);

            MSystem::frameS[スキル説明.frameNo].Draw(スキル説明.rect);
            MFont::fontS[1].Draw(スキル説明.rect.GetPoint() + Point(10,10), Color::White, 説明文);

            リセット.DrawText(MFont::fontS[2], "Reset" , 2);
            レベル.DrawText(MFont::fontS[2], { "Total ", std::setw(4), TDSystem::最大スキルポイント }, 2);
            残りポイント.DrawText(MFont::fontS[2], { "Rest ", std::setw(5), TDSystem::残りスキルポイント }, 2);
        }

        void LoadGUI() override
        {
#ifndef _DEBUG
            return;
#endif
            //@Load
            SDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , "SceneSkill", GUI_Factory);

            攻撃 = *dynamic_cast<UI_Button*>(guiData.dataS[0].get());
            リセット = *dynamic_cast<UI_Button*>(guiData.dataS[1].get());
            レベル = *dynamic_cast<UI_Frame*>(guiData.dataS[2].get());
            残りポイント = *dynamic_cast<UI_Frame*>(guiData.dataS[3].get());
            拡散 = *dynamic_cast<UI_Button*>(guiData.dataS[4].get());
            防壊 = *dynamic_cast<UI_Button*>(guiData.dataS[5].get());
            節約 = *dynamic_cast<UI_Button*>(guiData.dataS[6].get());
            対獣 = *dynamic_cast<UI_Button*>(guiData.dataS[7].get());
            対闇 = *dynamic_cast<UI_Button*>(guiData.dataS[8].get());
            対人 = *dynamic_cast<UI_Button*>(guiData.dataS[9].get());
            対竜 = *dynamic_cast<UI_Button*>(guiData.dataS[10].get());
            連射 = *dynamic_cast<UI_Button*>(guiData.dataS[11].get());
            体力 = *dynamic_cast<UI_Button*>(guiData.dataS[12].get());
            麻痺 = *dynamic_cast<UI_Button*>(guiData.dataS[13].get());
            回収 = *dynamic_cast<UI_Button*>(guiData.dataS[14].get());
            幸運 = *dynamic_cast<UI_Button*>(guiData.dataS[15].get());
            射程 = *dynamic_cast<UI_Button*>(guiData.dataS[16].get());
            対水 = *dynamic_cast<UI_Button*>(guiData.dataS[17].get());
            鈍足 = *dynamic_cast<UI_Button*>(guiData.dataS[18].get());
            魔力 = *dynamic_cast<UI_Button*>(guiData.dataS[19].get());
            強化 = *dynamic_cast<UI_Button*>(guiData.dataS[20].get());
            吹飛 = *dynamic_cast<UI_Button*>(guiData.dataS[21].get());
            必殺 = *dynamic_cast<UI_Button*>(guiData.dataS[22].get());
            試練 = *dynamic_cast<UI_Button*>(guiData.dataS[23].get());
            対樹 = *dynamic_cast<UI_Button*>(guiData.dataS[24].get());
            支援 = *dynamic_cast<UI_Button*>(guiData.dataS[25].get());
            逆境 = *dynamic_cast<UI_Button*>(guiData.dataS[26].get());
            スキル説明 = *dynamic_cast<UI_Frame*>(guiData.dataS[27].get());
            //@End
        }
    };
}
