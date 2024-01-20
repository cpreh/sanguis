#ifndef SANGUIS_FRIEND_TYPE_HPP_INCLUDED
#define SANGUIS_FRIEND_TYPE_HPP_INCLUDED

#include <sanguis/friend_type_fwd.hpp> // IWYU pragma: keep

namespace sanguis
{

enum class friend_type
{
  sentry,
  spider,
  fcppt_maximum = spider
};

}

#endif
