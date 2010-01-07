#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_SIMPLE_SPRITE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_SIMPLE_SPRITE_HPP_INCLUDED

#include "../entities/auto_ptr.hpp"
#include "../sprite/client/repetition_type.hpp"
#include "../sprite/client/system.hpp"
#include "../z_ordering.hpp"
#include "../../../load/resource/textures_fwd.hpp"
#include <fcppt/string.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

entities::auto_ptr
simple_sprite(
	sprite::client::system &,
	load::resource::textures const &,
	z_ordering::type,
	fcppt::string const &texture_name,
	sprite::client::repetition_type
);

}
}
}
}

#endif
