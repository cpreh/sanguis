#include <sanguis/model/part_map.hpp>
#include <sanguis/model/impl/serialize/map.hpp>
#include <sanguis/model/impl/serialize/part.hpp>
#include <sanguis/model/impl/serialize/part_map.hpp>
#include <sge/parse/json/member.hpp>
#include <fcppt/text.hpp>


sge::parse::json::member
sanguis::model::impl::serialize::part_map(
	sanguis::model::part_map const &_parts
)
{
	return
		sanguis::model::impl::serialize::map(
			_parts,
			FCPPT_TEXT("parts"),
			&sanguis::model::impl::serialize::part
		);
}
