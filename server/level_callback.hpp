#ifndef SANGUIS_SERVER_LEVEL_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_LEVEL_CALLBACK_HPP_INCLUDED

#include "leveL_type.hpp"
#include "entities/player_fwd.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{

typedef boost::function<
	void (entities::player &, level_type)
> level_callback;

}
}

#endif
