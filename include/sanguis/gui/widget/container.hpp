#ifndef SANGUIS_GUI_WIDGET_CONTAINER_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_CONTAINER_HPP_INCLUDED

#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/get_focus_fwd.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/container_fwd.hpp>
#include <sanguis/gui/widget/reference_vector.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class container
:
	public sanguis::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		container
	);
public:
	container(
		sanguis::gui::context &,
		sanguis::gui::widget::reference_vector const &,
		sge::rucksack::widget::base &
	);

	~container();
private:
	void
	on_update()
	override;

	void
	on_draw(
		sge::renderer::context::ffp &
	)
	override;

	sanguis::gui::get_focus const
	on_click(
		sge::rucksack::vector
	)
	override;

	sge::rucksack::widget::base &
	layout()
	override;

	template<
		typename Function
	>
	void
	foreach_widget(
		Function const &
	);

	sanguis::gui::context &context_;

	sanguis::gui::widget::reference_vector const widgets_;

	sge::rucksack::widget::base &layout_;
};

}
}
}

#endif
