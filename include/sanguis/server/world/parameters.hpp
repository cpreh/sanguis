#ifndef SANGUIS_SERVER_WORLD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_PARAMETERS_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/context_fwd.hpp>
#include <sanguis/server/world/parameters_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace world
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
		sanguis::server::world::context &,
		sanguis::server::environment::load_context &
	);

	sanguis::diff_clock const &
	diff_clock() const;

	sanguis::random_generator &
	random_generator() const;

	sanguis::server::world::context &
	context() const;

	sanguis::server::environment::load_context &
	load_context() const;
private:
	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::server::world::context &context_;

	sanguis::server::environment::load_context &load_context_;
};

}
}
}

#endif
