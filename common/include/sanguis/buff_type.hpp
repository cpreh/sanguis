#ifndef SANGUIS_BUFF_TYPE_HPP_INCLUDED
#define SANGUIS_BUFF_TYPE_HPP_INCLUDED

#include <sanguis/buff_type_fwd.hpp> // IWYU pragma: keep

namespace sanguis
{

enum class buff_type
{
  burn,
  slow,
  fcppt_maximum = slow
};

}

#endif
