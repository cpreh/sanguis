#include <sanguis/model/animation.hpp>
#include <sanguis/model/animation_name.hpp>
#include <sanguis/model/animation_sound.hpp>
#include <sanguis/model/deserialize.hpp>
#include <sanguis/model/exception.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_animation_sound.hpp>
#include <sanguis/model/part_name.hpp>
#include <sanguis/model/serialize.hpp>
#include <sanguis/model/weapon_category_name.hpp>
#include <sanguis/tools/animations/const_optional_image_file_ref.hpp>
#include <sanguis/tools/animations/delay_to_int.hpp>
#include <sanguis/tools/animations/find_image_file.hpp>
#include <sanguis/tools/animations/int_to_delay.hpp>
#include <sanguis/tools/animations/load_image_files.hpp>
#include <sanguis/tools/animations/main_window.hpp>
#include <sanguis/tools/animations/make_frames.hpp>
#include <sanguis/tools/animations/merge_models.hpp>
#include <sanguis/tools/animations/optional_animation_ref.hpp>
#include <sanguis/tools/animations/path_model_pair.hpp>
#include <sanguis/tools/animations/sge_systems.hpp>
#include <sanguis/tools/animations/qtutil/flow_layout.hpp>
#include <sanguis/tools/animations/qtutil/from_fcppt_string.hpp>
#include <sanguis/tools/animations/qtutil/string_to_optional.hpp>
#include <sanguis/tools/libmergeimage/exception.hpp>
#include <sanguis/tools/libmergeimage/merge_images.hpp>
#include <sanguis/tools/libmergeimage/merge_result.hpp>
#include <sanguis/tools/libmergeimage/save_images.hpp>
#include <sanguis/tools/libmergeimage/saved_image_vector.hpp>
#include <sanguis/tools/libmergeimage/to_model.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/truncation_check_cast.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QPixmap>
#include <QString>
#include <ui_main_window.h>
#include <exception>
#include <iterator>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::main_window::main_window(
	sanguis::tools::animations::sge_systems const &_sge_systems
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
	image_files_(),
	frame_timer_(
		this
	),
	frames_(),
	frame_iterator_()
{
	ui_->setupUi(
		this
	);

	ui_->scrollAreaWidgetContents->setLayout(
		new sanguis::tools::animations::qtutil::FlowLayout()
	);

	connect(
		&frame_timer_,
		SIGNAL(timeout()),
		this,
		SLOT(updateFrame())
	);
}

sanguis::tools::animations::main_window::~main_window()
{
}

void
sanguis::tools::animations::main_window::actionJSON()
{
	sanguis::tools::animations::main_window::optional_path const chosen_json_file{
		sanguis::tools::animations::qtutil::string_to_optional<
			boost::filesystem::path
		>(
			QFileDialog::getOpenFileName(
				this,
				tr("Open JSON"),
				QString(),
				tr("JSON files (*.json)")
			)
		)
	};

	if(
		!chosen_json_file
	)
		return;

	this->open_json(
		*chosen_json_file
	);
}

