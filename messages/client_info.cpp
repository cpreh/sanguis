#include "client_info.hpp"
#include "../archive.hpp"
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sanguis::messages::client_info)

sanguis::messages::client_info::client_info(const string &name)
: name(name)
{}
