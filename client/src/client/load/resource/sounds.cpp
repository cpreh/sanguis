#include <sanguis/media_path.hpp>
#include <sanguis/client/load/resource/optional_sound.hpp>
#include <sanguis/client/load/resource/sounds.hpp>
#include <sge/audio/buffer.hpp>
#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/load.hpp>
#include <sge/audio/loader_ref.hpp>
#include <sge/audio/optional_file_unique_ptr.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/player_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sanguis::client::load::resource::sounds::sounds(
    sge::audio::loader_ref const _multi_loader, sge::audio::player_ref const _player)
    : multi_loader_(_multi_loader), player_(_player), buffers_()
{
}

sanguis::client::load::resource::sounds::~sounds() = default;

sanguis::client::load::resource::optional_sound
sanguis::client::load::resource::sounds::load(fcppt::string const &_name) const
{
  return this->load_path(sanguis::media_path() / FCPPT_TEXT("sound") / _name);
}

sanguis::client::load::resource::optional_sound
sanguis::client::load::resource::sounds::load_path(std::filesystem::path const &_path) const
{
  return fcppt::optional::deref(fcppt::container::get_or_insert(
      buffers_,
      _path,
      [this](std::filesystem::path const &_npath)
          -> sanguis::client::load::resource::sounds::optional_buffer
      {
        sge::audio::optional_file_unique_ptr const opt_file{
            sge::audio::load(multi_loader_, _npath)};

        return fcppt::optional::map(
            opt_file,
            [this](sge::audio::file_unique_ptr const &_file) -> sge::audio::buffer_unique_ptr
            { return player_->create_buffer(*_file); });
      }));
}
