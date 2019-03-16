#include <sanguis/model/animation_range.hpp>
#include <sanguis/model/impl/animation_range_vector.hpp>
#include <sanguis/model/impl/serialize/animation_range.hpp>
#include <sge/parse/json/make_value.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/convert/from_container.hpp>
#include <fcppt/math/to_array.hpp>


sge::parse::json::member
sanguis::model::impl::serialize::animation_range(
	sanguis::model::animation_range const &_range
)
{
	return
		sge::parse::json::member(
			"range",
			sge::parse::json::make_value(
				sge::parse::json::convert::from_container(
					fcppt::math::to_array(
						sanguis::model::impl::animation_range_vector{
							_range.begin(),
							_range.end()
						}
					)
				)
			)
		);
}
