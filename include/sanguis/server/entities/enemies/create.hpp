#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_CREATE_HPP_INCLUDED

#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/random_generator_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

entities::unique_ptr
create(
	sanguis::diff_clock const &,
	sanguis::random_generator &,
	enemy_type::type,
	environment::load_context &,
	entities::auto_weak_link spawn
);

}
}
}
}

#endif
