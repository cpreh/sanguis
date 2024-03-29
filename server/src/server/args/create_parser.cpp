#include <sanguis/server/args/create_parser.hpp>
#include <sanguis/server/args/parser_unique_ptr.hpp>
#include <sanguis/server/args/result.hpp>
#include <sanguis/server/args/labels/log_level.hpp>
#include <sanguis/server/args/labels/port.hpp>
#include <alda/net/port.hpp>
#include <fcppt/strong_typedef_input.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/strong_typedef_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/text.hpp>
#include <fcppt/enum/names_array.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/log/level.hpp>
#include <fcppt/log/level_input.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/log/level_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/log/level_to_string_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/optional/make.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/make_base.hpp>
#include <fcppt/options/make_default_value.hpp>
#include <fcppt/options/option.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/optional_short_name.hpp>
#include <fcppt/options/pretty_type_enum.hpp> // NOLINT(misc-include-cleaner)

sanguis::server::args::parser_unique_ptr sanguis::server::args::create_parser()
{
  return fcppt::options::make_base<sanguis::server::args::result>(fcppt::options::apply(
      fcppt::options::option<sanguis::server::args::labels::port, alda::net::port>{
          fcppt::options::optional_short_name{},
          fcppt::options::long_name{FCPPT_TEXT("port")},
          fcppt::options::make_default_value(fcppt::optional::make(alda::net::port{
              31337U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          })),
          fcppt::options::optional_help_text{
              fcppt::options::help_text{FCPPT_TEXT("The port the server listens on")}}},
      fcppt::options::option<sanguis::server::args::labels::log_level, fcppt::log::level>{
          fcppt::options::optional_short_name{},
          fcppt::options::long_name{FCPPT_TEXT("server-log-level")},
          fcppt::options::make_default_value(fcppt::optional::make(fcppt::log::level::info)),
          fcppt::options::optional_help_text{
              fcppt::options::help_text{FCPPT_TEXT("The log level used by the server")}}}));
}
