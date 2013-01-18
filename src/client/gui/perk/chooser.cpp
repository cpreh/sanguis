#include <sanguis/client/gui/perk/chooser.hpp>
#include <sanguis/client/gui/perk/item_color.hpp>
#include <sanguis/client/gui/perk/item.hpp>
#include <sanguis/client/gui/perk/item_tree.hpp>
#include <sanguis/client/gui/perk/item_user_data.hpp>
#include <sanguis/client/gui/object.hpp>
#include <sanguis/client/perk/choosable_state.hpp>
#include <sanguis/client/perk/find_info.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/state.hpp>
#include <sanguis/client/perk/to_string.hpp>
#include <sanguis/media_path.hpp>
#include <sanguis/perk_type.hpp>
#include <sge/cegui/to_cegui_color.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/algorithm/find_if_exn.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/container/tree/object_impl.hpp>
#include <fcppt/container/tree/pre_order.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/widgets/Tree.h>
#include <algorithm>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::gui::perk::chooser::chooser(
	gui::object &_gui,
	client::perk::state &_state
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
				&gui::perk::chooser::perks,
				this,
				std::placeholders::_1
			)
		)
	),
	level_connection_(
		_state.register_level_change(
			std::bind(
				&gui::perk::chooser::level,
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
					&chooser::handle_selection_changed,
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
					&chooser::handle_perk_choose,
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
	client::perk::tree const &_perks
)
{
	items_.clear();

	typedef fcppt::container::tree::pre_order<
		client::perk::tree const
	> perk_traversal;

	perk_traversal perk_trav(
		_perks
	);

	for(
		perk_traversal::iterator it(
			perk_trav.begin()
		);
		it != perk_trav.end();
		++it
	)
	{
		typedef fcppt::container::tree::pre_order<
			gui::perk::item_tree
		> item_traversal;

		// root node, skip it
		if(
			!it->has_parent()
		)
			continue;

		item_traversal item_trav(
			items_
		);

		sanguis::perk_type const cur_type(
			it->parent()->value().type()
		);

		item_traversal::iterator const item_it(
			std::find_if(
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

		if(
			item_it == item_trav.end()
		)
			items_.push_back(
				fcppt::make_unique_ptr<
					gui::perk::item
				>(
					gui::perk::node(
						&tree_widget_
					),
					gui_,
					it->value()
				)
			);
		else
			item_it->push_back(
				fcppt::make_unique_ptr<
					gui::perk::item
				>(
					gui::perk::node(
						&item_it->value()->widget()
					),
					gui_,
					it->value()
				)
			);
	}

	this->update_tree_data();
}

void
sanguis::client::gui::perk::chooser::level(
	client::player_level
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
			),
			gui_.charconv_system()
		)
	);
}

void
sanguis::client::gui::perk::chooser::update_bottom_text(
	sanguis::perk_type const _perk_type
)
{
	client::perk::info const &info(
		client::perk::find_info(
			_perk_type,
			state_.perks()
		).value()
	);

	bottom_text_.setText(
		sge::cegui::to_cegui_string(
			FCPPT_TEXT('(')
			+
			client::perk::to_string(
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
			),
			gui_.charconv_system()
		)
	);
}

void
sanguis::client::gui::perk::chooser::update_tree_data()
{
	typedef fcppt::container::tree::pre_order<
		gui::perk::item_tree
	> traversal;

	traversal trav(
		items_
	);

	for(
		traversal::iterator it(
			trav.begin()
		);
		it != trav.end();
		++it
	)
	{
		// skip the tree itself
		if(
			!it->has_parent()
		)
			continue;

		CEGUI::TreeItem &widget(
			it->value()->widget()
		);

		widget.setTextColours(
			sge::cegui::to_cegui_color(
				gui::perk::item_color(
					state_.choosable(
						it->value()->perk_type()
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

#if 0
sanguis::client::perk_chooser::image_map::const_iterator const
	sanguis::client::perk_chooser::load_from_cache(
		perk_type::type const r)
{
	fcppt::filesystem::path const p =
		media_path()/
		FCPPT_TEXT("menu")/
		FCPPT_TEXT("buttons")/
		FCPPT_TEXT("perks");

	fcppt::filesystem::path const base =
		p/from_perk_type(r);

	image_map::const_iterator pi =
		images_.find(
			r
		);

	if (pi != images_.end())
		return pi;

	perk_image new_image;

	new_image.normal =
		sge::gui::make_image(
			image_loader_.load(
				base/
				FCPPT_TEXT("normal.png")
			)
		);

	new_image.hover =
		sge::gui::make_image(
			image_loader_.load(
				base/
				FCPPT_TEXT("hover.png")
			)
		);

	pi = images_.insert(
		std::make_pair(
			r,
			new_image
		)
	).first;

	return pi;
}
#endif
