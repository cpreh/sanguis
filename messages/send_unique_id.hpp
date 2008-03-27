#ifndef SANGUIS_MESSAGES_SEND_UNIQUE_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_SEND_UNIQUE_ID_HPP_INCLUDED

#include "base.hpp"
#include "../entity_id.hpp"
#include <boost/serialization/access.hpp>
#include <vector>

namespace sanguis
{
namespace messages
{

class send_unique_id : public base {
public:
	typedef std::vector<entity_id> id_vector;
	send_unique_id();
	explicit send_unique_id(id_vector const&);
	id_vector const &ids() const;
private:
	id_vector ids_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
