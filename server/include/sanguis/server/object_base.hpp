#ifndef SANGUIS_SERVER_OBJECT_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_OBJECT_BASE_HPP_INCLUDED

#include <sanguis/server/object_base_fwd.hpp>
#include <sanguis/server/symbol.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server
{

class object_base
{
  FCPPT_NONMOVABLE(object_base);

protected:
  object_base();

public:
  SANGUIS_SERVER_SYMBOL
  virtual ~object_base();

  virtual void run() = 0;
};

}

#endif
