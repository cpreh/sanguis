#include "client_info.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::client_info, "client_info")

sanguis::messages::client_info::client_info()
{}

sanguis::messages::client_info::client_info(
	const string &name_)
: name_(name_)
{}

sanguis::messages::string const &
sanguis::messages::client_info::name() const
{
	return name_;
}

template<typename Archive>
void sanguis::messages::client_info::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<base>(*this)
	   & name_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(client_info)
