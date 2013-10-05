#ifndef SANGUIS_SERVER_NET_VALUE_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_NET_VALUE_IMPL_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/server/net/value_decl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


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
			sanguis::duration_second(
				0.5f
			)
			//Policy::start_duration()
		)/*.active(
			false
		)*/
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

/*
	timer_.interval(
		Policy::start_duration()
	);*/

	timer_.reset();

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
	old_ = _value;
/*
	if(
		!old_
	)
	{
		old_ =
			_value;

		timer_.active(
			true
		);

		return;
	}
	timer_.interval(
		std::max(
			sanguis::duration_second(
				0
			),
			timer_.interval<
				sanguis::duration
			>()
			-
			Policy::difference(
				*old_,
				_value
			)
		)
	);

	old_ =
		_value;*/
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
/*
	timer_.active(
		false
	);*/
}

#endif
