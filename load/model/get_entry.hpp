#ifndef SANGUIS_LOAD_MODEL_GET_ENTRY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_GET_ENTRY_HPP_INCLUDED

#include "../../exception.hpp"
#include <sge/text.hpp>
#include <sge/string.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/member_name_equal.hpp>
#include <boost/variant/get.hpp>
#include <algorithm>

namespace sanguis
{
namespace load
{
namespace model
{

template<
	typename T
>
T
get_entry(
	sge::parse::json::object const &o,
	sge::string const &name)
{
	sge::parse::json::object::member_vector::const_iterator const it(
		std::find_if(
			o.members.begin(),
			o.members.end(),
			sge::parse::json::member_name_equal(
				name
			)
		)
	);

	if(it == o.members.end())
		throw exception(
			SGE_TEXT("entry ")
			+ name
			+ SGE_TEXT(" not found")
		);
	
	return boost::get<
		T
	>(
		it->value_
	);
}

}
}
}

#endif
