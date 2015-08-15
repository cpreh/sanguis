#include <sanguis/client/gui/menu/resolution_chooser.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/gui/click_callback.hpp>
#include <sge/gui/context_fwd.hpp>
#include <sge/gui/index.hpp>
#include <sge/gui/optional_index.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/string_container.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/button.hpp>
#include <sge/gui/widget/choices.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/output.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::gui::menu::resolution_chooser::resolution_chooser(
	sge::gui::context &_context,
	sge::gui::style::base const &_style,
	sge::font::object &_font,
	sge::renderer::system const &_system,
	sge::renderer::device::ffp &_renderer,
	sge::renderer::device::index const _index
)
:
	display_modes_(
		_system.display_modes(
			_index
		)
	),
	renderer_(
		_renderer
	),
	choices_(
		_context,
		_style,
		_renderer,
		_font,
		// TODO: Add window mode
		fcppt::algorithm::map<
			sge::gui::string_container
		>(
			display_modes_,
			[](
				sge::renderer::display_mode::object const &_display_mode
			)
			{
				return
					sge::font::from_fcppt_string(
						fcppt::insert_to_fcppt_string(
							_display_mode
						)
					);
			}
		),
		display_modes_.empty()
		?
			sge::gui::optional_index()
		:
			sge::gui::optional_index(
				// TODO
				sge::gui::index(
					0u
				)
			)
	),
	apply_button_(
		_style,
		_renderer,
		_font,
		SGE_FONT_LIT("Apply"),
		sge::gui::optional_needed_width()
	),
	widget_(
		_context,
		sge::gui::widget::reference_alignment_vector{
			sge::gui::widget::reference_alignment_pair{
				sge::gui::widget::reference{
					choices_
				},
				sge::rucksack::alignment::center
			},
			sge::gui::widget::reference_alignment_pair{
				sge::gui::widget::reference{
					apply_button_
				},
				sge::rucksack::alignment::center
			}
		},
		sge::rucksack::axis::y
	),
	apply_connection_{
		apply_button_.click(
			sge::gui::click_callback{
				std::bind(
					&sanguis::client::gui::menu::resolution_chooser::on_apply,
					this
				)
			}
		)
	}
{
}

sanguis::client::gui::menu::resolution_chooser::~resolution_chooser()
{
}

sge::gui::widget::base &
sanguis::client::gui::menu::resolution_chooser::widget()
{
	return
		widget_;
}

void
sanguis::client::gui::menu::resolution_chooser::on_apply()
{
	fcppt::maybe_void(
		choices_.index(),
		[
			this
		](
			sge::gui::index const _index
		)
		{
			renderer_.display_mode(
				sge::renderer::display_mode::optional_object(
					display_modes_[
						_index.get()
					]
				)
			);
		}
	);
}
