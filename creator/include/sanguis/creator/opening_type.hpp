#ifndef SANGUIS_CREATOR_OPENING_TYPE_HPP_INCLUDED
#define SANGUIS_CREATOR_OPENING_TYPE_HPP_INCLUDED

#include <sanguis/creator/opening_type_fwd.hpp> // IWYU pragma: keep

namespace sanguis::creator
{

enum class opening_type
{
  entry,
  exit,
  fcppt_maximum = exit
};

}

#endif
