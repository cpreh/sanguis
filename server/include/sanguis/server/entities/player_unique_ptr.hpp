#ifndef SANGUIS_SERVER_ENTITIES_PLAYER_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PLAYER_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/entities/player_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

using
player_unique_ptr
=
fcppt::unique_ptr<
	sanguis::server::entities::player
>;

}
}
}

#endif
