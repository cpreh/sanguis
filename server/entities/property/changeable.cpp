#include "changeable.hpp"
#include "initial.hpp"
#include "../../../exception.hpp"
#include <fcppt/text.hpp>
#include <algorithm>

sanguis::server::entities::property::changeable::changeable(
	initial const &initial_
)
:
	base(
		initial_.base()
	),
	current_(
		initial_.current()
	),
	max_(
		initial_.base()
	)
{}

sanguis::server::entities::property::changeable::changeable(
	value_type const base_,
	value_type const current_
)
:
	base(
		base_
	),
	current_(
		current_
	),
	max_(
		base_
	)
{
	check_current();
}

void
sanguis::server::entities::property::changeable::current(
	value_type const ncurrent_
)
{
	value_type const old(
		current()
	);

	current_ = ncurrent_;

	if(
		old != current()
	)
		change_signal_(
			current()
		);

	check_current();
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
	change_callback const &callback_
)
{
	return
		change_signal_.connect(
			callback_
		);
}

fcppt::signal::auto_connection
sanguis::server::entities::property::changeable::register_max_change_callback(
	change_callback const &callback_
)
{
	return
		max_change_signal_.connect(
			callback_
		);
}

void
sanguis::server::entities::property::changeable::on_recalc_max(
	value_type const nmax_
)
{
	max_ = nmax_;

	max_change_signal_(
		max()
	);

	current(
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
		throw exception(
			FCPPT_TEXT("current > max")
		);
}
