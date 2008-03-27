#ifndef SANGUIS_MESSAGES_REQUEST_UNIQUE_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_REQUEST_UNIQUE_ID_HPP_INCLUDED

#include "base.hpp"
#include "types.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class request_unique_id : public base {
public:
	request_unique_id();
	request_unique_id(size_type num_ids);
	size_type num_ids() const;
private:
	size_type num_ids_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
