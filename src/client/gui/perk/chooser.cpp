#include <sanguis/duration.hpp>
#include <sanguis/media_path.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/gui/object.hpp>
#include <sanguis/client/gui/perk/chooser.hpp>
#include <sanguis/client/gui/perk/item_color.hpp>
#include <sanguis/client/gui/perk/item.hpp>
#include <sanguis/client/gui/perk/item_tree.hpp>
#include <sanguis/client/gui/perk/item_user_data.hpp>
#include <sanguis/client/gui/perk/node.hpp>
#include <sanguis/client/perk/choosable_state.hpp>
#include <sanguis/client/perk/find_info.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/state.hpp>
#include <sanguis/client/perk/to_string.hpp>
#include <sge/cegui/to_cegui_color.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_if_exn.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/container/tree/pre_order.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/widgets/Tree.h>
#include <algorithm>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::gui::perk::chooser::chooser(
	sanguis::client::gui::object &_gui,
	sanguis::client::perk::state &_state
)
:
	gui_(
		_gui
	),
	state_(
		_state
	),
	active_perk_(),
	perk_connection_(
		_state.register_perks_change(
			std::bind(
				&sanguis::client::gui::perk::chooser::perks,
				this,
				std::placeholders::_1
			)
		)
	),
	level_connection_(
		_state.register_level_change(
			std::bind(
				&sanguis::client::gui::perk::chooser::level,
				this,
				std::placeholders::_1
			)
		)
	),
	scoped_layout_(
		gui_.system(),
		sanguis::media_path()
		/ FCPPT_TEXT("gui")
		/ FCPPT_TEXT("perk_chooser.layout")
	),
	scoped_gui_sheet_(
		gui_.system(),
		scoped_layout_.window()
	),
	tree_widget_(
		dynamic_cast<
			CEGUI::Tree &
		>(
			*scoped_layout_.window().getChild(
				"Tree"
			)
		)
	),
	top_text_(
		*scoped_layout_.window().getChild(
			"TopText"
		)
	),
	bottom_text_(
		*scoped_layout_.window().getChild(
			"BottomText"
		)
	),
	choose_button_(
		*scoped_layout_.window().getChild(
			"ChooseButton"
		)
	),
	selection_connection_(
		tree_widget_.subscribeEvent(
			CEGUI::Tree::EventSelectionChanged,
			CEGUI::Event::Subscriber(
				std::bind(
					&sanguis::client::gui::perk::chooser::handle_selection_changed,
					this,
					std::placeholders::_1
				)
			)
		)
	),
	choose_connection_(
		choose_button_.subscribeEvent(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				std::bind(
					&sanguis::client::gui::perk::chooser::handle_perk_choose,
					this,
					std::placeholders::_1
				)
			)
		)
	),
	items_()
{
	choose_button_.setEnabled(
		false
	);

	this->perks(
		_state.perks()
	);

	this->level(
		_state.player_level()
	);
}

sanguis::client::gui::perk::chooser::~chooser()
{
}

void
sanguis::client::gui::perk::chooser::process(
	sanguis::duration const &_delta
)
{
	gui_.update(
		_delta
	);
}

void
sanguis::client::gui::perk::chooser::draw(
	sge::renderer::context::ffp &_render_context
)
{
	gui_.render(
		_render_context
	);
}

void
sanguis::client::gui::perk::chooser::perks(
	sanguis::client::perk::tree const &_perks
)
{
	items_.clear();

	typedef fcppt::container::tree::pre_order<
		client::perk::tree const
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
					gui_,
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
					gui_,
					*element.value()
				)
			);
	}

	this->update_tree_data();
}

void
sanguis::client::gui::perk::chooser::level(
	sanguis::client::player_level
)
{
	this->update_top_text();
}

void
sanguis::client::gui::perk::chooser::update_top_text()
{
	top_text_.setText(
		sge::cegui::to_cegui_string(
			FCPPT_TEXT("Level: ")
			+
			fcppt::insert_to_fcppt_string(
				state_.player_level()
			)
			+
			FCPPT_TEXT(", Perks to choose: ")
			+
			fcppt::insert_to_fcppt_string(
				state_.levels_left()
			)
		)
	);
}

void
sanguis::client::gui::perk::chooser::update_bottom_text(
	sanguis::perk_type const _perk_type
)
{
	sanguis::client::perk::info const &info(
		*sanguis::client::perk::find_info(
			_perk_type,
			state_.perks()
		).value()
	);

	bottom_text_.setText(
		sge::cegui::to_cegui_string(
			FCPPT_TEXT('(')
			+
			sanguis::client::perk::to_string(
				_perk_type
			)
			+
			FCPPT_TEXT(") level: ")
			+
			fcppt::insert_to_fcppt_string(
				state_.perk_level(
					_perk_type
				)
			)
			+
			FCPPT_TEXT(", max level: ")
			+
			fcppt::insert_to_fcppt_string(
				info.max_level()
			)
		)
	);
}

void
sanguis::client::gui::perk::chooser::update_tree_data()
{
	typedef fcppt::container::tree::pre_order<
		sanguis::client::gui::perk::item_tree
	> traversal;

	for(
		auto const &element
		:
		traversal(
			items_
		)
	)
	{
		// skip the tree itself
		if(
			!element.has_parent()
		)
			continue;

		CEGUI::TreeItem &widget(
			element.value()->widget()
		);

		widget.setTextColours(
			sge::cegui::to_cegui_color(
				sanguis::client::gui::perk::item_color(
					state_.choosable(
						element.value()->perk_type()
					)
				)
			)
		);
	}
}

void
sanguis::client::gui::perk::chooser::update_choose_button(
	sanguis::perk_type const _perk_type
)
{
	choose_button_.setEnabled(
		state_.choosable(
			_perk_type
		)
		== sanguis::client::perk::choosable_state::ok
	);
}

bool
sanguis::client::gui::perk::chooser::handle_selection_changed(
	CEGUI::EventArgs const &
)
{
	CEGUI::TreeItem *const selected(
		tree_widget_.getFirstSelectedItem()
	);

	if(
		selected
	)
	{
		sanguis::perk_type const perk_type(
			gui::perk::item_user_data(
				*selected
			)
		);

		active_perk_ = perk_type;

		this->update_bottom_text(
			perk_type
		);

		this->update_choose_button(
			perk_type
		);
	}
	else
	{
		active_perk_.reset();

		bottom_text_.setText(
			CEGUI::String()
		);

		choose_button_.setEnabled(
			false
		);
	}

	return true;
}

bool
sanguis::client::gui::perk::chooser::handle_perk_choose(
	CEGUI::EventArgs const &
)
{
	if(
		state_.levels_left().get() == 0
	)
		return true;

	if(
		!active_perk_
	)
		return true;

	if(
		!state_.choose_perk(
			*active_perk_
		)
	)
		return true;

	this->update_top_text();

	this->update_bottom_text(
		*active_perk_
	);

	this->update_tree_data();

	this->update_choose_button(
		*active_perk_
	);

	return true;
}