void
sanguis::tools::animations::main_window::actionResourcePath()
try
{
	sanguis::tools::animations::main_window::optional_path const resource_directory{
		sanguis::tools::animations::qtutil::string_to_optional<
			boost::filesystem::path
		>(
			QFileDialog::getExistingDirectory(
				this,
				tr("Open the resource directory")
			)
		)
	};

	if(
		!resource_directory
	)
		return;

	sanguis::tools::libmergeimage::merge_result merged_result(
		sanguis::tools::libmergeimage::merge_images(
			sge_systems_.image_system(),
			*resource_directory
		)
	);

	if(
		!loaded_model_
	)
	{
		this->message_box(
			QMessageBox::Icon::Warning,
			QString(
				tr("No output path")
			),
			QString(
				tr("You don't have an output path yet. Please choose one.")
			)
		);
	}

	sanguis::tools::animations::main_window::optional_path const save_path(
		loaded_model_
		?
			this->resource_path()
		:
			sanguis::tools::animations::qtutil::string_to_optional<
				boost::filesystem::path
			>(
				QFileDialog::getExistingDirectory(
					this,
					tr("Select a directory to save the merged images to")
				)
			)
	);

	if(
		!save_path
	)
		return;

	boost::filesystem::path const json_file(
		*save_path
		/
		(
			fcppt::filesystem::stem(
				*save_path
			)
			+
			FCPPT_TEXT(".json")
		)
	);

	sanguis::tools::libmergeimage::saved_image_vector const saved_images(
		sanguis::tools::libmergeimage::save_images(
			sge_systems_.image_system(),
			*save_path,
			merged_result.images()
		)
	);

	sanguis::model::object converted_model(
		sanguis::tools::libmergeimage::to_model(
			merged_result.cell_size(),
			saved_images
		)
	);

	sanguis::model::serialize(
		json_file,
		loaded_model_
		?
			sanguis::tools::animations::merge_models(
				loaded_model_->model(),
				std::move(
					converted_model
				)
			)
		:
			std::move(
				converted_model
			)
	);

	this->open_json(
		json_file
	);
}
catch(
	sanguis::tools::libmergeimage::exception const &_error
)
{
	this->message_box(
		QMessageBox::Icon::Critical,
		QString(
			tr("Error loading resource directory")
		),
		sanguis::tools::animations::qtutil::from_fcppt_string(
			_error.string()
		)
	);
}
catch(
	std::exception const &_error
)
{
	this->message_box(
		QMessageBox::Icon::Critical,
		QString(
			tr("Error loading resource directory")
		),
		QString::fromStdString(
			_error.what()
		)
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
			loaded_model_->path(),
			loaded_model_->model()
		);
	}
	catch(
		sanguis::model::exception const &_error
	)
	{
		this->message_box(
			QMessageBox::Icon::Critical,
			QString(
				tr("Error saving JSON")
			),
			sanguis::tools::animations::qtutil::from_fcppt_string(
				_error.string()
			)
		);

		return;
	}
}

void
sanguis::tools::animations::main_window::actionQuit()
{
	qApp->quit();
}

void
sanguis::tools::animations::main_window::actionSound()
{
	sanguis::tools::animations::optional_animation_ref const animation(
		this->current_animation()
	);

	if(
		!animation
	)
		return;

	sanguis::tools::animations::main_window::optional_path const chosen_sound_file{
		sanguis::tools::animations::qtutil::string_to_optional<
			boost::filesystem::path
		>(
			QFileDialog::getOpenFileName(
				this,
				tr("Open Sound"),
				QString()
			)
		)
	};

	if(
		!chosen_sound_file
	)
		return;

	sanguis::model::animation_sound const animation_sound{
		fcppt::filesystem::path_to_string(
			chosen_sound_file->filename()
		)
	};

	animation->animation_sound(
		sanguis::model::optional_animation_sound(
			animation_sound
		)
	);

	this->ui_->soundEdit->setText(
		sanguis::tools::animations::qtutil::from_fcppt_string(
			animation_sound.get()
		)
	);
}

void
sanguis::tools::animations::main_window::selectedPartChanged()
{
	sanguis::tools::animations::main_window::optional_part_name const part(
		this->selected_part()
	);

	if(
		!loaded_model_
		||
		!part
	)
		return;

	ui_->weaponComboBox->clear();

	for(
		auto const &weapon_category
		:
		loaded_model_->model().part(
			*part
		).weapon_categories()
	)
		ui_->weaponComboBox->insertItem(
			0,
			sanguis::tools::animations::qtutil::from_fcppt_string(
				weapon_category.first.get()
			)
		);
}

