#include <sanguis/server/entities/property/always_max.hpp>

sanguis::server::entities::property::always_max::always_max(
	value_type const _base
)
:
	base(
		_base
	),
	current_(_base)
{}

sanguis::server::entities::property::always_max::value_type
sanguis::server::entities::property::always_max::current() const
{
	return current_;
}

fcppt::signal::auto_connection
sanguis::server::entities::property::always_max::register_change_callback(
	change_callback const &_callback
)
{
	return
		change_signal_.connect(
			_callback
		);
}

void
sanguis::server::entities::property::always_max::on_recalc_max(
	value_type const _max
)
{
	current_ = _max;

	change_signal_(
		current()
	);
}
