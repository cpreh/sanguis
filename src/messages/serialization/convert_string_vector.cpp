#include <sanguis/messages/serialization/convert_string_vector.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>


namespace
{

template<
	typename Dest,
	typename Src,
	typename ConvertString
>
Dest
convert(
	Src const &_src,
	ConvertString const &_convert_string
)
{
	Dest dest;

	for(
		auto const element : _src
	)
		dest.push_back(
			_convert_string(
				element
			)
		);

	return dest;
}

}

sanguis::messages::types::string_vector
sanguis::messages::serialization::convert_string_vector(
	sanguis::string_vector const &_src
)
{
	return
		::convert<
			sanguis::messages::types::string_vector
		>(
			_src,
			sge::charconv::fcppt_string_to_utf8
		);
}

sanguis::string_vector
sanguis::messages::serialization::convert_string_vector(
	messages::types::string_vector const &_src
)
{
	return
		::convert<
			sanguis::string_vector
		>(
			_src,
			sge::charconv::utf8_string_to_fcppt
		);
}
