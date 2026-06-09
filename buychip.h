#pragma once

#include<vector>

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace clientlogic
        {
            void BuyChip(long uid, const vector<char> &vecMsgData, GameRoot *root);
        }
    }
}

