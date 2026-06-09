#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "logic/clientlogic/core/prolong.h"
#include "utils/tarslog.h"
#include "context/context.h"
#include "dz.pb.h"
#include "CommonCode.pb.h"
#include "process/process.h"
#include "message/sendclientmessage.h"
#include "message/sendroommessage.h"
#include "logic/gamelogic/core/endtimer.h"
#include "logic/gamelogic/core/begintimer.h"
#include "logic/gamelogic/core/paoma.h"
#include "config/gameconfig.h"
#include "logic/gamelogic/core/defer.h"

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace clientlogic
        {
            void PaomaApplyAct(long uid, const vector<char> &vecMsgData, GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                using namespace context;
                using namespace message;
                using namespace RoomSo;
                using namespace gamelogic;

                XGameDZProto::NN_msg2sPaomaApply nncm = pbToObj<XGameDZProto::NN_msg2sPaomaApply>(vecMsgData);

                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey()<<", "<<"PaomaApply"<<", uid: "<<uid<<", count: " << nncm.icount());

                int count = nncm.icount();

                if (uid != root->con->getPaomaApplyUID())
                {
                    return;
                }

                // 已分胜负
                if (root->con->getWinCid() != nil_cid)
                {
                    return;
                }

                PaomaApply(root, uid, count);

                __CATCH__
                PERFSTATS_EXIT();
            }

            void PaomaAnswerAct(long uid, const vector<char> &vecMsgData, GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                using namespace context;
                using namespace message;
                using namespace RoomSo;
                using namespace gamelogic;

                XGameDZProto::NN_msg2sPaomaAnswer nncm = pbToObj<XGameDZProto::NN_msg2sPaomaAnswer>(vecMsgData);

                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey()<<", "<<"PaomaAnswer"<<", uid: "<<uid<<", agree: " << nncm.agree());

                // 已分胜负
                if (root->con->getWinCid() != nil_cid)
                {
                    return;
                }

                int agree = nncm.agree();
                PaomaAnswer(root, uid, agree);

                __CATCH__
                PERFSTATS_EXIT();
            }
        }
    }
}
