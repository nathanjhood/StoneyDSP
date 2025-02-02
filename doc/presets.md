# Presets

- ## Mode

  To *check* which of preset is automatically selected by your system, run `make preset` in your terminal inside the StoneyDSP project. The current preset name will be reported to the terminal. Example:

  ```sh
  $ make preset
  x64-linux-release
  ```

  *NOTE:* this command does not build anything or "activate" any preset. It simply reports the name of the chosen preset to your terminal; a useful sanity-checker, and utility.

  To demonstrate how our presets respond to your environment using the common `DEBUG` and `VERBOSE` environment variables when building StoneyDSP with `make`, for a Linux 64-bit machine:

  - ### default

    ```sh
    $ make preset
    x64-linux-release
    ```

  - ### "debug" mode

    ```sh
    $ DEBUG=1 make preset
    x64-linux-debug
    ```

  - ### "release" verbose mode

    ```sh
    $ VERBOSE=1 make preset
    x64-linux-release-verbose
    ```

  - ### "debug" verbose mode

    ```sh
    $ DEBUG=1 VERBOSE=1 make preset
    x64-linux-debug-verbose
    ```

  The above is a simple demonstration, but the principles apply to *any* of our `make`-based commands, including the mutliple underlying `cmake`-based commands which can perform specific actions and tasks within our project structure.

  The next example takes the priniciples of our preset system demonstrated above, and applies them to a reasonable sequence of tasks which might resemble a regular development workflow, or CI/CD pipeline:

  ```sh
  $ DEBUG=1 make test
  # CMake build output....

  $ make run-test
  # Unit tests output....
  # (test executable was compiled with debug flags and symbols...)

  # ...test successful!
  # 13/13 cases passed.

  $ make clean
  # ...

  $ make install
  # CMake build output...
  # (this time, we're compiling without debug flags and symbols activated...)
  ```

  *NOTE:* both `DEBUG` and `VERBOSE` may be set to run for a single command, as shown above, or they may be set as environment variables in your shell, user profile, or operating system. Be mindful, however, that setting these globally will likely interfere with other tools and processes in potentially confusing ways.

- ## Support

  The below support matrix aims to provide an accurate overview of all possible presets; please note, however, that support may vary in some cases, since we don't quite have the "CI pipeline capacity"* to run full integration tests for all extensive cases.

  To this end, we very much appreciate field reports and user-feedback, and will aim to support all cases where sufficient resources are available to do so.

  Please note that this table denotes the platforms and architectures we currently test - and in some cases, deploy - against; it does *not* attempt to reflect the current status of any branch or CI run, only that we actively support the platform (or not).

  - ### Support Matrix:

    |         | Toolchain                        | x86 | x64 | arm64 |
    | :-      |                                  | :-: | :-: |  :-:  |
    | Linux   | GNU                              |     |  ✔️  |       |
    | Linux   | Clang                            |     |  ✔️  |       |
    | Apple   | GNU                              |     |  ✔️  |   ✔️   |
    | Apple   | Clang                            |     |  ✔️  |   ✔️   |
    | Windows | MSVC                             |     |     |       |
    | Windows | Clang MinGW universal c runtime  |     |  ✔️  |       |
    | Windows | GNU MinGW universal c runtime    |     |  ✔️  |       |
    | Windows | GNU MinGW msvc runtime           |     |  ✔️  |       |

  If you have any experience with using StoneyDSP in the wild, we would love to hear any feedback you might have - success or fail -  that can help us ensure our support matrix looks a bit more ✔️ by continuously iterating on and deploying* improvements to our library, thanks to your valuable feedback!
