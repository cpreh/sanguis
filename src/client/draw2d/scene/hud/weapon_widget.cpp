#include <sanguis/optional_weapon_description.hpp>
#include <sanguis/client/draw2d/scene/hud/weapon_widget.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/image.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sanguis/load/hud/context.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/alignment.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::client::draw2d::scene::hud::weapon_widget::weapon_widget(
	sanguis::load::hud::context &_resources,
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
		sge::font::string()
	),
	container_(
		_gui_context,
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					text_
				),
				sge::rucksack::alignment::left_or_top
			)
		},
		sge::rucksack::axis::x,
		sanguis::gui::default_aspect()
	)
{
}

sanguis::client::draw2d::scene::hud::weapon_widget::~weapon_widget()
{
}

void
sanguis::client::draw2d::scene::hud::weapon_widget::weapon_description(
	sanguis::optional_weapon_description const &_description
)
{
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
		return;

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
			sge::rucksack::alignment::left_or_top
		)
	);

	container_.layout().relayout();
}

sanguis::gui::widget::box_container &
sanguis::client::draw2d::scene::hud::weapon_widget::widget()
{
	return
		container_;
}
