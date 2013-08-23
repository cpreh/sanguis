#include <sanguis/string_vector.hpp>
#include <sanguis/to_console_arg_list.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <fcppt/algorithm/map.hpp>


sge::console::arg_list const
sanguis::to_console_arg_list(
	sanguis::string_vector const &_vector
)
{
	return
		fcppt::algorithm::map<
			sge::console::arg_list
		>(
			_vector,
			&sge::font::from_fcppt_string
		);
}
