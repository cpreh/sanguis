#ifndef SANGUIS_SERVER_NET_VALUE_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_NET_VALUE_IMPL_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/server/net/value_decl.hpp>
#include <fcppt/optional_impl.hpp>


template<
	typename Type,
	typename Policy
>
sanguis::server::net::value<
	Type,
	Policy
>::value(
	sanguis::diff_clock const &_diff_clock
)
:
	timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			Policy::start_duration()
		).active(
			false
		)
	),
	old_()
{
}

template<
	typename Type,
	typename Policy
>
sanguis::server::net::value<
	Type,
	Policy
>::~value()
{
}

template<
	typename Type,
	typename Policy
>
bool
sanguis::server::net::value<
	Type,
	Policy
>::update()
{
	if(
		!timer_.expired()
	)
		return false;

	timer_.active(
		false
	);

	return true;
}

template<
	typename Type,
	typename Policy
>
void
sanguis::server::net::value<
	Type,
	Policy
>::set(
	Type const _value
)
{
	if(
		!old_
	)
	{
		old_ =
			_value;

		this->restart_timer();

		return;
	}

	if(
		!timer_.active()
	)
		this->restart_timer();

	timer_.interval(
		timer_.interval<
			sanguis::duration
		>()
		-
		Policy::difference(
			*old_,
			_value
		)
	);

	old_ =
		_value;
}

template<
	typename Type,
	typename Policy
>
void
sanguis::server::net::value<
	Type,
	Policy
>::reset()
{
	old_.reset();

	timer_.active(
		false
	);
}

template<
	typename Type,
	typename Policy
>
void
sanguis::server::net::value<
	Type,
	Policy
>::restart_timer()
{
	timer_.active(
		true
	);

	timer_.interval(
		Policy::start_duration()
	);

	timer_.reset();
}

#endif
