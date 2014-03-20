#include <sanguis/model/deserialize.hpp>
#include <sanguis/model/exception.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/tools/animations/main_window.hpp>
#include <sanguis/tools/animations/sge_systems.hpp>
#include <sanguis/tools/animations/qtutil/from_fcppt_string.hpp>
#include <sanguis/tools/animations/qtutil/to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/assert/error.hpp>
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
	),
	loaded_model_()
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

	ui_->partComboBox->clear();

	try
	{
		loaded_model_ =
			sanguis::model::deserialize(
				sanguis::tools::animations::qtutil::to_fcppt_string(
					result
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
			sanguis::tools::animations::qtutil::from_fcppt_string(
				_error.string()
			),
			QMessageBox::StandardButton::Ok,
			this
		);

		msgbox.exec();

		return;
	}

	FCPPT_ASSERT_ERROR(
		loaded_model_.has_value()
	);

	for(
		auto const &part
		:
		loaded_model_->parts()
	)
		ui_->partComboBox->insertItem(
			0,
			sanguis::tools::animations::qtutil::from_fcppt_string(
				part.first
			)
		);
}

void
sanguis::tools::animations::main_window::actionQuit()
{
	qApp->quit();
}

void
sanguis::tools::animations::main_window::selectedPartChanged(
	QString const &_string
)
{
	if(
		!loaded_model_
		||
		_string.isEmpty()
	)
		return;

	ui_->weaponComboBox->clear();

	for(
		auto const &weapon_category
		:
		loaded_model_->part(
			sanguis::tools::animations::qtutil::to_fcppt_string(
				_string
			)
		).weapon_categories()
	)
		ui_->weaponComboBox->insertItem(
			0,
			sanguis::tools::animations::qtutil::from_fcppt_string(
				weapon_category.first
			)
		);
}

void
sanguis::tools::animations::main_window::selectedWeaponChanged(
	QString const &_string
)
{
	QString const selected_part(
		ui_->partComboBox->currentText()
	);

	if(
		!loaded_model_
		||
		selected_part.isEmpty()
		||
		_string.isEmpty()
	)
		return;

	ui_->animationComboBox->clear();

	for(
		auto const &animation
		:
		loaded_model_->part(
			sanguis::tools::animations::qtutil::to_fcppt_string(
				selected_part
			)
		).weapon_category(
			sanguis::tools::animations::qtutil::to_fcppt_string(
				_string
			)
		).animations()
	)
		ui_->animationComboBox->insertItem(
			0,
			sanguis::tools::animations::qtutil::from_fcppt_string(
				animation.first
			)
		);
}
