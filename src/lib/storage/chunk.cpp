#include <iomanip>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "abstract_segment.hpp"
#include "chunk.hpp"

#include "utils/assert.hpp"

namespace opossum {

void Chunk::add_segment(const std::shared_ptr<AbstractSegment> segment) { segments.push_back(segment); }

void Chunk::append(const std::vector<AllTypeVariant>& values) {

  // check if values are empty
  if (values.empty()){
    throw std::exception();
  }
  // check if shape matches
  if (column_count() != values.size())
    throw std::exception();

  // append values to right segments
  for (ChunkOffset i = 0; i < values.size(); i++) {
    segments[i]->append(values[i]);
  }
}

std::shared_ptr<AbstractSegment> Chunk::get_segment(const ColumnID column_id) const {
  if (column_id >= column_count()){
    throw  std::exception();
  }
  return segments[column_id];
}

ColumnCount Chunk::column_count() const {
  return ColumnCount{segments.size()};
}

ChunkOffset Chunk::size() const {
  ChunkOffset max = 0;
  for (const std::shared_ptr<AbstractSegment>& n : segments) {
    if (n->size() > max) {
      max = n->size();
    }
  }
  return max;
}

}  // namespace opossum
