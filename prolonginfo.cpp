#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "logic/clientlogic/core/prolonginfo.h"
#include "utils/tarslog.h"
#include "context/context.h"
#include "dz.pb.h"
#include "process/process.h"
#include "message/sendclientmessage.h"
#include "message/sendroommessage.h"
#include "logic/gamelogic/core/endtimer.h"
#include "logic/gamelogic/core/begintimer.h"
#include "config/gameconfig.h"

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace clientlogic
        {
            void ProlongInfo(long uid, const vector<char> &vecMsgData, GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                using namespace context;
                using namespace message;
                using namespace RoomSo;

                //DLOG_TRACE("roomkey:" << root->cfg->getRoomKey()<<", "<<"NN_msg2csProlongInfo_E" << ", lPlayerID: " << uid);

                User *user = root->con->getUserByUid(uid);
                if (user == NULL)
                {
                    DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", " << "get user error, userid: " << uid);
                    return;
                }

                XGameDZProto::NN_msg2cPrologInfoRsp nncn;
                nncn.set_iret(0);
                int maxTimes = root->con->getProlongTimes(uid);
                nncn.set_ifree(maxTimes == 0 ? 0 : 1);
                nncn.set_iremaintimes(user->getProlongFlag() == 1 ? 0 : 1);
                sendClientMessage<XGameDZProto::NN_msg2cPrologInfoRsp>(uid, XGameDZProto::NN_msg2csProlongInfo_E, nncn, root);

                __CATCH__
                PERFSTATS_EXIT();
            }
        }
    }
}
