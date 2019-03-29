#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_FACTORY_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_FACTORY_PARAMETERS_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{
namespace skills
{
namespace factory
{

class parameters
{
public:
	parameters(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::server::entities::enemies::difficulty
	);

	sanguis::diff_clock const &
	diff_clock() const;

	sanguis::random_generator &
	random_generator() const;

	sanguis::server::entities::enemies::difficulty
	difficulty() const;
private:
	fcppt::reference<
		sanguis::diff_clock const
	> diff_clock_;

	fcppt::reference<
		sanguis::random_generator
	> random_generator_;

	sanguis::server::entities::enemies::difficulty difficulty_;
};

}
}
}
}
}
}

#endif
