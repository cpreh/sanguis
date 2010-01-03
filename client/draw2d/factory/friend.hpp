#ifndef SANGUIS_DRAW_FACTORY_FRIEND_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_FRIEND_HPP_INCLUDED

#include "../environment_fwd.hpp"
#include "../entity_auto_ptr.hpp"
#include "../../entity_id.hpp"
#include "../../friend_type.hpp" 

namespace sanguis
{
namespace draw
{
namespace factory
{

entity_auto_ptr
friend_(
	environment const &,
	entity_id,
	friend_type::type);

}
}
}

#endif
