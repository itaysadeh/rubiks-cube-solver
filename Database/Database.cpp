#include "Database.h"

bool Database::load()
{
    const std::string path = "./Database/Generated_Databases/" + m_fileName;
    std::ifstream input(path);

    if (input)
    {
        size_t value;
        for (size_t i = 0; i < m_size; ++i)
        {
            input >> value;
            m_data[i] = value;
            if (m_data[i] == 0xFF)
            {
                std::cout << "Database doesn't match " << path << ". Failed to load.\n";
                reset();
                return false;
            }
            m_currentCapacity++;
        }
    }
    else
    {
        std::cout << "Failed to open database file \"" << m_fileName << "\".\n";
        return false;
    }

    input.close();
    return full();
}

void Database::write() const
{
    const std::string path = "./Database/Generated_Databases/" + m_fileName;
    std::ofstream outfile;
    outfile.open(path);

    for (size_t i = 0; i < m_size; ++i)
    {
        outfile << (size_t)m_data[i] << "\n";
    }
    outfile.close();
}


bool Database::index(uint32_t index, uint8_t value)
{
    if (m_data[index] >= value)
    {
        if (m_data[index] == 0xFF)
        {
            m_currentCapacity++;
        }

        m_data[index] = value;
        return true;
    }

    return false;
}

bool Database::index(const Rubiks& cube, uint8_t value)
{
    return index(getIndex(cube), value);
}

bool Database::isSet(uint32_t index) const
{
    return (m_data[index] != 0xFF);
}

bool Database::isSet(const Rubiks& cube) const
{
    return isSet(getIndex(cube));
}

bool Database::full() const
{
    return (m_currentCapacity == m_size);
}

std::size_t Database::currentSize() const
{
    return m_currentCapacity;
}

void Database::reset()
{
    // fills the data with 0xFF (unset)
    std::fill(m_data.begin(), m_data.end(), 0xFF);
    m_currentCapacity = 0;
}

std::size_t Database::size() const
{
    return m_size;
}

uint8_t Database::at(uint32_t index) const
{
    return m_data[index];
}

uint8_t Database::getDistance(const Rubiks& cube) const
{
    return m_data[getIndex(cube)];
}

uint8_t Database::getDistance(uint32_t index) const
{
    return m_data[index];
}
