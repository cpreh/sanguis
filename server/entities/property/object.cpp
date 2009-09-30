#include "object.hpp"
#include "initial.hpp"
#include <algorithm>

sanguis::server::entities::property::object::object(
	initial const &initial_
)
:
	base_(initial_.base()),
	current_(initial_.current())
{}

sanguis::server::entities::property::object::object(
	value_type const base_,
	value_type const current_
)
:
	base_(base_),
	current_(current_),
	max_(base_)
{
	clamp_current();
}

sanguis::server::entities::property::object::constant_type const
sanguis::server::entities::property::object::constant()
{
	return constant_;
}

sanguis::server::entities::property::object::linear_type const
sanguis::server::entities::property::object::linear()
{
	return linear_;
}

void
sanguis::server::entities::property::object::constant(
	constant_type const &nconstant_
)
{
	constant_ = nconstant_;
	
	recalc_max();
}

void
sanguis::server::entities::property::object::linear(
	linear_type const &nlinear_
)
{
	linear_ = nlinear_;

	recalc_max();
}

void
sanguis::server::entities::property::object::current(
	value_type const ncurrent_
)
{
	current_ = ncurrent_;

	clamp_current();
}

sanguis::server::entities::property::object::value_type
sanguis::server::entities::property::object::current() const
{
	return current_;
}

sanguis::server::entities::property::object::value_type
sanguis::server::entities::property::object::max() const
{
	return max_;
}

sge::signal::auto_connection
sanguis::server::entities::property::object::register_change_callback(
	change_callback const &callback_
)
{
	return
		change_signal_.connect(
			callback_
		);
}

sge::signal::auto_connection
sanguis::server::entities::property::object::register_max_change_callback(
	change_callback const &callback_
)
{
	return
		max_change_signal_.connect(
			callback_
		);
}

void
sanguis::server::entities::property::object::recalc_max()
{
	max_ =
		(base_ + constant_.value())
		* linear_.value();

	clamp_current();
}

void
sanguis::server::entities::property::object::clamp_current()
{
	current_ =
		std::min(
			current_,
			max_
		);
}
