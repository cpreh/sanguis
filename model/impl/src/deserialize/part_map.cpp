#include <sanguis/model/part_map.hpp>
#include <sanguis/model/impl/deserialize/map.hpp>
#include <sanguis/model/impl/deserialize/part.hpp>
#include <sanguis/model/impl/deserialize/part_map.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <fcppt/text.hpp>


sanguis::model::part_map
sanguis::model::impl::deserialize::part_map(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::impl::deserialize::map<
			sanguis::model::part_map
		>(
			_object,
			FCPPT_TEXT("parts"),
			&sanguis::model::impl::deserialize::part
		);
}
