#include <sanguis/main_object.hpp>
#include <sanguis/server/original_object.hpp>
#include <alda/net/port.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_success.hpp>


sanguis::server::original_object::original_object(
	alda::net::port const _port
)
:
	sanguis::main_object(),
	impl_(
		_port
	)
{
}

sanguis::server::original_object::~original_object()
{
}

awl::main::exit_code const
sanguis::server::original_object::run()
{
	impl_.run();

	return
		awl::main::exit_success();
}
