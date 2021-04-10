#include "database.h"

bool Database::load()
{
    std::ifstream input(m_dataPath + m_filePath);

    if (input)
    {
        size_t value;
        for (size_t i = 0; i < m_size; ++i)
        {
            input >> value;
            m_data[i] = (uint8_t)value;
            if (m_data[i] == 0xFF)
            {
                std::cout << "Database doesn't match " << m_filePath << ". Failed to load." << std::endl;
                reset();
                return false;
            }
            m_currentCapacity++;
        }
    }
    else
    {
        std::cout << "Failed to open database file \"" << m_filePath << "\"." << std::endl;
        return false;
    }

    input.close();
    return full();
}

void Database::write() const
{
    std::ofstream outfile;
    outfile.open(m_dataPath + m_filePath);

    for (size_t i = 0; i < m_size; ++i)
    {
        outfile << (size_t)m_data[i] << std::endl;
    }
    outfile.close();
}


bool Database::set(uint32_t index, uint8_t value)
{
    if (m_data[index] > value)
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

bool Database::set(const Rubiks& cube, uint8_t value)
{
    return set(getInd(cube), value);
}

bool Database::isSet(uint32_t index) const
{
    return (m_data[index] != 0xFF);
}

bool Database::isSet(const Rubiks& cube) const
{
    return isSet(getInd(cube));
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
    // fills the data with 0xFF (= unset)
    std::fill(m_data.begin(), m_data.end(), 0xFF);
    m_currentCapacity = 0;
}

std::size_t Database::size() const
{
    return m_size;
}

uint8_t Database::operator [](uint32_t index) const
{
    return m_data[index];
}

uint8_t Database::operator [](const Rubiks& cube) const
{
    return m_data[getInd(cube)];
}
