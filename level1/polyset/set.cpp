#include "set.hpp"
#include "searchable_array_bag.hpp"

set::set(searchable_bag&sbag): bag(sbag){}

set::~set(){}

bool set::has(int n) const{
  return (bag.has(n));
}

void set::insert(int n){
  if (!(this->has(n)))
	bag.insert(n);
}

void set::insert(int *data, int n){
  for (int i = 0; i < n; i++)
	this->insert(data[i]);
}

void set::print() const{
  bag.print();
}

const searchable_bag &set::get_bag(){
  return this->bag;
}
