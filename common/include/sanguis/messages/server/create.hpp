#ifndef SANGUIS_MESSAGES_SERVER_CREATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_CREATE_HPP_INCLUDED

#include <sanguis/messages/server/concrete.hpp>

namespace sanguis::messages::server
{

template <typename T>
inline sanguis::messages::server::concrete<T> create(T const &_value)
{
  return sanguis::messages::server::concrete<T>(_value);
}

}

#endif
