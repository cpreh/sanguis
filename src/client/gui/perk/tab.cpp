#include <sanguis/client/gui/perk/tab.hpp>
#include <sanguis/client/perk/category_to_string.hpp>
#include <sanguis/client/perk/const_tree_range.hpp>
#include <sanguis/client/perk/optional_info.hpp>
#include <sanguis/client/perk/to_category.hpp>
#include <sanguis/client/perk/to_string.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/widget/button.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_tree_vector.hpp>
#include <sanguis/gui/widget/unique_ptr.hpp>
#include <sanguis/gui/widget/unique_ptr_tree.hpp>
#include <sanguis/gui/widget/unique_ptr_tree_vector.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/tree/map.hpp>


sanguis::client::gui::perk::tab::tab(
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sanguis::gui::context &_context,
	sanguis::client::perk::const_tree_range const &_range
)
:
	tree_widgets_(
		fcppt::algorithm::map<
			sanguis::gui::widget::unique_ptr_tree_vector
		>(
			_range,
			[
				&_renderer,
				&_font
			](
				sanguis::client::perk::tree const &_element
			)
			{
				return
					fcppt::container::tree::map<
						sanguis::gui::widget::unique_ptr_tree
					>(
						_element,
						[
							&_renderer,
							&_font
						](
							sanguis::client::perk::optional_info const &_info
						)
						{
							return
								fcppt::make_unique_ptr<
									sanguis::gui::widget::button
								>(
									_renderer,
									_font,
									sge::font::from_fcppt_string(
										sanguis::client::perk::to_string(
											_info->perk_type()
										)
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
				sanguis::gui::widget::unique_ptr_tree const &_tree
			)
			{
				return
					fcppt::container::tree::map<
						sanguis::gui::widget::reference_tree
					>(
						_tree,
						[](
							sanguis::gui::widget::unique_ptr const &_widget
						)
						{
							return
								sanguis::gui::widget::reference(
									*_widget
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
					_range.begin()->value()->perk_type()
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
