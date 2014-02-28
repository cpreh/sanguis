#include <sanguis/model/deserialize.hpp>
#include <sanguis/model/exception.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/tools/animations/main_window.hpp>
#include <sanguis/tools/animations/fcppt_string_to_qt.hpp>
#include <sanguis/tools/animations/qt_string_to_fcppt.hpp>
#include <sanguis/tools/animations/sge_systems.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QString>
#include <ui_main_window.h>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::main_window::main_window(
	sanguis::tools::animations::sge_systems &_sge_systems
)
:
	QMainWindow(
		nullptr
	),
	sge_systems_(
		_sge_systems
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

	try
	{
		sanguis::model::object loaded_model(
			sanguis::model::deserialize(
				sanguis::tools::animations::qt_string_to_fcppt(
					result
				)
			)
		);
	}
	catch(
		sanguis::model::exception const &_error
	)
	{
		QMessageBox msgbox(
			QMessageBox::Icon::Critical,
			QString(
				tr("Error loading JSON")
			),
			sanguis::tools::animations::fcppt_string_to_qt(
				_error.string()
			),
			QMessageBox::StandardButton::Ok,
			this
		);

		msgbox.exec();
	}
}

void
sanguis::tools::animations::main_window::actionQuit()
{
	qApp->quit();
}
