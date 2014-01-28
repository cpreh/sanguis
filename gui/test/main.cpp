#include <sanguis/build/media_path.hpp>
#include <sanguis/gui/context.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/duration.hpp>
#include <sanguis/gui/master.hpp>
#include <sanguis/gui/text_color.hpp>
#include <sanguis/gui/viewport_adaptor.hpp>
#include <sanguis/gui/widget/button.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/edit.hpp>
#include <sanguis/gui/widget/image.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sanguis/gui/widget/reference_name_pair.hpp>
#include <sanguis/gui/widget/reference_name_vector.hpp>
#include <sanguis/gui/widget/reference_tree.hpp>
#include <sanguis/gui/widget/reference_tree_vector.hpp>
#include <sanguis/gui/widget/tab.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sanguis/gui/widget/tree.hpp>
#include <sanguis/gui/widget/tree_unique_ptr.hpp>
#include <sanguis/gui/widget/unique_ptr.hpp>
#include <sanguis/gui/widget/unique_ptr_tree.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_scoped_ptr.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/system.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/desired_fps.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/to_dpi.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/systems/cursor_demuxer.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/keyboard_collector.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_font.hpp>
#include <sge/systems/with_image2d.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/timer/scoped_frame_limiter.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/tree/map.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <main.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
sanguis_gui_test::main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance<
		boost::mpl::vector5<
			sge::systems::with_font,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_window,
			sge::systems::with_input<
				boost::mpl::vector2<
					sge::systems::keyboard_collector,
					sge::systems::cursor_demuxer
				>
			>,
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("gui test")
					),
					sge::window::dim(
						1024,
						768
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters::object(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::off,
						sge::renderer::pixel_format::optional_multi_samples(),
						sge::renderer::pixel_format::srgb::no
					),
					sge::renderer::parameters::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::fill_on_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)
		(
			sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set(
					sge::media::extension_set{
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					}
				)
			)
		)
	);

	sge::font::object_scoped_ptr const font(
		sys.font_system().create_font(
			sge::font::parameters()
			.dpi(
				sge::renderer::display_mode::to_dpi(
					sys.renderer_ffp().display_mode()
				)
			)
		)
	);

	sanguis::gui::widget::button button(
		sys.renderer_ffp(),
		*font,
		SGE_FONT_LIT("Quit")
	);

	fcppt::signal::scoped_connection const quit_connection(
		button.click(
			[
				&sys
			]()
			{
				sys.window_system().quit(
					awl::main::exit_success()
				);
			}
		)
	);

	sanguis::gui::widget::edit edit(
		sys.renderer_ffp(),
		*font,
		SGE_FONT_LIT("Test")
	);

	sanguis::gui::widget::image image(
		sys.renderer_ffp(),
		sys.image_system().load(
			sanguis::build_media_path()
			/
			FCPPT_TEXT("car.png")
		)->view()
	);

	sanguis::gui::context context;

	auto const make_tree(
		[
			&sys,
			&font
		](
			sge::font::string const &_label
		)
		{
			return
				sanguis::gui::widget::unique_ptr_tree(
					fcppt::make_unique_ptr<
						sanguis::gui::widget::text
					>(
						sys.renderer_ffp(),
						*font,
						_label,
						sanguis::gui::text_color(
							sge::image::color::predef::black()
						)
					),
					fcppt::assign::make_container<
						sanguis::gui::widget::unique_ptr_tree::child_list
					>(
						sanguis::gui::widget::unique_ptr_tree(
							fcppt::make_unique_ptr<
								sanguis::gui::widget::button
							>(
								sys.renderer_ffp(),
								*font,
								SGE_FONT_LIT("Child 1")
							)
						)
					)(
						sanguis::gui::widget::unique_ptr_tree(
							fcppt::make_unique_ptr<
								sanguis::gui::widget::button
							>(
								sys.renderer_ffp(),
								*font,
								SGE_FONT_LIT("Child 2 asdljasdljasdklasdjklasdjlkasdjaskldjjasdkljasdklasdjlk")
							)
						)
					)
					.move_container()
				);
		}
	);

	auto const make_widget_tree(
		[
			&context
		](
			sanguis::gui::widget::unique_ptr_tree const &_tree
		)
		{
			return
				fcppt::make_unique_ptr<
					sanguis::gui::widget::tree
				>(
					context,
					sanguis::gui::widget::reference_tree_vector{
						fcppt::container::tree::map<
							sanguis::gui::widget::reference_tree
						>(
							_tree,
							[](
								sanguis::gui::widget::unique_ptr const &_widget
							)
							{
								return
									sanguis::gui::widget::reference(
										*_widget
									);
							}
						)
					}
				);
		}
	);

	sanguis::gui::widget::unique_ptr_tree tree1_widgets(
		make_tree(
			SGE_FONT_LIT("Toplevel 1")
		)
	);

	sanguis::gui::widget::tree_unique_ptr tree1(
		make_widget_tree(
			tree1_widgets
		)
	);

	sanguis::gui::widget::unique_ptr_tree tree2_widgets(
		make_tree(
			SGE_FONT_LIT("Toplevel 2")
		)
	);

	sanguis::gui::widget::tree_unique_ptr tree2(
		make_widget_tree(
			tree2_widgets
		)
	);

	sanguis::gui::widget::tab tab(
		sys.renderer_ffp(),
		*font,
		context,
		sanguis::gui::widget::reference_name_vector{
			sanguis::gui::widget::reference_name_pair(
				sanguis::gui::widget::reference(
					*tree1
				),
				SGE_FONT_LIT("Tab 1 asdkljasdlasdlkasdjklasdjklasdjklasjjklasdfoasdioasdjhiosjjaojasdfojasdfojasdfoasdfjaklasdgjkl")
			),
			sanguis::gui::widget::reference_name_pair(
				sanguis::gui::widget::reference(
					*tree2
				),
				SGE_FONT_LIT("Tab 2")
			)
		}
	);

	sanguis::gui::widget::box_container line_widget(
		context,
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					button
				),
				sge::rucksack::alignment::center
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					edit
				),
				sge::rucksack::alignment::center
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					image
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::x,
		sanguis::gui::default_aspect()
	);

	sanguis::gui::widget::box_container main_widget(
		context,
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					tab
				),
				sge::rucksack::alignment::left_or_top
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					line_widget
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::y,
		sanguis::gui::default_aspect()
	);

	sanguis::gui::master master(
		sys.renderer_ffp(),
		sys.keyboard_collector(),
		sys.cursor_demuxer(),
		context,
		main_widget
	);

	sanguis::gui::viewport_adaptor viewport_adaptor(
		sys.renderer_ffp(),
		sys.viewport_manager(),
		main_widget.layout()
	);

	while(
		sys.window_system().poll()
	)
	{
		sge::timer::scoped_frame_limiter const limiter(
			sge::renderer::display_mode::desired_fps(
				sys.renderer_ffp().display_mode()
			)
		);

		master.update(
			// FIXME
			sanguis::gui::duration(
				0
			)
		);

		sge::renderer::context::scoped_ffp const scoped_block(
			sys.renderer_ffp(),
			sys.renderer_ffp().onscreen_target()
		);

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::color::predef::blue()
			)
		);

		master.draw(
			scoped_block.get()
		);
	}

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_error
)
{
	awl::show_error(
		_error.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	awl::show_error_narrow(
		_error.what()
	);

	return
		awl::main::exit_failure();
}
