#include <sanguis/model/part_map.hpp>
#include <sanguis/model/aux_/serialize/map.hpp>
#include <sanguis/model/aux_/serialize/part.hpp>
#include <sanguis/model/aux_/serialize/part_map.hpp>
#include <sge/parse/json/member.hpp>
#include <fcppt/text.hpp>


sge::parse::json::member
sanguis::model::aux_::serialize::part_map(
	sanguis::model::part_map const &_parts
)
{
	return
		sanguis::model::aux_::serialize::map(
			_parts,
			FCPPT_TEXT("parts"),
			&sanguis::model::aux_::serialize::part
		);
}
