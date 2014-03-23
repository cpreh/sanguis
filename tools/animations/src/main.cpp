#include <sanguis/tools/animations/main_window.hpp>
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

	sanguis::tools::animations::main_window window;

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
