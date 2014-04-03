#ifndef SANGUIS_GUI_WIDGET_CONTAINER_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_CONTAINER_HPP_INCLUDED

#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/duration.hpp>
#include <sanguis/gui/get_focus_fwd.hpp>
#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/container_fwd.hpp>
#include <sanguis/gui/widget/optional_focus_fwd.hpp>
#include <sanguis/gui/widget/optional_ref_fwd.hpp>
#include <sanguis/gui/widget/reference_fwd.hpp>
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
	SANGUIS_GUI_SYMBOL
	container(
		sanguis::gui::context &,
		sanguis::gui::widget::reference_vector const &,
		sge::rucksack::widget::base &
	);

	SANGUIS_GUI_SYMBOL
	~container();

	SANGUIS_GUI_SYMBOL
	sge::rucksack::widget::base &
	layout()
	override;
protected:
	void
	push_front_widget(
		sanguis::gui::widget::reference
	);

	void
	pop_front_widget();

	void
	push_back_widget(
		sanguis::gui::widget::reference
	);

	void
	pop_back_widget();

	void
	replace_widgets(
		sanguis::gui::widget::reference_vector::size_type,
		sanguis::gui::widget::reference
	);
private:
	void
	insert_widget(
		sanguis::gui::widget::reference_vector::iterator,
		sanguis::gui::widget::reference
	);

	sanguis::gui::widget::reference_vector::iterator
	erase_widget(
		sanguis::gui::widget::reference_vector::iterator
	);

	void
	on_update(
		sanguis::gui::duration
	)
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

	sanguis::gui::widget::optional_ref const
	on_tab(
		sanguis::gui::widget::optional_focus &
	)
	override;

	void
	unregister(
		sanguis::gui::widget::base const &
	)
	override;

	template<
		typename Function
	>
	void
	foreach_widget(
		Function const &
	);

	sanguis::gui::context &context_;

	sanguis::gui::widget::reference_vector widgets_;

	sge::rucksack::widget::base &layout_;
};

}
}
}

#endif
