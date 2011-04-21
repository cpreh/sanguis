#include "chooser.hpp"
#include "item.hpp"
#include "item_tree.hpp"
#include "../object.hpp"
#include "../../perk/state.hpp"
#include "../../../media_path.hpp"
#include "../../../perk_type.hpp"
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/container/tree/object_impl.hpp>
#include <fcppt/container/tree/pre_order.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <CEGUI/elements/CEGUITree.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <algorithm>

namespace
{

class compare_perk
{
	FCPPT_NONASSIGNABLE(
		compare_perk
	);
public:
	explicit compare_perk(
		sanguis::perk_type::type
	);

	bool
	operator()(
		sanguis::client::gui::perk::item_tree const &
	) const;
private:
	sanguis::perk_type::type const type_;
};

}

sanguis::client::gui::perk::chooser::chooser(
	gui::object &_gui,
	client::perk::state &_state
)
:
	gui_(_gui),
	state_(_state),
	perk_connection_(
		_state.register_perks_change(
			std::tr1::bind(
				&gui::perk::chooser::perks,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	level_connection_(
		_state.register_level_change(
			std::tr1::bind(
				&gui::perk::chooser::level,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	scoped_layout_(
		sanguis::media_path()
		/ FCPPT_TEXT("gui")
		/ FCPPT_TEXT("perk_chooser.layout"),
		_gui.charconv_system()
	),
	scoped_gui_sheet_(
		scoped_layout_.window()
	),
	tree_widget_(
		dynamic_cast<
			CEGUI::Tree &
		>(
			*CEGUI::WindowManager::getSingleton().getWindow(
				"PerkChooser/Tree"
			)
		)
	),
	selection_connection_(
		tree_widget_.subscribeEvent(
			CEGUI::Tree::EventSelectionChanged,
			CEGUI::Event::Subscriber(
				std::tr1::bind(
					&chooser::handle_selection_changed,
					this,
					std::tr1::placeholders::_1
				)
			)
		)
	),
	items_()
{
	this->perks(
		_state.perks()
	);

	this->level(
		_state.level()
	);
}

sanguis::client::gui::perk::chooser::~chooser()
{
}

void
sanguis::client::gui::perk::chooser::process(
	time_type const _delta
)
{
	gui_.update(
		_delta
	);
}

void
sanguis::client::gui::perk::chooser::draw()
{
	gui_.render();
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

		item_traversal::iterator const item_it(
			std::find_if(
				item_trav.begin(),
				item_trav.end(),
				::compare_perk(
					it->parent().value().type()
				)
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
					fcppt::ref(
						gui_
					),
					it->value()
				)
			);
		else
			item_it->push_back(
				fcppt::make_unique_ptr<
					gui::perk::item
				>(
					gui::perk::node(
						&item_it->value().widget()
					),
					fcppt::ref(
						gui_
					),
					it->value()
				)
			);
	}
}

void
sanguis::client::gui::perk::chooser::level(
	client::level const _level
)
{
}

bool
sanguis::client::gui::perk::chooser::handle_selection_changed(
	CEGUI::EventArgs const &
)
{
	if(
		state_.levels_left().get() == 0
	)
		return true;

	CEGUI::TreeItem *const selected(
		tree_widget_.getFirstSelectedItem()
	);

	if(
		selected
	)
		state_.choose_perk(
			*static_cast<
				sanguis::perk_type::type const *
			>(
				selected->getUserData()
			)
		);

	return true;
}

namespace
{

compare_perk::compare_perk(
	sanguis::perk_type::type const _type
)
:
	type_(_type)
{
}

bool
compare_perk::operator()(
	sanguis::client::gui::perk::item_tree const &_tree
) const
{
	return
		_tree.holder()
		&&
		_tree.value().perk_type() == type_;
}

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
