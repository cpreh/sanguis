#ifndef SANGUIS_GUI_WIDGET_BOX_CONTAINER_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_BOX_CONTAINER_HPP_INCLUDED

#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/box_container_fwd.hpp>
#include <sanguis/gui/widget/container.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair_fwd.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sge/rucksack/alignment_fwd.hpp>
#include <sge/rucksack/aspect_fwd.hpp>
#include <sge/rucksack/axis_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/box/base.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class box_container
:
	public sanguis::gui::widget::container
{
	FCPPT_NONCOPYABLE(
		box_container
	);
public:
	SANGUIS_GUI_SYMBOL
	box_container(
		sanguis::gui::context &,
		sanguis::gui::widget::reference_alignment_vector const &,
		sge::rucksack::axis,
		sge::rucksack::aspect
	);

	SANGUIS_GUI_SYMBOL
	~box_container();

	SANGUIS_GUI_SYMBOL
	void
	push_front(
		sanguis::gui::widget::reference_alignment_pair const &
	);

	SANGUIS_GUI_SYMBOL
	void
	pop_front();

	SANGUIS_GUI_SYMBOL
	void
	push_back(
		sanguis::gui::widget::reference_alignment_pair const &
	);

	SANGUIS_GUI_SYMBOL
	void
	pop_back();

	SANGUIS_GUI_SYMBOL
	void
	replace(
		sge::rucksack::widget::box::base::size_type,
		sanguis::gui::widget::reference_alignment_pair const &
	);

	SANGUIS_GUI_SYMBOL
	sge::rucksack::widget::box::base &
	box_layout();
private:
	sge::rucksack::widget::box::base layout_;
};

}
}
}

#endif
