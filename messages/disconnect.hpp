#ifndef SANGUIS_MESSAGES_DISCONNECT_HPP_INCLUDED
#define SANGUIS_MESSAGES_DISCONNECT_HPP_INCLUDED

#include "base.hpp"
#include <boost/serialization/base_object.hpp>

namespace sanguis
{
namespace messages
{

class disconnect : public base {
public:
	disconnect();

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned)
	{
		ar & boost::serialization::base_object<base>(*this);
	}

};

}
}

#endif
