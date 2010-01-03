#ifndef SANGUIS_DRAW_FACTORY_CLIENT_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_CLIENT_HPP_INCLUDED

#include "../environment_fwd.hpp"
#include "../entity_auto_ptr.hpp"
#include "../../client_messages/add_fwd.hpp"
#include <sge/renderer/screen_size.hpp>

namespace sanguis
{
namespace draw
{
namespace factory
{

entity_auto_ptr
client(
	environment const &,
	client_messages::add const &,
	sge::renderer::screen_size const &
);
}
}
}

#endif