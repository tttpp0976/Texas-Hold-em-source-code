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

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace clientlogic
        {
            void TuoGuan(long uid, const vector<char> &vecMsgData, GameRoot *root)
            {
                __TRY__

                using namespace RoomSo;
                using namespace context;
                using namespace process;
                using namespace message;
                using namespace config;
                using namespace RoomSo;

                //解码
                XGameDZProto::NN_msg2csTuoGuan nncm = pbToObj<XGameDZProto::NN_msg2csTuoGuan>(vecMsgData);

                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey()<<", "<<"sit" << ", uid: " << uid << ", tuoguan:" << nncm.btuoguan());

                XGameDZProto::NN_msg2cTuoGuan tmm;
                tmm.set_iret(0);

                User *user = root->con->getUserByUid(uid);
                if(user != NULL)
                {
                    if(nncm.btuoguan() ==  user->isTuoGuan())
                    {
                        tmm.set_iret(-1);
                    }
                    else
                    {
                        user->setTuoGuan(nncm.btuoguan());

                        if(!nncm.btuoguan())
                        {
                            user->setTimeOut(0);
                        }
                        tmm.set_btuoguan(nncm.btuoguan());
                        tmm.set_cid(user->getCid());
                    }
                }
                else
                {
                    tmm.set_iret(-2);
                }
                sendAllClientMessage<XGameDZProto::NN_msg2cTuoGuan>(XGameDZProto::NN_msg2cTuoGuan_E, tmm, root);
                __CATCH__
            }
        }
    }
}
