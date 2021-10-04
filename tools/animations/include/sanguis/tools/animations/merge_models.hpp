#ifndef SANGUIS_TOOLS_ANIMATIONS_MERGE_MODELS_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_MERGE_MODELS_HPP_INCLUDED

#include <sanguis/model/object.hpp>


namespace sanguis::tools::animations
{

sanguis::model::object
merge_models(
	sanguis::model::object const &,
	sanguis::model::object &&
);

}

#endif
