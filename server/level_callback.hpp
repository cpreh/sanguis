#ifndef SANGUIS_SERVER_LEVEL_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_LEVEL_CALLBACK_HPP_INCLUDED

#include "level_type.hpp"
#include "entities/player_fwd.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef sge::function::object<
	void (entities::player &, level_type)
> level_callback;

}
}

#endif
