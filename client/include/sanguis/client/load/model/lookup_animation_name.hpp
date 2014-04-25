#ifndef SANGUIS_CLIENT_LOAD_MODEL_LOOKUP_ANIMATION_NAME_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_LOOKUP_ANIMATION_NAME_HPP_INCLUDED

#include <sanguis/client/load/animation_type_fwd.hpp>
#include <sanguis/model/animation_name_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

sanguis::client::load::animation_type
lookup_animation_name(
	sanguis::model::animation_name const &
);

}
}
}
}

#endif
