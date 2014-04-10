#ifndef SANGUIS_SERVER_AURAS_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_CONTAINER_HPP_INCLUDED

#include <sanguis/server/auras/unique_ptr.hpp>
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
	sanguis::server::auras::unique_ptr
>
container;

}
}
}

#endif
