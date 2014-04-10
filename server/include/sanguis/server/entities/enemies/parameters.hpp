#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_PARAMETERS_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/regeneration.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/auras/unique_ptr.hpp>
#include <sanguis/server/damage/armor_array.hpp>
#include <sanguis/server/damage/armor_unit.hpp>
#include <sanguis/server/damage/type_fwd.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

class parameters
{
	FCPPT_NONCOPYABLE(
		parameters
	);
public:
	parameters(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::creator::enemy_type,
		sanguis::server::environment::load_context &,
		sanguis::server::damage::armor_array const &,
		sanguis::server::health,
		sanguis::server::entities::movement_speed,
		sanguis::server::ai::create_function const &,
		sanguis::server::weapons::unique_ptr &&,
		sanguis::server::pickup_probability,
		sanguis::server::exp,
		sanguis::server::entities::enemies::difficulty,
		sanguis::server::entities::spawn_owner const &,
		sanguis::server::auras::container &&
	);

	parameters(
		parameters &&
	);

	parameters &
	operator=(
		parameters &&
	) = delete;

	~parameters();

	sanguis::diff_clock const &
	diff_clock() const;

	sanguis::random_generator &
	random_generator() const;

	sanguis::creator::enemy_type
	enemy_type() const;

	sanguis::server::environment::load_context &
	load_context() const;

	sanguis::server::damage::armor_array const &
	armor() const;

	sanguis::server::health const
	health() const;

	sanguis::server::regeneration const
	regeneration() const;

	sanguis::server::entities::movement_speed const
	movement_speed() const;

	sanguis::server::ai::create_function const &
	ai_create_function() const;

	sanguis::server::weapons::unique_ptr &
	weapon();

	sanguis::server::pickup_probability const
	pickup_probability() const;

	sanguis::server::exp const
	exp() const;

	sanguis::server::entities::enemies::difficulty const
	difficulty() const;

	sanguis::server::entities::spawn_owner const &
	spawn_owner() const;

	sanguis::server::auras::container &
	auras();

	sanguis::server::weapons::ias const
	ias() const;

	sanguis::server::weapons::irs const
	irs() const;

	sanguis::server::entities::enemies::parameters &
	health(
		sanguis::server::health
	);

	sanguis::server::entities::enemies::parameters &
	regeneration(
		sanguis::server::regeneration
	);

	sanguis::server::entities::enemies::parameters &
	movement_speed(
		sanguis::server::entities::movement_speed
	);

	sanguis::server::entities::enemies::parameters &
	pickup_probability(
		sanguis::server::pickup_probability
	);

	sanguis::server::entities::enemies::parameters &
	exp(
		sanguis::server::exp
	);

	sanguis::server::entities::enemies::parameters &
	difficulty(
		sanguis::server::entities::enemies::difficulty
	);

	sanguis::server::entities::enemies::parameters &
	ias(
		sanguis::server::weapons::ias
	);

	sanguis::server::entities::enemies::parameters &
	irs(
		sanguis::server::weapons::irs
	);

	sanguis::server::entities::enemies::parameters &
	add_aura(
		sanguis::server::auras::unique_ptr &&
	);

	sanguis::server::entities::enemies::parameters &
	armor_element(
		sanguis::server::damage::type,
		sanguis::server::damage::armor_unit
	);
private:
	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::creator::enemy_type const enemy_type_;

	sanguis::server::environment::load_context &load_context_;

	sanguis::server::damage::armor_array armor_;

	sanguis::server::health health_;

	sanguis::server::regeneration regeneration_;

	sanguis::server::entities::movement_speed movement_speed_;

	sanguis::server::ai::create_function ai_create_function_;

	sanguis::server::weapons::unique_ptr weapon_;

	sanguis::server::pickup_probability pickup_probability_;

	sanguis::server::exp exp_;

	sanguis::server::entities::enemies::difficulty difficulty_;

	sanguis::server::entities::spawn_owner const spawn_owner_;

	sanguis::server::auras::container auras_;

	sanguis::server::weapons::ias ias_;

	sanguis::server::weapons::irs irs_;
};

}
}
}
}

#endif
