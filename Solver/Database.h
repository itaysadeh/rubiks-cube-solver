#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <istream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "../Cube.h"

class Database
{
public:
    Database(size_t size, const std::string& filePath)
        : m_size(size), m_filePath(filePath)
    {
        m_data.resize(size);
        reset();
    }

    virtual uint32_t getIndex(const Rubiks& cube) const = 0;

    bool load();
    void write() const;

    // sets all values to 0xFF and resets current capacity
    void reset();

    uint8_t operator[](uint32_t index) const;
    uint8_t operator[](const Rubiks& cube) const;

    // updates value in a given index
    bool set(uint32_t index, uint8_t value);
    bool set(const Rubiks& cube, uint8_t value);

    // returns true if the distance is lower than 0xFF
    bool isSet(uint32_t index) const;
    bool isSet(const Rubiks& cube) const;

    bool full() const;

    size_t currentSize() const;
    size_t size() const;
    
private:
    std::vector<uint8_t> m_data;
    size_t m_currentCapacity = 0;
    size_t m_size;
    std::string m_filePath;
    const std::string m_dataPath = "./Data/";
};

#endif // DATABASE_H
