#include <sanguis/tools/animations/main.hpp>
#include <sanguis/tools/animations/main_window.hpp>
#include <sanguis/tools/animations/sge_systems.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/make_list.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QApplication>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
sanguis::tools::animations::main(
	awl::main::function_context const &_function_context
)
try
{
	int argc(
		_function_context.argc()
	);

	QApplication app(
		argc,
		_function_context.argv()
	);

	sanguis::tools::animations::sge_systems const sge_systems{
		sge::systems::make_list
		(
			sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set()
			)
		)
	};

	sanguis::tools::animations::main_window window(
		sge_systems
	);

	window.show();

	return
		awl::main::exit_code(
			app.exec()
		);
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return
		awl::main::exit_failure();
}
