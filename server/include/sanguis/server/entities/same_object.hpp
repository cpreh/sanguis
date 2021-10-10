#ifndef SANGUIS_SERVER_ENTITIES_SAME_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SAME_OBJECT_HPP_INCLUDED

#include <sanguis/server/entities/base.hpp>

namespace sanguis::server::entities
{

template <typename T1, typename T2>
bool same_object(T1 const &_t1, T2 const &_t2)
{
  return &static_cast<sanguis::server::entities::base const &>(_t1) ==
         &static_cast<sanguis::server::entities::base const &>(_t2);
}

}

#endif
