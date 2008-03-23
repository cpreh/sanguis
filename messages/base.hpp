#ifndef SANGUIS_MESSAGES_BASE_HPP_INCLUDED
#define SANGUIS_MESSAGES_BASE_HPP_INCLUDED

#include "../entity_id.hpp"
#include <sge/shared_ptr.hpp>
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class base {
public:
	base(const entity_id = entity_id(0));
	entity_id id() const;
	virtual ~base();
private:
	entity_id id_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned) 
	{ 
		ar & id_; 
	}
};

}

typedef sge::shared_ptr<messages::base> message_ptr;
}

#endif
