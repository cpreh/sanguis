#include "read.hpp"
#include "../log.hpp"
#include <sge/parse/json/parse_range.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/assign/make_container.hpp>
#include <sge/log/headers.hpp>
#include <sge/string.hpp>
#include <sge/char_type.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include <istream>

sanguis::client::highscore::table const
sanguis::client::highscore::read(
	sge::istream &stream)
{
	sge::parse::json::object result;

	{
		// TODO: can't we use the istream iterators directly?
		sge::string str;

		sge::char_type ch;

		while(stream.get(ch))
			str.push_back(ch);

		sge::string::const_iterator beg(
			str.begin()
		);

		if(
			!sge::parse::json::parse_range(
				beg,
				static_cast<
					sge::string::const_iterator
				>(
					str.end()
				),
				result
			)
		)
		{
			SGE_LOG_ERROR(
				log(),
				sge::log::_
					<< SGE_TEXT("Errors in the highscore file detected!")
			);

			return table();
		}
	}

	table t;

	BOOST_FOREACH(
		sge::parse::json::element_vector::const_reference elem,
		sge::parse::json::find_member<
			sge::parse::json::array
		>(
			result.members,
			SGE_TEXT("entries")
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
			sge::parse::json::find_member<
				sge::parse::json::array
			>(
				members,
				SGE_TEXT("names")
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
				sge::parse::json::find_member<
					int
				>(
					members,
					SGE_TEXT("score")
				)
			)
		);
	}

	return t;
}
