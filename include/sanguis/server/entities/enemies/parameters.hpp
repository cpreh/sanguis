#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_PARAMETERS_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>
#include <sanguis/server/entities/enemies/spawn_owner.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
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
		sanguis::creator::enemy_type,
		sanguis::server::environment::load_context &,
		sanguis::server::damage::armor const &,
		sanguis::server::health,
		sanguis::server::entities::movement_speed,
		sanguis::server::ai::create_function const &,
		sanguis::server::weapons::unique_ptr &&,
		sanguis::server::pickup_probability,
		sanguis::server::exp,
		sanguis::server::entities::enemies::difficulty,
		sanguis::server::entities::enemies::spawn_owner const &,
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

	sanguis::creator::enemy_type
	enemy_type() const;

	sanguis::server::environment::load_context &
	load_context() const;

	sanguis::server::damage::armor const &
	armor() const;

	sanguis::server::health const
	health() const;

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

	sanguis::server::entities::enemies::spawn_owner const &
	spawn_owner() const;

	sanguis::server::auras::container &
	auras();

	void
	health(
		sanguis::server::health
	);
private:
	sanguis::diff_clock const &diff_clock_;

	sanguis::creator::enemy_type const enemy_type_;

	sanguis::server::environment::load_context &load_context_;

	sanguis::server::damage::armor const armor_;

	sanguis::server::health health_;

	sanguis::server::entities::movement_speed const movement_speed_;

	sanguis::server::ai::create_function ai_create_function_;

	sanguis::server::weapons::unique_ptr weapon_;

	sanguis::server::pickup_probability const pickup_probability_;

	sanguis::server::exp const exp_;

	sanguis::server::entities::enemies::difficulty const difficulty_;

	sanguis::server::entities::enemies::spawn_owner const spawn_owner_;

	sanguis::server::auras::container auras_;
};

}
}
}
}

#endif
