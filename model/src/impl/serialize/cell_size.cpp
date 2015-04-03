#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/impl/serialize/cell_size.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/convert/from_container.hpp>
#include <fcppt/text.hpp>


sge::parse::json::member
sanguis::model::impl::serialize::cell_size(
	sanguis::model::cell_size const _cell_size
)
{
	return
		sge::parse::json::member(
			FCPPT_TEXT("cell_dimensions"),
			sge::parse::json::convert::from_container(
				_cell_size.get()
			)
		);
}
