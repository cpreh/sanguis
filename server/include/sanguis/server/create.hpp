#ifndef SANGUIS_SERVER_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_HPP_INCLUDED

#include <sanguis/server/object_base_unique_ptr.hpp>
#include <sanguis/server/symbol.hpp>
#include <alda/net/port.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


namespace sanguis::server
{

SANGUIS_SERVER_SYMBOL
sanguis::server::object_base_unique_ptr
create(
	fcppt::log::context_reference,
	alda::net::port
);

}

#endif
