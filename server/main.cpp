#include <sanguis/log_level_streams.hpp>
#include <sanguis/server/create.hpp>
#include <sanguis/server/object_base.hpp>
#include <sanguis/server/object_base_unique_ptr.hpp>
#include <sanguis/server/args/create_parser.hpp>
#include <sanguis/server/args/result.hpp>
#include <sanguis/server/args/labels/log_level.hpp>
#include <sanguis/server/args/labels/port.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/main.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/optional_level.hpp>
#include <fcppt/options/base.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/error_output.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/usage.hpp>
#include <fcppt/options/usage_output.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wmissing-declarations)

int FCPPT_MAIN(int argc, fcppt::args_char **argv)
try
{
  return fcppt::variant::match(
      fcppt::options::parse_help(
          fcppt::options::default_help_switch(),
          *sanguis::server::args::create_parser(),
          fcppt::args_from_second(argc, argv)),
      [](fcppt::options::result<sanguis::server::args::result> const &_result)
      {
        return fcppt::either::match(
            _result,
            [](fcppt::options::error const &_error)
            {
              fcppt::io::cerr() << _error << FCPPT_TEXT('\n');

              return EXIT_FAILURE;
            },
            [](sanguis::server::args::result const &_args)
            {
              fcppt::log::context log_context{
                  fcppt::log::optional_level{
                      fcppt::record::get<sanguis::server::args::labels::log_level>(_args)},
                  sanguis::log_level_streams()};

              sanguis::server::object_base_unique_ptr const server(sanguis::server::create(
                  fcppt::make_ref(log_context),
                  fcppt::record::get<sanguis::server::args::labels::port>(_args)));

              server->run();

              return EXIT_SUCCESS;
            });
      },
      [](fcppt::options::usage const &_usage)
      {
        fcppt::io::cout() << _usage << FCPPT_TEXT('\n');

        return EXIT_SUCCESS;
      });
}
catch (fcppt::exception const &_error)
{
  fcppt::io::cerr() << FCPPT_TEXT("Caught fcppt exception: ") << _error.string()
                    << FCPPT_TEXT('\n');

  return EXIT_FAILURE;
}
catch (std::exception const &_error)
{
  std::cout << "Caught standard exception: " << _error.what() << '\n';

  return EXIT_FAILURE;
}

FCPPT_PP_POP_WARNING
