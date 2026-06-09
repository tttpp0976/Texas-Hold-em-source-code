#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "logic/clientlogic/core/guesshdcard.h"
#include "utils/tarslog.h"
#include "context/context.h"
#include "dz.pb.h"
#include "process/process.h"
#include "message/sendclientmessage.h"
#include "logic/gamelogic/core/endtimer.h"
#include "logic/gamelogic/core/begintimer.h"


using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace clientlogic
        {
            void GuessHdCard(long uid, const vector<char> &vecMsgData, GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                //DLOG_TRACE("roomkey:" << root->cfg->getRoomKey()<<", "<<"GuessHdCard" << ", uid: " << uid);

                using namespace context;
                using namespace message;

                User *user = root->con->getUserByUid(uid);
                if (user == NULL)
                {
                    //DLOG_TRACE("roomkey:" << root->cfg->getRoomKey()<<", "<<"get user error, userid: " << uid);
                    return;
                }

                XGameDZProto::NN_msg2csGuessHdCard nncm = pbToObj<XGameDZProto::NN_msg2csGuessHdCard>(vecMsgData);
                if (nncm.lguessnum() > 0)
                {
                    return;
                }

                user->setGuessNum(nncm.lguessnum());
                user->setGuessType(nncm.iguesstype());

                __CATCH__
                PERFSTATS_EXIT();
            }
        }
    }
}
