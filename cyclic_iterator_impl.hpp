#ifndef SANGUIS_CYCLIC_ITERATOR_IMPL_HPP_INCLUDED
#define SANGUIS_CYCLIC_ITERATOR_IMPL_HPP_INCLUDED

#include "cyclic_iterator.hpp"

template<typename ContainerIterator>
sanguis::cyclic_iterator<ContainerIterator>::cyclic_iterator()
{}


template<typename ContainerIterator>
template<typename OtherIterator>
sanguis::cyclic_iterator<ContainerIterator>::cyclic_iterator(
	const cyclic_iterator<OtherIterator> &other)
: it(other.it),
  begin_(other.begin_),
  end_(other.end_)
{}

template<typename ContainerIterator>
sanguis::cyclic_iterator<ContainerIterator>::cyclic_iterator(
	const container_iterator_type &it,
	const container_iterator_type &begin_,
	const container_iterator_type &end_)
: it(it),
  begin_(begin_),
  end_(end_)
{}

template<typename ContainerIterator>
template<typename OtherIterator>
sanguis::cyclic_iterator<ContainerIterator> &
sanguis::cyclic_iterator<ContainerIterator>::operator=(
	cyclic_iterator<OtherIterator> const &r)
{
	it = r.it;
	begin_ = r.begin_;
	end_ = r.end_;
	return *this;
}

template<typename ContainerIterator>
void sanguis::cyclic_iterator<ContainerIterator>::begin(
	container_iterator_type const &_begin)
{
	begin_ = _begin;
}

template<typename ContainerIterator>
void sanguis::cyclic_iterator<ContainerIterator>::end(
	container_iterator_type const &_end)
{
	end_ = _end;
}

template<typename ContainerIterator>
typename sanguis::cyclic_iterator<ContainerIterator>::container_iterator_type
sanguis::cyclic_iterator<ContainerIterator>::begin() const
{
	return begin_;
}

template<typename ContainerIterator>
typename sanguis::cyclic_iterator<ContainerIterator>::container_iterator_type
sanguis::cyclic_iterator<ContainerIterator>::end() const
{
	return end_;
}

template<typename ContainerIterator>
typename sanguis::cyclic_iterator<ContainerIterator>::container_iterator_type
sanguis::cyclic_iterator<ContainerIterator>::get() const
{
	return it;
}

template<typename ContainerIterator>
void sanguis::cyclic_iterator<ContainerIterator>::increment()
{
	if (begin_ != end_ && ++it == end_)
		it = begin_;
}

template<typename ContainerIterator>
void sanguis::cyclic_iterator<ContainerIterator>::decrement()
{
	if (begin_ != end_ && it == begin_)
		it = boost::prior(end_);
}

template<typename ContainerIterator>
template<typename OtherIterator>
bool sanguis::cyclic_iterator<ContainerIterator>::equal(
	cyclic_iterator<OtherIterator> const &r) const
{
	return it == r.it;
}

template<typename ContainerIterator>
typename sanguis::cyclic_iterator<ContainerIterator>::reference
sanguis::cyclic_iterator<ContainerIterator>::dereference() const
{
	return *it;
}

template<typename ContainerIterator>
template<typename OtherIterator>
typename sanguis::cyclic_iterator<ContainerIterator>::difference_type
sanguis::cyclic_iterator<ContainerIterator>::distance_to(
	cyclic_iterator<OtherIterator> const &r) const
{
	return r.it - it;
}

#endif
