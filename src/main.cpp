#include <sanguis/app_name.hpp>
#include <sanguis/company_name.hpp>
#include <sanguis/args/log_level.hpp>
#include <sanguis/args/options.hpp>
#include <sanguis/args/parse.hpp>
#include <sanguis/args/server_only.hpp>
#include <sanguis/client/create.hpp>
#include <sanguis/server/create_original.hpp>
#include <sanguis/log_context.hpp>
#include <sanguis/log_location.hpp>
#include <sanguis/main.hpp>
#include <sanguis/main_object.hpp>
#include <sanguis/main_object_scoped_ptr.hpp>
#include <sge/config/app_name.hpp>
#include <sge/config/log_path.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/show_message_narrow.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context.hpp>
#include <awl/main/scoped_output.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/clog.hpp>
#include <fcppt/log/activate_levels_recursive.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <exception>
#include <sstream>
#include <string>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
sanguis::main(
	awl::main::function_context const &_function_context
)
try
{
	boost::program_options::options_description desc(
		sanguis::args::options()
	);

	boost::program_options::variables_map const vm(
		sanguis::args::parse(
			_function_context.argc(),
			_function_context.argv(),
			desc
		)
	);

	if(
		vm.count(
			"help"
		)
	)
	{
		std::ostringstream out;

		out <<
			desc;

		awl::show_message_narrow(
			out.str()
		);

		return
			awl::main::exit_success();
	}

	awl::main::scoped_output const output(
		fcppt::io::clog(),
		sge::config::log_path(
			sanguis::company_name(),
			sge::config::app_name(
				sanguis::app_name()
			)
		)
	);

	fcppt::log::activate_levels_recursive(
		sanguis::log_context(),
		sanguis::log_location(),
		sanguis::args::log_level(
			vm
		)
	);

	sanguis::main_object_scoped_ptr const obj(
		sanguis::args::server_only(
			vm
		)
		?
			sanguis::server::create_original(
				vm
			)
		:
			sanguis::client::create(
				vm
			)
		);

	return
		obj->run();
}
catch(
	fcppt::exception const &_error
)
{
	awl::show_error(
		FCPPT_TEXT("Caught fcppt exception: ")
		+
		_error.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	awl::show_error_narrow(
		std::string(
			"Caught standard exception: "
		)
		+
		_error.what()
	);

	return
		awl::main::exit_failure();
}
