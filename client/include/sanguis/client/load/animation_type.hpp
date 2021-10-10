#ifndef SANGUIS_CLIENT_LOAD_ANIMATION_TYPE_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_ANIMATION_TYPE_HPP_INCLUDED

#include <sanguis/client/load/animation_type_fwd.hpp>

namespace sanguis::client::load
{

enum class animation_type
{
  none,
  attacking,
  walking,
  dying,
  deploying,
  reloading,
  fcppt_maximum = reloading
};

}

#endif
