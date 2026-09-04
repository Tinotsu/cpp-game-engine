# Game Engine, with The Cherno tutorials

## Design

- Entry point, what control, what happens
- Application layer, life cycle and events
- Window layer, desktop platform
  - Input
  - Events
- Renderer, graphics
- Render API abstraction
- Debugging support
- Scripting, python
- Memory System, performance
- Entity-component System (ECS), Create game object, include system
- Physics
- File i/o, VFS
- Build System

### Event System

The Application (which make the loop that make everything running) create the
Window and dispatch event to the layer. The Application need to receives events.
The Window class represents the Window and whenever we receive events in the
Window we need to send the events to the Application class but we do not want
the Window to be linked to the Application. We need an Event class that contains
all the details about the events that occurs like mouse click (x and y coordinate,
button clicked) and be able to send all that data to the Application, and for that
we make the Application provide a callback to the Window so it can calls a function
OnEvent(Event struct) from the window.
