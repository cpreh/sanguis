#ifndef SANGUIS_SERVER_PLAYER_ID_HPP_INCLUDED
#define SANGUIS_SERVER_PLAYER_ID_HPP_INCLUDED

#include <fcppt/strong_typedef.hpp>
#include <boost/cstdint.hpp>

namespace sanguis
{
namespace server
{

FCPPT_MAKE_STRONG_TYPEDEF(
	boost::uint32_t,
	player_id
);

}
}

#endif
