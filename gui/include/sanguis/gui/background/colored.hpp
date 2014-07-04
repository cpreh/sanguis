#ifndef SANGUIS_GUI_BACKGROUND_COLORED_HPP_INCLUDED
#define SANGUIS_GUI_BACKGROUND_COLORED_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/background/base.hpp>
#include <sanguis/gui/main_area/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace background
{

class colored
:
	public sanguis::gui::background::base
{
	FCPPT_NONCOPYABLE(
		colored
	);
public:
	SANGUIS_GUI_SYMBOL
	colored(
		sge::renderer::device::ffp &,
		sanguis::gui::main_area::base &
	);

	SANGUIS_GUI_SYMBOL
	~colored()
	override;
private:
	void
	on_draw(
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	)
	override;

	sge::renderer::device::ffp &renderer_;
};

}
}
}

#endif
