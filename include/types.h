#ifndef TYPES_H
#define TYPES_H

enum class CellStatus {
    unknown = 0,
    hit = 1,
    sink = 2,
    miss = 3
};

enum class Orientation {
    unknown = 0,
    horizontal = 1,
    vertical = 2
};

#endif