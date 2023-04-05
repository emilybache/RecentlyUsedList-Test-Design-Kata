

#include "InMemoryPageStorage.h"

string InMemoryPageStorage::lookup(int index) {
    return contents.at(index);
}