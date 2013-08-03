#ifndef SANGUIS_SERVER_WEAPONS_STATES_RELOADING_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_RELOADING_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/states/reloading_parameters_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace states
{

class reloading_parameters
{
	FCPPT_NONASSIGNABLE(
		reloading_parameters
	);
public:
	explicit
	reloading_parameters(
		sanguis::server::weapons::irs
	);

	sanguis::server::weapons::irs const
	irs() const;
private:
	sanguis::server::weapons::irs const irs_;
};

}
}
}
}

#endif
