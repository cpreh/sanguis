#include <sanguis/args/log_level.hpp>
#include <sanguis/args/options.hpp>
#include <sanguis/args/parse.hpp>
#include <sanguis/args/server_only.hpp>
#include <sanguis/client/create.hpp>
#include <sanguis/load/server_context.hpp>
#include <sanguis/server/create.hpp>
#include <sanguis/apply_log_level.hpp>
#include <sanguis/log_context.hpp>
#include <sanguis/log_location.hpp>
#include <sanguis/main.hpp>
#include <sanguis/main_object.hpp>
#include <sge/log/global_context.hpp>
#include <sge/log/location.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cstdlib>
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
		std::cout << desc << '\n';

		return awl::main::exit_success();
	}

	fcppt::log::level::type const log_level(
		sanguis::args::log_level(
			vm
		)
	);

	sanguis::apply_log_level(
		sanguis::log_location(),
		sanguis::log_context(),
		log_level
	);

	bool const server_only(
		sanguis::args::server_only(
			vm
		)
	);

	typedef fcppt::scoped_ptr<
		sanguis::load::context_base
	> server_context;

	server_context context;

	// TODO: ugly!
	if(
		server_only
	)
		context.take(
			fcppt::make_unique_ptr<
				sanguis::load::server_context
			>()
		);

	typedef fcppt::scoped_ptr<
		sanguis::main_object
	> main_object_scoped_ptr;

	main_object_scoped_ptr obj(
		server_only
		?
			sanguis::server::create(
				vm,
				*context
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

	return obj->run();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< FCPPT_TEXT("caught fcppt exception: ")
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< "caught standard exception: "
		<< _error.what()
		<< '\n';

	return awl::main::exit_failure();
}
