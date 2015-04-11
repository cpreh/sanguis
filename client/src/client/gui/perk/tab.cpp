#include <sanguis/client/gui/perk/line.hpp>
#include <sanguis/client/gui/perk/line_unique_ptr.hpp>
#include <sanguis/client/gui/perk/line_unique_ptr_tree.hpp>
#include <sanguis/client/gui/perk/line_unique_ptr_tree_vector.hpp>
#include <sanguis/client/gui/perk/tab.hpp>
#include <sanguis/client/perk/category_to_string.hpp>
#include <sanguis/client/perk/const_tree_range.hpp>
#include <sanguis/client/perk/optional_info.hpp>
#include <sanguis/client/perk/state_fwd.hpp>
#include <sanguis/client/perk/to_category.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_tree_vector.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/tree/map.hpp>


sanguis::client::gui::perk::tab::tab(
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sanguis::gui::context &_context,
	sanguis::gui::style::base const &_style,
	sanguis::client::perk::state &_state,
	sanguis::client::perk::const_tree_range const &_range
)
:
	tree_widgets_(
		fcppt::algorithm::map<
			sanguis::client::gui::perk::line_unique_ptr_tree_vector
		>(
			_range,
			[
				&_renderer,
				&_font,
				&_context,
				&_style,
				&_state
			](
				sanguis::client::perk::tree const &_element
			)
			{
				return
					fcppt::container::tree::map<
						sanguis::client::gui::perk::line_unique_ptr_tree
					>(
						_element,
						[
							&_renderer,
							&_font,
							&_context,
							&_style,
							&_state
						](
							sanguis::client::perk::optional_info const &_info
						)
						{
							return
								fcppt::make_unique_ptr<
									sanguis::client::gui::perk::line
								>(
									_renderer,
									_font,
									_context,
									_style,
									_state,
									FCPPT_ASSERT_OPTIONAL_ERROR(
										_info
									)
								);
						}
					);
			}
		)
	),
	tree_(
		_context,
		fcppt::algorithm::map<
			sanguis::gui::widget::reference_tree_vector
		>(
			tree_widgets_,
			[](
				sanguis::client::gui::perk::line_unique_ptr_tree const &_tree
			)
			{
				return
					fcppt::container::tree::map<
						sanguis::gui::widget::reference_tree
					>(
						_tree,
						[](
							sanguis::client::gui::perk::line_unique_ptr const &_line
						)
						{
							return
								sanguis::gui::widget::reference(
									_line->widget()
								);
						}
					);
			}
		)
	),
	name_(
		sge::font::from_fcppt_string(
			sanguis::client::perk::category_to_string(
				sanguis::client::perk::to_category(
					// TODO: This is unsafe!
					FCPPT_ASSERT_OPTIONAL_ERROR(
						_range.begin()->value()
					).perk_type()
				)
			)
		)
	)
{
}

sanguis::client::gui::perk::tab::~tab()
{
}

sanguis::gui::widget::tree &
sanguis::client::gui::perk::tab::widget()
{
	return
		tree_;
}

sge::font::string const &
sanguis::client::gui::perk::tab::name() const
{
	return
		name_;
}
