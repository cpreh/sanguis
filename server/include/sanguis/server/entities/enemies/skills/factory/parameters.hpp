#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_FACTORY_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_FACTORY_PARAMETERS_HPP_INCLUDED

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters_fwd.hpp>


namespace sanguis::server::entities::enemies::skills::factory
{

class parameters
{
public:
	parameters(
		sanguis::diff_clock_cref,
		sanguis::random_generator_ref,
		sanguis::server::entities::enemies::difficulty
	);

	[[nodiscard]]
	sanguis::diff_clock const &
	diff_clock() const;

	[[nodiscard]]
	sanguis::random_generator &
	random_generator() const;

	[[nodiscard]]
	sanguis::server::entities::enemies::difficulty
	difficulty() const;
private:
	sanguis::diff_clock_cref diff_clock_;

	sanguis::random_generator_ref random_generator_;

	sanguis::server::entities::enemies::difficulty difficulty_;
};

}

#endif
