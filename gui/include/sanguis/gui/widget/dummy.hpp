#ifndef SANGUIS_GUI_WIDGET_DUMMY_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_DUMMY_HPP_INCLUDED

#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/dummy_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis_policy2_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
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
	explicit
	dummy(
		sge::rucksack::axis_policy2 const &
	);

	~dummy()
	override;
private:
	void
	on_draw(
		sge::renderer::context::ffp &
	)
	override;

	sge::rucksack::widget::base &
	layout()
	override;

	sge::rucksack::widget::dummy layout_;
};

}
}
}

#endif
