# presets

  When building StoneyDSP from source, we provide an extensive set of curated CMake Presets for a simplified, streamlined workflow.

  CMake presets provide multiple possible actions - configure, build, test, package, and so forth - and also the ability to chain these actions together into a "workflow".

  For example, configuring the CMake project for 64-bit Linux platforms in "Release" mode with extra logging enabled is as easy as:

  ```sh
  $ cmake --preset x64-linux-release-verbose
  ```

  Our CMake Presets are specified as: `<arch>-<platform>-<mode>[-<option>]`

  Where `<arch>` may be any of:

  - `x86` (32-bit machines)
  - `x64` (64-bit machines)
  - `arm64` (ARM machines)

  Where `<platform>` may be any of:

  - `windows`
  - `osx`
  - `linux`

  Where `<mode>` may be any of:

  - `release`
  - `debug`

  Where `[-option]` may be unspecified, or any of:

  - `verbose`

  CMake, CTest, and CPack all respond appropriately to the various preset combinations available. The entire set of actions, demonstrated with the example preset as before, is as follows:

  CMake configure with a preset:

  ```sh
  $ cmake --preset x64-linux-release-verbose
  ```

  CMake re-configure with a preset:

  ```sh
  $ cmake --preset x64-linux-release-verbose --fresh
  ```

  CMake build with a prest:

  ```sh
  $ cmake --build ./build --preset x64-linux-release-verbose
  ```

  CTest test with a preset:

  ```sh
  $ ctest --test-dir ./build --preset x64-linux-release-verbose
  ```

  CMake package the build tree with a preset (calls CPack underneath):

  ```sh
  $ cmake --build ./build --preset x64-linux-release-verbose --target package
  ```

  CMake package the source tree with a preset (calls CPack underneath):

  ```sh
  $ cmake --build ./build --preset x64-linux-release-verbose --target package_source
  ```

  *NOTE:* Our presets all use Ninja as a generator to ensure cross-compatibility and reduce complexity.

  Not all platform and architecture combinations are currently supported; here is a summary of what we guarantee as of writing:

  ```txt
  // windows
  "x86-windows-debug"
  "x86-windows-release"
  "x86-windows-debug-verbose"
  "x86-windows-release-verbose"

  "x64-windows-debug"
  "x64-windows-release"
  "x64-windows-debug-verbose"
  "x64-windows-release-verbose"

  // osx
  "x86-osx-debug"
  "x86-osx-release"
  "x86-osx-debug-verbose"
  "x86-osx-release-verbose"

  "x64-osx-debug"
  "x64-osx-release"
  "x64-osx-debug-verbose"
  "x64-osx-release-verbose"

  "arm64-osx-debug"
  "arm64-osx-release"
  "arm64-osx-debug-verbose"
  "arm64-osx-release-verbose"

  // Linux
  "x86-linux-debug"
  "x86-linux-release"
  "x86-linux-debug-verbose"
  "x86-linux-release-verbose"

  "x64-linux-debug"
  "x64-linux-release"
  "x64-linux-debug-verbose"
  "x64-linux-release-verbose"
  ```

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

  The below support matrix aims to provide an accurate overview of all possible presets; please note, however, that support may vary in some cases, since we don't quite have the CI pipeline capacity to run full integration tests for all extensive cases.

  To this end, we very much appreciate field reports and user-feedback, and will aim to support all cases where sufficient resources are available to do so.

  Please note that this table denotes the platforms and architectures we currently test - and in some cases, deploy - against; it does *not* attempt to reflect the current status of any branch or CI run, only that we actively support the platform (or not).

  - ### Support Matrix:

    |         | Toolchain                        | x86 | x64 | arm64 |
    | :-      |                                  | :-: | :-: |  :-:  |
    | Linux   | GNU                              |     |  ✔️  |       |
    | Linux   | Clang                            |     |  ✔️  |       |
    | Apple   | GNU                              |  ✔️  |  ✔️  |   ✔️   |
    | Apple   | Clang                            |  ✔️  |  ✔️  |   ✔️   |
    | Windows | MSVC                             |     |     |       |
    | Windows | Clang MinGW universal c runtime  |     |  ✔️  |       |
    | Windows | GNU MinGW universal c runtime    |  ✔️  |  ✔️  |       |
    | Windows | GNU MinGW msvc runtime           |  ✔️  |  ✔️  |       |

  If you have any experience with using StoneyDSP in the wild, we would love to hear any feedback you might have - success or fail -  that can help us ensure our support matrix looks a bit more ✔️ by continuously iterating on and deploying* improvements to our library, thanks to your valuable feedback!
