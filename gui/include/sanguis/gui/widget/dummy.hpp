#ifndef SANGUIS_GUI_WIDGET_DUMMY_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_DUMMY_HPP_INCLUDED

#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/dummy_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class dummy
:
	public sanguis::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		dummy
	);
public:
	dummy();

	~dummy()
	override;
private:
	void
	on_draw(
		sge::renderer::context::ffp &
	)
	override;
};

}
}
}

#endif
