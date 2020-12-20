#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/mass.hpp>
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
#include <fcppt/reference_impl.hpp>


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
		sanguis::creator::enemy_type,
		sanguis::server::environment::load_context &, // NOLINT(google-runtime-references)
		sanguis::server::damage::armor_array const &,
		sanguis::server::mass,
		sanguis::server::health,
		sanguis::server::entities::movement_speed,
		sanguis::server::ai::create_function &&,
		sanguis::server::weapons::unique_ptr &&,
		sanguis::server::pickup_probability,
		sanguis::server::exp,
		sanguis::server::entities::enemies::difficulty,
		sanguis::server::entities::spawn_owner,
		sanguis::server::auras::container &&
	);

	parameters(
		parameters &&
	)
	noexcept;

	parameters &
	operator=(
		parameters &&
	)
	noexcept;

	~parameters();

	[[nodiscard]]
	sanguis::creator::enemy_type
	enemy_type() const;

	[[nodiscard]]
	sanguis::server::environment::load_context &
	load_context() const;

	[[nodiscard]]
	sanguis::server::damage::armor_array const &
	armor() const;

	[[nodiscard]]
	sanguis::server::mass
	mass() const;

	[[nodiscard]]
	sanguis::server::health
	health() const;

	[[nodiscard]]
	sanguis::server::regeneration
	regeneration() const;

	[[nodiscard]]
	sanguis::server::entities::movement_speed
	movement_speed() const;

	[[nodiscard]]
	sanguis::server::ai::create_function const &
	ai_create_function() const;

	[[nodiscard]]
	sanguis::server::weapons::unique_ptr &
	weapon();

	[[nodiscard]]
	sanguis::server::pickup_probability
	pickup_probability() const;

	[[nodiscard]]
	sanguis::server::exp
	exp() const;

	[[nodiscard]]
	sanguis::server::entities::enemies::difficulty
	difficulty() const;

	[[nodiscard]]
	sanguis::server::entities::spawn_owner const &
	spawn_owner() const;

	[[nodiscard]]
	sanguis::server::auras::container &
	auras();

	[[nodiscard]]
	sanguis::server::weapons::ias
	ias() const;

	[[nodiscard]]
	sanguis::server::weapons::irs
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

	sanguis::server::entities::enemies::parameters &
	ai(
		sanguis::server::ai::create_function const &
	);
private:
	sanguis::creator::enemy_type enemy_type_;

	fcppt::reference<
		sanguis::server::environment::load_context
	> load_context_;

	sanguis::server::damage::armor_array armor_;

	sanguis::server::mass mass_;

	sanguis::server::health health_;

	sanguis::server::regeneration regeneration_;

	sanguis::server::entities::movement_speed movement_speed_;

	sanguis::server::ai::create_function ai_create_function_;

	sanguis::server::weapons::unique_ptr weapon_;

	sanguis::server::pickup_probability pickup_probability_;

	sanguis::server::exp exp_;

	sanguis::server::entities::enemies::difficulty difficulty_;

	sanguis::server::entities::spawn_owner spawn_owner_;

	sanguis::server::auras::container auras_;

	sanguis::server::weapons::ias ias_;

	sanguis::server::weapons::irs irs_;
};

}
}
}
}

#endif
