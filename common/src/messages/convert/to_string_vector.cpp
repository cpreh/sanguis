#include <sanguis/string_vector.hpp>
#include <sanguis/messages/convert/to_string_vector.hpp>
#include <sanguis/messages/types/string_vector.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/string.hpp>
#include <fcppt/algorithm/map.hpp>


sanguis::messages::types::string_vector
sanguis::messages::convert::to_string_vector(
	sanguis::string_vector const &_src
)
{
	return
		fcppt::algorithm::map<
			sanguis::messages::types::string_vector
		>(
			_src,
			[](
				fcppt::string const &_elem
			)
			{
				return
					sge::charconv::fcppt_string_to_utf8(
						_elem
					);
			}
		);
}
