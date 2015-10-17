#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_HOVER_VARIANT_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_HOVER_VARIANT_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/hover/name_and_health_fwd.hpp>
#include <sanguis/client/draw2d/entities/hover/weapon_fwd.hpp>
#include <fcppt/variant/variadic_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace hover
{

typedef
fcppt::variant::variadic<
	sanguis::client::draw2d::entities::hover::name_and_health,
	sanguis::client::draw2d::entities::hover::weapon
>
variant;

}
}
}
}
}

#endif
