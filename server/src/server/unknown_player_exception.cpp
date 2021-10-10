#include <sanguis/exception.hpp>
#include <sanguis/server/unknown_player_exception.hpp>
#include <fcppt/text.hpp>

sanguis::server::unknown_player_exception::unknown_player_exception()
    : sanguis::exception(FCPPT_TEXT("unknown player"))
{
}

sanguis::server::unknown_player_exception::unknown_player_exception(
    unknown_player_exception &&) noexcept = default;

sanguis::server::unknown_player_exception::unknown_player_exception(
    unknown_player_exception const &) = default;

sanguis::server::unknown_player_exception &sanguis::server::unknown_player_exception::operator=(
    unknown_player_exception &&) noexcept = default;

sanguis::server::unknown_player_exception &
sanguis::server::unknown_player_exception::operator=(unknown_player_exception const &) = default;

sanguis::server::unknown_player_exception::~unknown_player_exception() noexcept = default;
