#ifndef SANGUIS_CAST_ENUM_HPP_INCLUDED
#define SANGUIS_CAST_ENUM_HPP_INCLUDED

#include "cast_enum_impl.hpp"

#define SANGUIS_CAST_ENUM(\
	enum_,\
	value_\
)\
sanguis::cast_enum_impl<\
	enum_::type,\
	enum_::size\
>(\
	value_\
)

#endif
