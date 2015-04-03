#include <sanguis/model/animation_range.hpp>
#include <sanguis/model/impl/animation_range_vector.hpp>
#include <sanguis/model/impl/serialize/animation_range.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/convert/from_container.hpp>
#include <fcppt/text.hpp>


sge::parse::json::member
sanguis::model::impl::serialize::animation_range(
	sanguis::model::animation_range const &_range
)
{
	return
		sge::parse::json::member(
			FCPPT_TEXT("range"),
			sge::parse::json::convert::from_container(
				sanguis::model::impl::animation_range_vector{
					_range.begin(),
					_range.end()
				}
			)
		);
}
