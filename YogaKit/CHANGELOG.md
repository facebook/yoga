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

### Enhancements

- Pixel Rounding now uses `roundf()` instead of `round()`.

- There is now a method that allows "bulk" updates to YGLayout.
```objc
[view configureLayoutWithBlock:^(YGLayout *layout) {
  layout.isEnabled = YES;
  layout.width = 50;
  layout.height = 50;
}];
```

```swift
view.configureLayout { (layout) in
  layout.isEnabled = true
  layout.width = 50
  layout.height = 50
}
```
