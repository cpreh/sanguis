#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_MODEL_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_MODEL_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/with_auras_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

typedef
sanguis::client::draw2d::entities::with_auras<
	sanguis::client::draw2d::entities::model::object
>
with_auras_model;

}
}
}
}

#endif
