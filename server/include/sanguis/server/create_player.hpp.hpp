#ifndef SANGUIS_SERVER_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_HPP_INCLUDED

#include <sanguis/server/object_base_unique_ptr.hpp>
#include <sanguis/server/symbol.hpp>
#include <alda/net/port.hpp>


namespace sanguis
{
namespace server
{

SANGUIS_SERVER_SYMBOL
sanguis::server::object_base_unique_ptr
create(
	alda::net::port
);

}
}

#endif
