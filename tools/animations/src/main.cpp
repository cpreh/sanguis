#include <sanguis/tools/animations/main_window.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QApplication>
#include <fcppt/config/external_end.hpp>


// TODO: Make an AWL main here
int
main(
	int argc,
	char *argv[]
)
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
