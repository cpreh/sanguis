#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/aux_/draw_image.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/image.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/is_expanding.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/optional_scalar.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/dim.hpp>


sanguis::gui::widget::image::image(
	sge::renderer::device::ffp &_renderer,
	sge::image2d::view::const_object const &_image
)
:
	renderer_(
		_renderer
	),
	texture_(
		sge::renderer::texture::create_planar_from_view(
			_renderer,
			_image,
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::emulate_srgb::no
		)
	),
	layout_(
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					fcppt::cast::size<
						sge::rucksack::scalar
					>(
						fcppt::cast::to_signed(
							texture_.size().w()
						)
					)
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()
				),
				sge::rucksack::is_expanding(
					false
				)
			),
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					fcppt::cast::size<
						sge::rucksack::scalar
					>(
						fcppt::cast::to_signed(
							texture_.size().h()
						)
					)
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()
				),
				sge::rucksack::is_expanding(
					false
				)
			),
			sanguis::gui::default_aspect()
		)
	)
{
}

sanguis::gui::widget::image::~image()
{
}

sge::rucksack::widget::base &
sanguis::gui::widget::image::layout()
{
	return
		layout_;
}

void
sanguis::gui::widget::image::on_draw(
	sge::renderer::context::ffp &_context
)
{
	sanguis::gui::aux_::draw_image(
		renderer_,
		_context,
		texture_,
		layout_.position()
		+
		(
			layout_.size()
			-
			fcppt::math::dim::structure_cast<
				sge::rucksack::dim
			>(
				texture_.area().size()
			)
		)
		/
		fcppt::literal<
			sge::rucksack::scalar
		>(
			2
		)
	);
}
