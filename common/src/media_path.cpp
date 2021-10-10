#include <sanguis/media_path.hpp>
#include <sanguis/build/media_path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

std::filesystem::path sanguis::media_path() { return sanguis::build_media_path(); }
