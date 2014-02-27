#include <sanguis/model/animation_map.hpp>
#include <sanguis/model/aux_/deserialize/animation.hpp>
#include <sanguis/model/aux_/deserialize/animation_map.hpp>
#include <sanguis/model/aux_/deserialize/map.hpp>
#include <sanguis/model/aux_/deserialize/parameters_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <fcppt/text.hpp>


sanguis::model::animation_map
sanguis::model::aux_::deserialize::animation_map(
	sanguis::model::aux_::deserialize::parameters const &_parameters,
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::aux_::deserialize::map<
			sanguis::model::animation_map
		>(
			_parameters,
			_object,
			FCPPT_TEXT("animations"),
			&sanguis::model::aux_::deserialize::animation
		);
}
