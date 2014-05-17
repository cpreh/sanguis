#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/index.hpp>
#include <sanguis/gui/index_callback.hpp>
#include <sanguis/gui/needed_width_from_strings.hpp>
#include <sanguis/gui/optional_index.hpp>
#include <sanguis/gui/optional_needed_width.hpp>
#include <sanguis/gui/string_container.hpp>
#include <sanguis/gui/text_color.hpp>
#include <sanguis/gui/aux_/style/text_color.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/choices.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/optional_bind.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::gui::widget::choices::choices(
	sanguis::gui::context &_context,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sanguis::gui::string_container const &_strings,
	sanguis::gui::optional_index const _index
)
:
	sanguis::gui::widget::box_container(
		_context,
		sanguis::gui::widget::reference_alignment_vector(),
		sge::rucksack::axis::x,
		sanguis::gui::default_aspect()
	),
	strings_(
		_strings
	),
	left_button_(
		_renderer,
		_font,
		SGE_FONT_LIT("<"),
		sanguis::gui::optional_needed_width()
	),
	middle_text_(
		_renderer,
		_font,
		_index
		?
			_strings[
				_index->get()
			]
		:
			sge::font::string()
		,
		sanguis::gui::text_color(
			sanguis::gui::aux_::style::text_color()
		),
		sanguis::gui::optional_needed_width(
			sanguis::gui::needed_width_from_strings(
				_font,
				_strings
			)
		)
	),
	right_button_(
		_renderer,
		_font,
		SGE_FONT_LIT(">"),
		sanguis::gui::optional_needed_width()
	),
	index_{
		_index
	},
	left_connection_{
		left_button_.click(
			std::bind(
				&sanguis::gui::widget::choices::left_clicked,
				this
			)
		)
	},
	right_connection_{
		right_button_.click(
			std::bind(
				&sanguis::gui::widget::choices::right_clicked,
				this
			)
		)
	},
	index_changed_()
{
	this->push_back(
		sanguis::gui::widget::reference_alignment_pair(
			sanguis::gui::widget::reference(
				left_button_
			),
			sge::rucksack::alignment::center
		)
	);

	this->push_back(
		sanguis::gui::widget::reference_alignment_pair(
			sanguis::gui::widget::reference(
				middle_text_
			),
			sge::rucksack::alignment::center
		)
	);

	this->push_back(
		sanguis::gui::widget::reference_alignment_pair(
			sanguis::gui::widget::reference(
				right_button_
			),
			sge::rucksack::alignment::center
		)
	);
}

sanguis::gui::widget::choices::~choices()
{
}

fcppt::signal::auto_connection
sanguis::gui::widget::choices::change(
	sanguis::gui::index_callback const &_callback
)
{
	return
		index_changed_.connect(
			_callback
		);
}

sanguis::gui::optional_index const
sanguis::gui::widget::choices::index() const
{
	return
		index_;
}

void
sanguis::gui::widget::choices::left_clicked()
{
	this->update_index(
		[
			this
		](
			sanguis::gui::index const _index
		)
		{
			return
				_index.get()
				==
				0u
				?
					index_
				:
					sanguis::gui::optional_index(
						sanguis::gui::index(
							_index.get()
							-
							1u
						)
					)
				;
		}
	);
}

void
sanguis::gui::widget::choices::right_clicked()
{
	this->update_index(
		[
			this
		](
			sanguis::gui::index const _index
		)
		{
			return
				_index.get()
				==
				strings_.size() - 1u
				?
					index_
				:
					sanguis::gui::optional_index(
						sanguis::gui::index(
							_index.get()
							+
							1u
						)
					)
				;
		}
	);
}

template<
	typename Func
>
void
sanguis::gui::widget::choices::update_index(
	Func const &_func
)
{
	index_ =
		fcppt::optional_bind(
			index_,
			_func
		);

	if(
		!index_
	)
		return;

	middle_text_.value(
		strings_[
			index_->get()
		]
	);

	index_changed_(
		*index_
	);
}
