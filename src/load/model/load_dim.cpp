#include <sanguis/load/model/cell_size.hpp>
#include <sanguis/load/model/load_dim.hpp>
#include <sanguis/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/to_int.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/text.hpp>


sanguis::load::model::cell_size const
sanguis::load::model::load_dim(
	sge::parse::json::object const &_object
)
{
	sge::parse::json::array const &array(
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			_object.members,
			FCPPT_TEXT("cell_dimensions")
		)
	);

	sge::parse::json::element_vector const &elements(
		array.elements
	);

	if(
		elements.size() < 2
	)
		throw sanguis::exception(
			FCPPT_TEXT("Insufficient members in cell_dimensions!")
		);

	return
		sanguis::load::model::cell_size(
			sanguis::load::model::cell_size::value_type(
				sge::parse::json::convert::to_int<
					sge::renderer::size_type
				>(
					elements[0]
				),
				sge::parse::json::convert::to_int<
					sge::renderer::size_type
				>(
					elements[1]
				)
			)
		);
}


