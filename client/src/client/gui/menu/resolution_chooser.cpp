#include <sanguis/client/gui/menu/resolution_chooser.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/index.hpp>
#include <sanguis/gui/optional_index.hpp>
#include <sanguis/gui/optional_needed_width.hpp>
#include <sanguis/gui/string_container.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/button.hpp>
#include <sanguis/gui/widget/choices.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/output.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::gui::menu::resolution_chooser::resolution_chooser(
	sanguis::gui::context &_context,
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
		_renderer,
		_font,
		// TODO: Add window mode
		fcppt::algorithm::map<
			sanguis::gui::string_container
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
			sanguis::gui::optional_index()
		:
			sanguis::gui::optional_index(
				// TODO
				sanguis::gui::index(
					0u
				)
			)
	),
	apply_button_(
		_renderer,
		_font,
		SGE_FONT_LIT("Apply"),
		sanguis::gui::optional_needed_width()
	),
	widget_(
		_context,
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair{
				sanguis::gui::widget::reference{
					choices_
				},
				sge::rucksack::alignment::center
			},
			sanguis::gui::widget::reference_alignment_pair{
				sanguis::gui::widget::reference{
					apply_button_
				},
				sge::rucksack::alignment::center
			}
		},
		sge::rucksack::axis::y,
		sanguis::gui::default_aspect()
	),
	apply_connection_{
		apply_button_.click(
			std::bind(
				&sanguis::client::gui::menu::resolution_chooser::on_apply,
				this
			)
		)
	}
{
}

sanguis::client::gui::menu::resolution_chooser::~resolution_chooser()
{
}

sanguis::gui::widget::base &
sanguis::client::gui::menu::resolution_chooser::widget()
{
	return
		widget_;
}

void
sanguis::client::gui::menu::resolution_chooser::on_apply()
{
	sanguis::gui::optional_index const index(
		choices_.index()
	);

	if(
		!index
	)
		return;

	renderer_.display_mode(
		sge::renderer::display_mode::optional_object(
			display_modes_[
				index->get()
			]
		)
	);
}
