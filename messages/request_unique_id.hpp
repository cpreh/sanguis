#ifndef SANGUIS_MESSAGES_REQUEST_UNIQUE_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_REQUEST_UNIQUE_ID_HPP_INCLUDED

#include "base.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class request_unique_id : public base {
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
