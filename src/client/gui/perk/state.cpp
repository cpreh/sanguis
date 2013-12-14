#include <sanguis/client/gui/perk/state.hpp>
#include <sanguis/gui/widget/unique_ptr_vector.hpp>


namespace
{

sanguis::gui::widget::unique_ptr_vector
make_top_buttons(
	sanguis::client::perk::state const &_perk_state
)
{
	typedef
	std::map<
		sanguis::client::perk::category,
		sanguis::gui::widget::unique_ptr
	>
	widget_map;

	widget_map widgets;

	for(
		auto const &node
		:
		_perk_state.tree()
	)
	{
		sanguis::client::perk::to_category const category(
			node.value().type()
		);

		widgets.insert(
			std::make_pair(
				category,
				fcppt::make_unique_ptr<
					sanguis::gui::widget::button
				>(
					sanguis::client::perk::category_to_string(
						category
					)
				)
			)
		);
	}

	return
		std::move(
			widgets
		);
}

}

sanguis::client::gui::perk::state::state()
:
	top_buttons_(
		make_top_buttons(
			_state
		)
	),
	top_buttons_widget_(
	),
	main_box_(
	)
{
}

sanguis::client::gui::perk::state::~state()
{
}

/*
	items_.clear();

	typedef fcppt::container::tree::pre_order<
		sanguis::client::perk::tree const
	> perk_traversal;

	for(
		auto const &element
		:
		perk_traversal(
			_perks
		)
	)
	{
		// root node, skip it
		if(
			!element.has_parent()
		)
			continue;

		if(
			element.parent()->value().has_value()
		)
		{
			sanguis::perk_type const cur_type(
				element.parent()->value()->type()
			);

			typedef fcppt::container::tree::pre_order<
				sanguis::client::gui::perk::item_tree
			> item_traversal;

			item_traversal item_trav(
				items_
			);

			item_traversal::iterator const item_it(
				fcppt::algorithm::find_if_exn(
					item_trav.begin(),
					item_trav.end(),
					[
						cur_type
					](
						sanguis::client::gui::perk::item_tree const &_tree
					)
					{
						return
							_tree.value()
							&&
							_tree.value()->perk_type() == cur_type;
					}
				)
			);

			item_it->push_back(
				fcppt::make_unique_ptr<
					sanguis::client::gui::perk::item
				>(
					sanguis::client::gui::perk::node(
						&item_it->value()->widget()
					),
					*element.value()
				)
			);
		}
		else
			items_.push_back(
				fcppt::make_unique_ptr<
					sanguis::client::gui::perk::item
				>(
					sanguis::client::gui::perk::node(
						&tree_widget_
					),
					*element.value()
				)
			);
	}

	this->update_tree_data();
*/
