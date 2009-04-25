#ifndef SANGUIS_DETAIL_TRUNCATION_CHECK_CAST_IMPL_HPP_INCLUDED
#define SANGUIS_DETAIL_TRUNCATION_CHECK_CAST_IMPL_HPP_INCLUDED

#include "../exception.hpp"
#include <sge/text.hpp>
#include <sge/format.hpp>

#include <typeinfo>

template<typename Dest, typename Source>
Dest sanguis::truncation_check_cast(const Source& source)
{
	const Dest dest(static_cast<Dest>(source));
	if(static_cast<Source>(dest) != source)
		throw exception((
			sge::format(
				SGE_TEXT("truncation_check_cast_failed when casting from ")
				SGE_TEXT("(type: '%1%', value: %2%) to (type: '%3%', value: %4%)!")
			) % typeid(Source).name()
			  % source
			  % typeid(Dest).name()
			  % dest).str());
	return dest;
}


#endif
