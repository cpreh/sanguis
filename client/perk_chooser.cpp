#include "perk_chooser.hpp"
#include "from_perk_type.hpp"
#include "log.hpp"
#include "cursor/object.hpp"
#include "../media_path.hpp"
#include "../resolution_type.hpp"
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/make_image.hpp>
#include <sge/renderer/device.hpp>
#include <sge/image/multi_loader.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <utility>

namespace
{

fcppt::log::object mylogger(
	fcppt::log::parameters::inherited(
		sanguis::client::log(),
		FCPPT_TEXT("perk chooser: ")
	)
);

sge::gui::dim const
dialog_size(
	sanguis::resolution_type const &resolution_
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
	sanguis::resolution_type const &resolution_
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
}

sanguis::client::perk_chooser::activation::activation(
	perk_chooser &_instance
)
:
	instance_(_instance)
{
	FCPPT_ASSERT(!instance_.activated());
	instance_.activated(true);
}

sanguis::client::perk_chooser::activation::~activation()
{
	FCPPT_ASSERT(instance_.activated());
	instance_.activated(false);
}

sanguis::client::perk_chooser::perk_chooser(
	sge::renderer::device_ptr const _renderer,
	sge::input::system_ptr const _input_system,
	sge::image::multi_loader &_image_loader,
	sge::font::metrics_ptr const _font_metrics,
	send_callback const &_send_callback,
	sanguis::client::cursor::object_ptr const _cursor
)
:
	image_loader_(_image_loader),
	perks_(),
	current_level_(
		static_cast<level_type>(0)),
	consumed_levels_(
		static_cast<level_type>(0)),
	m_(
		_renderer,
		_input_system,
		sge::gui::skins::ptr(
			new sge::gui::skins::standard(
				_font_metrics
			)
		),
		_cursor
	),
	background_(
		m_,
		sge::gui::widgets::parameters()
			.pos(
				dialog_pos(
					_renderer->screen_size()
				)
			)
			.size(
				dialog_size(
					_renderer->screen_size()
				)
			)
			.activation(
				sge::gui::activation_state::inactive)
			.layout(
				fcppt::make_shared_ptr<sge::gui::layouts::vertical>())),
	perks_left_(
		background_,
		sge::gui::widgets::parameters(),
		FCPPT_TEXT("")),
	buttons_(),
	connections_(),
	dirty_(false),
	send_callback_(_send_callback),
	images_()
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("started, dialog size: ")
			<< background_.size()
			<< FCPPT_TEXT(", dialog position: ")
			<< background_.screen_pos());
}

void sanguis::client::perk_chooser::process()
{
	if (activated())
	{
		m_.update();
		m_.draw();
	}
}

void sanguis::client::perk_chooser::perks(
	perk_container const &_perks)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("got new set of perks"));

	perks_ = _perks;
	if (activated())
		regenerate_widgets();
	else
		dirty_ = true;
}

void sanguis::client::perk_chooser::level_up(
	level_type const _current_level)
{
	FCPPT_ASSERT(current_level_ <= _current_level);

	current_level_ = _current_level;
	if (activated())
		regenerate_label();
	else
		dirty_ = true;
}

bool sanguis::client::perk_chooser::activated() const
{
	switch (background_.activation())
	{
		case sge::gui::activation_state::active:
			return true;
		case sge::gui::activation_state::inactive:
			return false;
	}
	return false;
}

void sanguis::client::perk_chooser::activated(bool const n)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("set activation to ")
		             << n);

	background_.activation(
		n ? sge::gui::activation_state::active
		  : sge::gui::activation_state::inactive);
	
	if (n && dirty_)
	{
		regenerate_widgets();
		dirty_ = false;
	}
}

sanguis::client::level_type sanguis::client::perk_chooser::levels_left() const
{
	return static_cast<level_type>(
		current_level_-consumed_levels_);
}

void sanguis::client::perk_chooser::regenerate_label()
{
	perks_left_.text(
			FCPPT_TEXT("Perks left: ")+
			fcppt::lexical_cast<fcppt::string>(
				levels_left()));
}

void sanguis::client::perk_chooser::regenerate_widgets()
{
	regenerate_label();

	buttons_.clear();

	connections_.clear();

	BOOST_FOREACH(perk_container::const_reference r,perks_)
	{
		image_map::const_iterator const pi = 
			load_from_cache(
				r
			);

		buttons_.push_back(
			new sge::gui::widgets::buttons::image(
				background_,
				sge::gui::widgets::parameters(),
				pi->second.normal,
				pi->second.hover,
				pi->second.hover,
				pi->second.hover
			)
		);

		connections_.connect(
			buttons_.back().register_clicked(
				std::tr1::bind(
					&perk_chooser::choose_callback,
					this,
					r
				)
			)
		);
	}
}

void sanguis::client::perk_chooser::choose_callback(
	perk_type::type const p)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("chose perk ")
			<< p
			 << FCPPT_TEXT(", levels left: ")
			 << levels_left()
	);

	if (!levels_left())
		return;

	send_callback_(
		p);
	consume_level();
}

void sanguis::client::perk_chooser::consume_level()
{
	FCPPT_ASSERT(levels_left());
	consumed_levels_++;

	if (activated())
		regenerate_label();
	else
		dirty_ = true;
}

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
