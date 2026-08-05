
#include "TreeX_Robotics_Task.h"


int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cout << "No file name!";
        return 1;
    }
    string filename;
    int threshold=500;
    if (argc >= 2)
    {
        filename = argv[1];
        if (argc == 3)
        {
            if (is_all_digits(argv[2]))
            {
                threshold = stold(argv[2]);
            }
            else
            {
                std::cout << "Wrong threshold number!";
                return 1;
            }
        }
    }
    std::ifstream f(filename);
    if (!f.is_open()) 
    {
        std::cout << "Error opening the file!";
        return 1;
    }
    string line, timestamp, sensor_id, value;
    std::unordered_map<string, array<double,6>> dict;
    std::array<string, 3> parts;
    int malformed_counter = 0;
    int timestamp_num;
    double value_num;
    while (std::getline(f,line))
    {
        if (is_valid_line(line))
        {
            parts = parse_line(line);
            timestamp = parts[0];
            sensor_id = parts[1];
            value = parts[2];
            timestamp_num = stoi(timestamp);
            value_num = stold(value);
            if (dict.find(sensor_id) == dict.end())
            {
                dict[sensor_id] = array<double, 6>();
                dict[sensor_id][0] = 0;
                dict[sensor_id][1] = value_num;
                dict[sensor_id][2] = value_num;
                dict[sensor_id][3] = 0;
                dict[sensor_id][4] = timestamp_num;
                dict[sensor_id][5] = 0;
            }
            dict[sensor_id][0]++;
            if (value_num <dict[sensor_id][1])
            {
                dict[sensor_id][1] = value_num;
            }
            if (value_num > dict[sensor_id][2])
            {
                dict[sensor_id][2] = value_num;
            }
            dict[sensor_id][3] += value_num;
            if (timestamp_num - dict[sensor_id][4] > threshold)
            {
                dict[sensor_id][5]++;
            }
            dict[sensor_id][4] = timestamp_num;
        }
        else
        {
            malformed_counter++;
        }
    }
    f.close();

    for (const pair<string,array<double,6>>& p : dict)
    {
        std::cout << "Sensor: " << p.first << std::endl;
        std::cout << p.second[0] << " reports" << std::endl;
        std::cout << "min: " << p.second[1] << std::endl;
        std::cout << "max: " << p.second[2] << std::endl;
        std::cout << "mean: " << p.second[3]/p.second[0] << std::endl;
        std::cout << "Gap detection: " << p.second[5] << std::endl;
        std::cout << std::endl;
    }
    std::string malformed_lines_message = "There were " + std::to_string(malformed_counter) + " malformed lines";
    std::cout << malformed_lines_message << std::endl;


}

static bool is_all_digits(const std::string& s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

static bool is_valid_line(const std::string& s)
{
    size_t first_space_index = s.find(' ');
    if (first_space_index == string::npos)
    {
        return false;
    }
    size_t second_space_index = s.find(' ', first_space_index + 1);
    if (second_space_index == string::npos)
    {
        return false;
    }
    std::string timestamp_ms = s.substr(0, first_space_index);
    if (!is_all_digits(timestamp_ms))
    {
        return false;
    }
    std::string value = s.substr(second_space_index + 1);
    size_t dot_index = value.find('.');
    if (dot_index == string::npos)
    {
        return false;
    }
    value[dot_index] = '0';
    size_t minus_index = value.find('-');
    if (minus_index != string::npos)
    {
        value[minus_index] = '0';
    }
    if (!is_all_digits(value))
    {
        std::cout << value << std::endl;
        return false;
    }
    return true;
}

static std::array<string, 3> parse_line(std::string& s)
{
std:array<string, 3> parts;
    int space_index;
    s = s + ' ';
    for (int i = 0; i < 3; i++)
    {
        space_index = s.find(' ');
        parts[i] = s.substr(0, space_index);
        s.erase(0, space_index + 1);
    }
    return parts;
}