#include "load_dim.hpp"
#include "../../exception.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>

sge::renderer::dim_type const
sanguis::load::model::load_dim(
	sge::parse::json::member_vector const &entries
)
{
	sge::parse::json::array const &array(
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			entries,
			FCPPT_TEXT("cell_dimensions")
		)
	);

	sge::parse::json::element_vector const &elements(
		array.elements
	);

	if(elements.size() < 2)
		throw sanguis::exception(
			FCPPT_TEXT("Insufficient members in cell_dimensions!")
		);
	
	return
		sge::renderer::dim_type(
			static_cast<
				sge::renderer::size_type
			>(
				sge::parse::json::get<
					int	
				>(
					elements[0]
				)
			),
			static_cast<
				sge::renderer::size_type
			>(
				sge::parse::json::get<
					int	
				>(
					elements[1]
				)
			)
		);
}


