#ifndef SANGUIS_CAST_ENUM_HPP_INCLUDED
#define SANGUIS_CAST_ENUM_HPP_INCLUDED

#include <sanguis/exception.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{

template<
	typename Enum,
	typename Value
>
Enum
cast_enum(
	Value const &_value
)
{
	if(
		_value
		>
		static_cast<
			Value
		>(
			Enum::size
		)
	)
		throw sanguis::exception(
			FCPPT_TEXT("Received invalid enum: ")
			+ fcppt::type_name(
				typeid(
					Enum
				)
			)
			+ FCPPT_TEXT(", value = ")
			+ fcppt::insert_to_fcppt_string(
				static_cast<
					unsigned long
				>(
					_value
				)
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

