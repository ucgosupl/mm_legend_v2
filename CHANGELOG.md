Changelog
============
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]
------------------------

### Added

### Changed

### Fixed

### Deprecated

### Removed

## [0.5.0] - 2018-03-24
------------------------

### Added
- adc: add adc implementation.
- led: add led driver implementation.
- map: add module storing labirynth map.
- pcb: new PCB design.
- project: add incremental compilation to makefiles.
- scripts: add scripts for generating sensor lookup table from measurements.
- solver: add implementation of maze solver.
- vbat: add battery saving procedure.
- wall: add wall sensor task.
- wall: add conversion routine separate for every sensor.

### Changed
- pcb: move status led to the front.

### Fixed
- pcb: change wall sensor placement - Fixes issue #7.
- pcb: reroute paths to h-bridge around imu sensor - Fixes issue #6.
- pcb: fix motor connector wiring - Fixes issue #1.

### Deprecated

### Removed

## [0.4.0] - 2017-12-23
------------------------

### Added
- external: add matrix calculations library.
- position: implement position estimation based on EKF.
- position: implement gyro drift reduction.

### Changed

### Fixed
- imu: add timeout in startup procedure to eliminate junk readings.

### Deprecated

### Removed

## [0.3.0] - 2017-11-18
------------------------

### Added
- encoder: implement encoders driver.
- i2c: add i2c master driver.
- imu: add IMU task reading data from sensor.
- logger: implement logger task and integrate it with system printf.
- motor: implement PID controller for forward velocity.
- motor: implement PID controller for angular velocity.
- pcb: fix motor connectors and BT connector.
- uart: implement Tx functionality.

### Changed

### Fixed
- ci: Travis failing after gcc update - use fixed gcc version and precompiled binary.

### Deprecated

### Removed

## [0.2.0] - 2017-07-02
------------------------

### Added
- console: added ability to control motors manually using console.
- console: implement uart console task.
- hbridge: TB6612 H-Bridge driver implementation.
- src: added skeleton interfaces for code components.
- uart: implement Rx functionality.

### Changed

### Fixed
- src: fixed wrong bus frequency definitions.

### Deprecated

### Removed

## [0.1.1] - 2017-04-22
------------------------

### Added

### Changed

### Fixed
- ci: remove Travis-CI dependency on fixed gcc version.

### Deprecated

### Removed

## 0.1.0 - 2017-04-22
------------------------

### Added
- ci: initial Travis-CI configuration.
- pcb: designed electric circuit.
- pcb: designed PCB.
- src: initial project setup.
- unit_test: configured CppUTest.

### Changed

### Fixed

### Deprecated

### Removed


[Unreleased]: https://github.com/ucgosupl/mm_legend_v2/compare/v0.5.0...dev
[0.1.1]: https://github.com/ucgosupl/mm_legend_v2/compare/v0.1.0...v0.1.1
[0.2.0]: https://github.com/ucgosupl/mm_legend_v2/compare/v0.1.1...0.2.0
[0.3.0]: https://github.com/ucgosupl/mm_legend_v2/compare/0.2.0...v0.3.0
[0.4.0]: https://github.com/ucgosupl/mm_legend_v2/compare/0.3.0...v0.4.0
[0.5.0]: https://github.com/ucgosupl/mm_legend_v2/compare/0.4.0...v0.5.0
