#ifndef SANGUIS_LOAD_MODEL_GET_ENTRY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_GET_ENTRY_HPP_INCLUDED

#include "../../exception.hpp"
#include <sge/text.hpp>
#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_vector.hpp>
#include <boost/variant/get.hpp>
#include <boost/foreach.hpp>

#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <typeinfo>
#include <iostream>

namespace sanguis
{
namespace load
{
namespace model
{

struct temp_visitor : boost::static_visitor<> {
	template<
		typename T
	>
	void operator()(T const &) const
	{
		std::cerr << typeid(T).name() << '\n';
	}
};

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
	{
		boost::apply_visitor(
			temp_visitor(),
			r.value_
		);

		if(r.name == name)
			return boost::get<double>(r.value_);
	}

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
