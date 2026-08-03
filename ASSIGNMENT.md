# TreeX Robotics — Junior Software Developer Home Task

**Time budget:** 1–2 hours. Please don't over-invest — we care about your thinking, not polish.

**Language:** C++ (C++17). Build with CMake.

## Tools policy (read this)

**Do not use AI assistants (Claude, ChatGPT, Copilot, etc.) to write the code.** We want to see your
own work and reasoning. You may use standard references (documentation, cppreference, etc.).

**You must fully understand every line you submit.** We will walk through your code together and ask
you to explain choices, change things live, and reason about edge cases. The code is the starting
point of that conversation, not the whole grade.

---

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

Write a command-line program that reads such a file and prints a per-sensor summary.

### Required

1. Read the file given as a command-line argument.
2. For **each** `sensor_id`, report: **count, min, max, mean**.
3. **Gap detection:** for each sensor, report the number of gaps — cases where the time between two
   consecutive readings *of that sensor* exceeds a threshold. Threshold is **500 ms by default** and
   should be **configurable** by the user.
4. Skip malformed lines without crashing, and report how many lines were skipped.
5. Print a readable summary report to stdout.

### Deliverables

- Source file(s) + `CMakeLists.txt` (must build with `cmake` + `make`).
- A short `README.md`: how to build/run, and a few sentences on the design choices you made and
  anything you'd improve with more time.

### Do NOT

- Don't load the entire file into memory at once — process it as a stream. (The real logs are large.)
- Don't use third-party libraries beyond the C++ standard library.

---

## Submission

Push your solution to a GitHub repository and reply the link.

A sample input file `sample_log.txt` is included so you can test. Good luck!
