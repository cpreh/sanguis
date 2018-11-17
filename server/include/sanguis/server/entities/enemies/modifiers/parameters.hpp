#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_PARAMETERS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/modifiers/parameters_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{
namespace modifiers
{

class parameters
{
public:
	explicit
	parameters(
		sanguis::random_generator &
	);

	sanguis::random_generator &
	random_generator() const;
private:
	fcppt::reference<
		sanguis::random_generator
	> random_generator_;
};

}
}
}
}
}

#endif
