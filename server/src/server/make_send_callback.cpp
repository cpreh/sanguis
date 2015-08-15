#include <sanguis/messages/server/base.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/make_send_callback.hpp>
#include <sanguis/server/send_callback.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::send_callback
sanguis::server::make_send_callback(
	sanguis::server::machine &_machine
)
{
	return
		sanguis::server::send_callback{
			std::bind(
				&sanguis::server::machine::send_to_all,
				&_machine,
				std::placeholders::_1
			)
		};
}
