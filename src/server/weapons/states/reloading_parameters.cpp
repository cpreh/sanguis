#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/states/reloading_parameters.hpp>


sanguis::server::weapons::states::reloading_parameters::reloading_parameters(
	sanguis::server::weapons::irs const _irs
)
:
	irs_(
		_irs
	)
{
}

sanguis::server::weapons::irs const
sanguis::server::weapons::states::reloading_parameters::irs() const
{
	return irs_;
}
