#include <sanguis/gui/context.hpp>
#include <sanguis/gui/duration.hpp>
#include <sanguis/gui/get_focus.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/container.hpp>
#include <sanguis/gui/widget/optional_ref.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_vector.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/algorithm/remove_if.hpp>
#include <fcppt/math/box/contains_point.hpp>


sanguis::gui::widget::container::container(
	sanguis::gui::context &_context,
	sanguis::gui::widget::reference_vector const &_widgets,
	sge::rucksack::widget::base &_layout
)
:
	sanguis::gui::widget::base(),
	context_(
		_context
	),
	widgets_(
		_widgets
	),
	layout_(
		_layout
	)
{
	this->foreach_widget(
		[
			this
		](
			sanguis::gui::widget::base &_widget
		)
		{
			_widget.parent(
				sanguis::gui::widget::optional_ref(
					*this
				)
			);
		}
	);
}

sanguis::gui::widget::container::~container()
{
	this->foreach_widget(
		[
			this
		](
			sanguis::gui::widget::base &_widget
		)
		{
			_widget.parent(
				sanguis::gui::widget::optional_ref()
			);

			this->context_.destroy(
				_widget
			);
		}
	);
}

sge::rucksack::widget::base &
sanguis::gui::widget::container::layout()
{
	return
		layout_;
}

void
sanguis::gui::widget::container::push_front_widget(
	sanguis::gui::widget::base &_widget
)
{
	widgets_.insert(
		widgets_.begin(),
		sanguis::gui::widget::reference(
			_widget
		)
	);

	_widget.parent(
		sanguis::gui::widget::optional_ref(
			*this
		)
	);
}

void
sanguis::gui::widget::container::pop_front_widget()
{
	widgets_.front().get().parent(
		sanguis::gui::widget::optional_ref()
	);

	widgets_.erase(
		widgets_.begin()
	);
}

void
sanguis::gui::widget::container::push_back_widget(
	sanguis::gui::widget::base &_widget
)
{
	widgets_.push_back(
		sanguis::gui::widget::reference(
			_widget
		)
	);

	_widget.parent(
		sanguis::gui::widget::optional_ref(
			*this
		)
	);
}

void
sanguis::gui::widget::container::pop_back_widget()
{
	widgets_.back().get().parent(
		sanguis::gui::widget::optional_ref()
	);

	widgets_.pop_back();
}

void
sanguis::gui::widget::container::on_update(
	sanguis::gui::duration const _duration
)
{
	this->foreach_widget(
		[
			_duration
		](
			sanguis::gui::widget::base &_widget
		)
		{
			_widget.on_update(
				_duration
			);
		}
	);
}

void
sanguis::gui::widget::container::on_draw(
	sge::renderer::context::ffp &_context
)
{
	this->foreach_widget(
		[
			&_context
		](
			sanguis::gui::widget::base &_widget
		)
		{
			_widget.on_draw(
				_context
			);
		}
	);
}

sanguis::gui::get_focus const
sanguis::gui::widget::container::on_click(
	sge::rucksack::vector const _pos
)
{
	if(
		!this->enabled()
	)
		return
			sanguis::gui::get_focus(
				false
			);

	this->foreach_widget(
		[
			this,
			_pos
		](
			sanguis::gui::widget::base &_widget
		)
		{
			if(
				!fcppt::math::box::contains_point(
					_widget.layout().area(),
					_pos
				)
			)
				return;

			if(
				_widget.on_click(
					_pos
				).get()
			)
				this->context_.focus(
					_widget
				);
		}
	);

	return
		sanguis::gui::get_focus(
			false
		);
}

void
sanguis::gui::widget::container::unregister(
	sanguis::gui::widget::base const &_widget
)
{
	fcppt::algorithm::remove_if(
		widgets_,
		[
			&_widget
		](
			sanguis::gui::widget::reference const _ref
		)
		{
			return
				&_ref.get()
				==
				&_widget;
		}
	);
}

template<
	typename Function
>
void
sanguis::gui::widget::container::foreach_widget(
	Function const &_function
)
{
	for(
		auto &ref
		:
		widgets_
	)
		_function(
			ref.get()
		);
}
