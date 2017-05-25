#ifndef include_defs
#define include_defs


#include <iostream> // pour debug
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <ctime>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

template <class T>
inline void hash_combine(std::size_t & seed, const T & v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
    template<typename S, typename T> struct hash<pair<S, T>> {
        inline size_t operator()(const pair<S, T> & v) const {
            size_t seed = 0;
            ::hash_combine(seed, v.first);
            ::hash_combine(seed, v.second);
            return seed;
        }
    };
}




#endif // contient les définitions des types et les includes de base
