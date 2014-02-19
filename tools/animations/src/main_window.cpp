#include <sanguis/tools/animations/main_window.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QFileDialog>
#include <QMainWindow>
#include <QObject>
#include <QString>
#include <ui_main_window.h>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::main_window::main_window(
	QWidget *const _parent
)
:
	QMainWindow(
		_parent
	),
	ui_(
		fcppt::make_unique_ptr<
			Ui::MainWindow
		>()
	)
{
	ui_->setupUi(
		this
	);
}

sanguis::tools::animations::main_window::~main_window()
{
}

void
sanguis::tools::animations::main_window::actionJSON()
{
	QString const result{
		QFileDialog::getOpenFileName(
			this,
			tr("Open JSON"),
			QString(),
			tr("JSON files (*.json)")
		)
	};

	if(
		result.isEmpty()
	)
		return;
}

void
sanguis::tools::animations::main_window::actionQuit()
{
	qApp->quit();
}
