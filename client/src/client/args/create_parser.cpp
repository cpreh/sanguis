#include <sanguis/client/args/create_parser.hpp>
#include <sanguis/client/args/parser_unique_ptr.hpp>
#include <sanguis/client/args/result.hpp>
#include <sanguis/client/args/labels/display_height.hpp>
#include <sanguis/client/args/labels/display_width.hpp>
#include <sanguis/client/args/labels/draw_debug.hpp>
#include <sanguis/client/args/labels/history_size.hpp>
#include <sanguis/client/args/labels/log_level.hpp>
#include <sanguis/client/args/labels/multi_samples.hpp>
#include <sanguis/client/args/labels/sge_log_level.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/server/args/create_parser.hpp>
#include <sge/console/gfx/output_line_limit.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/pixel_format/multi_samples.hpp>
#include <fcppt/strong_typedef_input.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/level_input.hpp>
#include <fcppt/log/level_output.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/flag.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/make_active_value.hpp>
#include <fcppt/options/make_base.hpp>
#include <fcppt/options/make_default_value.hpp>
#include <fcppt/options/make_inactive_value.hpp>
#include <fcppt/options/make_optional.hpp>
#include <fcppt/options/no_default_value.hpp>
#include <fcppt/options/option.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/optional_short_name.hpp>


sanguis::client::args::parser_unique_ptr
sanguis::client::args::create_parser()
{
	return
		fcppt::options::make_base<
			sanguis::client::args::result
		>(
			fcppt::options::apply(
				sanguis::server::args::create_parser(),
				fcppt::options::make_optional(
					fcppt::options::option<
						sanguis::client::args::labels::display_width,
						sge::renderer::screen_unit
					>{
						fcppt::options::optional_short_name{},
						fcppt::options::long_name{
							FCPPT_TEXT("display-width")
						},
						fcppt::options::no_default_value<
							sge::renderer::screen_unit
						>(),
						fcppt::options::optional_help_text{
							fcppt::options::help_text{
								FCPPT_TEXT("The width of the display mode")
							}
						}
					}
				),
				fcppt::options::make_optional(
					fcppt::options::option<
						sanguis::client::args::labels::display_height,
						sge::renderer::screen_unit
					>{
						fcppt::options::optional_short_name{},
						fcppt::options::long_name{
							FCPPT_TEXT("display-height")
						},
						fcppt::options::no_default_value<
							sge::renderer::screen_unit
						>(),
						fcppt::options::optional_help_text{
							fcppt::options::help_text{
								FCPPT_TEXT("The height of the display mode")
							}
						}
					}
				),
				fcppt::options::option<
					sanguis::client::args::labels::log_level,
					fcppt::log::level
				>{
					fcppt::options::optional_short_name{},
					fcppt::options::long_name{
						FCPPT_TEXT("client-log-level")
					},
					fcppt::options::make_default_value(
						fcppt::optional::make(
							fcppt::log::level::info
						)
					),
					fcppt::options::optional_help_text{
						fcppt::options::help_text{
							FCPPT_TEXT("The log level used by the client")
						}
					}
				},
				fcppt::options::option<
					sanguis::client::args::labels::sge_log_level,
					fcppt::log::level
				>{
					fcppt::options::optional_short_name{},
					fcppt::options::long_name{
						FCPPT_TEXT("sge-log-level")
					},
					fcppt::options::make_default_value(
						fcppt::optional::make(
							fcppt::log::level::warning
						)
					),
					fcppt::options::optional_help_text{
						fcppt::options::help_text{
							FCPPT_TEXT("The log level used by sge")
						}
					}
				},
				fcppt::options::option<
					sanguis::client::args::labels::history_size,
					sge::console::gfx::output_line_limit
				>{
					fcppt::options::optional_short_name{},
					fcppt::options::long_name{
						FCPPT_TEXT("console-history-size")
					},
					fcppt::options::make_default_value(
						fcppt::optional::make(
							sge::console::gfx::output_line_limit{
								1000u
							}
						)
					),
					fcppt::options::optional_help_text{
						fcppt::options::help_text{
							FCPPT_TEXT("The number of history lines in the console")
						}
					}
				},
				fcppt::options::make_optional(
					fcppt::options::option<
						sanguis::client::args::labels::multi_samples,
						sge::renderer::pixel_format::multi_samples
					>{
						fcppt::options::optional_short_name{},
						fcppt::options::long_name{
							FCPPT_TEXT("multi-samples")
						},
						fcppt::options::no_default_value<
							sge::renderer::pixel_format::multi_samples
						>(),
						fcppt::options::optional_help_text{
							fcppt::options::help_text{
								FCPPT_TEXT("The number of multi samples")
							}
						}
					}
				),
				fcppt::options::flag<
					sanguis::client::args::labels::draw_debug,
					sanguis::client::draw::debug
				>{
					fcppt::options::optional_short_name{},
					fcppt::options::long_name{
						FCPPT_TEXT("draw-debug")
					},
					fcppt::options::make_active_value(
						sanguis::client::draw::debug{
							true
						}
					),
					fcppt::options::make_inactive_value(
						sanguis::client::draw::debug{
							false
						}
					),
					fcppt::options::optional_help_text{
						fcppt::options::help_text{
							FCPPT_TEXT("Whether to draw debug tiles")
						}
					}
				}
			)
		);
}
