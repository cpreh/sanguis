#ifndef SANGUIS_DRAW_FACTORY_CLIENT_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_CLIENT_HPP_INCLUDED

#include "../entity_auto_ptr.hpp"
#include "../../client_messages/fwd.hpp"
#include <sge/renderer/screen_size_t.hpp>

namespace sanguis
{
namespace draw
{
class environment;
namespace factory
{

entity_auto_ptr
client(
	environment const &,
	client_messages::add const &,
	sge::renderer::screen_size_t const &);
}
}
}

#endif
