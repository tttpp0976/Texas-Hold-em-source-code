#include "common/macros.h"
#include "gameroot.h"
#include "utils/tarslog.h"
#include "message/sendclientmessage.h"
#include "message/sendroommessage.h"

namespace game
{
    namespace logic
    {
        namespace clientlogic
        {
            void stand(long uid, const vector<char> &vecMsgData, GameRoot *root)
            {
                __TRY__

                DLOG_TRACE("clientlogic roomid:" << root->roomid() <<", uid:" << uid << ", stand");

                using namespace message;
                using namespace RoomSo;

                TGAME_Stand tmm;
                tmm.lPlayerID = uid;
                tmm.iType = 0;
                tmm.bBuyIn = false;

                sendRoomMessage<TGAME_Stand>(TGAME_Stand_E, tmm, root);

                __CATCH__
            }
        }
    }
}