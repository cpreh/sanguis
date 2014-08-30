#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/container.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sanguis/gui/widget/reference_vector.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/widget/box.hpp>
#include <fcppt/algorithm/map.hpp>


sanguis::gui::widget::box_container::box_container(
	sanguis::gui::context &_context,
	sanguis::gui::widget::reference_alignment_vector const &_widgets,
	sge::rucksack::axis const _axis
)
:
	sanguis::gui::widget::container(
		_context,
		fcppt::algorithm::map<
			sanguis::gui::widget::reference_vector
		>(
			_widgets,
			[](
				sanguis::gui::widget::reference_alignment_pair const &_pair
			)
			{
				return
					_pair.reference();
			}
		),
		// This is pretty dangerous but the base class only uses the
		// reference here
		layout_
	),
	layout_(
		_axis
	)
{
	for(
		auto const &element
		:
		_widgets
	)
		layout_.push_back_child(
			element.reference().get().layout(),
			element.alignment()
		);
}

sanguis::gui::widget::box_container::~box_container()
{
}

void
sanguis::gui::widget::box_container::push_front(
	sanguis::gui::widget::reference_alignment_pair const &_pair
)
{
	this->push_front_widget(
		_pair.reference()
	);

	layout_.push_front_child(
		_pair.reference().get().layout(),
		_pair.alignment()
	);
}

void
sanguis::gui::widget::box_container::pop_front()
{
	layout_.pop_front_child();

	this->pop_front_widget();
}

void
sanguis::gui::widget::box_container::push_back(
	sanguis::gui::widget::reference_alignment_pair const &_pair
)
{
	this->push_back_widget(
		_pair.reference()
	);

	layout_.push_back_child(
		_pair.reference().get().layout(),
		_pair.alignment()
	);
}

void
sanguis::gui::widget::box_container::replace(
	sge::rucksack::widget::box::size_type const _index,
	sanguis::gui::widget::reference_alignment_pair const &_pair
)
{
	this->replace_widgets(
		_index,
		_pair.reference()
	);

	layout_.replace_children(
		layout_.child_position(
			_index
		),
		_pair.reference().get().layout(),
		_pair.alignment()
	);
}

void
sanguis::gui::widget::box_container::pop_back()
{
	layout_.pop_back_child();

	this->pop_back_widget();
}

void
sanguis::gui::widget::box_container::clear()
{
	layout_.clear();

	this->clear_widgets();
}

sge::rucksack::widget::box &
sanguis::gui::widget::box_container::box_layout()
{
	return
		layout_;
}
