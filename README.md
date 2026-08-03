# TreeX Robotics — Junior Software Developer Home Task

**Language:** C++ (C++17). Build with CMake.


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
Our project is a command-line program that reads such a file and prints a per-sensor summary as follows:

1. For each `sensor_id`, we report the number of lines it has on the file, the minimum and maximum values it reported,
the mean value it reported and the gap detection of the sensor.
2. **Gap detection:** for each sensor, we report the number of gaps — cases where the time between two
   consecutive readings of that sensor exceeds a threshold. Threshold is **500 ms by default** and
   can be configurable by the user.
3. We skip malformed lines, and report how many lines were skipped.
4. We print a summary report of each sensor report to stdout.

### Our files:

- Our project consits of a source file: `TreeX_Robotics_Task.cpp`, an header file: `TreeX_Robotics_Task.h` and a CMake file: `CMakeLists.txt`.


- We also present an example input file: `sample_log.txt`.


### Our design and code:
- In our project we use a map object that for each 'sensor_id' stores 6 values: its appearance counter, minimum reported value, maximum reported value,
sum of reported values (to become the mean), the number of gap detections and the previous timestamp (in ms) in which the sensor reproted a value.


- We read the input file (if opened correctly) line by line, we check its validity by verifing the required format: 
<timestamp_ms> <sensor_id> <value> where 'timestamp_ms' is an all digit string and 'value' is a floating point string.


- We parse each valid line, split it into three parts and convert the 'timestamp_ms' to an integer and the 'value' string to a double number.


-
