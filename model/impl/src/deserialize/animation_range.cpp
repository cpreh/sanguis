#include <sanguis/model/animation_range.hpp>
#include <sanguis/model/impl/animation_range_vector.hpp>
#include <sanguis/model/impl/deserialize/animation_range.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/to_static_container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::model::animation_range
sanguis::model::impl::deserialize::animation_range(
	sge::parse::json::object const &_object
)
{
	auto const result(
		sge::parse::json::convert::to_static_container<
			sanguis::model::impl::animation_range_vector
		>(
			sge::parse::json::find_member_exn<
				sge::parse::json::array
			>(
				_object.members,
				FCPPT_TEXT("range")
			)
		)
	);

	return
		sanguis::model::animation_range(
			result.x(),
			result.y()
		);
}
