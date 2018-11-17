#ifndef SANGUIS_SERVER_WORLD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_PARAMETERS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <sanguis/server/world/context_fwd.hpp>
#include <sanguis/server/world/parameters_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/context_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

class parameters
{
public:
	parameters(
		fcppt::log::context &,
		sanguis::random_generator &,
		sanguis::server::weapons::common_parameters const &,
		sanguis::server::world::context &,
		sanguis::server::environment::load_context &
	);

	fcppt::log::context &
	log_context() const;

	sanguis::random_generator &
	random_generator() const;

	sanguis::server::weapons::common_parameters const &
	weapon_parameters() const;

	sanguis::server::world::context &
	context() const;

	sanguis::server::environment::load_context &
	load_context() const;
private:
	fcppt::reference<
		fcppt::log::context
	> log_context_;

	fcppt::reference<
		sanguis::random_generator
	> random_generator_;

	sanguis::server::weapons::common_parameters weapon_parameters_;

	fcppt::reference<
		sanguis::server::world::context
	> context_;

	fcppt::reference<
		sanguis::server::environment::load_context
	> load_context_;
};

}
}
}

#endif
