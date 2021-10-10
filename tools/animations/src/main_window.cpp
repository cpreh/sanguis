#include <sanguis/model/animation.hpp>
#include <sanguis/model/animation_delay.hpp>
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
#include <sanguis/tools/animations/delay_to_int.hpp>
#include <sanguis/tools/animations/exception.hpp>
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
#include <sanguis/tools/libmergeimage/merge_images.hpp>
#include <sanguis/tools/libmergeimage/merge_result.hpp>
#include <sanguis/tools/libmergeimage/save_images.hpp>
#include <sanguis/tools/libmergeimage/saved_image_vector.hpp>
#include <sanguis/tools/libmergeimage/to_model.hpp>
#include <fcppt/const.hpp>
#include <fcppt/copy.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/truncation_check.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/optional/apply.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/maybe_void_multi.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ui_main_window.h>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QPixmap>
#include <QString>
#include <exception>
#include <filesystem>
#include <iterator>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::tools::animations::main_window::main_window(
    fcppt::reference<sanguis::tools::animations::sge_systems const> const _sge_systems)
    : QMainWindow(nullptr),
      sge_systems_(_sge_systems),
      ui_(fcppt::make_unique_ptr<Ui::MainWindow>()),
      loaded_model_(),
      image_files_(),
      frame_timer_(this),
      frames_(),
      frame_iterator_()
{
  ui_->setupUi(this);

  ui_->scrollAreaWidgetContents->setLayout(new sanguis::tools::animations::qtutil::FlowLayout());

  connect(&frame_timer_, SIGNAL(timeout()), this, SLOT(updateFrame()));
}

sanguis::tools::animations::main_window::~main_window() = default;

void sanguis::tools::animations::main_window::actionJSON()
{
  fcppt::optional::maybe_void(
      sanguis::tools::animations::qtutil::string_to_optional<std::filesystem::path>(
          QFileDialog::getOpenFileName(
              this, tr("Open JSON"), QString(), tr("JSON files (*.json)"))),
      [this](std::filesystem::path const &_chosen_json_file)
      { this->open_json(_chosen_json_file); });
}

void sanguis::tools::animations::main_window::actionResourcePath()
try
{
  fcppt::optional::maybe_void(
      sanguis::tools::animations::qtutil::string_to_optional<std::filesystem::path>(
          QFileDialog::getExistingDirectory(this, tr("Open the resource directory"))),
      [this](std::filesystem::path const &_resource_directory)
      {
        if (!loaded_model_.has_value())
        {
          this->message_box(
              QMessageBox::Icon::Warning,
              QString(tr("No output path")),
              QString(tr("You don't have an output path yet. Please choose one.")));
        }

        fcppt::optional::maybe_void(
            loaded_model_.has_value()
                ? this->resource_path()
                : sanguis::tools::animations::qtutil::string_to_optional<std::filesystem::path>(
                      QFileDialog::getExistingDirectory(
                          this, tr("Select a directory to save the merged images to"))),
            [&_resource_directory, this](std::filesystem::path const &_save_path)
            {
              sanguis::tools::libmergeimage::merge_result merged_result(
                  sanguis::tools::libmergeimage::merge_images(
                      sge_systems_->image_system(), _resource_directory));

              std::filesystem::path const json_file(
                  _save_path / (fcppt::filesystem::stem(_save_path) + FCPPT_TEXT(".json")));

              sanguis::tools::libmergeimage::saved_image_vector const saved_images(
                  sanguis::tools::libmergeimage::save_images(
                      sge_systems_->image_system(), _save_path, merged_result.images()));

              sanguis::model::object converted_model(
                  sanguis::tools::libmergeimage::to_model(merged_result.cell_size(), saved_images));

              sanguis::model::serialize(
                  json_file,
                  fcppt::optional::maybe(
                      loaded_model_,
                      [&converted_model] { return std::move(converted_model); },
                      [&converted_model](
                          sanguis::tools::animations::path_model_pair const &_loaded_model)
                      {
                        return sanguis::tools::animations::merge_models(
                            _loaded_model.model(), std::move(converted_model));
                      }));

              this->open_json(json_file);
            });
      });
}
catch (fcppt::exception const &_error)
{
  this->message_box(
      QMessageBox::Icon::Critical,
      QString(tr("Error loading resource directory")),
      sanguis::tools::animations::qtutil::from_fcppt_string(_error.string()));
}
catch (std::exception const &_error)
{
  this->message_box(
      QMessageBox::Icon::Critical,
      QString(tr("Error loading resource directory")),
      QString::fromStdString(_error.what()));
}

