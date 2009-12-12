#ifndef SANGUIS_DRAW_FACTORY_SIMPLE_SPRITE_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_SIMPLE_SPRITE_HPP_INCLUDED

#include "../environment_fwd.hpp"
#include "../entity.hpp"
#include "../z_ordering.hpp"
#include "../entity_auto_ptr.hpp"
#include "../sprite/client/repetition_type.hpp"
#include <sge/string.hpp>

namespace sanguis
{
namespace draw
{
namespace factory
{

entity_auto_ptr
simple_sprite(
	environment const &,
	entity_id,
	z_ordering::type,
	sge::string const &texture_name,
	sprite::client::repetition_type
);

}
}
}

#endif
