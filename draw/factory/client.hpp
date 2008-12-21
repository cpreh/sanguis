#ifndef SANGUIS_DRAW_FACTORY_CLIENT_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_CLIENT_HPP_INCLUDED

#include "types.hpp"
#include "../types.hpp"
#include "../../client_messages/fwd.hpp"
#include <sge/renderer/screen_types.hpp>

namespace sanguis
{
namespace load
{
class context;
}
namespace draw
{
namespace factory
{

entity_ptr
client(
	load::context const &,
	client_messages::add const &,
	system &,
	sge::renderer::screen_size_t const &);
}
}
}

#endif