void sanguis::tools::animations::main_window::actionSave()
{
  fcppt::optional::maybe_void(
      loaded_model_,
      [this](sanguis::tools::animations::path_model_pair const &_loaded_model)
      {
        try
        {
          sanguis::model::serialize(_loaded_model.path(), _loaded_model.model());
        }
        catch (sanguis::model::exception const &_error)
        {
          this->message_box(
              QMessageBox::Icon::Critical,
              QString(tr("Error saving JSON")),
              sanguis::tools::animations::qtutil::from_fcppt_string(_error.string()));
        }
      });
}

void sanguis::tools::animations::main_window::actionQuit() { qApp->quit(); }

void sanguis::tools::animations::main_window::actionSound()
{
  fcppt::optional::maybe_void_multi(
      [this](
          fcppt::reference<sanguis::model::animation> const _animation,
          std::filesystem::path const &_chosen_sound_file)
      {
        sanguis::model::animation_sound const animation_sound{
            fcppt::filesystem::path_to_string(_chosen_sound_file.filename())};

        _animation.get().animation_sound(sanguis::model::optional_animation_sound(animation_sound));

        this->ui_->soundEdit->setText(
            sanguis::tools::animations::qtutil::from_fcppt_string(animation_sound.get()));
      },
      this->current_animation(),
      sanguis::tools::animations::qtutil::string_to_optional<std::filesystem::path>(
          QFileDialog::getOpenFileName(this, tr("Open Sound"), QString())));
}

void sanguis::tools::animations::main_window::selectedPartChanged()
{
  fcppt::optional::maybe_void_multi(
      [this](
          sanguis::tools::animations::path_model_pair &_loaded_model,
          sanguis::model::part_name const &_part)
      {
        ui_->weaponComboBox->clear();

        for (auto const &weapon_category : _loaded_model.model().part(_part).weapon_categories())
        {
          ui_->weaponComboBox->insertItem(
              0,
              sanguis::tools::animations::qtutil::from_fcppt_string(weapon_category.first.get()));
        }
      },
      loaded_model_,
      this->selected_part());
}

void sanguis::tools::animations::main_window::selectedWeaponChanged()
{
  fcppt::optional::maybe_void_multi(
      [this](
          sanguis::tools::animations::path_model_pair &_loaded_model,
          sanguis::model::part_name const &_part,
          sanguis::model::weapon_category_name const &_weapon_category)
      {
        ui_->animationComboBox->clear();

        for (auto const &animation :
             _loaded_model.model().part(_part).weapon_category(_weapon_category).animations())
        {
          ui_->animationComboBox->insertItem(
              0, sanguis::tools::animations::qtutil::from_fcppt_string(animation.first.get()));
        }
      },
      loaded_model_,
      this->selected_part(),
      this->selected_weapon_category());
}

void sanguis::tools::animations::main_window::selectedAnimationChanged()
{
  bool const animation_was_playing(frame_timer_.isActive());

  this->resetFrames();

  fcppt::optional::maybe_void(
      this->current_animation(),
      [animation_was_playing, this](fcppt::reference<sanguis::model::animation> const _animation)
      {
        ui_->delaySpinBox->setValue(fcppt::optional::maybe(
            _animation.get().animation_delay(),
            fcppt::const_(0),
            [](sanguis::model::animation_delay const _delay)
            {
              return fcppt::optional::to_exception(
                  fcppt::cast::truncation_check<int>(_delay.get().count()),
                  [] {
                    return sanguis::tools::animations::exception{
                        FCPPT_TEXT("animation delay too large")};
                  });
            }));

        ui_->soundEdit->setText(fcppt::optional::maybe(
            _animation.get().animation_sound(),
            [] { return QString(); },
            [](sanguis::model::animation_sound const &_sound)
            { return sanguis::tools::animations::qtutil::from_fcppt_string(_sound.get()); }));

        frames_.clear();

        fcppt::optional::maybe_void(
            sanguis::tools::animations::find_image_file(
                image_files_,
                FCPPT_ASSERT_OPTIONAL_ERROR(loaded_model_).model(),
                FCPPT_ASSERT_OPTIONAL_ERROR(this->selected_part()),
                FCPPT_ASSERT_OPTIONAL_ERROR(this->selected_weapon_category()),
                FCPPT_ASSERT_OPTIONAL_ERROR(this->selected_animation())),
            [_animation, animation_was_playing, this](fcppt::reference<QImage const> const _file)
            {
              frames_ = sanguis::tools::animations::make_frames(
                  _file.get(),
                  fcppt::make_ref(*ui_->scrollAreaWidgetContents),
                  FCPPT_ASSERT_OPTIONAL_ERROR(loaded_model_).model(),
                  _animation.get());

              if (animation_was_playing)
              {
                this->playFrames();
              }
            });
      });
}

