#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <istream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <filesystem>

#include "../Cube.h"

class Database
{
public:
    Database(size_t size, const std::string& fileName)
        : m_size(size), m_fileName(fileName)
    {
        m_data.resize(size);
        reset();
    }

    // read & write from file
    bool load();
    void write() const;

    // empty the database -> set all elements to 0xFF
    void reset();

    // access data
    uint8_t at(uint32_t index) const;
    uint8_t getDistance(const Rubiks& cube) const;
    uint8_t getDistance(uint32_t index) const;

    // each goal has different logic for indexing
    virtual uint32_t getIndex(const Rubiks& cube) const = 0;

    // updates the database only if the value isn't bigger than the current entry
    bool index(uint32_t index, uint8_t value);
    bool index(const Rubiks& cube, uint8_t value);

    // returns true if the distance is lower than 0xFF
    bool isSet(uint32_t index) const;
    bool isSet(const Rubiks& cube) const;

    bool full() const;

    // returns the amount of current items (0xFF = uninitialised)
    size_t currentSize() const;

    size_t size() const;
    
private:
    std::string m_fileName;
    std::vector<uint8_t> m_data;
    size_t m_currentCapacity = 0;
    size_t m_size;
};

#endif // DATABASE_H
