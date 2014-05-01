#ifndef SANGUIS_SERVER_AURAS_CREATE_CALLBACK_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_CREATE_CALLBACK_CONTAINER_HPP_INCLUDED

#include <sanguis/server/auras/create_callback.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

typedef
std::vector<
	sanguis::server::auras::create_callback
>
create_callback_container;

}
}
}

#endif
