#ifndef SANGUIS_SERVER_PLAYER_ID_HPP_INCLUDED
#define SANGUIS_SERVER_PLAYER_ID_HPP_INCLUDED

#include "../net/id_type.hpp"

namespace sanguis
{
namespace server
{

// TODO: we probably want to map player_ids to net::id_types in the server
typedef net::id_type player_id;

}
}

#endif
