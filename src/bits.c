#include "bits.h"
#include "cache.h"

int get_set(Cache *cache, address_type address) {
  // TODO:
  //  Extract the set bits from a 32-bit address.
  //
  int tag = (32 - cache->block_bits - cache->set_bits);
  int ret = (address << tag) >> (cache->block_bits + tag);
  return ret;
}

int get_line(Cache *cache, address_type address) {
  // TODO:
  // Extract the tag bits from a 32-bit address.
  //
  int tag = address >> (cache->block_bits + cache->set_bits);

  return tag;
}

int get_byte(Cache *cache, address_type address) {
  // TODO
  // Extract the block offset (byte index) bits from a 32-bit address.
  //
  int tag = (32 - cache->block_bits - cache->set_bits);
  int index = (address << (tag + cache->set_bits)) >> (tag + cache->set_bits); 
  return index;
}
