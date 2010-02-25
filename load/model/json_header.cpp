#include "json_header.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/text.hpp>

sge::parse::json::object const &
sanguis::load::model::json_header(
	sge::parse::json::member_vector const &global_entries
)
{
	return
		sge::parse::json::find_member<
			sge::parse::json::object
		>(
			global_entries,
			FCPPT_TEXT("header")
		);
}
