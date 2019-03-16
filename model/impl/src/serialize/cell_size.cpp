#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/impl/serialize/cell_size.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/make_value.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/convert/from_container.hpp>
#include <fcppt/math/to_array.hpp>


sge::parse::json::member
sanguis::model::impl::serialize::cell_size(
	sanguis::model::cell_size const _cell_size
)
{
	return
		sge::parse::json::member(
			sge::charconv::utf8_string{
				"cell_dimensions"
			},
			sge::parse::json::make_value(
				sge::parse::json::convert::from_container(
					fcppt::math::to_array(
						_cell_size.get()
					)
				)
			)
		);
}
