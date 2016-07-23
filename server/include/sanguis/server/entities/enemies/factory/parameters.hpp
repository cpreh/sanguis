#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_PARAMETERS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/entities/enemies/factory/parameters_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
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
		sanguis::random_generator &,
		sanguis::server::weapons::common_parameters const &,
		sanguis::creator::enemy_type,
		sanguis::creator::enemy_kind,
		sanguis::server::entities::enemies::difficulty,
		sanguis::server::environment::load_context &,
		sanguis::server::entities::spawn_owner const &,
		sanguis::server::entities::enemies::special_chance
	);

	sanguis::random_generator &
	random_generator() const;

	sanguis::server::weapons::common_parameters const &
	weapon_parameters() const;

	sanguis::creator::enemy_type
	enemy_type() const;

	sanguis::creator::enemy_kind
	enemy_kind() const;

	sanguis::server::entities::enemies::difficulty
	difficulty() const;

	sanguis::server::environment::load_context &
	load_context() const;

	sanguis::server::entities::spawn_owner const &
	spawn_owner() const;

	sanguis::server::entities::enemies::special_chance
	special_chance() const;
private:
	sanguis::random_generator &random_generator_;

	sanguis::server::weapons::common_parameters const weapon_parameters_;

	sanguis::creator::enemy_type const enemy_type_;

	sanguis::creator::enemy_kind const enemy_kind_;

	sanguis::server::entities::enemies::difficulty const difficulty_;

	sanguis::server::environment::load_context &load_context_;

	sanguis::server::entities::spawn_owner const spawn_owner_;

	sanguis::server::entities::enemies::special_chance const special_chance_;
};

}
}
}
}
}

#endif
