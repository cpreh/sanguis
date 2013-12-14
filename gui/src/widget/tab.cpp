#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/default_aspect.hpp>
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
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sanguis::gui::context &_context,
	sanguis::gui::widget::reference_name_vector const &_widgets
)
:
	sanguis::gui::widget::box_container(
		_context,
		sanguis::gui::widget::reference_alignment_vector(),
		sge::rucksack::axis::y,
		sanguis::gui::default_aspect()
	),
	top_buttons_(
		fcppt::algorithm::map<
			sanguis::gui::widget::unique_ptr_vector
		>(
			_widgets,
			[
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
						sge::renderer::device::ffp &_renderer_arg,
						sge::font::object &_font_arg,
						sge::font::string const &_name,
						sanguis::gui::widget::reference const _widget,
						sanguis::gui::widget::tab &_self
					)
					:
						sanguis::gui::widget::button(
							_renderer_arg,
							_font_arg,
							_name
						),
						click_connection_(
							this->click(
								[
									&_widget,
									&_self
								]
								()
								{
									_self.pop_back();

									_self.push_back(
										sanguis::gui::widget::reference_alignment_pair(
											_widget,
											sge::rucksack::alignment::right_or_bottom
										)
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
						sge::rucksack::alignment::center
					);
			}
		),
		sge::rucksack::axis::x,
		sanguis::gui::default_aspect()
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
				sge::rucksack::alignment::right_or_bottom
			)
		);
}

sanguis::gui::widget::tab::~tab()
{
}
