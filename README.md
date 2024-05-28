# Verlet Integration Particle Simulation

This project implements a particle simulation using Verlet Integration, a numerical method commonly used in physics simulations. The simulation models particles' behavior based on their position, velocity, and acceleration, providing a realistic and stable simulation environment.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Features

- Particle simulation using Verlet Integration.
- Realistic physics-based movement and collision handling.
- Customizable parameters for controlling simulation behavior.
- Graphics rendering and window management using SFML.
- Easy-to-use interface for integrating into other projects or simulations.

## Getting Started

### Prerequisites

- C++ Compiler
- [SFML](https://www.sfml-dev.org/) (for graphics rendering)

1. Clone the repository:

    ```bash
    git clone https://github.com/your_username/verlet-particle-simulation.git
    ```

2. Install SFML according to [SFML Installation Guide](https://www.sfml-dev.org/tutorials/2.5/start-linux.php).

## Usage

To use the Verlet Integration Particle Simulation in your project, you can simply run the project and use the hotkeys to interact with it:

 - A: switches between add mode or automatic mode, in add mode you're free to add some particles so the scene
 - R: removes all the particles from the screen
 - Left click: Places a particle where it is indicated
 - Mouse Wheel: Changes the size of the particle, the bigger the size the bigger the mass
 - I: Invert the gravity
 - Exit: Closes the simulation

## Examples

![Capture d'écran 2024-05-28 172050](https://github.com/bastienyoussfi/PhysicsEngine/assets/119053006/83a9f951-cf68-40fa-9fa1-d3ffd38c3431)

## Contributing

Contributions are welcome! If you have any suggestions, bug reports, or feature requests, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
