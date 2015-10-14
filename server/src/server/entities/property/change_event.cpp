#include <sanguis/server/entities/property/change_event.hpp>
#include <sanguis/server/entities/property/diff.hpp>


sanguis::server::entities::property::change_event::change_event(
	sanguis::server::entities::property::diff const _diff
)
:
	diff_(
		_diff
	)
{
}

sanguis::server::entities::property::diff
sanguis::server::entities::property::change_event::diff() const
{
	return
		diff_;
}
