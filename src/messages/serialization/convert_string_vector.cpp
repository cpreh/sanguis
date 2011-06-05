#include "convert_string_vector.hpp"
#include <fcppt/utf8/convert.hpp>

namespace
{

template<
	typename Dest,
	typename Src
>
Dest
convert(
	Src const &_src
)
{
	Dest dest;

	for(
		typename Src::const_iterator elem_it(
			_src.begin()
		);
		elem_it != _src.end();
		++elem_it
	)
		dest.push_back(
			fcppt::utf8::convert(
				*elem_it
			)
		);
	
	return dest;
}

}

sanguis::messages::types::string_vector const
sanguis::messages::serialization::convert_string_vector(
	sanguis::string_vector const &_src
)
{
	return
		::convert<
			sanguis::messages::types::string_vector		
		>(
			_src
		);
}

sanguis::string_vector const
sanguis::messages::serialization::convert_string_vector(
	messages::types::string_vector const &_src
)
{
	return
		::convert<
			sanguis::string_vector
		>(
			_src
		);
}
