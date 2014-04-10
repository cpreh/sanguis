#include <sanguis/magazine_remaining.hpp>
#include <sanguis/optional_weapon_description.hpp>
#include <sanguis/client/gui/hud/weapon_widget.hpp>
#include <sanguis/client/load/hud/context.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/text_color.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/image.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/alignment.hpp>
#include <fcppt/insert_to_string.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::client::gui::hud::weapon_widget::weapon_widget(
	sanguis::client::load::hud::context &_resources,
	sanguis::gui::context &_gui_context,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font
)
:
	resources_(
		_resources
	),
	renderer_(
		_renderer
	),
	image_(),
	text_(
		_renderer,
		_font,
		sge::font::string(),
		sanguis::gui::text_color(
			sge::image::color::predef::black()
		)
	),
	container_(
		_gui_context,
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					text_
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::x,
		sanguis::gui::default_aspect()
	),
	description_()
{
}

sanguis::client::gui::hud::weapon_widget::~weapon_widget()
{
}

void
sanguis::client::gui::hud::weapon_widget::weapon_description(
	sanguis::optional_weapon_description const &_description
)
{
	description_ =
		_description;

	if(
		image_
	)
	{
		container_.pop_front();

		image_.reset();
	}

	if(
		!_description
	)
	{
		text_.value(
			sge::font::string()
		);

		return;
	}

	this->update_text(
		description_->magazine_remaining()
	);

	image_.take(
		fcppt::make_unique_ptr<
			sanguis::gui::widget::image
		>(
			renderer_,
			resources_.weapon_icon(
				_description->weapon_type()
			)
		)
	);

	container_.push_front(
		sanguis::gui::widget::reference_alignment_pair(
			sanguis::gui::widget::reference(
				*image_
			),
			sge::rucksack::alignment::center
		)
	);

	container_.layout().relayout();
}

void
sanguis::client::gui::hud::weapon_widget::magazine_remaining(
	sanguis::magazine_remaining const _magazine_remaining
)
{
	if(
		!description_
	)
		return;

	this->update_text(
		_magazine_remaining
	);
}

sanguis::gui::widget::box_container &
sanguis::client::gui::hud::weapon_widget::widget()
{
	return
		container_;
}

sanguis::optional_weapon_description const &
sanguis::client::gui::hud::weapon_widget::weapon_description() const
{
	return
		description_;
}

void
sanguis::client::gui::hud::weapon_widget::update_text(
	sanguis::magazine_remaining const _magazine_remaining
)
{
	sge::font::string value(
		fcppt::insert_to_string<
			sge::font::string
		>(
			_magazine_remaining
		)
	);

	if(
		description_->magazine_size().get()
		!=
		0u
	)
		value +=
			SGE_FONT_LIT('/')
			+
			fcppt::insert_to_string<
				sge::font::string
			>(
				description_->magazine_size()
			);

	if(
		description_->magazine_extra().get()
		!=
		0u
	)
		value +=
			SGE_FONT_LIT('+')
			+
			fcppt::insert_to_string<
				sge::font::string
			>(
				description_->magazine_extra()
			);

	text_.value(
		value
	);
}