void
sanguis::tools::animations::main_window::selectedWeaponChanged()
{
	sanguis::tools::animations::main_window::optional_part_name const part(
		this->selected_part()
	);

	sanguis::tools::animations::main_window::optional_weapon_category_name const weapon_category(
		this->selected_weapon_category()
	);

	if(
		!loaded_model_
		||
		!part
		||
		!weapon_category
	)
		return;

	ui_->animationComboBox->clear();

	for(
		auto const &animation
		:
		loaded_model_->model().part(
			*part
		).weapon_category(
			*weapon_category
		).animations()
	)
		ui_->animationComboBox->insertItem(
			0,
			sanguis::tools::animations::qtutil::from_fcppt_string(
				animation.first.get()
			)
		);
}

void
sanguis::tools::animations::main_window::selectedAnimationChanged()
{
	sanguis::tools::animations::optional_animation_ref const animation(
		this->current_animation()
	);

	bool const animation_was_playing(
		frame_timer_.isActive()
	);

	this->resetFrames();

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
			loaded_model_->model(),
			*this->selected_part(),
			*this->selected_weapon_category(),
			*this->selected_animation()
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
			loaded_model_->model(),
			*animation
		);

	if(
		animation_was_playing
	)
		this->playFrames();
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

	loaded_model_->model().animation_delay(
		sanguis::tools::animations::int_to_delay(
			_value
		)
	);

	this->update_frame_timer();
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

	this->update_frame_timer();
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
		sanguis::tools::animations::qtutil::string_to_optional<
			sanguis::model::animation_sound
		>(
			_name
		)
	);
}

void
sanguis::tools::animations::main_window::updateFrame()
{
	if(
		frame_iterator_
		==
		frames_.end()
	)
		frame_iterator_ =
			frames_.begin();

	if(
		frame_iterator_
		==
		frames_.end()
	)
		return;

	this->ui_->animationPreview->setPixmap(
		frame_iterator_->pixmap()
	);

	++frame_iterator_;

	ui_->lcdNumber->display(
		fcppt::cast::size<
			int
		>(
			std::distance(
				frames_.cbegin(),
				frame_iterator_
			)
		)
	);
}

void
sanguis::tools::animations::main_window::playFrames()
{
	sanguis::model::optional_animation_delay const delay(
		this->current_animation_delay()
	);

	if(
		!delay
	)
	{
		this->message_box(
			QMessageBox::Icon::Critical,
			QString(
				tr("No animation delay")
			),
			QString(
				tr("No animation delay specified. Can't play the animation.")
			)
		);

		return;
	}

	frame_timer_.start(
		sanguis::tools::animations::delay_to_int(
			*delay
		)
	);

	frame_iterator_ =
		frames_.begin();
}

void
sanguis::tools::animations::main_window::resetFrames()
{
	frame_iterator_ =
		sanguis::tools::animations::frame_container::iterator();

	frame_timer_.stop();

	ui_->lcdNumber->display(
		0
	);

	this->ui_->animationPreview->setPixmap(
		QPixmap()
	);
}

sanguis::tools::animations::optional_animation_ref const
sanguis::tools::animations::main_window::current_animation()
{
	sanguis::tools::animations::main_window::optional_part_name const part(
		this->selected_part()
	);

	sanguis::tools::animations::main_window::optional_weapon_category_name const weapon_category(
		this->selected_weapon_category()
	);

	sanguis::tools::animations::main_window::optional_animation_name const animation(
		this->selected_animation()
	);

	return
		loaded_model_
		&&
		part
		&&
		weapon_category
		&&
		animation
		?
			sanguis::tools::animations::optional_animation_ref(
				loaded_model_->model().part(
					*part
				).weapon_category(
					*weapon_category
				).animation(
					*animation
				)
			)
		:
			sanguis::tools::animations::optional_animation_ref()
		;
}

