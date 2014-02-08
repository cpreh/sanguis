#ifndef SANGUIS_SERVER_EXP_TO_NET_HPP_INCLUDED
#define SANGUIS_SERVER_EXP_TO_NET_HPP_INCLUDED

#include <sanguis/messages/types/exp.hpp>
#include <sanguis/server/exp.hpp>


namespace sanguis
{
namespace server
{

sanguis::messages::types::exp
exp_to_net(
	sanguis::server::exp
);

}
}

#endif
