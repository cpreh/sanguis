#include <sanguis/exception.hpp>
#include <sanguis/client/gui/perk/line.hpp>
#include <sanguis/client/gui/perk/line_unique_ptr.hpp>
#include <sanguis/client/gui/perk/line_unique_ptr_tree.hpp>
#include <sanguis/client/gui/perk/line_unique_ptr_tree_vector.hpp>
#include <sanguis/client/gui/perk/tab.hpp>
#include <sanguis/client/perk/category_to_string.hpp>
#include <sanguis/client/perk/const_tree_range.hpp>
#include <sanguis/client/perk/optional_info.hpp>
#include <sanguis/client/perk/state_ref.hpp>
#include <sanguis/client/perk/to_category.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_tree.hpp>
#include <sge/gui/widget/reference_tree_vector.hpp>
#include <sge/gui/widget/tree_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/tree/map.hpp>
#include <fcppt/optional/to_exception.hpp>

sanguis::client::gui::perk::tab::tab(
    sge::renderer::device::ffp_ref const _renderer,
    sge::font::object_ref const _font,
    sge::gui::context_ref const _context,
    sge::gui::style::const_reference const _style,
    sanguis::client::perk::state_ref const _state,
    sanguis::client::perk::const_tree_range const &_range)
    : tree_widgets_(fcppt::algorithm::map<sanguis::client::gui::perk::line_unique_ptr_tree_vector>(
          _range,
          [&_renderer, &_font, &_context, &_style, &_state](
              sanguis::client::perk::tree const &_element)
          {
            return fcppt::container::tree::map<sanguis::client::gui::perk::line_unique_ptr_tree>(
                _element,
                [&_renderer, &_font, &_context, &_style, &_state](
                    sanguis::client::perk::optional_info const &_info)
                {
                  return fcppt::make_unique_ptr<sanguis::client::gui::perk::line>(
                      _renderer,
                      _font,
                      _context,
                      _style,
                      _state,
                      fcppt::optional::to_exception(
                          _info,
                          [] { return sanguis::exception{FCPPT_TEXT("Perk info not found!")}; }));
                });
          })),
      tree_(
          _context,
          fcppt::algorithm::map<sge::gui::widget::reference_tree_vector>(
              tree_widgets_,
              [](sanguis::client::gui::perk::line_unique_ptr_tree const &_tree)
              {
                return fcppt::container::tree::map<sge::gui::widget::reference_tree>(
                    _tree,
                    [](sanguis::client::gui::perk::line_unique_ptr const &_line)
                    { return sge::gui::widget::reference(_line->widget()); });
              })),
      name_(sge::font::from_fcppt_string(
          sanguis::client::perk::category_to_string(sanguis::client::perk::to_category(
              fcppt::optional::to_exception(
                  // TODO(philipp): This is unsafe!
                  _range.begin()->value(),
                  [] { return sanguis::exception{FCPPT_TEXT("Perk info not found!")}; })
                  .perk_type()))))
{
}

sanguis::client::gui::perk::tab::~tab() = default;

sge::gui::widget::tree &sanguis::client::gui::perk::tab::widget() { return tree_; }

sge::font::string const &sanguis::client::gui::perk::tab::name() const { return name_; }
