#include <sanguis/client/machine.hpp>
#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/send_callback.hpp>
#include <sanguis/messages/client/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::send_callback
sanguis::client::make_send_callback(
	sanguis::client::machine &_machine
)
{
	return
		sanguis::client::send_callback{
			std::bind(
				&sanguis::client::machine::send,
				&_machine,
				std::placeholders::_1
			)
		};
}
