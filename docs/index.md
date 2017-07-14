---
layout: home
title: Yoga
id: home
---

<div class="gridBlock alternateColor">
  <h3>C</h3>
  <div class="blockElement twoByGridBlock imageAlignSide">
    <div class="blockContent layoutsample">
      <div class="yoga sample" style="background-color: white; width: 500px; height: 120px; padding: 20px; flex-direction:row;">
        <div class="yoga" style="background-color: #97dccf; width: 80px; margin-right: 20px;"></div>
        <div class="yoga" style="background-color: #303846; flex-grow: 1; height: 25px; align-self: center;"></div>
      </div>
    </div>
    <div class="blockContent">
<div markdown="1" style="width: 700px; max-width: 100%;">
```c
YGNodeRef root = YGNodeNew();
YGNodeStyleSetWidth(root, 500);
YGNodeStyleSetHeight(root, 120);
YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
YGNodeStyleSetPadding(root, YGEdgeAll, 20);

YGNodeRef image = YGNodeNew();
YGNodeStyleSetWidth(image, 80);
YGNodeStyleSetMargin(image, YGEdgeEnd, 20);

YGNodeRef text = YGNodeNew();
YGNodeStyleSetHeight(text, 25);
YGNodeStyleSetAlignSelf(text, YGAlignCenter);
YGNodeStyleSetFlexGrow(text, 1);

YGNodeInsertChild(root, image, 0);
YGNodeInsertChild(root, text, 1);
```
</div>
    </div>
  </div>
</div>

<div class="gridBlock">
  <h3>OBJ-C</h3>
  <div class="blockElement twoByGridBlock imageAlignSide">
    <div class="blockContent layoutsample">
      <div class="yoga sample" style="background-color: white; width: 500px; height: 300px; align-items: center; justify-content: center; padding: 20px;">
        <div class="yoga" style="background-color: #97dccf; width: 150px; height: 150px; margin-bottom: 20px;"></div>
        <div class="yoga" style="background-color: #303846; height: 25px; width: 100px;"></div>
      </div>
    </div>
    <div class="blockContent">
<div markdown="1" style="width: 700px; max-width: 100%;">
```objc
UIView *root = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 500, 300)];
[root configureLayoutWithBlock:^void(YGLayout *layout) {
  layout.isEnabled = YES;
  layout.alignItems = YGAlignCenter;
  layout.justifyContent = YGJustifyContentCenter;
  layout.padding = 20.0f;
}];

UIImageView *image = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 150, 150)];
[image configureLayoutWithBlock:^void(YGLayout *layout) {
  layout.isEnabled = YES;
  layout.marginBottom = 20.0f;
}];
[root addSubview:image];

UILabel *text = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 25, 100)];
[root addSubview:text];
```
</div>
    </div>
  </div>
</div>

<div class="gridBlock alternateColor">
  <h3>JAVA</h3>
  <div class="blockElement twoByGridBlock imageAlignSide">
    <div class="blockContent layoutsample">
      <div class="yoga sample" style="background-color: white; width: 500px; height: 300px; align-items: center; justify-content: center; padding: 20px;">
        <div class="yoga" style="background-color: #303846; height: 25px; width: 200px;"></div>
        <div class="yoga" style="background-color: #97dccf; width: 50px; height: 50px; position: absolute; right: 20px; top: 20px;"></div>
      </div>
    </div>
    <div class="blockContent">
<div markdown="1" style="width: 700px; max-width: 100%;">
```java
YogaNode root = new YogaNode();
root.setWidth(500);
root.setHeight(300);
root.setAlignItems(CENTER);
root.setJustifyContent(CENTER);
root.setPadding(ALL, 20);

YogaNode text = new YogaNode();
text.setWidth(200);
text.setHeight(25);

YogaNode image = new YogaNode();
image.setWidth(50);
image.setHeight(50);
image.setPositionType(ABSOLUTE);
image.setPosition(END, 20);
image.setPosition(TOP, 20);

root.addChildAt(text, 0);
root.addChildAt(image, 1);
```
</div>
    </div>
  </div>
</div>

<div class="gridBlock">
  <h3>C#</h3>
  <div class="blockElement twoByGridBlock imageAlignSide">
    <div class="blockContent layoutsample">
      <div class="yoga sample" style="background-color: white; width: 500px; height: 300px;">
        <div class="yoga" style="background-color: #97dccf; flex-grow: 1;"></div>
        <div class="yoga" style="background-color: #303846; margin: 20px; height: 25px; width: 300px;"></div>
      </div>
    </div>
    <div class="blockContent">
<div markdown="1" style="width: 700px; max-width: 100%;">
```csharp
YogaNode root = new YogaNode {
  Width = 500,
  Height = 300
};

YogaNode image = new YogaNode { 
  FlexGrow = 1 
};

YogaNode text = new YogaNode {
  Width = 300,
  Height = 25,
  Margin = 20
};

root.Insert(image, 0);
root.Insert(text, 1);
```
</div>
    </div>
  </div>
</div>

<div class="gridBlock alternateColor">
  <h3>Android</h3>
  <div class="blockElement twoByGridBlock imageAlignSide">
    <div class="blockContent layoutsample">
      <div class="yoga sample" style="background-color: white; width: 500px; height: 300px; justify-content: stretch; flex-direction: column;">
        <div class="yoga" style="background-color: #97dccf; flex: 1;"></div>
        <div class="yoga" style="background-color: white; padding: 20px; flex-direction: row; align-items: center;">
          <div class="yoga" style="background-color: #97dccf; height: 50px; width: 50px;"></div>
          <div class="yoga" style="background-color: #303846; height: 25px; flex: 1; margin-left: 20px;"></div>
        </div>
      </div>
    </div>
    <div class="blockContent">
<div markdown="1" style="width: 700px; max-width: 100%;">
```xml
<YogaLayout
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    yoga:yg_justifyContent="stretch">
  <ImageView
      android:layout_width="wrap_content"
      android:layout_height="wrap_content"
      yoga:yg_flex="1"/>
  <VirtualYogaLayout
      android:layout_width="wrap_content"
      android:layout_height="wrap_content"
      yoga:yg_paddingAll="20px"
      yoga:yg_flexDirection="row"
      yoga:yg_alignItems="center">
    <ImageView
        android:layout_width="50dp"
        android:layout_height="50dp"/>
    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        yoga:yg_flex="1"
        yoga:yg_marginStart="20px"/>
  </VirtualYogaLayout>
</YogaLayout>
```
</div>
    </div>
  </div>
</div>

