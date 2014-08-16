#ifndef SANGUIS_GUI_BACKGROUND_BASE_HPP_INCLUDED
#define SANGUIS_GUI_BACKGROUND_BASE_HPP_INCLUDED

#include <sanguis/gui/background/base_fwd.hpp>
#include <sanguis/gui/main_area/base_fwd.hpp>
#include <sanguis/gui/renderer/base_fwd.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace background
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	explicit
	base(
		sanguis::gui::main_area::base &
	);
public:
	virtual
	~base() = 0;

	void
	draw(
		sanguis::gui::renderer::base &,
		sge::renderer::context::ffp &
	);

	sanguis::gui::widget::base &
	widget();
private:
	virtual
	void
	on_draw(
		sanguis::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) = 0;

	sanguis::gui::main_area::base &main_area_;
};

}
}
}

#endif
