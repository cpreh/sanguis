#ifndef SANGUIS_TRUNCATON_CHECK_STRUCTURE_CAST_IMPL_HPP_INCLUDED
#define SANGUIS_TRUNCATON_CHECK_STRUCTURE_CAST_IMPL_HPP_INCLUDED

#include "truncation_check_cast_impl.hpp"

template<typename Dest, typename Source>
Dest sanguis::truncation_check_structure_cast(const Source& source)
{
	Dest dest;
	for(typename Source::size_type i = 0; i < source.dim(); ++i)
		dest[i] = truncation_check_cast<typename Dest::value_type>(source[i]);
	return dest;
}

#endif
