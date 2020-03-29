#include <sanguis/server/create.hpp>
#include <sanguis/server/object.hpp>
#include <sanguis/server/object_base.hpp>
#include <sanguis/server/object_base_unique_ptr.hpp>
#include <alda/net/port.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_reference.hpp>


sanguis::server::object_base_unique_ptr
sanguis::server::create(
	fcppt::log::context_reference const _log_context,
	alda::net::port const _port
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::server::object_base
		>(
			fcppt::make_unique_ptr<
				sanguis::server::object
			>(
				_log_context,
				_port
			)
		);
}
