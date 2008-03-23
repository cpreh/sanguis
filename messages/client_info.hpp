#ifndef SANGUIS_MESSAGES_CLIENT_INFO_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_INFO_HPP_INCLUDED

#include "types.hpp"
#include "base.hpp"
#include <boost/serialization/base_object.hpp>

namespace sanguis
{
namespace messages
{

class client_info : public base {
public:
	string name;

	client_info() {}
	client_info(const string &);

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned)
	{
		ar & boost::serialization::base_object<base>(*this);
		ar & name;
	}
};

}
}

#endif
