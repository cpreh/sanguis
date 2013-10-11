#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/entities/enemies/enemy_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
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
std::unique_ptr<
	sanguis::server::entities::enemies::enemy
>
unique_ptr;

}
}
}
}

#endif
