# ECS-template
A simple ECS template to fork.

Using SFML for rendering and input handling.

## To know
When compiling, it will download the SFML on its own.


The coordinator is the main class that will handle the ECS. It will create the entities, components and systems.
There is 4 managers:
- The Entity Manager
- The Component Manager
- The System Manager
- The Network Manager


Some optimizations are made to make the ECS faster:
- When drawing, the system will optimize on its own the Y-axis system of rendering.
- When colliding, the boxes are stored in chunks.

Never destroy entities, kill them instead.

Tags are also useful. You can call:
- `getEntitiesFromTag("tag")` to get all the entities with the tag "tag"
- `getEntityFromTag("tag")` to get the first entity with the tag "tag"

When using network, `makePacket()` will be useful.
