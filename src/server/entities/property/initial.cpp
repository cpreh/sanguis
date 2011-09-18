#include <sanguis/server/entities/property/initial.hpp>

sanguis::server::entities::property::initial::initial(
	value_type const _base,
	value_type const _current
)
:
	base_(_base),
	current_(_current)
{}

sanguis::server::entities::property::initial::value_type
sanguis::server::entities::property::initial::base() const
{
	return base_;
}

sanguis::server::entities::property::initial::value_type
sanguis::server::entities::property::initial::current() const
{
	return current_;
}
