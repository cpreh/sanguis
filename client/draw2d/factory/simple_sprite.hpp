#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_SIMPLE_SPRITE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_SIMPLE_SPRITE_HPP_INCLUDED

#include "../environment_fwd.hpp"
#include "../entity.hpp"
#include "../z_ordering.hpp"
#include "../entity_auto_ptr.hpp"
#include "../sprite/client/repetition_type.hpp"
#include <fcppt/string.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

entity_auto_ptr
simple_sprite(
	environment const &,
	entity_id,
	z_ordering::type,
	fcppt::string const &texture_name,
	sprite::client::repetition_type
);

}
}
}
}

#endif
