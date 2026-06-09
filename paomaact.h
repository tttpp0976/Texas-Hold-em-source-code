#pragma once

#include<vector>

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace clientlogic
        {
            void PaomaApplyAct(long uid, const vector<char> &vecMsgData, GameRoot *root);
            void PaomaAnswerAct(long uid, const vector<char> &vecMsgData, GameRoot *root);
        }
    }
}