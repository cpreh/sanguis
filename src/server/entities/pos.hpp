#ifndef SANGUIS_SERVER_ENTITIES_POS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_POS_HPP_INCLUDED

#include "../center.hpp"
#include "../dim.hpp"
#include "../pos.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

server::pos const
pos(
	server::center const &,
	server::dim const &
);

}
}
}

#endif
