#include <sanguis/from_console_arg_list.hpp>
#include <sge/font/to_fcppt_string.hpp>
#include <fcppt/algorithm/map.hpp>

sanguis::string_vector const
sanguis::from_console_arg_list(
	sge::console::arg_list const &_list
)
{
	return
		fcppt::algorithm::map<
			sanguis::string_vector
		>(
			_list,
			&sge::font::to_fcppt_string
		);
}
