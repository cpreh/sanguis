#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/aux_/deserialize/cell_size.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/to_static_container.hpp>
#include <fcppt/text.hpp>


sanguis::model::cell_size const
sanguis::model::aux_::deserialize::cell_size(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::cell_size{
			sge::parse::json::convert::to_static_container<
				sanguis::model::cell_size::value_type
			>(
				sge::parse::json::find_member_exn<
					sge::parse::json::array
				>(
					_object.members,
					FCPPT_TEXT("cell_dimensions")
				)
			)
		};
}
