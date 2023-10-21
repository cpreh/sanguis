#include <sanguis/client/gui/perk/make_description.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/strong_typedef_output.hpp> // NOLINT(misc-include-cleaner)

sge::font::string
sanguis::client::gui::perk::make_description(sanguis::client::perk::info const &_info)
{
  return SGE_FONT_LIT('(') +
         sge::font::from_fcppt_string(fcppt::output_to_fcppt_string(_info.level())) +
         SGE_FONT_LIT('/') +
         sge::font::from_fcppt_string(fcppt::output_to_fcppt_string(_info.max_level())) +
         SGE_FONT_LIT(") (requires player level ") +
         sge::font::from_fcppt_string(
             fcppt::output_to_fcppt_string(_info.required_player_level())) +
         SGE_FONT_LIT(", parent level ") +
         sge::font::from_fcppt_string(
             fcppt::output_to_fcppt_string(_info.required_parent_level())) +
         SGE_FONT_LIT(')');
}
