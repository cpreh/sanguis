#include <sanguis/model/part_map.hpp>
#include <sanguis/model/aux_/deserialize/map.hpp>
#include <sanguis/model/aux_/deserialize/parameters_fwd.hpp>
#include <sanguis/model/aux_/deserialize/part.hpp>
#include <sanguis/model/aux_/deserialize/part_map.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <fcppt/text.hpp>


sanguis::model::part_map
sanguis::model::aux_::deserialize::part_map(
	sanguis::model::aux_::deserialize::parameters const &_parameters,
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::aux_::deserialize::map<
			sanguis::model::part_map
		>(
			_parameters,
			_object,
			FCPPT_TEXT("parts"),
			&sanguis::model::aux_::deserialize::part
		);
}
