#include "console_wrapper.hpp"
#include <sge/console/gfx.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_pair.hpp>
#include <tr1/functional>

sanguis::client::console::console(
	sge::console::gfx &_object,
	sge::input::system_ptr const _input_system,
	sge::input::key_code const _toggler
)
:
	object_(
		_object),
	input_connection_(
		_input_system->register_callback(
			std::tr1::bind(
				&console::input_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	toggler_(
		_toggler)
{}

void
sanguis::client::console::input_callback(
	sge::input::key_pair const &_k
)
{
	if (_k.key().code() == toggler_ && _k.value() != 0)
	{
		object_.active(
			!object_.active());
		return;
	}

	if (!object_.active())
		callbacks_(
			_k);
}

fcppt::signal::auto_connection
sanguis::client::console::register_callback(
	sge::input::callback const &_c
)
{
	return 
		callbacks_.connect(
			_c);
}

sge::console::gfx &
sanguis::client::console::object()
{
	return
		object_;
}

sge::console::gfx const &
sanguis::client::console::object() const
{
	return
		object_;
}