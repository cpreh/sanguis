#include "convert_string_vector.hpp"
#include <fcppt/utf8/convert.hpp>
#include <boost/foreach.hpp>

namespace
{

template<
	typename Dest,
	typename Src
>
Dest
convert(
	Src const &src
)
{
	Dest dest;

	BOOST_FOREACH(
		typename Src::const_reference elem,
		src
	)
		dest.push_back(
			fcppt::utf8::convert(
				elem
			)
		);
	
	return dest;
}

}

sanguis::messages::types::string_vector const
sanguis::messages::serialization::convert_string_vector(
	sanguis::string_vector const &src
)
{
	return
		convert<
			sanguis::messages::types::string_vector		
		>(
			src
		);
}

sanguis::string_vector const
sanguis::messages::serialization::convert_string_vector(
	messages::types::string_vector const &src
)
{
	return
		convert<
			sanguis::string_vector
		>(
			src
		);

}
