#include <sanguis/model/animation_index.hpp>
#include <sanguis/model/animation_range.hpp>
#include <sanguis/model/aux_/deserialize/animation_range.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/to_static_container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::model::animation_range const
sanguis::model::aux_::deserialize::animation_range(
	sge::parse::json::object const &_object
)
{
	typedef
	fcppt::math::vector::static_<
		sanguis::model::animation_index,
		2
	>
	animation_vector;

	animation_vector const result(
		sge::parse::json::convert::to_static_container<
			animation_vector
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
			result[0],
			result[1]
		);
}
