#include <sanguis/server/entities/property/base.hpp>
#include <sanguis/server/entities/property/change_callback.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/initial.hpp>
#include <sanguis/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/diff.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::property::changeable::changeable(
	sanguis::server::entities::property::initial const &_initial
)
:
	sanguis::server::entities::property::base(
		_initial.base()
	),
	current_(
		_initial.current()
	),
	max_(
		_initial.base()
	),
	change_signal_(),
	max_change_signal_()
{
}

sanguis::server::entities::property::changeable::changeable(
	sanguis::server::entities::property::base::value_type const _base,
	sanguis::server::entities::property::base::value_type const _current
)
:
	base(
		_base
	),
	current_(
		_current
	),
	max_(
		_base
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
	sanguis::server::entities::property::base::value_type const _current
)
{
	sanguis::server::entities::property::base::value_type const old(
		this->current()
	);

	current_ = _current;

	if(
		fcppt::math::diff(
			old,
			this->current()
		)
		>
		static_cast<
			value_type
		>(
			0.001f
		)
	)
		change_signal_(
			this->current()
		);

	this->check_current();
}

sanguis::server::entities::property::changeable::value_type
sanguis::server::entities::property::changeable::current() const
{
	return current_;
}

sanguis::server::entities::property::changeable::value_type
sanguis::server::entities::property::changeable::max() const
{
	return max_;
}

fcppt::signal::auto_connection
sanguis::server::entities::property::changeable::register_change_callback(
	change_callback const &_callback
)
{
	return
		change_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sanguis::server::entities::property::changeable::register_max_change_callback(
	change_callback const &_callback
)
{
	return
		max_change_signal_.connect(
			_callback
		);
}

void
sanguis::server::entities::property::changeable::on_recalc_max(
	sanguis::server::entities::property::base::value_type const _max
)
{
	max_ = _max;

	max_change_signal_(
		max()
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
		current_ > max_
	)
		throw sanguis::exception(
			FCPPT_TEXT("current > max")
		);
}
