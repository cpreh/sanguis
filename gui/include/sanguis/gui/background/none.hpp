#ifndef SANGUIS_GUI_BACKGROUND_NONE_HPP_INCLUDED
#define SANGUIS_GUI_BACKGROUND_NONE_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/background/base.hpp>
#include <sanguis/gui/main_area/base_fwd.hpp>
#include <sanguis/gui/renderer/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace background
{

class none
:
	public sanguis::gui::background::base
{
	FCPPT_NONCOPYABLE(
		none
	);
public:
	SANGUIS_GUI_SYMBOL
	explicit
	none(
		sanguis::gui::main_area::base &
	);

	SANGUIS_GUI_SYMBOL
	~none()
	override;
private:
	void
	on_draw(
		sanguis::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	)
	override;
};

}
}
}

#endif
