#ifndef SANGUIS_SERVER_WEAPONS_COMMON_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_COMMON_PARAMETERS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/weapons/log_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class common_parameters
{
	FCPPT_NONASSIGNABLE(
		common_parameters
	);
public:
	common_parameters(
		sanguis::server::weapons::log const &,
		sanguis::random_generator &
	);

	sanguis::server::weapons::log const &
	log() const;

	sanguis::random_generator &
	random_generator() const;
private:
	sanguis::server::weapons::log const &log_;

	sanguis::random_generator &random_generator_;
};

}
}
}

#endif
