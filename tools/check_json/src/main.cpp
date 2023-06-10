#include <sanguis/model/deserialize.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/main.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/error_output.hpp>
#include <fcppt/options/help_result.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/options/usage.hpp>
#include <fcppt/options/usage_output.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iostream>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wmissing-declarations)

int FCPPT_MAIN(int argc, fcppt::args_char **argv)
try
{
  FCPPT_RECORD_MAKE_LABEL(path_label);

  using parser_type = fcppt::options::argument<path_label, fcppt::string>;

  using result_type = fcppt::options::result_of<parser_type>;

  parser_type const parser{
      fcppt::options::long_name{FCPPT_TEXT("filename")}, fcppt::options::optional_help_text{}};

  fcppt::options::help_result<result_type> const result{fcppt::options::parse_help(
      fcppt::options::default_help_switch(), parser, fcppt::args_from_second(argc, argv))};

  return fcppt::variant::match(
      result,
      [](fcppt::options::result<result_type> const &_result)
      {
        return fcppt::either::match(
            _result,
            [](fcppt::options::error const &_error)
            {
              fcppt::io::cerr() << _error << FCPPT_TEXT('\n');

              return EXIT_FAILURE;
            },
            [](result_type const &_args)
            {
              sanguis::model::deserialize(
                  std::filesystem::path(fcppt::record::get<path_label>(_args)));

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
  fcppt::io::cerr() << _error.string() << FCPPT_TEXT('\n');

  return EXIT_FAILURE;
}
catch (std::exception const &_error)
{
  std::cerr << _error.what() << '\n';

  return EXIT_FAILURE;
}

FCPPT_PP_POP_WARNING
