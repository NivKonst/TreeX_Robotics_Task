# TreeX Robotics — Junior Software Developer Home Task


## The task: sensor log processor

A robot writes a telemetry log. Each line is:

```
<timestamp_ms> <sensor_id> <value>
```

- `timestamp_ms` — integer, milliseconds since start.
- `sensor_id` — short string (e.g. `imu`, `lidar`, `temp`).
- `value` — floating-point reading.

Example:
```
1000 imu 0.12
1005 temp 21.4
1010 imu 0.15
```

## Our project:
Our project is a command-line program, implemented in C++ (C++17), that reads such a file and prints a per-sensor summary as follows:

1. For each `sensor_id`, we report the number of lines it has in the file, the minimum and maximum values it reported,
the mean value it reported and the sensor's gap detection count.
2. **Gap detection:** for each sensor, we report the number of gaps — cases where the time between two
   consecutive readings of that sensor exceeds a threshold. The threshold is **500 ms by default** and
   can be configurable by the user.
3. We skip malformed lines, and report how many lines were skipped.
4. We print a summary report of each sensor to stdout.


### Our design and code:

1. In the program we use a map object that for each `sensor_id` stores six values: its occurrence counter, minimum reported value, maximum reported value,
sum of reported values (to become the mean), the number of gap detections and the previous timestamp (in ms) in which the sensor reported a value.


2. We read the input file (if it is opened successfully) line by line and verify that each line matches the required format: 
<timestamp_ms> <sensor_id> <value> where `timestamp_ms` is a string containing only digits and `value` is a floating-point string. We count every invalid line.

3. We parse each valid line, split it into three parts and convert the `timestamp_ms` to an integer and convert the `value` string to a double.

4. We check if the current sensor_id appears in the map, and if not we add it to the map and initialize its data.


5. We update the current sensor's data in the map by incrementing its reading count, updating its minimum and maximum values when necessary and
add the current reported value to the stored sum.

6. We check if the current timestamp is considered a gap with respect to the previous timestamp of the current sensor, and if so we increment
the sensor's gap detection counter. Then we save the current timestamp (as the previous timestamp) and move to the next line.

7. Finally, we iterate over each sensor in the map, we calculate its mean value and output all its stored data to stdout.
In addition, we present the number of invalid lines found in the input file.


### Our files:

- Our project is a C++ (C++17) project, built with CMake.

- The project consists of a source file: `TreeX_Robotics_Task.cpp`, a header file: `TreeX_Robotics_Task.h` and a CMake file: `CMakeLists.txt`.

- We also present an example input file: `sample_log.txt`.



### Building the project:

In order to build the project, use the following CMake command:

```
cmake -S . -B build
cmake --build build
```

The generated executable file can be found at: \build\Debug.


### Running the project:

In order to run the project using the provided sample_log.txt file use the following command:

```
.\build\Debug\TreeX_Robotics_Task.exe .\sample_log.txt
```

If you the use a 300 ms gap threshold instead of the default 500 ms, run following command:

```
.\build\Debug\TreeX_Robotics_Task.exe .\sample_log.txt 300ms
```
