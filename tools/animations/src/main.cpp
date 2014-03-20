#include <sanguis/tools/animations/main_window.hpp>
#include <sanguis/tools/animations/sge_systems.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/image2d.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QApplication>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>


// TODO: Make an AWL main here
int
main(
	int argc,
	char *argv[]
)
try
{
	QApplication app(
		argc,
		argv
	);

	sanguis::tools::animations::sge_systems sge_systems(
		sge::systems::make_list(
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

	sanguis::tools::animations::main_window window(
		sge_systems
	);

	window.show();

	return
		app.exec();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
