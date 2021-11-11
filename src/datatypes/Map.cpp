/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "common/datatypes/Map.h"

#include <folly/String.h>

#include <sstream>

namespace nebula {

std::string Map::toString() const {
  std::vector<std::string> value(kvs.size());
  std::transform(kvs.begin(), kvs.end(), value.begin(), [](const auto& iter) -> std::string {
    std::stringstream out;
    out << iter.first << ":" << iter.second;
    return out.str();
  });

  std::stringstream os;
  os << "{" << folly::join(",", value) << "}";
  return os.str();
}

}  // namespace nebula

namespace std {
std::size_t hash<nebula::Map>::operator()(const nebula::Map& m) const noexcept {
  size_t seed = 0;
  for (auto& v : m.kvs) {
    seed ^= hash<std::string>()(v.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }
  return seed;
}

}  // namespace std
