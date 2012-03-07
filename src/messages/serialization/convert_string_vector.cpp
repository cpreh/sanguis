#include <sanguis/messages/serialization/convert_string_vector.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/charconv/system_fwd.hpp>
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
	sge::charconv::system &_charconv_system,
	Src const &_src,
	ConvertString const &_convert_string
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
			_convert_string(
				_charconv_system,
				*elem_it
			)
		);

	return dest;
}

}

sanguis::messages::types::string_vector const
sanguis::messages::serialization::convert_string_vector(
	sge::charconv::system &_charconv_system,
	sanguis::string_vector const &_src
)
{
	return
		::convert<
			sanguis::messages::types::string_vector
		>(
			_charconv_system,
			_src,
			sge::charconv::fcppt_string_to_utf8
		);
}

sanguis::string_vector const
sanguis::messages::serialization::convert_string_vector(
	sge::charconv::system &_charconv_system,
	messages::types::string_vector const &_src
)
{
	return
		::convert<
			sanguis::string_vector
		>(
			_charconv_system,
			_src,
			sge::charconv::utf8_string_to_fcppt
		);
}
