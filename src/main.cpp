#include <sanguis/args/log_level.hpp>
#include <sanguis/args/options.hpp>
#include <sanguis/args/parse.hpp>
#include <sanguis/args/server_only.hpp>
#include <sanguis/client/create.hpp>
#include <sanguis/server/create_original.hpp>
#include <sanguis/apply_log_level.hpp>
#include <sanguis/log_context.hpp>
#include <sanguis/log_location.hpp>
#include <sanguis/main.hpp>
#include <sanguis/main_object.hpp>
#include <sanguis/main_object_scoped_ptr.hpp>
#include <sge/config/app_name.hpp>
#include <sge/config/company_name.hpp>
#include <sge/config/log_path.hpp>
#include <sge/log/global_context.hpp>
#include <sge/log/location.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context.hpp>
#include <awl/main/scoped_output.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/clog.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <exception>
#include <iostream>
#include <ostream>
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
		vm.count("help")
	)
	{
		// TODO: Fix this!
		std::cout << desc << '\n';

		return awl::main::exit_success();
	}

	awl::main::scoped_output const output(
		fcppt::io::clog(),
		sge::config::log_path(
			sge::config::company_name(
				FCPPT_TEXT("sanguis")
			),
			sge::config::app_name(
				FCPPT_TEXT("main")
			)
		)
	);

	fcppt::log::level const log_level(
		sanguis::args::log_level(
			vm
		)
	);

	sanguis::apply_log_level(
		sanguis::log_location(),
		sanguis::log_context(),
		log_level
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

	// TODO: this should be done right after sge::systems is constructed
	sanguis::apply_log_level(
		sge::log::location(),
		sge::log::global_context(),
		log_level
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
