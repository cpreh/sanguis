#ifndef SANGUIS_SERVER_UNKNOWN_PLAYER_EXCEPTION_HPP_INCLUDED
#define SANGUIS_SERVER_UNKNOWN_PLAYER_EXCEPTION_HPP_INCLUDED

#include <sanguis/exception.hpp>

namespace sanguis::server
{

class unknown_player_exception : public sanguis::exception
{
public:
  unknown_player_exception();

  unknown_player_exception(unknown_player_exception &&) noexcept;

  unknown_player_exception(unknown_player_exception const &);

  unknown_player_exception &operator=(unknown_player_exception &&) noexcept;

  unknown_player_exception &operator=(unknown_player_exception const &);

  ~unknown_player_exception() noexcept override;
};

}

#endif
