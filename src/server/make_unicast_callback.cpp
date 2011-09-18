#include <sanguis/server/make_unicast_callback.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/messages/base.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/function/object.hpp>

sanguis::server::unicast_callback const
sanguis::server::make_unicast_callback(
	server::machine &_machine
)
{
	return
		std::tr1::bind(
			&server::machine::send_unicast,
			&_machine,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		);
}
