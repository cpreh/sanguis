#ifndef SANGUIS_CAST_ENUM_IMPL_HPP_INCLUDED
#define SANGUIS_CAST_ENUM_IMPL_HPP_INCLUDED

#include "exception.hpp"
#include <fcppt/type_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/string.hpp>
#include <fcppt/lexical_cast.hpp>
#include <typeinfo>

namespace sanguis
{

template<
	typename Enum,
	Enum Size,
	typename Value
>
Enum
cast_enum_impl(
	Value const &_value
)
{
	if(
		_value
		>= static_cast<
			Value
		>(
			Size
		)
	)
		throw sanguis::exception(
			FCPPT_TEXT("Received invalid enum: ")
			+ fcppt::type_name(
				typeid(Enum)
			)
			+ FCPPT_TEXT(", value = ")
			+ fcppt::lexical_cast<
				fcppt::string
			>(
				_value
			)
		);
	
	return
		static_cast<
			Enum
		>(
			_value
		);
}

}

#endif

