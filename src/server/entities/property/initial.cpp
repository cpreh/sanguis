#include <sanguis/server/entities/property/initial.hpp>
#include <sanguis/server/entities/property/value.hpp>


sanguis::server::entities::property::initial::initial(
	sanguis::server::entities::property::initial::base const _base,
	sanguis::server::entities::property::initial::current const _current
)
:
	base_(
		_base.get()
	),
	current_(
		_current.get()
	)
{
}

sanguis::server::entities::property::value
sanguis::server::entities::property::initial::get_base() const
{
	return base_;
}

sanguis::server::entities::property::value
sanguis::server::entities::property::initial::get_current() const
{
	return current_;
}
