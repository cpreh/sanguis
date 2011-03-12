#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_CLIENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_CLIENT_HPP_INCLUDED

#include "../entities/auto_ptr.hpp"
#include "../sprite/client/system.hpp"
#include "../../entity_type.hpp"
#include "../../../load/resource/textures_fwd.hpp"
#include <sge/renderer/screen_size.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

entities::auto_ptr
client(
	sprite::client::system &,
	load::resource::textures const &,
	entity_type::type,	
	sge::renderer::screen_size const &
);

}
}
}
}

#endif