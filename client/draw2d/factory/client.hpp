#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_CLIENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_CLIENT_HPP_INCLUDED

#include "../entities/auto_ptr.hpp"
#include "../sprite/client/system.hpp"
#include "../../entity_type.hpp"
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
	sprite::client::system &client_system_,
	load::resource::textures const &textures_,
	entity_type::type,	
	sge::renderer::screen_size const &
);

}
}
}
}

#endif
