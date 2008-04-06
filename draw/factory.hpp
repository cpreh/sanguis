#ifndef SANGUIS_DRAW_FACTORY_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_HPP_INCLUDED

#include "entity.hpp"
#include "../entity_id.hpp"
#include "../entity_type.hpp"
#include <sge/renderer/types.hpp>
#include <memory>

namespace sanguis
{
namespace draw
{
namespace factory
{

typedef std::auto_ptr<entity> entity_ptr;
entity_ptr create_entity(
	entity_id,
	entity_type::type);

}
}
}

#endif
