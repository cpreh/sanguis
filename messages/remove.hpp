#ifndef SANGUIS_MESSAGES_REMOVE_HPP_INCLUDED
#define SANGUIS_MESSAGES_REMOVE_HPP_INCLUDED

#include "base.hpp"
#include <boost/serialization/base_object.hpp>

namespace sanguis
{
namespace messages
{

class remove : public base {
public:
	remove() {}
	remove(const entity_id);

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
