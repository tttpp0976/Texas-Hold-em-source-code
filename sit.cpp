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
            void sit(long uid, const vector<char> &vecMsgData, GameRoot *root)
            {
                __TRY__

                using namespace message;
                using namespace RoomSo;

                XGameDZProto::NN_msg2sSit nncm = pbToObj<XGameDZProto::NN_msg2sSit>(vecMsgData);

                DLOG_TRACE("clientlogic roomid:" << root->roomid() << ", uid:" << uid << ", sit:" << logPb(nncm));

                TGAME_Sit tmm;
                tmm.lPlayerID = uid;                    // 玩家ID
                tmm.iChairID = nncm.ichairid();         // 座位号
                tmm.lTakeCoin = nncm.ltakecoin();       // 当前代入
                tmm.sLongitude = nncm.longitude();      // 经度
                tmm.sLatitude = nncm.latitude();        // 纬度
                tmm.bHoldSeat = nncm.bholdseat();       // 是否占座

                // 下面都是没用的
                tmm.lClubID = nncm.lclubid();                   // 俱乐部ID
                tmm.bAutoSit = nncm.bautosit();                 // 自动找座位
                tmm.bAutoSupplement = nncm.bautosupplement();   // 自动补充
                tmm.bMaxTakenIn = nncm.bmaxtakenin();           // 当前最大代入
                tmm.bAutoAlignment = nncm.bautoalignment();     // 自动补齐

                sendRoomMessage<TGAME_Sit>(TGAME_Sit_E, tmm, root);

                __CATCH__
            }
        }
    }
}
