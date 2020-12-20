#include <sanguis/messages/server/base.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/make_send_callback.hpp>
#include <sanguis/server/send_callback.hpp>
#include <fcppt/reference_impl.hpp>


sanguis::server::send_callback
sanguis::server::make_send_callback(
	fcppt::reference<
		sanguis::server::machine
	> const _machine
)
{
	return
		sanguis::server::send_callback{
			[
				_machine
			](
				sanguis::messages::server::base const &_message
			)
			{
				_machine->send_to_all(
					_message
				);
			}
		};
}
