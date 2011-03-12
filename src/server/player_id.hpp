#ifndef SANGUIS_SERVER_PLAYER_ID_HPP_INCLUDED
#define SANGUIS_SERVER_PLAYER_ID_HPP_INCLUDED

#include "../net/id_type.hpp"
//#include <fcppt/strong_typedef.hpp>
#include <boost/cstdint.hpp>

namespace sanguis
{
namespace server
{

// TODO: we probably want to map player_ids and entity_ids!

typedef net::id_type player_id;

/*FCPPT_MAKE_STRONG_TYPEDEF(
	net::id_type,//boost::uint32_t,
	player_id
)
*/

}
}

#endif
