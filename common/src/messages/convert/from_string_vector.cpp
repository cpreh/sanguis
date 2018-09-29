#include <sanguis/exception.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/messages/convert/from_string_vector.hpp>
#include <sanguis/messages/types/string_vector.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/optional/to_exception.hpp>


sanguis::string_vector
sanguis::messages::convert::from_string_vector(
	sanguis::messages::types::string_vector const &_src
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
					// FIXME
					fcppt::optional::to_exception(
						sge::charconv::utf8_string_to_fcppt(
							_elem
						),
						[]{
							return
								sanguis::exception{
									FCPPT_TEXT("Failed to convert message string!")
								};
						}
					);
			}
		);
}
