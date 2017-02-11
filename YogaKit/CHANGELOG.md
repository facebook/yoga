# CHANGELOG

The changelog for `YogaKit`.

1.2.0 (**upcoming release**)
-----

### Breaking Changes

- `applyLayout()` has now been changed to `applyLayout(preservingOrigin:)`.

- Computed properties are no longer reflected in getter's of the affected properties.
```swift
// OLD
view.yoga.margin = 10
view.yoga.marginTop  // 10
view.yoga.marginLeft // 10

// NEW
view.yoga.margin = 10
view.yoga.marginTop // 0
view.yoga.marginLeft // 0
```
