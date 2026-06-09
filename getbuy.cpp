#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "logic/clientlogic/core/getbuy.h"
#include "utils/tarslog.h"
#include "context/context.h"
#include "dz.pb.h"
#include "process/process.h"
#include "message/sendclientmessage.h"
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
            void GetBuy(long uid, const vector<char> &vecMsgData, GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", " << "GetBuy" << ", uid: " << uid);

                using namespace context;
                using namespace message;
                using namespace config;

                User *user = root->con->getUserByUid(uid);
                User *tuser = root->con->getUserByUidTail(uid);
                if (user == NULL && tuser == NULL)
                {
                    //DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", " << "get user error, userid: " << uid);
                    return;
                }
                //

                XGameDZProto::NN_msg2sGetBuy nncn;

                long dzwealth = 0;
                long maxtakenin = 0;
                long wealth = 0;
                if(tuser && tuser->getCid() > 0)
                {
                    DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", cid:" << tuser->getCid() << ", dz wealth: "<< dzwealth);
                    dzwealth = tuser->getDZWealth();
                    maxtakenin = root->cfg->getMaxGold();
                    wealth = root->cfg->getDalao() == 3 ? tuser->getClubCoin() : tuser->getWealth();

                    nncn.set_lwealth(wealth);
                    nncn.set_lmaxbuynum(maxtakenin > dzwealth + tuser->getBuyChip() ? maxtakenin - dzwealth - tuser->getBuyChip() : 0);
                    (*nncn.mutable_sbuychip()).set_lbuynum(tuser->getBuyChip());
                }
                else if(user)
                {
                    dzwealth = user->getDZWealth();
                    maxtakenin = root->cfg->getMaxGold();
                    wealth = root->cfg->getDalao() == 3 ? user->getClubCoin() : user->getWealth();

                    nncn.set_lwealth(wealth);
                    nncn.set_lmaxbuynum(maxtakenin > dzwealth + user->getBuyChip() ? maxtakenin - dzwealth - user->getBuyChip() : 0);
                    (*nncn.mutable_sbuychip()).set_lbuynum(user->getBuyChip());
                }

                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << "wealth: "<< wealth << ", MaxTakeCoin:" << maxtakenin << ", dz wealth: "<< dzwealth);

                /**
                XGameDZProto::NN_msg2sGetBuy nncn;
                nncn.set_lwealth(wealth);
                nncn.set_lmaxbuynum(maxtakenin > dzwealth + user->getBuyChip() ? maxtakenin - dzwealth - user->getBuyChip() : 0);
                (*nncn.mutable_sbuychip()).set_lbuynum(user->getBuyChip());
                **/
                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", " << "GetBuy" << ", nncn: " << logPb(nncn));
                sendClientMessage<XGameDZProto::NN_msg2sGetBuy>(uid, XGameDZProto::NN_msg2csGetBuy_E, nncn, root);

                __CATCH__
                PERFSTATS_EXIT();
            }
        }
    }
}
