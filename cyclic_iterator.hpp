#ifndef SANGUIS_CYCLIC_ITERATOR_HPP_INCLUDED
#define SANGUIS_CYCLIC_ITERATOR_HPP_INCLUDED

#include <boost/iterator/iterator_facade.hpp>
#include <boost/next_prior.hpp>
#include <iterator>

namespace sanguis
{

// TODO: break this up in an impl header

template<typename ContainerIterator>
class cyclic_iterator
: public boost::iterator_facade<
	cyclic_iterator<ContainerIterator>,
	typename std::iterator_traits<ContainerIterator>::value_type,
	boost::bidirectional_traversal_tag,
	typename std::iterator_traits<ContainerIterator>::reference> {
public:
	typedef boost::iterator_facade<
		cyclic_iterator<ContainerIterator>,
		typename std::iterator_traits<ContainerIterator>::value_type,
		boost::bidirectional_traversal_tag,
		typename std::iterator_traits<ContainerIterator>::reference> base_type;

	typedef ContainerIterator container_iterator_type;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::reference reference;
	typedef typename base_type::pointer pointer;
	typedef typename base_type::difference_type difference_type;

	// Default-Konstruktor (fuer bidirectional noetig)
	cyclic_iterator() {}

	// Initialisierung mit einem anderen cyclic_iterator
	template <class OtherIterator>
	explicit cyclic_iterator(const cyclic_iterator<OtherIterator> &other)
		: it(other.it),begin_(other.begin_),end_(other.end_) {}

	// Initialisierung mit einem Container-Iterator und einem Container
	cyclic_iterator(const container_iterator_type &it,const container_iterator_type &begin_, const container_iterator_type &end_)
		: it(it),begin_(begin_),end_(end_) {}
		
	// operator= mit einem anderen Container
	template <class OtherIterator>
	cyclic_iterator<ContainerIterator> &operator=(const cyclic_iterator<OtherIterator> &r)
	{
		it = r.it;
		begin_ = r.begin_;
		end_ = r.end_;
		return *this;
	}

	void begin(const container_iterator_type _begin) { begin_ = _begin; }
	void end(const container_iterator_type _end) { end_ = _end; }

	container_iterator_type begin() const { return begin_; }
	container_iterator_type end() const { return end_; }

	container_iterator_type get() const
	{
		return it;
	}
private:

	friend class boost::iterator_core_access;
	void increment()
	{
		if (begin_ != end_ && ++it == end_)
			it = begin_;
	}

	void decrement()
	{
		if (begin_ != end_ && it == begin_)
			it = boost::prior(end_);
	}

	template <class OtherIterator>
	bool equal(const cyclic_iterator<OtherIterator> & r) const { return it == r.it; }

	reference dereference() const { return *it; }

	template <class OtherIterator>
	difference_type distance_to(const cyclic_iterator<OtherIterator> &r) const { return r.it - it; }
private:
	container_iterator_type it,begin_,end_;
};

}

#endif
