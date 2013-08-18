#include <sanguis/load/model/json_header.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/text.hpp>


sge::parse::json::object const &
sanguis::load::model::json_header(
	sge::parse::json::object const &_object
)
{
	return
		sge::parse::json::find_member_exn<
			sge::parse::json::object
		>(
			_object.members,
			FCPPT_TEXT("header")
		);
}
