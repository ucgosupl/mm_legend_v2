Changelog
============
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]
------------------------

### Added
- led: add led driver implementation.
- adc: add adc implementation.
- vbat: add battery saving procedure.
- wall: add wall sensor routine converting adc values to millimeters.
- project: add incremental compilation to makefiles.
- pcb: new PCB design.

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
- uart: implement Tx functionality.
- logger: implement logger task and integrate it with system printf.
- encoder: implement encoders driver.
- motor: implement PID controller for forward velocity.
- i2c: add i2c master driver.
- imu: add IMU task reading data from sensor.
- pcb: fix motor connectors and BT connector.
- motor: implement PID controller for angular velocity.

### Changed

### Fixed
- ci: Travis failing after gcc update - use fixed gcc version and precompiled binary.

### Deprecated

### Removed

## [0.2.0] - 2017-07-02
------------------------

### Added
- src: added skeleton interfaces for code components.
- hbridge: TB6612 H-Bridge driver implementation.
- uart: implement Rx functionality.
- console: implement uart console task.
- console: added ability to control motors manually using console.

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
- pcb: designed electric circuit.
- pcb: designed PCB.
- src: initial project setup.
- unit_test: configured CppUTest.
- ci: initial Travis-CI configuration.

### Changed

### Fixed

### Deprecated

### Removed


[Unreleased]: https://github.com/ucgosupl/mm_legend_v2/compare/v0.3.0...dev
[0.1.1]: https://github.com/ucgosupl/mm_legend_v2/compare/v0.1.0...v0.1.1
[0.2.0]: https://github.com/ucgosupl/mm_legend_v2/compare/v0.1.1...0.2.0
[0.3.0]: https://github.com/ucgosupl/mm_legend_v2/compare/0.2.0...v0.3.0
[0.4.0]: https://github.com/ucgosupl/mm_legend_v2/compare/0.3.0...v0.4.0