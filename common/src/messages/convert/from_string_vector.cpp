#include <sanguis/string_vector.hpp>
#include <sanguis/messages/convert/from_string_vector.hpp>
#include <sanguis/messages/types/string_vector.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <fcppt/algorithm/map.hpp>


sanguis::string_vector
sanguis::messages::convert::from_string_vector(
	messages::types::string_vector const &_src
)
{
	return
		fcppt::algorithm::map<
			sanguis::string_vector
		>(
			_src,
			[](
				sge::charconv::utf8_string const &_elem
			)
			{
				return
					sge::charconv::utf8_string_to_fcppt(
						_elem
					);
			}
		);
}
