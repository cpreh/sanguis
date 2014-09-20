#include <sanguis/gui/aux_/draw_image.hpp>
#include <sanguis/gui/renderer/base.hpp>
#include <sanguis/gui/style/base.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/image.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_to_index.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/make_axis_policy.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/dim.hpp>


sanguis::gui::widget::image::image(
	sanguis::gui::style::base const &_style,
	sge::texture::part const &_texture
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
									texture_.size()[
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
