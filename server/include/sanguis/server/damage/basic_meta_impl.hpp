#ifndef SANGUIS_SERVER_DAMAGE_BASIC_META_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_BASIC_META_IMPL_HPP_INCLUDED

#include <sanguis/server/damage/basic_meta_decl.hpp>
#include <sanguis/server/damage/type.hpp>

template <typename Unit>
sanguis::server::damage::basic_meta<Unit>::basic_meta(
    sanguis::server::damage::type const _type, Unit const _value)
    : type_(_type), value_(_value)
{
}

template <typename Unit>
sanguis::server::damage::type sanguis::server::damage::basic_meta<Unit>::type() const
{
  return type_;
}

template <typename Unit>
Unit sanguis::server::damage::basic_meta<Unit>::value() const
{
  return value_;
}

#endif
