#include "read.hpp"
#include "../log.hpp"
#include <sge/parse/json/parse_stream.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/string.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>
#include <istream>

sanguis::client::highscore::table const
sanguis::client::highscore::read(
	fcppt::io::istream &stream
)
{
	sge::parse::json::object result;

	if(
		!sge::parse::json::parse_stream(
			stream,
			result
		)
	)
	{
		FCPPT_LOG_ERROR(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("Highscore file could not be parsed!")
		);

		return table();
	}

	table t;

	BOOST_FOREACH(
		sge::parse::json::element_vector::const_reference elem,
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			result.members,
			FCPPT_TEXT("entries")
		).elements
	)
	{
		sge::parse::json::member_vector const &members(
			sge::parse::json::get<
				sge::parse::json::object
			>(
				elem
			).members
		);

		name_container names_result;

		BOOST_FOREACH(
			sge::parse::json::element_vector::const_reference name,
			sge::parse::json::find_member_exn<
				sge::parse::json::array
			>(
				members,
				FCPPT_TEXT("names")
			).elements
		)
			names_result.push_back(
				sge::parse::json::get<
					sge::parse::json::string
				>(
					name
				)
			);
		
		t.push_back(
			entry(
				names_result,
				sge::parse::json::find_member_exn<
					score_type
				>(
					members,
					FCPPT_TEXT("score")
				)
			)
		);
	}

	return t;
}
