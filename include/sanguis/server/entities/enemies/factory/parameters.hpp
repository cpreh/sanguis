#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_PARAMETERS_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/factory/parameters_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{
namespace factory
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	parameters(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::creator::enemy_type,
		sanguis::server::entities::enemies::difficulty,
		sanguis::server::environment::load_context &,
		sanguis::server::entities::spawn_owner const &
	);

	sanguis::diff_clock const &
	diff_clock() const;

	sanguis::random_generator &
	random_generator() const;

	sanguis::creator::enemy_type
	enemy_type() const;

	sanguis::server::entities::enemies::difficulty const
	difficulty() const;

	sanguis::server::environment::load_context &
	load_context() const;

	sanguis::server::entities::spawn_owner const &
	spawn_owner() const;
private:
	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::creator::enemy_type const enemy_type_;

	sanguis::server::entities::enemies::difficulty const difficulty_;

	sanguis::server::environment::load_context &load_context_;

	sanguis::server::entities::spawn_owner const spawn_owner_;
};

}
}
}
}
}

#endif
