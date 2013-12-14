#ifndef SANGUIS_GUI_WIDGET_IMAGE_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_IMAGE_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/image_fwd.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class image
:
	public sanguis::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		image
	);
public:
	SANGUIS_GUI_SYMBOL
	image(
		sge::renderer::device::ffp &,
		sge::image2d::view::const_object const &
	);

	SANGUIS_GUI_SYMBOL
	~image();

	SANGUIS_GUI_SYMBOL
	sge::rucksack::widget::base &
	layout()
	override;
private:
	void
	on_draw(
		sge::renderer::context::ffp &
	)
	override;

	sge::renderer::device::ffp &renderer_;

	sge::texture::part_raw_ptr const texture_;

	sge::rucksack::widget::dummy layout_;
};

}
}
}

#endif
