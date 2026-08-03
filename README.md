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
Our project is a command-line program that reads such a file and prints a per-sensor summary as follows:

1. For each `sensor_id`, we report the number of lines it has on the file, the minimum and maximum values it reported,
the mean value it reported and the gap detection of the sensor.
2. **Gap detection:** for each sensor, we report the number of gaps — cases where the time between two
   consecutive readings of that sensor exceeds a threshold. Threshold is **500 ms by default** and
   can be configurable by the user.
3. We skip malformed lines, and report how many lines were skipped.
4. We print a summary report of each sensor report to stdout.


### Our files:

- Our project is a the C++ (C++17) lenguage project, Built with CMake.

- Our project consits of a source file: `TreeX_Robotics_Task.cpp`, an header file: `TreeX_Robotics_Task.h` and a CMake file: `CMakeLists.txt`.

- We also present an example input file: `sample_log.txt`.


### Our design and code:
- In our project we use a map object that for each 'sensor_id' stores 6 values: its appearance counter, minimum reported value, maximum reported value,
sum of reported values (to become the mean), the number of gap detections and the previous timestamp (in ms) in which the sensor reproted a value.


- We read the input file (if opened correctly) line by line, we check its validity by verifing the required format: 
<timestamp_ms> <sensor_id> <value> where 'timestamp_ms' is an all digit string and 'value' is a floating point string. We count each invalid line.


- We parse each valid line, split it into three parts and convert the 'timestamp_ms' to an integer and the 'value' string to a double number.

- We check if the current sensor_id apear in the map, and if not we add it to the map and initialize its stored data.

- We store the relevant data of the current sensor on the map object: incriment its counter, updating (if needed) its minumum and maximum values and
add the current reported value to the stored sum.

- We check if the current timestamp is considered as gap with respect to the previous timestamp of the current sensor, and if so we incriment
the sensor's gap detection counter. Then we save the current timestamp (as the previous timestamp) and move to the next line.

- Finaly, we loop over each sensor in the map, we calculate its mean value and output all its stored data to the stdout.
In addition, we present the number of invalid lines appeared in the input file.