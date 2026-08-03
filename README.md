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
4. Print a readable summary report to stdout.

### Our files:

- Our project consits of a source file: `TreeX_Robotics_Task.cpp`, an header file: `TreeX_Robotics_Task.h` and a CMake file: `CMakeLists.txt`.


- We also present an example input file: `sample_log.txt`.


### Our design and algorithm:

- Don't load the entire file into memory at once — process it as a stream. (The real logs are large.)