void sanguis::tools::animations::main_window::globalDelayChanged(int const _value)
{
  fcppt::optional::maybe_void(
      loaded_model_,
      [_value, this](sanguis::tools::animations::path_model_pair &_loaded_model)
      {
        _loaded_model.model().animation_delay(sanguis::tools::animations::int_to_delay(_value));

        this->update_frame_timer();
      });
}

void sanguis::tools::animations::main_window::delayChanged(int const _value)
{
  fcppt::optional::maybe_void(
      this->current_animation(),
      [_value, this](fcppt::reference<sanguis::model::animation> const _animation)
      {
        _animation.get().animation_delay(sanguis::tools::animations::int_to_delay(_value));

        this->update_frame_timer();
      });
}

void sanguis::tools::animations::main_window::soundChanged(QString const &_name)
{
  fcppt::optional::maybe_void(
      this->current_animation(),
      [&_name](fcppt::reference<sanguis::model::animation> const _animation)
      {
        _animation.get().animation_sound(
            sanguis::tools::animations::qtutil::string_to_optional<sanguis::model::animation_sound>(
                _name));
      });
}

void sanguis::tools::animations::main_window::updateFrame()
{
  // TODO(philipp): cyclic_iterator?
  if (frame_iterator_ == frames_.end())
  {
    frame_iterator_ = frames_.begin();
  }

  if (frame_iterator_ == frames_.end())
  {
    return;
  }

  this->ui_->animationPreview->setPixmap(frame_iterator_->pixmap());

  ++frame_iterator_;

  ui_->lcdNumber->display(fcppt::cast::size<int>(std::distance(frames_.cbegin(), frame_iterator_)));
}

void sanguis::tools::animations::main_window::playFrames()
{
  fcppt::optional::maybe(
      this->current_animation_delay(),
      [this]
      {
        this->message_box(
            QMessageBox::Icon::Critical,
            QString(tr("No animation delay")),
            QString(tr("No animation delay specified. Can't play the animation.")));
      },
      [this](sanguis::model::animation_delay const _delay)
      {
        frame_timer_.start(sanguis::tools::animations::delay_to_int(_delay));

        frame_iterator_ = frames_.begin();
      });
}

void sanguis::tools::animations::main_window::resetFrames()
{
  frame_iterator_ = sanguis::tools::animations::frame_container::iterator();

  frame_timer_.stop();

  ui_->lcdNumber->display(0);

  this->ui_->animationPreview->setPixmap(QPixmap());
}

sanguis::tools::animations::optional_animation_ref
sanguis::tools::animations::main_window::current_animation()
{
  return fcppt::optional::apply(
      [](sanguis::tools::animations::path_model_pair &_loaded_model,
         sanguis::model::part_name const &_part,
         sanguis::model::weapon_category_name const &_weapon_category,
         sanguis::model::animation_name const &_animation)
      {
        return fcppt::make_ref(_loaded_model.model()
                                   .part(_part)
                                   .weapon_category(_weapon_category)
                                   .animation(_animation));
      },
      loaded_model_,
      this->selected_part(),
      this->selected_weapon_category(),
      this->selected_animation());
}

