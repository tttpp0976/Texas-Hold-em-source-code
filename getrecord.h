#pragma once

#include<vector>

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace clientlogic
        {
            void GetRecord(long uid, const vector<char> &vecMsgData, GameRoot *root);
            void CollectRecord(long uid, const vector<char> &vecMsgData, GameRoot *root);
        }
    }
}

