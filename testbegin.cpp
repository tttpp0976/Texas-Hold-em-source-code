#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "logic/clientlogic/core/testbegin.h"
#include "utils/tarslog.h"
#include "context/context.h"
#include "config/gameconfig.h"
#include "process/process.h"
#include "message/sendclientmessage.h"
#include "message/sendroommessage.h"
#include "logic/gamelogic/core/endtimer.h"
#include "logic/gamelogic/core/checkbegin.h"

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace clientlogic
        {
            void TestBegin(long uid, const vector<char> &vecMsgData, GameRoot *root)
            {
                __TRY__

                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey()<<", "<<"TestBegin" << ", uid: " << uid << ", roomid:" << root->roomid());

                using namespace context;
                using namespace process;
                using namespace message;
                using namespace gamelogic;
                using namespace config;

                //不是初始状态
                if (root->pro->getProcess() != nil_nnstate)
                {
                    DLOG_TRACE("roomkey:" << root->cfg->getRoomKey()<<", "<<"process is not nil_nnstate, uid: " << uid << ", process: " << root->pro->getProcess());
                    return;
                }

                //带入的货币通知
                XGameDZProto::NN_msg2sTestBegin nncm;
                std::map<cid_t, User> const &usermap = root->con->getUserMap();
                for (auto it = usermap.begin(); it != usermap.end(); it++)
                {
                    (*nncm.mutable_mdzwealth())[it->first] = it->second.getDZWealth();
                }

                //开始通知
                sendAllClientMessage<XGameDZProto::NN_msg2sTestBegin>(XGameDZProto::NN_msg2cTestBegin_E, nncm, root);

                //检查游戏开始
                //玩家离开状态不用检查游戏开始
                User *user = root->con->getUserByUid(uid);
                if (user != NULL && !user->isLeft())
                {
                    CheckBegin(root);
                }

                __CATCH__
            }
        }
    }
}
