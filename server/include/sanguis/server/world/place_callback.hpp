#ifndef SANGUIS_SERVER_WORLD_PLACE_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_PLACE_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

typedef
std::function<
	sanguis::server::entities::unique_ptr ()
>
place_callback;

}
}
}

#endif
