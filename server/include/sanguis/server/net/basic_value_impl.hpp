#ifndef SANGUIS_SERVER_NET_BASIC_VALUE_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_NET_BASIC_VALUE_IMPL_HPP_INCLUDED

#include <sanguis/server/net/value_decl.hpp>
#include <sge/timer/basic_impl.hpp>
#include <sge/timer/clocks/parameter.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>


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
	sge::timer::clocks::parameter<
		Clock
	> _clock
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
>::~basic_value<
	Type,
	Policy,
	Clock
>()
= default;

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
	{
		return
			false;
	}

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
	fcppt::optional::maybe(
		old_,
		[
			this
		]{
			this->restart_timer();
		},
		[
			_value,
			this
		](
			Type const _old
		)
		{
			if(
				!timer_.active()
			)
			{
				this->restart_timer();
			}

			timer_.interval(
				timer_.interval()
				-
				Policy::difference(
					_old,
					_value
				)
			);
		}
	);

	old_ =
		optional_type{
			_value
		};
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
	old_ =
		optional_type();

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
