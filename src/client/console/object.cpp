#include <sanguis/client/send_callback.hpp>
#include <sanguis/client/console/object.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/console_command.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/serialization/convert_string_vector.hpp>
#include <sanguis/from_console_arg_list.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/gfx.hpp>
#include <sge/console/object.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/string.hpp>
#include <fcppt/tr1/functional.hpp>


sanguis::client::console::object::object(
	sge::console::gfx &_gfx,
	sge::charconv::system &_charconv_system,
	sanguis::client::send_callback const &_send
)
:
	gfx_(
		_gfx
	),
	charconv_system_(
		_charconv_system
	),
	send_(
		_send
	),
	server_connections_()
{
}

sanguis::client::console::object::~object()
{
}

void
sanguis::client::console::object::register_server_command(
	fcppt::string const &_name,
	fcppt::string const &_description
)
{
	server_connections_.add(
		gfx_.object().insert(
			sge::console::callback::parameters(
				std::tr1::bind(
					&object::server_callback,
					this,
					std::tr1::placeholders::_1
				),
				sge::console::callback::name(
					sge::font::from_fcppt_string(
						_name
					)
				)
			)
			.short_description(
				sge::font::from_fcppt_string(
					_description
				)
			)
		)
	);
}

void
sanguis::client::console::object::active(
	bool const _active
)
{
	gfx_.active(
		_active
	);
}

bool
sanguis::client::console::object::active() const
{
	return
		gfx_.active();
}

void
sanguis::client::console::object::draw(
	sge::renderer::context::ffp &_context
)
{
	if(
		this->active()
	)
		gfx_.render(
			_context
		);
}

sge::console::object &
sanguis::client::console::object::sge_console()
{
	return
		gfx_.object();
}

void
sanguis::client::console::object::server_callback(
	sge::console::arg_list const &_args
)
{
	send_(
		*sanguis::messages::create(
			sanguis::messages::console_command(
				sanguis::messages::serialization::convert_string_vector(
					charconv_system_,
					sanguis::from_console_arg_list(
						_args
					)
				)
			)
		)
	);
}
