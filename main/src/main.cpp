#include <sanguis/main.hpp>
#include <sanguis/client/start.hpp>
#include <sanguis/client/args/create_parser.hpp>
#include <sanguis/client/args/result.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/show_message.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/options/base.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <exception>
#include <string>
#include <fcppt/config/external_end.hpp>

awl::main::exit_code sanguis::main(awl::main::function_context const &_function_context)
try
{
  return fcppt::variant::match(
      fcppt::options::parse_help(
          fcppt::options::default_help_switch(),
          *sanguis::client::args::create_parser(),
          fcppt::args_from_second(_function_context.argc(), _function_context.argv())),
      [](fcppt::options::result<sanguis::client::args::result> const &_result)
      {
        return fcppt::either::match(
            _result,
            [](fcppt::options::error const &_error)
            {
              awl::show_error(fcppt::output_to_fcppt_string(_error));

              return awl::main::exit_failure();
            },
            [](sanguis::client::args::result const &_args)
            { return sanguis::client::start(_args); });
      },
      [](fcppt::options::help_text const &_help_text)
      {
        awl::show_message(_help_text.get());

        return awl::main::exit_success();
      });
}
catch (fcppt::exception const &_error)
{
  awl::show_error(FCPPT_TEXT("Caught fcppt exception: ") + _error.string());

  return awl::main::exit_failure();
}
catch (std::exception const &_error)
{
  awl::show_error_narrow(std::string("Caught standard exception: ") + _error.what());

  return awl::main::exit_failure();
}
