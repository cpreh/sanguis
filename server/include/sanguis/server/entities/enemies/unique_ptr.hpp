#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/entities/enemies/enemy_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

typedef
fcppt::unique_ptr<
	sanguis::server::entities::enemies::enemy
>
unique_ptr;

}
}
}
}

#endif
