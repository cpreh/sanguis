#ifndef SANGUIS_SERVER_NET_ID_FROM_ARGS_HPP_INCLUDED
#define SANGUIS_SERVER_NET_ID_FROM_ARGS_HPP_INCLUDED

#include "../net/id.hpp"
#include <sge/console/arg_list.hpp>

namespace sanguis
{
namespace server
{

net::id
net_id_from_args(
	sge::console::arg_list const &
);

}
}

#endif
