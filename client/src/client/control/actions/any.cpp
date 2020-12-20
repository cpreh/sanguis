#include <sanguis/client/control/actions/any.hpp>
#include <sanguis/client/control/actions/variant.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::control::actions::any::any(
	sanguis::client::control::actions::variant _variant
)
:
	variant_(
		std::move(
			_variant
		)
	)
{
}

sanguis::client::control::actions::variant const &
sanguis::client::control::actions::any::get() const
{
	return
		variant_;
}
