#include <sanguis/model/animation.hpp>
#include <sanguis/model/animation_delay.hpp>
#include <sanguis/model/deserialize.hpp>
#include <sanguis/model/exception.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/serialize.hpp>
#include <sanguis/tools/animations/main_window.hpp>
#include <sanguis/tools/animations/sge_systems.hpp>
#include <sanguis/tools/animations/qtutil/from_fcppt_string.hpp>
#include <sanguis/tools/animations/qtutil/to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/truncation_check_cast.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QString>
#include <ui_main_window.h>
#include <chrono>
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
	loaded_model_(),
	json_file_()
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

	json_file_ =
		result;

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

	ui_->globalDelaySpinBox->setValue(
		loaded_model_->animation_delay()
		?
			fcppt::truncation_check_cast<
				int
			>(
				loaded_model_->animation_delay()->get().count()
			)
		:
			0
	);
}

void
sanguis::tools::animations::main_window::actionSave()
{
	if(
		!loaded_model_
	)
		return;

	try
	{
		sanguis::model::serialize(
			sanguis::tools::animations::qtutil::to_fcppt_string(
				json_file_
			),
			*loaded_model_
		);
	}
	catch(
		sanguis::model::exception const &_error
	)
	{
		QMessageBox msgbox(
			QMessageBox::Icon::Critical,
			QString(
				tr("Error saving JSON")
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

void
sanguis::tools::animations::main_window::selectedAnimationChanged(
	QString const &_string
)
{
	QString const selected_part(
		ui_->partComboBox->currentText()
	);

	QString const selected_weapon_category(
		ui_->weaponComboBox->currentText()
	);

	if(
		!loaded_model_
		||
		selected_part.isEmpty()
		||
		selected_weapon_category.isEmpty()
		||
		_string.isEmpty()
	)
		return;

	sanguis::model::animation const &animation(
		loaded_model_->part(
			sanguis::tools::animations::qtutil::to_fcppt_string(
				selected_part
			)
		).weapon_category(
			sanguis::tools::animations::qtutil::to_fcppt_string(
				selected_weapon_category
			)
		).animation(
			sanguis::tools::animations::qtutil::to_fcppt_string(
				_string
			)
		)
	);

	ui_->delaySpinBox->setValue(
		animation.animation_delay()
		?
			fcppt::truncation_check_cast<
				int
			>(
				animation.animation_delay()->get().count()
			)
		:
			0
	);

	ui_->soundEdit->setText(
		animation.animation_sound()
		?
			sanguis::tools::animations::qtutil::from_fcppt_string(
				animation.animation_sound()->get()
			)
		:
			QString()
	);
}

void
sanguis::tools::animations::main_window::globalDelayChanged(
	int const _value
)
{
	if(
		!loaded_model_
	)
		return;

	loaded_model_->animation_delay(
		_value
		!=
		0
		?
			sanguis::model::optional_animation_delay(
				sanguis::model::animation_delay(
					std::chrono::milliseconds(
						_value
					)
				)
			)
		:
			sanguis::model::optional_animation_delay()
	);
}
