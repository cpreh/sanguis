#include "initial.hpp"

sanguis::server::entities::property::initial::initial(
	value_type const base_,
	value_type const current_
)
:
	base_(base_),
	current_(current_)
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
