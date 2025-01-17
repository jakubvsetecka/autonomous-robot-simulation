# ICP Project 2023/2024
**Authors**: Jakub Všetečka [(xvsete00)](mailto:xvsete00@vutbr.cz), Tomáš Hobza [(xhobza03)](xhobza03@vutbr.cz)

This project is a simulation and visualisation of an autonomous and controlled robot in a discrete linear environment with obstacles and collision detection. The autonomous robots are controlled by a simple algorithm that enables them to navigate through the environment and avoid obstacles and other robots. The project is implemented in C++ and uses the Qt framework for visualisation and controls of the controllable robots as well as controls of the environment. The state of the environment can be saved and loaded from a file.

## Project Structure

The project is structured as follows:

- `README.md` - This file.
- `build/` - Directory containing build files.
- `doc/` - Documentation of the project, including `documentation.pdf` with generated Doxygen documentation. (When generated)
- `doc/diagrams/` - UML diagrams of the project in PlantUML and SVG format.
- `src/` - Source code of the project.
- `headers/` - Header files of the project.
- `conceptual_draft.png/` - Conceptual draft of the project with class hierarchy and main event loop as UML diagrams.

## Makefile

The project contains a Makefile that can be used to build the project. The Makefile contains the following targets:

- `configure` - Configures the project for building using CMake.
- `build` - Builds the project.
- `run` - Builds and runs the project.
- `clean` - Cleans the project build files.
- `doxygen` - Generates Doxygen documentation.
- `puml` - Generates PlantUML diagrams.
- `clean-doc` - Cleans the documentation files generated by Doxygen.

## Functionality

The project can be split into two main parts: the simulation and the visualisation. The simulation part is responsible for the simulation of the environment, the robots, and the collision detection. The visualisation part is responsible for the visualisation of the environment, the robots, and the controls of the robots and the environment.

<video src="icp-projekt/raw/branch/main/doc/video/stress_testing.mp4" alt="doc/video/stress_testing.mp4" controls></video>

*Caption: Video example showcasing stress-testing our solution with over 900 active objects in the scene.*

### Simulation

The simulation part of the project is built on a few basic ideas. The environment, or the scene, is a Cartesian space. We set the „upper left“ corner as the origin point `[0;0]` so that all positions are positive values. This would have much effect on the stability of the program as the simulation is heavily done through vector arithmetics.

#### Obstacles

There are just two types of object in the scene - robots and obstacles. The difference between a robot an obstacle is the movement vector and methods that an obstacle doesn‘t have. Obstacles have just their position and proportions (size).

#### Robots

Robots, on the other hand, can move. To represent movement, each robot has a movement vector. Moving the robot is hence just adding the movement vector to it‘s position. Using vectors as a way to represent robot‘s velocity and angle of movement is also very beneficial for speeding up or slowing down the movement - this will come in later.

Rotating the robot is done using vector transformation. The robot‘s movement vector is simply rotated around it‘s origin point.

It is important to note that there are two ways we represent vector here: magnitude and angle, and x-axis-offset and y-axis-offset. We use both and rely on implemented Qt functionality that seemlessly converts between these representations. For example for rotating the robot, the magnitude and angle representation is obviously simpler to change, but when adding the movement vector to the robot‘s position, the offset-based representation makes more sense - hence why we use both on a case-by-case basis.

#### Collision detection

Described above is a summary how our simulation represents position and movement. With that expained the next step is detecting collisions.

Since robots have a circular shape, detecting collisions is pretty simple. The distance between their centres has to be greater of equal to the sum of their radii. If the distance is less, a collision is detected.

We use a predictive pattern with detecting collisions. The collision is not detected for the robot‘s current position but rather for the step it‘s about to make. This prevents error states that would occus for reasons like rounding errors and so on. 

Rounding errors are also prevented by adding a small margin „around“ each robot that get‘s added to it‘s radius when calculating a potential collision. This margin also allows us to reliably calculate a robot that would be in a collision and/or is in a collision - why this is important will come in shortly.

The system is pretty simple - before taking a step check if the step would result in a collision. Autonomous robot also have a collision lookahead in the direction the robot is moving in. We accomplished this simply by also checking for a potential collision if the robot‘s position way ahead in the distance of the lookahead, even though the robot isn‘t going to step to that distance, it will avoid moving in that direction when the lookahead signals it would be a collision. It‘s useful to thing of this system as having a cane that blind people use to check if there‘s an obstacle in front of them in some distance. Taking one step wouldn‘t necessairly mean a collision, but the lookahead warns you, so the autonomous robots won‘t move in that direction.

The collision detection is a pretty expensive calculation - to at least ease the performance, we‘ve added a few optimizations. To have a fully fledged collision detection system each two robot‘s would have to be checked together. We speed the detection up by only checking robots if they‘re in a reasonable distance - hence creating a hitbox around each robot that is a rough, but efficient estimate of potential collisions.

Checking for collisions with obsticles is different, but not more complicated. Instead of the distance between two centers, the closes point of the obstacle to the robot is calculated. The distance between this point and the center of the robot has to be greater of equal to the robot‘s radius or a collision is detected.

#### Working with time

As we‘ve described, the movement is done by adding a movement vector to the robot‘s position. This raises the question of how often this happens. It is obvious that the simulations runs in iterations as completely discrete movement is impossible on conventional computers. The rate of these iterations is crutial. The relative movement between two iterations will always be the same, but since a big part of this project is the visualization. It is important to take real-world time into account as well. 

A straight forward solution would be to set a reasonable „refresh rate“ (*the rate of iterations happening per a time unit*), but we decided to make the simulation completely independent. The movement should show up on screen relative to real-world time always the same regardless of the refresh rate. 

We acheived this by multiplying all the movement vectors (as well as rotation speed) by a time constant so that the longer the time between two iterations, the longer the movement step will be.

The collision detection system runs on the same refresh rate as the movement incerements. This will result in „worse“ detection as the collision detection system has to „predict“ more into the future. We could have disconnected these systems, but we decided to keep them together to allow for lower refresh rates that will like this have great performance gains.

Another constant was added along the time constant. Simulation speed is a constant that all movement vectors get multiplied with and allows the user to set the „simulation time speed“ independent of the real-world time.

<video src="icp-projekt/raw/branch/main/doc/video/fps_independency.mp4" alt="doc/video/fps_independency.mp4" controls></video>

*Caption: Showcase of time independecy in the visualization.*

#### Anticollision

When a robot is in a collision currently - so that it‘s current position is colliding, an anticollision system is in place to fix this problem. The robot get‘s moved slightly away from the collision point and will get over time slowly unstuck.

<video src="icp-projekt/raw/branch/main/doc/video/anticollision.mp4" alt="doc/video/anticollision.mp4" controls></video>

*Caption: Anticollision in action on two collided robots.*

### Visualization

The simulation is real-time visualized using the Qt framework. We used the Qt classes as parents of our own classes. That also allowed us to easily render the objects into the UI. The UI also has controls that allow a user to control the simulation, load or save simulations.

## Ensuring backwards compatibility

To prevent any issues with other Qt versions, we added a flag `MERLIN=1` to all Makefile targets that (when ran on Merlin) will use the Qt version 5.5.1. We regularly checked that our code, that we developed on versions newer than 5.5.1, also work on the legacy version outlined in the assignment details.

<video src="icp-projekt/raw/branch/main/doc/video/merlin_testing.mp4" alt="doc/video/merlin_testing.mp4" controls></video>

*Caption: Testing on Merling with Qt version 5.5.1*
