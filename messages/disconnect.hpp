#ifndef SANGUIS_MESSAGES_DISCONNECT_HPP_INCLUDED
#define SANGUIS_MESSAGES_DISCONNECT_HPP_INCLUDED

#include "base.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class disconnect : public base {
public:
	disconnect();
private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
