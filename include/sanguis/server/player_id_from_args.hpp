#ifndef SANGUIS_SERVER_PLAYER_ID_FROM_ARGS_HPP_INCLUDED
#define SANGUIS_SERVER_PLAYER_ID_FROM_ARGS_HPP_INCLUDED

#include <sanguis/server/player_id.hpp>
#include <sge/console/arg_list.hpp>

namespace sanguis
{
namespace server
{

server::player_id const
player_id_from_args(
	sge::console::arg_list const &
);

}
}

#endif
