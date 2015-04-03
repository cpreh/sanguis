#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/optional_needed_width.hpp>
#include <sanguis/gui/impl/relayout_ancestor.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/button.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sanguis/gui/widget/reference_name_pair.hpp>
#include <sanguis/gui/widget/reference_name_vector.hpp>
#include <sanguis/gui/widget/tab.hpp>
#include <sanguis/gui/widget/unique_ptr.hpp>
#include <sanguis/gui/widget/unique_ptr_vector.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>


sanguis::gui::widget::tab::tab(
	sanguis::gui::context &_context,
	sanguis::gui::style::base const &_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sanguis::gui::widget::reference_name_vector const &_widgets
)
:
	sanguis::gui::widget::box_container(
		_context,
		sanguis::gui::widget::reference_alignment_vector(),
		sge::rucksack::axis::y
	),
	top_buttons_(
		fcppt::algorithm::map<
			sanguis::gui::widget::unique_ptr_vector
		>(
			_widgets,
			[
				&_style,
				&_renderer,
				&_font,
				this
			](
				sanguis::gui::widget::reference_name_pair const &_pair
			)
			{
				class gui_button
				:
					public sanguis::gui::widget::button
				{
					FCPPT_NONCOPYABLE(
						gui_button
					);
				public:
					gui_button(
						sanguis::gui::style::base const &_style_arg,
						sge::renderer::device::ffp &_renderer_arg,
						sge::font::object &_font_arg,
						sge::font::string const &_name,
						sanguis::gui::widget::reference const _widget,
						sanguis::gui::widget::tab &_self
					)
					:
						sanguis::gui::widget::button(
							_style_arg,
							_renderer_arg,
							_font_arg,
							_name,
							sanguis::gui::optional_needed_width()
						),
						click_connection_(
							this->click(
								[
									_widget,
									&_self
								]
								()
								{
									_self.replace(
										1u,
										sanguis::gui::widget::reference_alignment_pair(
											_widget,
											sge::rucksack::alignment::left_or_top
										)
									);

									sanguis::gui::impl::relayout_ancestor(
										_self
									);
								}
							)
						)
					{
					}

					~gui_button()
					{
					}
				private:
					fcppt::signal::scoped_connection const click_connection_;
				};

				return
					fcppt::make_unique_ptr<
						gui_button
					>(
						_style,
						_renderer,
						_font,
						_pair.name(),
						_pair.reference(),
						*this
					);
			}
		)
	),
	top_buttons_box_(
		_context,
		fcppt::algorithm::map<
			sanguis::gui::widget::reference_alignment_vector
		>(
			top_buttons_,
			[](
				sanguis::gui::widget::unique_ptr const &_widget
			)
			{
				return
					sanguis::gui::widget::reference_alignment_pair(
						sanguis::gui::widget::reference(
							*_widget
						),
						sge::rucksack::alignment::left_or_top
					);
			}
		),
		sge::rucksack::axis::x
	)
{
	this->push_back(
		sanguis::gui::widget::reference_alignment_pair(
			sanguis::gui::widget::reference(
				top_buttons_box_
			),
			sge::rucksack::alignment::left_or_top
		)
	);

	if(
		!_widgets.empty()
	)
		this->push_back(
			sanguis::gui::widget::reference_alignment_pair(
				_widgets.front().reference(),
				sge::rucksack::alignment::left_or_top
			)
		);
}

sanguis::gui::widget::tab::~tab()
{
}
