#ifndef SANGUIS_LOAD_MODEL_MODEL_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_MODEL_HPP_INCLUDED

#include "part.hpp"
#include <sge/path.hpp>
#include <sge/string.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace model
{

class model {
public:
	explicit model(sge::path const&);
	part const& operator[](sge::string const&) const;
private:
	typedef std::map<sge::string, part> part_map;
	part_map parts;
};

}
}
}

#endif
