#ifndef SANGUIS_SERVER_ENTITIES_OPTIONAL_PLAYER_REF_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_OPTIONAL_PLAYER_REF_FWD_HPP_INCLUDED

#include <sanguis/server/entities/player_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

typedef
fcppt::optional::reference<
	sanguis::server::entities::player
>
optional_player_ref;

}
}
}

#endif
