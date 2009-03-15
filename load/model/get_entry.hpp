#ifndef SANGUIS_LOAD_MODEL_GET_ENTRY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_GET_ENTRY_HPP_INCLUDED

#include "../../exception.hpp"
#include <sge/text.hpp>
#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_vector.hpp>
#include <boost/variant/get.hpp>
#include <boost/foreach.hpp>

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
	sge::parse::ini::entry_vector const &e,
	sge::string const &name)
{
	BOOST_FOREACH(
		sge::parse::ini::entry_vector::const_reference r,
		e
	)
		if(r.name == name)
			return boost::get<T>(r.value_);

	throw exception(
		SGE_TEXT("entry ")
		+ name
		+ SGE_TEXT(" not found")
	);
}

}
}
}

#endif
