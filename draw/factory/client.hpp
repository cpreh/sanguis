#ifndef SANGUIS_DRAW_FACTORY_CLIENT_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_CLIENT_HPP_INCLUDED

#include "types.hpp"
#include "../types.hpp"
#include "../../client_messages/fwd.hpp"
#include <sge/renderer/types.hpp>

namespace sanguis
{
namespace draw
{
namespace factory
{

entity_ptr client(
	client_messages::add const &,
	system &,
	sge::renderer::screen_size_t const &);
}
}
}

#endif
