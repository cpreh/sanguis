#ifndef SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE_HPP_INCLUDED

// only for internal use
// don't include this in headers

#include "../archive.hpp"

#define SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(x) \
template void sanguis::messages::x::serialize<sanguis::iarchive>(iarchive &, unsigned); \
template void sanguis::messages::x::serialize<sanguis::oarchive>(oarchive &, unsigned);

#endif
