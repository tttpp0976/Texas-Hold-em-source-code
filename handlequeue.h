
#pragma once

#include<vector>

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace clientlogic
        {
            void HandleQueue(int eMSG, long uid, const vector<char> &vecMsgData, GameRoot *root);
        }
    }
}

