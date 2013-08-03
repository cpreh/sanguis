#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/states/castpoint_parameters.hpp>


sanguis::server::weapons::states::castpoint_parameters::castpoint_parameters(
	sanguis::server::weapons::ias const _ias
)
:
	ias_(
		_ias
	)
{
}

sanguis::server::weapons::ias const
sanguis::server::weapons::states::castpoint_parameters::ias() const
{
	return ias_;
}
