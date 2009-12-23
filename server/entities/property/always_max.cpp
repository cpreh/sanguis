#include "always_max.hpp"

sanguis::server::entities::property::always_max::always_max(
	value_type const base_
)
:
	base(
		base_
	),
	current_(base_)
{}

sanguis::server::entities::property::always_max::value_type
sanguis::server::entities::property::always_max::current() const
{
	return current_;
}

fcppt::signal::auto_connection
sanguis::server::entities::property::always_max::register_change_callback(
	change_callback const &callback_
)
{
	return
		change_signal_.connect(
			callback_
		);
}

void
sanguis::server::entities::property::always_max::on_recalc_max(
	value_type const max_
)
{
	current_ = max_;

	change_signal_(
		current()
	);
}
