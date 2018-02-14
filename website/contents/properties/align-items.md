---
path: "docs/align-items"
title: "Align Items / Self"
hasPlayground: true
---

## Align Items

Align items describes how to align children along the cross axis of their container.
Align items is very similar to [Justify Content](justify-content) but instead of
applying to the main axis, Align Items applies to the cross axis.

**STRETCH (DEFAULT)** Stretch children of a container to match the height of the container's cross axis.

**FLEX START** Align children of a container to the start of the container's cross axis.

**FLEX END** Align children of a container to the end of the container's cross axis.

**CENTER** Align children of a container in the center of the container's cross axis.

<controls prop="alignItems"></controls>

## Align Self

Align self has the same options and effect as Align Items but instead of
affecting the children within a container, you can apply this property to
a single child to change its alignment within its parent. `Align Self`
overrides any option set by the parent with `Align Items`.

<controls prop="alignSelf"></controls>
