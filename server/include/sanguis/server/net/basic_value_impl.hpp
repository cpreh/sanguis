#ifndef SANGUIS_SERVER_NET_BASIC_VALUE_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_NET_BASIC_VALUE_IMPL_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/net/value_decl.hpp>
#include <sge/timer/interval.hpp>
#include <fcppt/optional_impl.hpp>


template<
	typename Type,
	typename Policy,
	typename Clock
>
sanguis::server::net::basic_value<
	Type,
	Policy,
	Clock
>::basic_value(
	Clock const &_clock
)
:
	timer_(
		typename
		timer::parameters{
			_clock,
			Policy::start_duration()
		}.active(
			false
		)
	),
	old_()
{
}

template<
	typename Type,
	typename Policy,
	typename Clock
>
sanguis::server::net::basic_value<
	Type,
	Policy,
	Clock
>::~basic_value()
{
}

template<
	typename Type,
	typename Policy,
	typename Clock
>
bool
sanguis::server::net::basic_value<
	Type,
	Policy,
	Clock
>::update()
{
	if(
		!timer_.expired()
	)
		return
			false;

	timer_.active(
		false
	);

	return
		true;
}

template<
	typename Type,
	typename Policy,
	typename Clock
>
void
sanguis::server::net::basic_value<
	Type,
	Policy,
	Clock
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
		sge::timer::interval<
			sanguis::duration
		>(
			timer_
		)
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
	typename Policy,
	typename Clock
>
void
sanguis::server::net::basic_value<
	Type,
	Policy,
	Clock
>::reset()
{
	old_.reset();

	timer_.active(
		false
	);
}

template<
	typename Type,
	typename Policy,
	typename Clock
>
void
sanguis::server::net::basic_value<
	Type,
	Policy,
	Clock
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
