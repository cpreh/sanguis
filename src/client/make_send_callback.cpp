#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/machine.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/tr1/functional.hpp>

sanguis::client::send_callback const
sanguis::client::make_send_callback(
	client::machine &_machine
)
{
	return
		std::tr1::bind(
			&client::machine::send,
			&_machine,
			std::tr1::placeholders::_1
		);
}
