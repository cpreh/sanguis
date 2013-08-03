#ifndef SANGUIS_SERVER_WEAPONS_STATES_BACKSWING_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_BACKSWING_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/states/backswing_parameters_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace states
{

class backswing_parameters
{
	FCPPT_NONASSIGNABLE(
		backswing_parameters
	);
public:
	explicit
	backswing_parameters(
		sanguis::server::weapons::ias
	);

	sanguis::server::weapons::ias const
	ias() const;
private:
	sanguis::server::weapons::ias const ias_;
};

}
}
}
}

#endif
