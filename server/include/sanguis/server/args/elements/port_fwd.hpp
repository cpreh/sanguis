#ifndef SANGUIS_SERVER_ARGS_ELEMENTS_PORT_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ARGS_ELEMENTS_PORT_FWD_HPP_INCLUDED

#include <sanguis/server/args/labels/port.hpp>
#include <alda/net/port_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace args
{
namespace elements
{

typedef
fcppt::record::element<
	sanguis::server::args::labels::port,
	alda::net::port
>
port;

}
}
}
}

#endif
