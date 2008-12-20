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
	typedef std::map<sge::string, part> part_map;
public:
	typedef part_map::value_type     value_type;
	typedef part_map::const_iterator const_iterator;
	typedef part_map::size_type      size_type;

	part const &operator[](sge::string const &) const;
	const_iterator begin() const;
	const_iterator end() const;
	size_type size() const;
private:
	explicit model(sge::path const &);

	friend class collection;

	part_map parts;
};

}
}
}

#endif
