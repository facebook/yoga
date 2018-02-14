---
path: "docs/flex-wrap"
title: "Flex Wrap"
hasPlayground: true
initialPlayground: eyJ3aWR0aCI6NTAwLCJoZWlnaHQiOjUwMCwiY2hpbGRyZW4iOlt7fSx7fSx7fSx7fSx7fSx7fSx7fSx7fV19
---

## Flex Wrap

The `flexWrap` property is set on containers and controls what happens when
children overflow the size of the container along the main axis. By default
children are forced into a single line (which can shrink elements).

If wrapping is allowed items are wrapped into multiple lines along the main
axis if needed. `WRAP_REVERSE` behaves the same, but the order of the lines is
reversed.

<controls prop="flexWrap"></controls>

When wrapping lines [alignContent](align-content) can be used to specify how the
lines are placed in the container.
