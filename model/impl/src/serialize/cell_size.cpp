#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/impl/serialize/cell_size.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/convert/from_container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/to_array.hpp>


sge::parse::json::member
sanguis::model::impl::serialize::cell_size(
	sanguis::model::cell_size const _cell_size
)
{
	return
		sge::parse::json::member(
			FCPPT_TEXT("cell_dimensions"),
			sge::parse::json::value(
				sge::parse::json::convert::from_container(
					fcppt::math::to_array(
						_cell_size.get()
					)
				)
			)
		);
}
