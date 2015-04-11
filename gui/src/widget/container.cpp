#include <sanguis/gui/context.hpp>
#include <sanguis/gui/duration.hpp>
#include <sanguis/gui/get_focus.hpp>
#include <sanguis/gui/renderer/base_fwd.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/container.hpp>
#include <sanguis/gui/widget/optional_focus.hpp>
#include <sanguis/gui/widget/optional_ref.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_vector.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/optional_ref_compare.hpp>
#include <fcppt/algorithm/remove_if.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/math/box/contains_point.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


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

			return
				sanguis::gui::widget::container::foreach_result::continue_;
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

			return
				sanguis::gui::widget::container::foreach_result::continue_;
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
	sanguis::gui::widget::reference const _widget
)
{
	this->insert_widget(
		widgets_.begin(),
		_widget
	);
}

void
sanguis::gui::widget::container::pop_front_widget()
{
	this->erase_widget(
		widgets_.begin()
	);
}

void
sanguis::gui::widget::container::push_back_widget(
	sanguis::gui::widget::reference const _widget
)
{
	this->insert_widget(
		widgets_.end(),
		_widget
	);
}

void
sanguis::gui::widget::container::pop_back_widget()
{
	this->erase_widget(
		std::prev(
			widgets_.end()
		)
	);
}

void
sanguis::gui::widget::container::replace_widgets(
	sanguis::gui::widget::reference_vector::size_type const _pos,
	sanguis::gui::widget::reference const _widget
)
{
	this->insert_widget(
		this->erase_widget(
			std::next(
				widgets_.begin(),
				fcppt::cast::to_signed(
					_pos
				)
			)
		),
		_widget
	);
}

void
sanguis::gui::widget::container::clear_widgets()
{
	for(
		auto it(
			widgets_.begin()
		);
		it != widgets_.end();
		it =
			this->erase_widget(
				it
			)
	)
		;
}

void
sanguis::gui::widget::container::insert_widget(
	sanguis::gui::widget::reference_vector::iterator const _pos,
	sanguis::gui::widget::reference const _widget
)
{
	widgets_.insert(
		_pos,
		_widget
	);

	_widget.get().parent(
		sanguis::gui::widget::optional_ref(
			*this
		)
	);
}

sanguis::gui::widget::reference_vector::iterator
sanguis::gui::widget::container::erase_widget(
	sanguis::gui::widget::reference_vector::iterator const _pos
)
{
	_pos->get().parent(
		sanguis::gui::widget::optional_ref()
	);

	return
		widgets_.erase(
			_pos
		);
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

			return
				sanguis::gui::widget::container::foreach_result::continue_;
		}
	);
}

void
sanguis::gui::widget::container::on_draw(
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context
)
{
	this->foreach_widget(
		[
			&_renderer,
			&_context
		](
			sanguis::gui::widget::base &_widget
		)
		{
			_widget.on_draw(
				_renderer,
				_context
			);

			return
				sanguis::gui::widget::container::foreach_result::continue_;
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
				return
					sanguis::gui::widget::container::foreach_result::continue_;

			if(
				_widget.on_click(
					_pos
				)
				==
				sanguis::gui::get_focus{
					true
				}
			)
				this->context_.focus(
					_widget
				);

			return
				sanguis::gui::widget::container::foreach_result::abort;
		}
	);

	return
		sanguis::gui::get_focus(
			false
		);
}

sanguis::gui::widget::optional_ref const
sanguis::gui::widget::container::on_tab(
	sanguis::gui::widget::optional_focus &_focus
)
{
	for(
		auto &ref
		:
		widgets_
	)
	{
		sanguis::gui::widget::optional_ref const result(
			ref.get().on_tab(
				_focus
			)
		);

		if(
			!result.has_value()
		)
			continue;

		if(
			!_focus.get().has_value()
		)
			return
				result;

		if(
			fcppt::optional_ref_compare(
				_focus.get(),
				result
			)
		)
			_focus =
				sanguis::gui::widget::optional_focus(
					sanguis::gui::widget::optional_ref()
				);
	}

	return
		sanguis::gui::widget::optional_ref();
}

void
sanguis::gui::widget::container::unregister(
	sanguis::gui::widget::base const &_widget
)
{
	context_.destroy(
		_widget
	);

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
		if(
			_function(
				ref.get()
			)
			==
			sanguis::gui::widget::container::foreach_result::abort
		)
			return;
}
