#include <sanguis/load/model/json_header.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/text.hpp>

sge::parse::json::object const &
sanguis::load::model::json_header(
	sge::parse::json::member_vector const &_global_entries
)
{
	return
		sge::parse::json::find_member_exn<
			sge::parse::json::object
		>(
			_global_entries,
			FCPPT_TEXT("header")
		);
}
