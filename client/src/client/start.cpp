#include <sanguis/app_name.hpp>
#include <sanguis/company_name.hpp>
#include <sanguis/log_level_streams.hpp>
#include <sanguis/client/create.hpp>
#include <sanguis/client/object_base.hpp>
#include <sanguis/client/object_base_unique_ptr.hpp>
#include <sanguis/client/start.hpp>
#include <sanguis/client/args/result.hpp>
#include <sanguis/client/args/labels/log_level.hpp>
#include <sge/config/app_name.hpp>
#include <sge/config/log_path.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/scoped_output.hpp>
#include <fcppt/io/clog.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/optional_level.hpp>
#include <fcppt/record/get.hpp>


awl::main::exit_code
sanguis::client::start(
	sanguis::client::args::result const &_args
)
{
	// FIXME: Include all log streams
	awl::main::scoped_output const output(
		fcppt::io::clog(),
		sge::config::log_path(
			sanguis::company_name(),
			sge::config::app_name(
				sanguis::app_name()
			)
		)
	);

	fcppt::log::context log_context{
		fcppt::log::optional_level{
			fcppt::record::get<
				sanguis::client::args::labels::log_level
			>(
				_args
			)
		},
		sanguis::log_level_streams()
	};

	sanguis::client::object_base_unique_ptr const client(
		sanguis::client::create(
			log_context,
			_args
		)
	);

	return
		client->run();
}