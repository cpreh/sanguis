#ifndef SANGUIS_DRAW_CLIENT_FACTORY_HPP_INCLUDED
#define SANGUIS_DRAW_CLIENT_FACTORY_HPP_INCLUDED

#include "entity.hpp"
#include "../client_messages/fwd.hpp"
#include <sge/renderer/types.hpp>
#include <memory>

namespace sanguis
{
namespace draw
{
namespace client_factory
{

typedef std::auto_ptr<entity> entity_ptr;
entity_ptr create_entity(
	const client_messages::add &,
	const sge::renderer::screen_size_t &);
}
}
}

#endif
