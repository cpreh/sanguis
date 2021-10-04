#ifndef SANGUIS_CLIENT_LOAD_MODEL_MAKE_DELAY_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_MAKE_DELAY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/model/animation_fwd.hpp>
#include <sanguis/model/optional_animation_delay_fwd.hpp>


namespace sanguis::client::load::model
{

sanguis::duration
make_delay(
	sanguis::model::animation const &,
	sanguis::model::optional_animation_delay const &
);

}

#endif
