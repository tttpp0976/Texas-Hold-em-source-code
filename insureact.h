#pragma once

#include<vector>

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace clientlogic
        {
            void InsureActHehe(long uid, const vector<char> &vecMsgData, GameRoot *root);

            void InsureAct(long uid, const vector<char> &vecMsgData, GameRoot *root);
        }
    }
}