void sanguis::tools::animations::main_window::open_json(std::filesystem::path const &_path)
{
  loaded_model_ = optional_path_model_pair();

  ui_->partComboBox->clear();

  ui_->resourcePathEdit->clear();

  try
  {
    loaded_model_ = optional_path_model_pair(sanguis::tools::animations::path_model_pair(
        fcppt::copy(_path), sanguis::model::deserialize(_path)));
  }
  catch (sanguis::model::exception const &_error)
  {
    this->message_box(
        QMessageBox::Icon::Critical,
        QString(tr("Error loading JSON")),
        sanguis::tools::animations::qtutil::from_fcppt_string(_error.string()));

    return;
  }

  ui_->resourcePathEdit->setText(sanguis::tools::animations::qtutil::from_fcppt_string(
      fcppt::filesystem::path_to_string(FCPPT_ASSERT_OPTIONAL_ERROR(this->resource_path()))));

  // TODO(philipp): Do this differently!
  sanguis::tools::animations::path_model_pair &loaded_model(loaded_model_.get_unsafe());

  try
  {
    image_files_ = sanguis::tools::animations::load_image_files(
        FCPPT_ASSERT_OPTIONAL_ERROR(this->resource_path()), loaded_model.model());
  }
  catch (sanguis::model::exception const &_error)
  {
    this->message_box(
        QMessageBox::Icon::Critical,
        QString(tr("Error loading image files")),
        sanguis::tools::animations::qtutil::from_fcppt_string(_error.string()));
  }

  for (auto const &part : loaded_model.model().parts())
  {
    ui_->partComboBox->insertItem(
        0, sanguis::tools::animations::qtutil::from_fcppt_string(part.first.get()));
  }

  ui_->globalDelaySpinBox->setValue(fcppt::optional::maybe(
      loaded_model.model().animation_delay(),
      fcppt::const_(0),
      [](sanguis::model::animation_delay const _delay)
      {
        return fcppt::optional::to_exception(
            fcppt::cast::truncation_check<int>(_delay.get().count()),
            [] {
              return sanguis::tools::animations::exception{FCPPT_TEXT("animation delay too large")};
            });
      }));
}

sanguis::tools::animations::main_window::optional_part_name
sanguis::tools::animations::main_window::selected_part() const
{
  return sanguis::tools::animations::qtutil::string_to_optional<sanguis::model::part_name>(
      ui_->partComboBox->currentText());
}

sanguis::tools::animations::main_window::optional_weapon_category_name
sanguis::tools::animations::main_window::selected_weapon_category() const
{
  return sanguis::tools::animations::qtutil::string_to_optional<
      sanguis::model::weapon_category_name>(ui_->weaponComboBox->currentText());
}

sanguis::tools::animations::main_window::optional_animation_name
sanguis::tools::animations::main_window::selected_animation() const
{
  return sanguis::tools::animations::qtutil::string_to_optional<sanguis::model::animation_name>(
      ui_->animationComboBox->currentText());
}

sanguis::tools::animations::main_window::optional_path
sanguis::tools::animations::main_window::resource_path()
{
  return fcppt::optional::map(
      loaded_model_,
      [](sanguis::tools::animations::path_model_pair const &_model)
      { return std::filesystem::path(_model.path()).remove_filename(); });
}

void sanguis::tools::animations::main_window::update_frame_timer()
{
  fcppt::optional::maybe(
      this->current_animation_delay(),
      [this] { this->resetFrames(); },
      [this](sanguis::model::animation_delay const _delay)
      { frame_timer_.setInterval(sanguis::tools::animations::delay_to_int(_delay)); });
}

sanguis::model::optional_animation_delay
sanguis::tools::animations::main_window::current_animation_delay()
{
  return fcppt::optional::bind(
      this->current_animation(),
      [this](fcppt::reference<sanguis::model::animation> const _animation)
      {
        return _animation.get().animation_delay().has_value()
                   ? _animation.get().animation_delay()
                   : FCPPT_ASSERT_OPTIONAL_ERROR(loaded_model_).model().animation_delay();
      });
}

void sanguis::tools::animations::main_window::message_box(
    QMessageBox::Icon const _icon, QString const &_title, QString const &_text)
{
  QMessageBox msgbox(_icon, _title, _text, QMessageBox::StandardButton::Ok, this);

  msgbox.exec();
}
