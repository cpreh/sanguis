#include <sanguis/model/animation.hpp>
#include <sanguis/model/animation_sound.hpp>
#include <sanguis/model/deserialize.hpp>
#include <sanguis/model/exception.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/optional_animation_sound.hpp>
#include <sanguis/model/serialize.hpp>
#include <sanguis/tools/animations/const_optional_image_file_ref.hpp>
#include <sanguis/tools/animations/find_image_file.hpp>
#include <sanguis/tools/animations/int_to_delay.hpp>
#include <sanguis/tools/animations/load_image_files.hpp>
#include <sanguis/tools/animations/main_window.hpp>
#include <sanguis/tools/animations/make_frames.hpp>
#include <sanguis/tools/animations/optional_animation_ref.hpp>
#include <sanguis/tools/animations/qtutil/from_fcppt_string.hpp>
#include <sanguis/tools/animations/qtutil/to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/truncation_check_cast.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QString>
#include <ui_main_window.h>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::main_window::main_window()
:
	QMainWindow(
		nullptr
	),
	ui_(
		fcppt::make_unique_ptr<
			Ui::MainWindow
		>()
	),
	loaded_model_(),
	json_file_(),
	image_files_(),
	frames_()
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
	QString const chosen_json_file{
		QFileDialog::getOpenFileName(
			this,
			tr("Open JSON"),
			QString(),
			tr("JSON files (*.json)")
		)
	};

	if(
		chosen_json_file.isEmpty()
	)
		return;

	json_file_ =
		chosen_json_file;

	ui_->partComboBox->clear();

	fcppt::string const fcppt_json_file(
		sanguis::tools::animations::qtutil::to_fcppt_string(
			chosen_json_file
		)
	);

	try
	{
		loaded_model_ =
			sanguis::model::deserialize(
				fcppt_json_file
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

	try
	{
		image_files_ =
			sanguis::tools::animations::load_image_files(
				boost::filesystem::path(
					fcppt_json_file
				).remove_filename(),
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
				tr("Error loading image files")
			),
			sanguis::tools::animations::qtutil::from_fcppt_string(
				_error.string()
			),
			QMessageBox::StandardButton::Ok,
			this
		);

		msgbox.exec();
	}

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
	QString const &
)
{
	sanguis::tools::animations::optional_animation_ref const animation(
		this->current_animation()
	);

	if(
		!animation
	)
		return;

	ui_->delaySpinBox->setValue(
		animation->animation_delay()
		?
			fcppt::truncation_check_cast<
				int
			>(
				animation->animation_delay()->get().count()
			)
		:
			0
	);

	ui_->soundEdit->setText(
		animation->animation_sound()
		?
			sanguis::tools::animations::qtutil::from_fcppt_string(
				animation->animation_sound()->get()
			)
		:
			QString()
	);

	sanguis::tools::animations::const_optional_image_file_ref const file(
		sanguis::tools::animations::find_image_file(
			image_files_,
			*loaded_model_,
			sanguis::tools::animations::qtutil::to_fcppt_string(
				ui_->partComboBox->currentText()
			),
			sanguis::tools::animations::qtutil::to_fcppt_string(
				ui_->weaponComboBox->currentText()
			),
			sanguis::tools::animations::qtutil::to_fcppt_string(
				ui_->animationComboBox->currentText()
			)
		)
	);

	frames_.clear();

	if(
		!file
	)
		return;

	frames_ =
		sanguis::tools::animations::make_frames(
			*file,
			*ui_->scrollAreaWidgetContents,
			*loaded_model_,
			*animation
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
		sanguis::tools::animations::int_to_delay(
			_value
		)
	);
}

void
sanguis::tools::animations::main_window::delayChanged(
	int const _value
)
{
	sanguis::tools::animations::optional_animation_ref const animation(
		this->current_animation()
	);

	if(
		!animation
	)
		return;

	animation->animation_delay(
		sanguis::tools::animations::int_to_delay(
			_value
		)
	);
}

void
sanguis::tools::animations::main_window::soundChanged(
	QString const &_name
)
{
	sanguis::tools::animations::optional_animation_ref const animation(
		this->current_animation()
	);

	if(
		!animation
	)
		return;

	animation->animation_sound(
		_name.isEmpty()
		?
			sanguis::model::optional_animation_sound(
				sanguis::model::animation_sound(
					sanguis::tools::animations::qtutil::to_fcppt_string(
						_name
					)
				)
			)
		:
			sanguis::model::optional_animation_sound()
	);
}

sanguis::tools::animations::optional_animation_ref const
sanguis::tools::animations::main_window::current_animation()
{
	QString const selected_part(
		ui_->partComboBox->currentText()
	);

	QString const selected_weapon_category(
		ui_->weaponComboBox->currentText()
	);

	QString const selected_animation(
		ui_->animationComboBox->currentText()
	);

	return
		!loaded_model_
		||
		selected_part.isEmpty()
		||
		selected_weapon_category.isEmpty()
		||
		selected_animation.isEmpty()
		?
			sanguis::tools::animations::optional_animation_ref()
		:
			sanguis::tools::animations::optional_animation_ref(
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
						selected_animation
					)
				)
			)
		;
}
