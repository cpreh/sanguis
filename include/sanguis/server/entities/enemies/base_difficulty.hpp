#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_BASE_DIFFICULTY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_BASE_DIFFICULTY_HPP_INCLUDED

#include <sanguis/creator/enemy_type_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty_value.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

sanguis::server::entities::enemies::difficulty_value
base_difficulty(
	sanguis::creator::enemy_type
);

}
}
}
}

#endif