void
sanguis::tools::animations::main_window::open_json(
	boost::filesystem::path const &_path
)
{
	loaded_model_.reset();

	ui_->partComboBox->clear();

	ui_->resourcePathEdit->clear();

	try
	{
		loaded_model_ =
			sanguis::tools::animations::path_model_pair(
				_path,
				sanguis::model::deserialize(
					_path
				)
			);
	}
	catch(
		sanguis::model::exception const &_error
	)
	{
		this->message_box(
			QMessageBox::Icon::Critical,
			QString(
				tr("Error loading JSON")
			),
			sanguis::tools::animations::qtutil::from_fcppt_string(
				_error.string()
			)
		);

		return;
	}

	FCPPT_ASSERT_ERROR(
		loaded_model_.has_value()
	);

	ui_->resourcePathEdit->setText(
		sanguis::tools::animations::qtutil::from_fcppt_string(
			fcppt::filesystem::path_to_string(
				*this->resource_path()
			)
		)
	);

	try
	{
		image_files_ =
			sanguis::tools::animations::load_image_files(
				*this->resource_path(),
				loaded_model_->model()
			);
	}
	catch(
		sanguis::model::exception const &_error
	)
	{
		this->message_box(
			QMessageBox::Icon::Critical,
			QString(
				tr("Error loading image files")
			),
			sanguis::tools::animations::qtutil::from_fcppt_string(
				_error.string()
			)
		);
	}

	for(
		auto const &part
		:
		loaded_model_->model().parts()
	)
		ui_->partComboBox->insertItem(
			0,
			sanguis::tools::animations::qtutil::from_fcppt_string(
				part.first.get()
			)
		);

	ui_->globalDelaySpinBox->setValue(
		loaded_model_->model().animation_delay()
		?
			fcppt::truncation_check_cast<
				int
			>(
				loaded_model_->model().animation_delay()->get().count()
			)
		:
			0
	);
}

sanguis::tools::animations::main_window::optional_part_name
sanguis::tools::animations::main_window::selected_part() const
{
	return
		sanguis::tools::animations::qtutil::string_to_optional<
			sanguis::model::part_name
		>(
			ui_->partComboBox->currentText()
		);
}

sanguis::tools::animations::main_window::optional_weapon_category_name
sanguis::tools::animations::main_window::selected_weapon_category() const
{
	return
		sanguis::tools::animations::qtutil::string_to_optional<
			sanguis::model::weapon_category_name
		>(
			ui_->weaponComboBox->currentText()
		);
}

sanguis::tools::animations::main_window::optional_animation_name
sanguis::tools::animations::main_window::selected_animation() const
{
	return
		sanguis::tools::animations::qtutil::string_to_optional<
			sanguis::model::animation_name
		>(
			ui_->animationComboBox->currentText()
		);
}

sanguis::tools::animations::main_window::optional_path
sanguis::tools::animations::main_window::resource_path()
{
	return
		fcppt::optional_bind_construct(
			loaded_model_,
			[](
				sanguis::tools::animations::path_model_pair const &_model
			)
			{
				return
					boost::filesystem::path(
						_model.path()
					).remove_filename();
			}
		);
}

void
sanguis::tools::animations::main_window::update_frame_timer()
{
	sanguis::model::optional_animation_delay const delay(
		this->current_animation_delay()
	);

	if(
		!delay
	)
		this->resetFrames();
	else
		frame_timer_.setInterval(
			sanguis::tools::animations::delay_to_int(
				*delay
			)
		);
}

sanguis::model::optional_animation_delay const
sanguis::tools::animations::main_window::current_animation_delay()
{
	sanguis::tools::animations::optional_animation_ref const animation(
		this->current_animation()
	);

	if(
		!animation
	)
		return
			sanguis::model::optional_animation_delay();

	return
		animation->animation_delay()
		?
			animation->animation_delay()
		:
			loaded_model_->model().animation_delay()
		;
}

void
sanguis::tools::animations::main_window::message_box(
	QMessageBox::Icon const _icon,
	QString const &_title,
	QString const &_text
)
{
	QMessageBox msgbox(
		_icon,
		_title,
		_text,
		QMessageBox::StandardButton::Ok,
		this
	);

	msgbox.exec();
}
