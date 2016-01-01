#ifndef SANGUIS_TOOLS_ANIMATIONS_OPTIONAL_ANIMATION_REF_FWD_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_OPTIONAL_ANIMATION_REF_FWD_HPP_INCLUDED

#include <sanguis/model/animation_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{

typedef
fcppt::optional::object<
	sanguis::model::animation &
>
optional_animation_ref;

}
}
}

#endif
