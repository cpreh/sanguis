#ifndef SANGUIS_SERVER_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_OBJECT_HPP_INCLUDED

#include <sanguis/io_service.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/object_base.hpp>
#include <sanguis/server/object_fwd.hpp> // IWYU pragma: keep
#include <sanguis/server/symbol.hpp>
#include <alda/net/port.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/scoped_state_machine.hpp>
#include <fcppt/log/context_reference_fwd.hpp>

namespace sanguis::server
{

class object : public sanguis::server::object_base
{
  FCPPT_NONMOVABLE(object);

public:
  SANGUIS_SERVER_SYMBOL
  object(fcppt::log::context_reference, alda::net::port);

  SANGUIS_SERVER_SYMBOL
  ~object() override;

  SANGUIS_SERVER_SYMBOL
  void run() override;

  SANGUIS_SERVER_SYMBOL
  void stop();

private:
  sanguis::io_service io_service_;

  sanguis::server::machine machine_;

  using scoped_machine = fcppt::scoped_state_machine<sanguis::server::machine>;

  scoped_machine scoped_machine_;
};

}

#endif
