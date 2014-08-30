#include <sanguis/gui/aux_/draw_image.hpp>
#include <sanguis/gui/renderer/base.hpp>
#include <sanguis/gui/style/base.hpp>
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
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_to_index.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/make_axis_policy.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/dim.hpp>


sanguis::gui::widget::image::image(
	sanguis::gui::style::base const &_style,
	sge::renderer::device::ffp &_renderer,
	sge::image2d::view::const_object const &_image
)
:
	sanguis::gui::widget::image::image(
		_style,
		fcppt::make_shared_ptr<
			sge::texture::part_raw_ptr
		>(
			sge::renderer::texture::create_planar_from_view(
				_renderer,
				_image,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags_field::null(),
				sge::renderer::texture::emulate_srgb::no
			)
		)
	)
{
}

sanguis::gui::widget::image::image(
	sanguis::gui::style::base const &_style,
	sge::texture::const_part_shared_ptr const _texture
)
:
	style_(
		_style
	),
	texture_(
		_texture
	),
	layout_{
		sge::rucksack::make_axis_policy(
			[
				this
			](
				sge::rucksack::axis const _axis
			)
			{
				return
					sge::rucksack::axis_policy{
						sge::rucksack::preferred_size{
							fcppt::cast::size<
								sge::rucksack::scalar
							>(
								fcppt::cast::to_signed(
									texture_->size()[
										sge::rucksack::axis_to_index(
											_axis
										)
									]
								)
							)
							+
							style_.image_spacing()[
								sge::rucksack::axis_to_index(
									_axis
								)
							]
						}
					};
			}
		)
	}
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
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context
)
{
	style_.draw_image(
		_renderer,
		_context,
		this->layout().area()
	);

	_renderer.draw_image(
		_context,
		*texture_,
		layout_.position()
		+
		(
			layout_.size()
			-
			fcppt::math::dim::structure_cast<
				sge::rucksack::dim
			>(
				texture_->area().size()
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
