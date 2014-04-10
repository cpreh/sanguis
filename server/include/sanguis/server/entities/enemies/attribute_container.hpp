#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_ATTRIBUTE_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_ATTRIBUTE_CONTAINER_HPP_INCLUDED

#include <sanguis/server/entities/enemies/attribute.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

typedef
std::vector<
	sanguis::server::entities::enemies::attribute
>
attribute_container;

}
}
}
}

#endif
