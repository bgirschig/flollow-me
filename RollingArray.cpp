#include "RollingArray.h"

RollingArray::RollingArray(int alloc_size) {
  this->alloc_size = alloc_size;
  values = new float[alloc_size];

  for (int i = 0; i < alloc_size; i++) values[i] = 0;
  setLength(alloc_size);
}

void RollingArray::setLength(int size) {
  this->size = size;
  start_idx = 0;
  sum = 0;
  
  // reset array values
  for (int i = 0; i < size; i++) values[i] = 0;
}

float RollingArray::get(int index) {
  return values[(start_idx+index) % size];
}

void RollingArray::append(float value) {
  start_idx += 1;  
  if(start_idx >= size) start_idx = 0;

  int target_idx = (start_idx + size - 1) % size;
  sum = sum + value - values[target_idx];
  values[target_idx] = value;
}

std::string RollingArray::toString() {
  std::stringstream output;

  output << "array(size:" << size << " sum:" << sum << ")";
  
  output << " [";
  for (int i = 0; i < size; i++) output << get(i) << ",";
  output << "]\n";

  return output.str();
}