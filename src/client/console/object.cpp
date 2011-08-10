#include "object.hpp"
#include "../../messages/base.hpp"
#include "../../messages/create.hpp"
#include "../../messages/console_command.hpp"
#include "../../messages/serialization/convert_string_vector.hpp"
#include "../../from_console_arg_list.hpp"
#include <sge/console/gfx.hpp>
#include <sge/console/object.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <fcppt/tr1/functional.hpp>

sanguis::client::console::object::object(
	sge::console::gfx &_gfx,
	client::send_callback const &_send
)
:
	gfx_(
		_gfx
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
			sge::font::text::from_fcppt_string(
				_name
			),
			std::tr1::bind(
				&object::server_callback,
				this,
				std::tr1::placeholders::_1
			),
			sge::font::text::from_fcppt_string(
				_description
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
sanguis::client::console::object::draw()
{
	if(
		this->active()
	)
		gfx_.render();
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
		sanguis::messages::create(
			sanguis::messages::console_command(
				sanguis::messages::serialization::convert_string_vector(
					sanguis::from_console_arg_list(
						_args
					)
				)
			)
		)
	);
}
