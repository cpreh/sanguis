#include "chooser.hpp"
//#include "from_perk_type.hpp"
#include "../../log.hpp"
//#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
//#include <fcppt/filesystem/path.hpp>
//#include <fcppt/math/dim/arithmetic.hpp>
//#include <fcppt/math/dim/output.hpp>
//#include <fcppt/math/dim/structure_cast.hpp>
//#include <fcppt/math/vector/arithmetic.hpp>
//#include <fcppt/math/vector/output.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
//#include <fcppt/tr1/functional.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>

namespace
{

fcppt::log::object mylogger(
	fcppt::log::parameters::inherited(
		sanguis::client::log(),
		FCPPT_TEXT("perk chooser")
	)
);

#if 0
sge::gui::dim const
dialog_size(
	sanguis::resolution_type const &_resolution
)
{
	float const scale_x = 0.4f,
	            scale_y = 0.8f;
	
	return sge::gui::dim(
		static_cast<sge::gui::unit>(
			static_cast<float>(
				resolution_.w()
			) * scale_x
		),
		static_cast<sge::gui::unit>(
			static_cast<float>(
				resolution_.h()
			) * scale_y
		)
	);
}

sge::gui::point const
dialog_pos(
	sanguis::resolution_type const &_resolution
)
{
	return 
		fcppt::math::dim::structure_cast<sge::gui::point>(
			resolution_
		) /
		static_cast<sge::gui::unit>(2) -
		fcppt::math::dim::structure_cast<sge::gui::point>(
			dialog_size(
				resolution_
			)
		) /
		static_cast<sge::gui::unit>(2);
}
#endif

}

sanguis::client::gui::perk::chooser::chooser(
	gui::object &_gui,
	perk::send_callback const &_send_callback
)
:
	perks_(),
	current_level_(
		0
	),
	consumed_levels_(
		0
	),
	connections_(),
	send_callback_(_send_callback)
{
#if 0
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("started, dialog size: ")
			<< background_.size()
			<< FCPPT_TEXT(", dialog position: ")
			<< background_.screen_pos()
	);
#endif
}

sanguis::client::gui::perk::chooser::~chooser()
{
}

void
sanguis::client::gui::perk::chooser::process()
{
#if 0
	if(activated())
	{
		manager_.update();
		manager_.draw();
	}
#endif
}

void
sanguis::client::gui::perk::chooser::perks(
	client::perk_container const &_perks
)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("got new set of perks")
	);

	perks_ = _perks;

#if 0
	if (activated())
		regenerate_widgets();
	else
		dirty_ = true;
#endif
}

void
sanguis::client::gui::perk::chooser::level_up(
	client::level const _current_level
)
{
	FCPPT_ASSERT(
		current_level_ <= _current_level
	);

	current_level_ = _current_level;

#if 0
	if (activated())
		regenerate_label();
	else
		dirty_ = true;
#endif
}

bool
sanguis::client::gui::perk::chooser::activated() const
{
#if 0
	switch (background_.activation())
	{
		case sge::gui::activation_state::active:
			return true;
		case sge::gui::activation_state::inactive:
			return false;
	}
	return false;
#endif
	return false; // FIXME
}

void
sanguis::client::gui::perk::chooser::activated(
	bool const _activated
)
{
#if 0
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("set activation to ")
			<< _activated
	);

	background_.activation(
		_n
		?
			sge::gui::activation_state::active
		:
			sge::gui::activation_state::inactive
	);
	
	if (_n && dirty_)
	{
		regenerate_widgets();
		dirty_ = false;
	}
#endif
}

sanguis::client::level const
sanguis::client::gui::perk::chooser::levels_left() const
{
	return
		current_level_
		- consumed_levels_;
}

void
sanguis::client::gui::perk::chooser::regenerate_label()
{
#if 0
	perks_left_.text(
		SGE_FONT_TEXT_LIT("Perks left: ")
		+
		fcppt::lexical_cast<
			sge::font::text::string
		>(
			this->levels_left()
		)
	);
#endif
}

void
sanguis::client::gui::perk::chooser::regenerate_widgets()
{
#if 0
	regenerate_label();

	buttons_.clear();

	connections_.clear();

	BOOST_FOREACH(perk_container::const_reference r,perks_)
	{
		image_map::const_iterator const pi = 
			load_from_cache(
				r
			);

		fcppt::container::ptr::push_back_unique_ptr(
			buttons_,
			fcppt::make_unique_ptr<
				sge::gui::widgets::buttons::image
			>(
				sge::gui::widgets::parent_data(
					background_
				),
				sge::gui::widgets::parameters(),
				pi->second.normal,
				pi->second.hover,
				pi->second.hover,
				pi->second.hover
			)
		);

		connections_.add(
			buttons_.back().register_clicked(
				std::tr1::bind(
					&perk_chooser::choose_callback,
					this,
					r
				)
			)
		);
	}
#endif
}

void
sanguis::client::gui::perk::chooser::choose_callback(
	perk_type::type const _perk
)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("chose perk ")
			<< _perk
			<< FCPPT_TEXT(", levels left: ")
			<< this->levels_left()
	);

	if(
		this->levels_left().get() == 0
	)
		return;

	send_callback_(
		_perk
	);

	this->consume_level();
}

void
sanguis::client::gui::perk::chooser::consume_level()
{
	FCPPT_ASSERT(
		this->levels_left().get() != 0
	);

	consumed_levels_++;

#if 0
	if (activated())
		regenerate_label();
	else
		dirty_ = true;
#endif
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
