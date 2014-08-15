#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_HOVER_VARIANT_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_HOVER_VARIANT_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/hover/name_fwd.hpp>
#include <sanguis/client/draw2d/entities/hover/weapon_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


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
fcppt::variant::object<
	boost::mpl::vector2<
		sanguis::client::draw2d::entities::hover::name_and_health,
		sanguis::client::draw2d::entities::hover::weapon
	>
>
variant;

}
}
}
}
}

#endif
