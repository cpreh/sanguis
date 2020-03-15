#include <sanguis/server/entities/property/base.hpp>
#include <sanguis/server/entities/property/change_callback.hpp>
#include <sanguis/server/entities/property/change_event.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/diff.hpp>
#include <sanguis/server/entities/property/initial.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <cmath>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::property::changeable::changeable(
	sanguis::server::entities::property::initial const &_initial
)
:
	sanguis::server::entities::property::base(
		_initial.get_base()
	),
	current_(
		_initial.get_current()
	),
	max_(
		_initial.get_base()
	),
	change_signal_(),
	max_change_signal_()
{
	this->check_current();
}

sanguis::server::entities::property::changeable::~changeable()
{
}

void
sanguis::server::entities::property::changeable::current(
	sanguis::server::entities::property::value const _current
)
{
	sanguis::server::entities::property::diff const diff(
		_current
		-
		this->current()
	);

	current_ = _current;

	this->check_current();

	if(
		std::abs(
			diff.get()
		)
		>
		fcppt::literal<
			sanguis::server::entities::property::value
		>(
			0.001
		)
	)
		change_signal_(
			sanguis::server::entities::property::change_event(
				diff
			)
		);
}

sanguis::server::entities::property::value
sanguis::server::entities::property::changeable::current() const
{
	return
		current_;
}

sanguis::server::entities::property::value
sanguis::server::entities::property::changeable::max() const
{
	return
		max_;
}

fcppt::signal::auto_connection
sanguis::server::entities::property::changeable::register_change_callback(
	sanguis::server::entities::property::change_callback &&_callback
)
{
	return
		change_signal_.connect(
			std::move(
				_callback
			)
		);
}

fcppt::signal::auto_connection
sanguis::server::entities::property::changeable::register_max_change_callback(
	sanguis::server::entities::property::change_callback &&_callback
)
{
	return
		max_change_signal_.connect(
			std::move(
				_callback
			)
		);
}

void
sanguis::server::entities::property::changeable::on_recalc_max(
	sanguis::server::entities::property::value const _max
)
{
	sanguis::server::entities::property::diff const diff(
		_max
		-
		max_
	);

	max_ =
		_max;

	max_change_signal_(
		sanguis::server::entities::property::change_event(
			diff
		)
	);

	this->current(
		std::min(
			current_,
			max_
		)
	);
}

void
sanguis::server::entities::property::changeable::check_current()
{
	if(
		current_
		>
		max_
	)
		current_ =
			max_;
}
