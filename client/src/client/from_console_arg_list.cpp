#include <sanguis/exception.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/client/from_console_arg_list.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/font/string.hpp>
#include <sge/font/to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/optional/to_exception.hpp>


sanguis::string_vector
sanguis::client::from_console_arg_list(
	sge::console::arg_list const &_list
)
{
	return
		fcppt::algorithm::map<
			sanguis::string_vector
		>(
			_list,
			[](
				sge::font::string const &_element
			)
			{
				// FIXME
				return
					fcppt::optional::to_exception(
						sge::font::to_fcppt_string(
							_element
						),
						[]{
							return
								sanguis::exception{
									FCPPT_TEXT("Failed to convert console argument!")
								};
						}
					);
			}
		);
}
