#include <sanguis/gui/context.hpp>
#include <sanguis/gui/get_focus.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/container.hpp>
#include <sanguis/gui/widget/reference_vector.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_parent.hpp>
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
			_widget.layout().parent(
				sge::rucksack::widget::optional_parent(
					this->layout_
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
sanguis::gui::widget::container::on_update()
{
	this->foreach_widget(
		[](
			sanguis::gui::widget::base &_widget
		)
		{
			_widget.on_update();
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
					sge::rucksack::rect(
						_widget.layout().position(),
						_widget.layout().size()
					),
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
