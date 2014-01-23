#include <sanguis/messages/server/base.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/make_unicast_callback.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::unicast_callback
sanguis::server::make_unicast_callback(
	sanguis::server::machine &_machine
)
{
	return
		std::bind(
			&sanguis::server::machine::send_unicast,
			&_machine,
			std::placeholders::_1,
			std::placeholders::_2
		);
}
